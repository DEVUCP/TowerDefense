#include "Components/MusicPlayer.hpp"
#include <cassert>

std::unordered_map<MusicPlayer::MusicType, std::string>
    MusicPlayer::music_files = {
        {MAIN_MUSIC, "./assets/music/main_menu.mp3"},
        {LEVEL_MUSIC, "./assets/music/game_music.mp3"},
};

MusicPlayer::MusicPlayer() : cur_type(UNKNOWN) {}

MusicPlayer& MusicPlayer::get_instance() {
  static MusicPlayer m;
  return m;
}

void MusicPlayer::play(MusicPlayer::MusicType type) {
  assert(type != UNKNOWN);
  if (type == cur_type) return;
  music.openFromFile(music_files[MAIN_MUSIC]);
  music.play();
  music.setLoop(true);
}

void MusicPlayer::toggle() {
  if (is_playing()) {
    music.pause();
  } else {
    music.play();
  }
}

bool MusicPlayer::is_playing() const {
  return music.getStatus() == sf::Music::Playing;
}
