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

// TODO: Make Change Music & Continue Music
void MusicPlayer::play() {
  music.openFromFile(music_files[cur_type]);
  music.play();
  music.setLoop(true);
  music.setVolume(50);
}
void MusicPlayer::set_current_music(MusicType type) {
  assert(type != UNKNOWN);
  if (type != cur_type) {
    cur_type = type;
    if (is_playing()) play();
  }
}
void MusicPlayer::toggle() {
  if (is_playing())
    music.stop();
  else
    music.play();
}

bool MusicPlayer::is_playing() const {
  return music.getStatus() == sf::Music::Playing;
}
