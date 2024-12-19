#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class MusicPlayer {
public:
  enum MusicType { UNKNOWN = -1, MAIN_MUSIC = 0, LEVEL_MUSIC };

public:
  // remove copying
  MusicPlayer(const MusicPlayer&) = delete;
  MusicPlayer operator=(const MusicPlayer&) = delete;

  /*
   * @brief get instance
   */
  static MusicPlayer& get_instance();

  /*
   * @brief Play a game
   */
  void play(MusicType);

  /*
   * @brief toggle the state of the music
   */
  void toggle();

  /*
   * @brief Check if playing
   */
  bool is_playing() const;

private:
  MusicPlayer();

private:
  sf::Music music;
  MusicType cur_type;
  static std::unordered_map<MusicType, std::string> music_files;
};
