//
// Created by nico on 10.05.23.
//

#ifndef BATTLESHIP_AUDIOPLAYER_H
#define BATTLESHIP_AUDIOPLAYER_H

#include "EmoteHandler.h"
#include "wx/sound.h"
#include <map>
#include <string>
#include <wx/wx.h>

class AudioPlayer {
public:
  /*!
   * Collection of general sound effect clips
   */
  enum Clip {
    ButtonClick,
    SelectShip,
    PlaceShip,
    Cannon,
    Hit,
    Miss,
    GameOver,
    PopUp
  };

  /*!
   * Play the selected audio clip
   * @param clip
   */
  static void play(const Clip &clip);

  /*!
   * Play a general audio file in .wav format.
   * Use this to play the sound of emotes:
   * AudioPlayer::play(EmoteHandler::getSound(emote));
   * @param file full path to the .wav-file (Has to be specific WAV format! Default output of Audacity works)"
   */
  static void play(const std::string &file);

private:
  static const std::map<Clip, std::string> _clips; ///< maps sound clip enums to the respective audio filepath
};

#endif // BATTLESHIP_AUDIOPLAYER_H
