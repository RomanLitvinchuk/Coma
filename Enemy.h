#ifndef ENEMY_H_
#define ENEMY_H_

#include <string>
#include <vector>
class Enemy {
 private:
  std::string id_;
  int health_;
  int attack_;
  int experience_;
  std::string name_;

 public:
  Enemy(std::string id, const std::string& name, int health, int attack,
        int experience);
  int GetAttack() const { return attack_; }
  int GetExperience() const { return experience_; }
  std::string GetName() const { return name_; }
  std::string GetID() const { return id_; }
  bool IsAlive() const { return health_ > 0; }
  void TakeDamage(int amount);
  int GetHealth() const { return health_; }
};

std::vector<Enemy> LoadAllEnemies(const std::string& filename);
std::vector<Enemy> EnemyFactory(const std::vector<Enemy>& all_enemies, const std::vector<std::string>& enemy_ids);
#endif  // ENEMY_H_
