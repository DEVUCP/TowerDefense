#include "Level.hpp"
#include <LevelReader.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Tower/Towers/ArcheryTower.hpp"
#include "Tower/Towers/CatapultTower.hpp"
#include "Tower/Towers/ElectroTower.hpp"
#include "Tower/Towers/IonPrism.hpp"
#include "Tower/Towers/SlingshotTower.hpp"

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
      level_num(level_num) {}
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
  if (wave_mng->wave_over()) {
    wave_mng->next_wave();
  }

  if (wave_mng->should_spawn_enemy()) {
    auto enm = enemy_mng->generate_enemy(wave_mng->get_wave());
    on_enemy_created(enm);
    wave_mng->spawn_enemy();
    enemy_mng->regiseter_enemy(enm);
  }

  enemy_mng->filter_enemies();
  enemy_mng->move_enemies();
  // attack_mng->move_attacks();

  // TODO: Call the appropriate tower manager method when it is implemented.
  // tower_mng.check_ranges();
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
    case BaseTower::IonPrism:
      twr = std::make_shared<IonPrism>(tile);
      break;
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

int Level::get_lives() const { return lives; }
int Level::get_score() const { return score; }
int Level::get_coins() const { return coins; }

int Level::get_level_num() const { return level_num; }
void Level::set_on_enemy_created(
    std::function<void(std::shared_ptr<BaseEnemy>)> handler) {
  on_enemy_created = handler;
}
