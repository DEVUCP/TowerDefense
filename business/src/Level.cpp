#include "Level.hpp"

#include <LevelReader.hpp>

Level::Level(int lives,  int coins, std::shared_ptr<Map> map, std::shared_ptr<WaveManager> wave_mng, std::shared_ptr<AttackManager> attack_mng, std::shared_ptr<TowerManager> tower_mng, std::shared_ptr<EnemyManager> enemy_mng): lives{lives}, coins{coins}, map(map), wave_mng(wave_mng), attack_mng(attack_mng), enemy_mng(enemy_mng), tower_mng{tower_mng}, state(ON)
{ }

void Level::update_lives(int amount) {
  lives += amount;

  if (lives < 0) {
    end_game();
  }
}

void Level::increase_score(int amount) {
  score += (amount < 0 ? amount * -1 : amount);

  // TODO: Call the appropriate Game class method when it is implemented.
  // Game.add_xp(score);
}

bool Level::update_coins(int amount) {
  if (coins + amount < 0) return false;

  coins += amount;
  return true;
}


std::pair<bool, int> Level::end_game() {
  // TODO: Call the appropriate Game class methods when it is implemented.
  // Game.add_xp(score);
  // Game.save_xp();

  state = lives >= 0 ? WON : LOST;

  return {lives >= 0, score};
}

bool Level::is_paused() const {
  return state == PAUSED;
}

bool Level::has_ended() const {
  return state == WON || state == LOST;
}

Level::GameState Level::get_game_state() const {
  return state;
}

void Level::run_iteration() {
  if(is_paused() || has_ended()) return;
  if(wave_mng->wave_over()) {
    wave_mng->next_wave();
  }

  if(wave_mng->should_spawn_enemy()) {
    enemy_mng->generate_enemy();
  }

  enemy_mng->filter_enemies();
  enemy_mng->move_enemies();
  attack_mng->move_attacks();

  // TODO: Call the appropriate tower manager method when it is implemented.
  // tower_mng.check_ranges();
}

std::shared_ptr<AttackManager> Level::get_attack_mng() const {
  return attack_mng;
}

std::shared_ptr<EnemyManager> Level::get_enemy_mng() const {
  return enemy_mng;
}

std::shared_ptr<TowerManager> Level::get_tower_mng() const {
  return tower_mng;
}

std::shared_ptr<WaveManager> Level::get_wave_mng() const {
  return wave_mng;
}

Level& Level::read_level(int level_num) {
  return LevelReader::get_instance().build_level(level_num);
}

int Level::get_level_count() {
  return LevelReader::get_instance().levels_count();
}