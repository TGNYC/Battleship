//
// Created by nico on 10.05.23.
//

#include "AudioPlayer.h"
#include "Logger.h"

const std::map<AudioPlayer::Clip, std::string> AudioPlayer::clips = {
    {ButtonClick, "../assets/audio/BestPirate.wav"},
    {GameOver, "../assets/audio/BestPirate.wav"},
    {ShipHit, "../assets/audio/BestPirate.wav"},
    {ShipMiss, "../assets/audio/BestPirate.wav"},
    {BestPirate, "../assets/audio/BestPirate.wav"}
};

void AudioPlayer::play(const AudioPlayer::Clip& clip) {
  play(AudioPlayer::clips.at(clip));
}

void AudioPlayer::play(const std::string& file) {
  const wxSound sound(file, false);
  if (sound.IsOk()) {
    sound.Play(wxSOUND_ASYNC);
  } else {
    Logger::log("Could not play audio file " + file, Logger::Type::Error);
    std::cout << "Could not play audio file" << file << std::endl;
  }
}