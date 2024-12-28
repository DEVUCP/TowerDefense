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
#include <iostream>
#include <stdexcept>
#include "Enemy/BaseEnemy.hpp"
#include "GameSettings.hpp"

/*
File Format:
Line: lives coins max_wave initial_enemy_count
EnemyTypeCount Lines: enemy[i].tickets enemy[i].starting_wave
Enemy Path Beginning: row column
Remaining: "28 space-separated chatacters representing each tile type
B=Buildable, N=NonBuildable, U(p) D(own) R(ight) L(eft)=Enemy" e.g. "N B N R R R
D N N B ......"
*/

struct EnemyInfo {
  int tickets, starting_wave;
};

std::shared_ptr<Level> LevelReader::build_level(int level_num) {
  int lives;
  int coins;
  int max_wave;
  int initial_enemy_count;

  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();

  std::pair<unsigned, unsigned> enemy_path_begin;

  std::string path = get_level_path(level_num);
  assert(std::filesystem::exists(path));

  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    exit(1);
  }

  // Read the first 4 lines of data in the level's file
  file >> lives >> coins >> max_wave >> initial_enemy_count;

  // Read Enemies Info
  // EnemyType is zero-indexed enum, so we can access info with type directly
  std::vector<EnemyInfo> enemy_info(BaseEnemy::EnemyTypeCount);

  for (int i = 0; i < BaseEnemy::EnemyTypeCount; i++) {
    file >> enemy_info[i].tickets >> enemy_info[i].starting_wave;
  }
  std::vector<std::vector<std::shared_ptr<BaseTile>>> grid(
      row, std::vector<std::shared_ptr<BaseTile>>(col));
  std::list<std::shared_ptr<EnemyPathTile>> enemy_path;
  auto len = GameSettings::get_instance().get_tile_size();

  // Read enemy path begining (assuming rows & columns are zero-indexed)
  file >> enemy_path_begin.first >> enemy_path_begin.second;

  std::unordered_map<unsigned, char> enemy_path_positions;

  // Then, read the Map data
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      char c;
      if (!(file >> c)) {
        if (file.eof())
          throw std::runtime_error("Unexpected end of file while reading data");
        else
          throw std::runtime_error("Error reading from file");
      }

      std::shared_ptr<BaseTile> tile = nullptr;

      switch (c) {
        case 'B':
          tile = std::make_shared<BuildableTile>(static_cast<float>(j * len),
                                                 static_cast<float>(i * len));
          break;
        case 'L':
        case 'R':
        case 'U':
        case 'D':
          tile = std::make_shared<EnemyPathTile>(static_cast<float>(j * len),
                                                 static_cast<float>(i * len));

          enemy_path_positions.insert({i * col + j, c});
          break;
        case 'N':
          tile = std::make_shared<NonBuildableTile>(
              static_cast<float>(j * len), static_cast<float>(i * len));
          break;
        default:
          throw std::runtime_error("Invalid Format from file");
      };

      grid[i][j] = tile;
    }
  }

  // populate enemy_path with enemy tiles in the appropriate order
  unsigned current_row = enemy_path_begin.first;
  unsigned current_column = enemy_path_begin.second;

  while (enemy_path_positions.find(current_row * col + current_column) !=
         enemy_path_positions.end()) {
    enemy_path.push_back(std::static_pointer_cast<EnemyPathTile>(
        grid[current_row][current_column]));

    switch (enemy_path_positions[current_row * col + current_column]) {
      case 'U':
        current_row -= 1;
        break;
      case 'D':
        current_row += 1;
        break;
      case 'R':
        current_column += 1;
        break;
      case 'L':
        current_column -= 1;
        break;
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

  for (int i = 0; i < enemy_info.size(); i++) {
    auto& [tickets, starting_wave] = enemy_info[i];
    enemy_manager->assign_tickets(static_cast<BaseEnemy::EnemyType>(i),
                                  tickets);
    enemy_manager->set_starting_wave(static_cast<BaseEnemy::EnemyType>(i),
                                     starting_wave);
  }

  // Create AttackManager
  auto attack_manager = std::make_shared<AttackManager>();

  // Create TowerManager
  auto tower_manager = std::make_shared<TowerManager>();

  // Create a Level with the data read
  return std::make_shared<Level>(lives, coins, map, wave_manager,
                                 attack_manager, tower_manager, enemy_manager, level_num);
}

int LevelReader::levels_count() {
  int count = 0;

  std::string levels_directory = get_level_path(-1);

  for (auto& p : std::filesystem::directory_iterator(levels_directory)) count++;

  return count;
}

std::string LevelReader::get_level_path(int level_num = -1) {
  if (level_num == -1)
    return std::filesystem::current_path().string() + levels_path;

  return std::filesystem::current_path().string() + levels_path +
         std::to_string(level_num) + ".txt";
}

LevelReader& LevelReader::get_instance() {
  static LevelReader instance;
  return instance;
}
