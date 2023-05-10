#include "EmoteHandler.h"

const std::map<EmoteHandler::Emote, std::string> EmoteHandler::images = {
    {MiddleFinger, "../assets/ship_1.png"},
    {RussianWarshipGoFuckYourself, "../assets/ship_2.png"},
    {Mocking, "../assets/ship_2.png"}
};

const std::map<EmoteHandler::Emote, std::string> EmoteHandler::sounds = {
    {MiddleFinger, ""},
    {RussianWarshipGoFuckYourself, ""},
    {Mocking, ""}
};

std::string EmoteHandler::getImage(EmoteHandler::Emote emote) {
  return images.at(emote);
}

std::string EmoteHandler::getSound(EmoteHandler::Emote emote) {
  return sounds.at(emote);
}