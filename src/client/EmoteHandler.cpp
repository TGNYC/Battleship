#include "EmoteHandler.h"

const std::string EmoteHandler::imagePath = "../assets/emotes/";
const std::string EmoteHandler::audioPath = "../assets/audio/";

const std::map<EmoteType, std::string> EmoteHandler::_images = {
    {EmoteType::MiddleFinger, "middlefinger.png"},
    {EmoteType::RussianWarshipGoFuckYourself, "gofuckyourself.png"},
    {EmoteType::Mocking, "mocking.png"},
    {EmoteType::BestPirate, "bestpirate.png"},
    {EmoteType::Panic, "panic.png"},
    {EmoteType::Clown, "clown.png"}};

const std::map<EmoteType, std::string> EmoteHandler::_sounds = {
    {EmoteType::MiddleFinger, "popup.wav"}, {EmoteType::RussianWarshipGoFuckYourself, "russianwarship.wav"},
    {EmoteType::Mocking, "popup.wav"},      {EmoteType::BestPirate, "bestpirate.wav"},
    {EmoteType::Panic, "popup.wav"},        {EmoteType::Clown, "honk.wav"}};

std::string EmoteHandler::getImage(EmoteType emote) {
  return imagePath + _images.at(emote);
}

std::string EmoteHandler::getImageLarge(EmoteType emote) {
  return imagePath + "large_" + _images.at(emote);
}

std::string EmoteHandler::getSound(EmoteType emote) {
  return audioPath + _sounds.at(emote);
}