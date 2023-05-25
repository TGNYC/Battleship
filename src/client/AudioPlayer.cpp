//
// Created by nico on 10.05.23.
//

#include "AudioPlayer.h"
#include "Logger.h"

const std::map<AudioPlayer::Clip, std::string> AudioPlayer::_clips = {
    {ButtonClick, "../assets/audio/button.wav"},
    {GameOver, "../assets/audio/popup.wav"},
    {Hit, "../assets/audio/woodbreak.wav"},
    {Miss, "../assets/audio/watersplash2.wav"},
    {PlaceShip, "../assets/audio/placeship.wav"},
    {Shoot, "../assets/audio/cannon1.wav"}
};

void AudioPlayer::play(const AudioPlayer::Clip& clip) {
  play(AudioPlayer::_clips.at(clip));
}

void AudioPlayer::play(const std::string& file) {
  LOG("trying to play a sound");
  wxSound sound(file);
  if (sound.IsOk()) {
    LOG("sound is ok");
    sound.Play(wxSOUND_ASYNC);
    LOG("played the sound");
  } else {
    LOG("Could not play audio file " + file);
  }
}
