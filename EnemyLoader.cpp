#include "Enemy.h"
#include "TextView.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::vector<Enemy> EnemyLoader(const std::string& filename, const std::vector<int>& idsToLoad) 
{
    std::vector<Enemy> enemies;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        TextView::showMessage("Failed to open file enemies.txt");
        return enemies;
    }

    std::string line;
    std::unordered_map<std::string, std::string> currentEnemyData;
    int currentId = -1;
    bool shouldLoadCurrent = false;

    while (std::getline(file, line))
    {
        // Пропускаем комментарии и пустые строки
        if (line.empty() || line.find("//") == 0) continue;

        if (line[0] == '[' && line.back() == ']')
        {
            // Если уже есть данные о предыдущем враге и он нужен, сохраняем их
            if (currentId != -1 && !currentEnemyData.empty() && shouldLoadCurrent)
            {
                try
                {
                    enemies.emplace_back(
                        std::to_string(currentId),
                        currentEnemyData["name"],
                        std::stoi(currentEnemyData["health"]),
                        std::stoi(currentEnemyData["attack"]),
                        std::stoi(currentEnemyData["experience"])
                    );
                }
                catch (const std::exception& e)
                {
                    TextView::showMessage(u8"Error by parsing enemy data");
                }
            }

            currentEnemyData.clear();

            // Получаем новый ID и проверяем, нужно ли его загружать
            try
            {
                currentId = std::stoi(line.substr(1, line.size() - 2));
                shouldLoadCurrent = std::find(idsToLoad.begin(), idsToLoad.end(), currentId) != idsToLoad.end();
            }
            catch (const std::exception& e)
            {
                TextView::showMessage(u8"Invalid ID format");
                currentId = -1;
                shouldLoadCurrent = false;
            }
        }
        else if (shouldLoadCurrent)
        {
            // Парсим параметры только если текущий враг нужен
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos)
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                currentEnemyData[key] = value;
            }
        }
    }

    // Добавляем последнего врага, если он нужен
    if (currentId != -1 && !currentEnemyData.empty() && shouldLoadCurrent)
    {
        try
        {
            enemies.emplace_back(
                std::to_string(currentId),
                currentEnemyData["name"],
                std::stoi(currentEnemyData["health"]),
                std::stoi(currentEnemyData["attack"]),
                std::stoi(currentEnemyData["experience"])
            );
        }
        catch (const std::exception& e)
        {
            TextView::showMessage(u8"Error by parsing enemy data");
        }
    }

    return enemies;
}