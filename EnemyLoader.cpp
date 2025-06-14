#include "Enemy.h"
#include "TextView.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::vector<Enemy> LoadAllEnemies(const std::string& filename) 
{
    std::vector<Enemy> enemies;
    std::ifstream file(filename);
    
    if (!file.is_open()) 
    {
        //std::cerr << "Failed to open file: " << filename << std::endl;
        return enemies;
    }

    std::string line;
    std::unordered_map<std::string, std::string> currentEnemyData;
    int currentId = -1;

    while (std::getline(file, line)) 
    {
        // ���������� ����������� � ������ ������
        if (line.empty() || line.find("//") == 0) continue;

        if (line[0] == '[' && line.back() == ']') 
        {
            // ���� ��� ���� ������ � ���������� �����, ��������� ��
            if (currentId != -1 && !currentEnemyData.empty()) 
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
                    //std::cerr << "Error parsing enemy data for ID " << currentId << ": " << e.what() << std::endl;
                }
                
                currentEnemyData.clear();
            }
            
            // �������� ����� ID
            try 
            {
                currentId = std::stoi(line.substr(1, line.size() - 2));
            }
            catch (const std::exception& e) 
            {
                //std::cerr << "Invalid enemy ID format: " << line << std::endl;
                currentId = -1;
            }
        }
        else 
        {
            // ������ ��������� ���� key=value
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) 
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                currentEnemyData[key] = value;
            }
        }
    }

    // ��������� ���������� �����
    if (currentId != -1 && !currentEnemyData.empty()) 
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
            //std::cerr << "Error parsing enemy data for ID " << currentId << ": " << e.what() << std::endl;
        }
    }

    return enemies;
}
