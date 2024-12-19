#include "LevelReader.hpp"

#include <Attack/AttackManager.hpp>
#include <Enemy/EnemyManager.hpp>
#include <Level.hpp>
#include <Tower/TowerManager.hpp>
#include <WaveManager.hpp>
#include <filesystem>

/*
File Format:
Line 1: lives coins max_wave initial_enemy_count
Line 2: Ant_Tickets Ant_StartingWave
Line 3: Cockroach_Tickets Cockroach_StartingWave
Line 4: Beetle_Tickets Beetle_StartingWave
Line 5-22: "28 space-separated chatacters representing each tile type
B=Buildable, N=NonBuildable, E=Enemy" e.g. "N B N E E N N N N B ......"
#1#
*/
// TODO: Make enemy initialization dynamic

std::shared_ptr<Level> LevelReader::build_level(int level_num) {
  int lives;
  int coins;
  int max_wave;

  int initial_enemy_count;

  int ant_tickets, ant_starting_wave;
  int cockroach_tickets, cockroach_starting_wave;
  int beetle_tickets, beetle_starting_wave;

  // TODO: Read the data from the respective level file e.g. Level 1 -> "1.txt",
  // Level 2 -> "2.txt" First, read all the values initialized above

  // Then, read the Map data
  std::shared_ptr<Map> map;

  // Create WaveManager with the initial enemy count and the total number of
  // waves
  auto wave_manager =
      std::make_shared<WaveManager>(initial_enemy_count, max_wave);

  // Create Enemy Manager and populate it with the initial info for each type of
  // enemy
  auto enemy_manager = std::make_shared<EnemyManager>();

  enemy_manager->set_starting_wave(BaseEnemy::EnemyType::ANT,
                                   ant_starting_wave);
  enemy_manager->assign_tickets(BaseEnemy::EnemyType::ANT, ant_tickets);

  enemy_manager->set_starting_wave(BaseEnemy::EnemyType::COCKROACH,
                                   cockroach_starting_wave);
  enemy_manager->assign_tickets(BaseEnemy::EnemyType::COCKROACH,
                                cockroach_tickets);

  enemy_manager->set_starting_wave(BaseEnemy::EnemyType::BETTLE,
                                   beetle_starting_wave);
  enemy_manager->assign_tickets(BaseEnemy::EnemyType::BETTLE, beetle_tickets);

  // Create AttackManager
  auto attack_manager = std::make_shared<AttackManager>();

  // Create TowerManager
  auto tower_manager = std::make_shared<TowerManager>();

  // Create a Level with the data read
  auto level =
      std::make_shared<Level>(lives, coins, map, wave_manager, attack_manager,
                              tower_manager, enemy_manager);

  return level;
}

int LevelReader::levels_count() {
  int count = 0;

  // std::filesystem::path data_dir("");

  return count;
}
