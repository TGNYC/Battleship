//
// Created by nico on 10.05.23.
//

#include "AudioPlayer.h"
#include "Logger.h"
#include <wx/init.h>

const std::map<AudioPlayer::Clip, std::string> AudioPlayer::_clips = {
    {ButtonClick, "../assets/audio/Button.wav"},
    {GameOver, "../assets/audio/BestPirate.mp3"},
    {ShipHit, "../assets/audio/BestPirate.wav"},
    {ShipMiss, "../assets/audio/BestPirate.wav"},
    {BestPirate, "../assets/audio/BestPirate.wav"}
};

void AudioPlayer::play(const AudioPlayer::Clip& clip) {
  play(AudioPlayer::_clips.at(clip));
}

void AudioPlayer::play(const std::string& file) {
  /*LOG("trying to play a sound");
  LOG("filepath: " + file);
  wxChar** c;
  int a = 1;
  wxInitializer initializer(a, c);
  if (!initializer.IsOk()){
    LOG("init problem");
    return;
  }
  wxSound* sound;
  wxString filepath(file);
  bool success = sound->Create(filepath);
  LOG("created? " + std::to_string(success));

  LOG("created sound object");
  if (sound->IsOk()) {
    LOG("sound is ok");
    sound->Play(wxSOUND_ASYNC | wxSOUND_LOOP);
    LOG("played the sound");
  } else {
    LOG("Could not play audio file " + file);
  }
  //_mediaCtrl->Load(file);
  //_mediaCtrl->Play();*/
}
/*
void AudioPlayer::setMediaCtrl(wxMediaCtrl* mediaCtrl) {
  _mediaCtrl = mediaCtrl;
}*/