//
// Created by nico on 10.05.23.
//

#include "AudioPlayer.h"
#include "Logger.h"
#include <wx/init.h>

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
  /*std::cout << "Got here " << file << std::endl;
  //wxInitializer initializer();
  wxString filepath(file);
  wxSound sound(filepath);
  std::cout << "stuck";
  if (sound.IsOk()) {
    std::cout << "haha";
    sound.Play(wxSOUND_ASYNC);
    std::cout << "finished? " << sound.IsOk();
  } else {
    std::cout << "dafuq";
    Logger::log("Could not play audio file " + file, Logger::Type::Error);
    std::cout << "Could not play audio file" << file << std::endl;
  }
  std::cout << sound.IsPlaying(); */

  //_mediaCtrl->Load(file);
  //_mediaCtrl->Play();
}

/*void AudioPlayer::setMediaCtrl(wxMediaCtrl* mediaCtrl) {
  _mediaCtrl = mediaCtrl;
}*/