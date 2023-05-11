//
// Created by nico on 10.05.23.
//

#ifndef BATTLESHIP_AUDIOPLAYER_H
#define BATTLESHIP_AUDIOPLAYER_H

#define wxUSE_MEDIACTRL

#include "EmoteHandler.h"
#include "wx/sound.h"
#include <map>
#include <string>
#include <wx/mediactrl.h>
#include <wx/wx.h>

class AudioPlayer {
public:
  /*!
   * Available sound effects you are able to call with AudioPlayer::play(AudioPlayer::Clip::ButtonClick);
   */
  enum Clip {
    ButtonClick,
    GameOver,
    ShipHit,
    ShipMiss,
    BestPirate
  };

  /*!
   * Play the selected audio clip
   * @param clip
   */
  static void play(const Clip& clip);

  /*!
   * Play a general audio file in .wav format.
   * Use this to play the sound of emotes:
   * AudioPlayer::play(EmoteHandler::getAudio(EmoteHandler::Mocking));
   * @param file filepath .wav
   */
  static void play(const std::string& file);

  //static void setMediaCtrl(wxMediaCtrl* mediaCtrl);

private:
  static const std::map<Clip, std::string> clips;
  //static wxMediaCtrl* _mediaCtrl;
};

#endif // BATTLESHIP_AUDIOPLAYER_H
