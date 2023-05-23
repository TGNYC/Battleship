#include "EmoteHandler.h"

const std::map<EmoteType, std::string> EmoteHandler::_images = {
    {EmoteType::MiddleFinger, "../assets/emotes/middlefinger.png"},
    {EmoteType::RussianWarshipGoFuckYourself, "../assets/emotes/gofuckyourself.png"},
    {EmoteType::Mocking, "../assets/emotes/mocking.png"},
    {EmoteType::BestPirate, "../assets/emotes/bestpirate.png"}
};

const std::map<EmoteType, std::string> EmoteHandler::_sounds = {
    {EmoteType::MiddleFinger, ""},
    {EmoteType::RussianWarshipGoFuckYourself, ""},
    {EmoteType::Mocking, ""}
};

std::string EmoteHandler::getImage(EmoteType emote) {
  return _images.at(emote);
}

std::string EmoteHandler::getSound(EmoteType emote) {
  return _sounds.at(emote);
}