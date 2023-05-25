#ifndef EMOTEHANDLER_H
#define EMOTEHANDLER_H

#include <string>
#include <map>
#include "network/responses/EmoteEvent.h"

/*!
 * Class to provide images and audio files for all available emotes
 */
class EmoteHandler {
public:
  static std::string getSound(EmoteType emote);
  static std::string getImage(EmoteType emote);
  static std::string getImageLarge(EmoteType emote);

private:
  static const std::map<EmoteType, std::string> _images; ///< Mapping emotes to their visuals
  static const std::map<EmoteType, std::string> _sounds; ///< Mapping emotes to their sound effects
  static const std::string imagePath; ///< image assets directory
  static const std::string audioPath; ///< audio assets directory
};

#endif // EMOTEHANDLER_H