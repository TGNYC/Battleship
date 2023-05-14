#include "EmoteHandler.h"

const std::map<EmoteType, std::string> EmoteHandler::images = {
    {EmoteType::MiddleFinger, "../assets/emotes/middlefinger.png"},
    {EmoteType::RussianWarshipGoFuckYourself, "../assets/emotes/gofuckyourself.png"},
    {EmoteType::Mocking, "../assets/emotes/mocking.png"}
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