#include "Level.hpp"
#include <LevelReader.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Attack/Attacks/ArcheryAttack.hpp"
#include "Attack/Attacks/CatapultAttack.hpp"
#include "Attack/Attacks/CrossbowAttack.hpp"
#include "Attack/Attacks/ElectroAttack.hpp"
#include "Attack/Attacks/OrbAttack.hpp"
#include "Attack/Attacks/SlingshotAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Tower/Towers/ArcheryTower.hpp"
#include "Tower/Towers/CatapultTower.hpp"
#include "Tower/Towers/CrossbowTower.hpp"
#include "Tower/Towers/ElectroTower.hpp"
#include "Tower/Towers/OrbTower.hpp"
#include "Tower/Towers/SlingshotTower.hpp"

class BuildableTileView;
Level::Level(int lives, int coins, std::shared_ptr<Map> map,
             std::shared_ptr<WaveManager> wave_mng,
             std::shared_ptr<AttackManager> attack_mng,
             std::shared_ptr<TowerManager> tower_mng,
             std::shared_ptr<EnemyManager> enemy_mng, int level_num)
    : lives{lives},
      coins{coins},
      map(map),
      wave_mng(wave_mng),
      attack_mng(attack_mng),
      enemy_mng(enemy_mng),
      tower_mng{tower_mng},
      state(ON),
      score(0),
      level_num(level_num) {
  init_default_callbacks();
}

void Level::decrease_lives(int amount) { lives -= amount; }

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

bool Level::is_paused() const { return state == PAUSED; }

bool Level::has_ended() const { return state == WON || state == LOST; }

Level::GameState Level::get_game_state() const { return state; }

void Level::run_iteration() {
  // Get the current time
  auto now = std::chrono::steady_clock::now();

  // Calculate the time elapsed since the last run
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_run_time)
          .count();

  // Return early if the elapsed time is less than the minimum frame time
  if (elapsed_ms < frame_time_ms) return;

  // Update the last run time
  last_run_time = now;

  // Iterate
  if (is_paused() || has_ended()) return;

  // Update
  wave_mng->set_current_enemies(enemy_mng->get_enemy_count());

  // Check Next Wave
  if (wave_mng->wave_over()) {
    wave_mng->next_wave();
  }

  if (wave_mng->should_spawn_enemy()) {
    auto enm = enemy_mng->generate_enemy(wave_mng->get_wave());
    on_enemy_created(enm);
    wave_mng->spawn_enemy();
    enemy_mng->regiseter_enemy(enm);
  }

  // Enemy Manager
  enemy_mng->process_enemies_states(
      [this](std::shared_ptr<BaseEnemy> enm) { on_enemy_death(enm); },
      [this](std::shared_ptr<BaseEnemy> enm) { on_enemy_out_of_bound(enm); });
  enemy_mng->move_enemies();

  // Attack manager
  attack_mng->filter_attacks(
      [this](std::shared_ptr<BaseAttack> enm) { on_attack_hit(enm); },
      [this](std::shared_ptr<BaseAttack> att) { on_attack_out_of_bound(att); });
  attack_mng->move_attacks();
}

std::shared_ptr<AttackManager> Level::get_attack_mng() const {
  return attack_mng;
}

std::shared_ptr<EnemyManager> Level::get_enemy_mng() const { return enemy_mng; }

std::shared_ptr<TowerManager> Level::get_tower_mng() const { return tower_mng; }

std::shared_ptr<WaveManager> Level::get_wave_mng() const { return wave_mng; }

int Level::get_level_count() {
  return LevelReader::get_instance().levels_count();
}

std::shared_ptr<Map> Level::get_map() const { return map; }

std::shared_ptr<BaseTower> Level::build_tower(
    BaseTower::TowerType type, std::shared_ptr<BuildableTile> tile) {
  std::shared_ptr<BaseTower> twr = nullptr;
  switch (type) {
    case BaseTower::ArcheryTower:
      twr = std::make_shared<ArcheryTower>(tile);
      break;
    case BaseTower::CatapultTower:
      twr = std::make_shared<CatapultTower>(tile);
      break;
    case BaseTower::ElectroTower:
      twr = std::make_shared<ElectroTower>(tile);
      break;
    case BaseTower::SlingshotTower:
      twr = std::make_shared<SlingshotTower>(tile);
      break;
    case BaseTower::OrbTower:
      twr = std::make_shared<OrbTower>(tile);
      break;
    case BaseTower::CrossbowTower:
      twr = std::make_shared<CrossbowTower>(tile);
      break;
    default:
      throw std::runtime_error("Load all towers");
  }

  if (twr->get_buy_price(type) <= get_coins()) {
    tower_mng->add_tower(twr);
    update_coins(-1 * twr->get_buy_price(type));
  } else {
    twr = nullptr;
  }

  return twr;
}

std::shared_ptr<BaseTower> Level::upgrade_tower(
    std::shared_ptr<BaseTower> twr) {
  if (twr->get_upgrade_price() <= get_coins() &&
      twr->get_level() < twr->get_upgrades_count()) {
    update_coins(-1 * twr->get_upgrade_price());
    tower_mng->upgrade_tower(twr);
  } else {
    twr = nullptr;
  }

  return twr;
}

void Level::sell_tower(std::shared_ptr<BaseTower> twr) {
  update_coins(1 * twr->get_sell_price());
  tower_mng->remove_tower(twr);
}

int Level::get_lives() const { return lives; }
int Level::get_score() const { return score; }
int Level::get_coins() const { return coins; }

int Level::get_level_num() const { return level_num; }
void Level::set_on_enemy_created(
    std::function<void(std::shared_ptr<BaseEnemy>)> handler) {
  on_enemy_created_callbacks.push_back(handler);
}

void Level::attack(std::shared_ptr<BaseTower> tower, float x, float y,
                   float width, float height, Vector<float> target) {
  std::shared_ptr<BaseAttack> attack;
  switch (tower->get_type()) {
    case BaseTower::ArcheryTower:
      attack = std::make_shared<ArcheryAttack>(tower->get_level(), x, y, width,
                                               height, target);
      break;
    case BaseTower::ElectroTower:
      attack = std::make_shared<ElectroAttack>(tower->get_level(), x, y, width,
                                               height, target);
      break;
    case BaseTower::SlingshotTower:
      attack = std::make_shared<SlingshotAttack>(tower->get_level(), x, y,
                                                 width, height, target);
      break;
    case BaseTower::CatapultTower:
      attack = std::make_shared<CatapultAttack>(tower->get_level(), x, y, width,
                                                height, target);
      break;
    case BaseTower::OrbTower:
      attack = std::make_shared<OrbAttack>(tower->get_level(), x, y, width,
                                           height, target);
      break;
    case BaseTower::CrossbowTower:
      attack = std::make_shared<CrossbowAttack>(tower->get_level(), x, y, width,
                                                height, target);
      break;
    default:
      throw std::runtime_error("Unidentified Tower Type");
  }
  attack_mng->register_attack(attack);
  on_attack_created(attack);
  tower->reset_shoot_time();
}

void Level::set_on_attack_created(
    std::function<void(std::shared_ptr<BaseAttack>)> handler) {
  on_attack_created_callbacks.push_back(handler);
}

void Level::set_on_attack_hit(
    std::function<void(std::shared_ptr<BaseAttack>)> handler) {
  on_attack_hit_callbacks.push_back(handler);
}
void Level::set_on_attack_out_of_bound(
    std::function<void(std::shared_ptr<BaseAttack>)> handler) {
  on_attack_out_of_bound_callbacks.push_back(handler);
}
void Level::set_on_enemy_death(
    std::function<void(std::shared_ptr<BaseEnemy>)> handler) {
  on_enemy_death_callbacks.push_back(handler);
}
void Level::set_on_enemy_out_of_bound(
    std::function<void(std::shared_ptr<BaseEnemy>)> handler) {
  on_enemy_out_of_bound_callbacks.push_back(handler);
}
void Level::on_enemy_created(std::shared_ptr<BaseEnemy> enm) {
  for (auto& fun : on_enemy_created_callbacks) fun(enm);
}
void Level::on_attack_created(std::shared_ptr<BaseAttack> v) {
  for (auto& fun : on_attack_created_callbacks) fun(v);
}
void Level::on_attack_hit(std::shared_ptr<BaseAttack> v) {
  for (auto& fun : on_attack_hit_callbacks) fun(v);
}
void Level::on_enemy_death(std::shared_ptr<BaseEnemy> v) {
  for (auto& fun : on_enemy_death_callbacks) fun(v);
}
void Level::on_enemy_out_of_bound(std::shared_ptr<BaseEnemy> v) {
  for (auto& fun : on_enemy_out_of_bound_callbacks) fun(v);
}
void Level::on_attack_out_of_bound(std::shared_ptr<BaseAttack> v) {
  for (auto& fun : on_attack_out_of_bound_callbacks) fun(v);
}

void Level::init_default_callbacks() {
  set_on_enemy_out_of_bound(
      [this](std::shared_ptr<BaseEnemy> enm) { decrease_lives(1); });
  set_on_enemy_death([this](std::shared_ptr<BaseEnemy> enm) {
    update_coins(enm->get_kill_coins());
  });
}
