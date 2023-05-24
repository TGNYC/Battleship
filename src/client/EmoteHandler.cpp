#include "EmoteHandler.h"

const std::map<EmoteType, std::string> EmoteHandler::_images = {
    {EmoteType::MiddleFinger, "../assets/emotes/middlefinger.png"},
    {EmoteType::RussianWarshipGoFuckYourself, "../assets/emotes/gofuckyourself.png"},
    {EmoteType::Mocking, "../assets/emotes/mocking.png"},
    {EmoteType::BestPirate, "../assets/emotes/bestpirate.png"},
    {EmoteType::Panic, "../assets/emotes/panic.png"}  
};

const std::map<EmoteType, std::string> EmoteHandler::_sounds = {
    {EmoteType::MiddleFinger, ""},
    {EmoteType::RussianWarshipGoFuckYourself, ""},
    {EmoteType::Mocking, ""},
    {EmoteType::BestPirate, "../assets/audio/BestPirate.wav"},
    {EmoteType::Panic, ""}
};

std::string EmoteHandler::getImage(EmoteType emote) {
  return _images.at(emote);
}

std::string EmoteHandler::getSound(EmoteType emote) {
  return _sounds.at(emote);
}