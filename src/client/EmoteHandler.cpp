#include "EmoteHandler.h"

const std::map<EmoteType, std::string> EmoteHandler::images = {
    {EmoteType::MiddleFinger, "../assets/ship_1.png"},
    {EmoteType::RussianWarshipGoFuckYourself, "../assets/ship_2.png"},
    {EmoteType::Mocking, "../assets/ship_2.png"}
};

const std::map<EmoteType, std::string> EmoteHandler::sounds = {
    {EmoteType::MiddleFinger, ""},
    {EmoteType::RussianWarshipGoFuckYourself, ""},
    {EmoteType::Mocking, ""}
};

std::string EmoteHandler::getImage(EmoteType emote) {
  return images.at(emote);
}

std::string EmoteHandler::getSound(EmoteType emote) {
  return sounds.at(emote);
}