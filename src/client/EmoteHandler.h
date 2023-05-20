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
  static const std::map<EmoteType, std::string> _images; /// Mapping emotes to their visuals
  static const std::map<EmoteType, std::string> _sounds; ///< Mapping emotes to their sound effects. unused atm
};

#endif // EMOTEHANDLER_H