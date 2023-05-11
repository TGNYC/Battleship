#ifndef EMOTEHANDLER_H
#define EMOTEHANDLER_H

#include <string>
#include <map>
#include "network/responses/EmoteEvent.h"

class EmoteHandler {
public:
  static std::string getImage(EmoteType emote);
  static std::string getSound(EmoteType emote);

private:
  static const std::map<EmoteType, std::string> images; ///< Mapping emotes to their visuals. For audio-only a clear png will be mapped
  static const std::map<EmoteType, std::string> sounds; ///< Mapping emotes to their sound effects. For visual-only an empty WAV will be mapped
};

#endif // EMOTEHANDLER_H