#include "LevelReader.hpp"

#include <Attack/AttackManager.hpp>
#include <Enemy/EnemyManager.hpp>
#include <Level.hpp>
#include <Map/BaseTile.hpp>
#include <Map/BuildableTile.hpp>
#include <Map/EnemyPathTile.hpp>
#include <Map/NonBuildableTile.hpp>
#include <Tower/TowerManager.hpp>
#include <WaveManager.hpp>
#include <cassert>
#include <filesystem>
#include <fstream>

/*
File Format:
Line 1: lives coins max_wave initial_enemy_count
Line 2: Ant_Tickets Ant_StartingWave
Line 3: Cockroach_Tickets Cockroach_StartingWave
Line 4: Beetle_Tickets Beetle_StartingWave
Line 5-22: "28 space-separated chatacters representing each tile type
B=Buildable, N=NonBuildable, E=Enemy" e.g. "N B N E E N N N N B ......"
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

  std::string path = get_level_path(level_num);
  assert(std::filesystem::exists(path));

  std::ifstream file(path);

  // Read the first 4 lines of data in the level's file
  file >> lives >> coins >> max_wave >> initial_enemy_count;
  file >> ant_tickets >> ant_starting_wave;
  file >> cockroach_tickets >> cockroach_starting_wave;
  file >> beetle_tickets >> beetle_starting_wave;

  // Then, read the Map data
  std::vector<std::vector<std::shared_ptr<BaseTile>>> grid;
  std::list<std::shared_ptr<EnemyPathTile>> enemy_path;

  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 28; j++) {
      char c;
      file >> c;

      std::shared_ptr<BaseTile> tile;

      if (c == 'B') {
        tile = std::make_shared<BuildableTile>();
      } else if (c == 'E') {
        tile = std::make_shared<EnemyPathTile>();
        enemy_path.push_back(std::static_pointer_cast<EnemyPathTile>(tile));
      } else {
        tile = std::make_shared<NonBuildableTile>();
      }

      grid[i].push_back(tile);
    }
  }

  // Create the Map
  auto map = std::make_shared<Map>(std::move(grid), std::move(enemy_path));

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

  std::string levels_directory = get_level_path(-1);

  for (auto& p : std::filesystem::directory_iterator(levels_directory)) {
    count++;
  }

  return count;
}

std::string LevelReader::get_level_path(int level_num = -1) {
  if (level_num == -1)
    return std::filesystem::current_path().string() + levels_path;

  return std::filesystem::current_path().string() + levels_path +
         std::to_string(level_num) + ".txt";
}
