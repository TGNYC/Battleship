#ifndef EMOTEHANDLER_H
#define EMOTEHANDLER_H

#include <string>
#include <map>

class EmoteHandler {
public:
  enum Emote {
    MiddleFinger,
    RussianWarshipGoFuckYourself,
    Mocking,
  };

  static std::string getImage(Emote emote);
  static std::string getSound(Emote emote);

private:
  static const std::map<Emote, std::string> images; ///< Mapping emotes to their visuals. For audio-only a clear png will be mapped
  static const std::map<Emote, std::string> sounds; ///< Mapping emotes to their sound effects. For visual-only an empty WAV will be mapped
};

#endif // EMOTEHANDLER_H