#include "uuid.h"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <ios>
#include <random>
#include <sstream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,hicpp-signed-bitwise)
uuid::uuid(const std::string &uuidString) {
  std::stringstream stream(uuidString);

  unsigned long input = 0;
  stream >> std::hex >> input;
  _octets[3] = input & 0xff;
  input       >>= 8;
  _octets[2] = input & 0xff;
  input       >>= 8;
  _octets[1] = input & 0xff;
  input       >>= 8;
  _octets[0] = input & 0xff;

  char character = 0;
  stream >> character;
  assert(character == '-');

  stream >> std::hex >> input;
  _octets[5] = input & 0xff;
  input       >>= 8;
  _octets[4] = input & 0xff;

  stream >> character;
  assert(character == '-');

  stream >> std::hex >> input;
  _octets[7] = input & 0xff;
  input       >>= 8;
  _octets[6] = input & 0xff;

  stream >> character;
  assert(character == '-');

  stream >> std::hex >> input;
  _octets[9] = input & 0xff;
  input       >>= 8;
  _octets[8] = input & 0xff;

  stream >> character;
  assert(character == '-');

  stream >> std::hex >> input;
  _octets[15] = input & 0xff;
  input        >>= 8;
  _octets[14] = input & 0xff;
  input        >>= 8;
  _octets[13] = input & 0xff;
  input        >>= 8;
  _octets[12] = input & 0xff;
  input        >>= 8;
  _octets[11] = input & 0xff;
  input        >>= 8;
  _octets[10] = input & 0xff;
}

auto uuid::generateRandomUuid() -> uuid {
  static std::random_device                           randomDevice;
  static std::mt19937                                 generator(randomDevice());
  static std::uniform_int_distribution<unsigned char> distribution;

  uuid result;
  std::generate(result._octets.begin(), result._octets.end(), []() {
    return distribution(generator);
  });

  result._octets[6] &= 0x0f;
  result._octets[6] |= 0x40;

  result._octets[8] &= 0b00111111;
  result._octets[8] |= 0b10000000;

  return result;
}

auto uuid::ToString() const -> std::string {
  std::stringstream stream;

  for (int index = 0; const auto octet : _octets) {
    stream << std::hex << std::setfill('0') << std::setw(2) << +octet;
    if (index == 3 || index == 5 || index == 7 || index == 9) {
      stream << '-';
    }
    ++index;
  }
  return stream.str();
}
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,hicpp-signed-bitwise)