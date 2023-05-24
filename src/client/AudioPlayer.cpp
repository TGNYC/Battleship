//
// Created by nico on 10.05.23.
//

#include "AudioPlayer.h"
#include "Logger.h"
#include <wx/init.h>

const std::map<AudioPlayer::Clip, std::string> AudioPlayer::_clips = {
    {ButtonClick, "../assets/audio/Button.wav"},
    {GameOver, "../assets/audio/BestPirate.mp3"},
    {ShipHit, "../assets/audio/test.wav"},
    {ShipMiss, "../assets/audio/BestPirate.wav"},
    {BestPirate, "../assets/audio/BestPirate.wav"}
};

void AudioPlayer::play(const AudioPlayer::Clip& clip) {
  play(AudioPlayer::_clips.at(clip));
}

void AudioPlayer::play(const std::string& file) {
  LOG("trying to play a sound");
  LOG("filepath: " + file);
  wxSound sound(file);
  LOG("created sound object");
  if (sound.IsOk()) {
    LOG("sound is ok");
    sound.Play(wxSOUND_ASYNC | wxSOUND_LOOP);
    LOG("played the sound");
  } else {
    LOG("Could not play audio file " + file);
  }
}
