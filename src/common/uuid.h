#ifndef UUID_H
#define UUID_H

#include <array>
#include <cstdint>
#include <string>

class uuid {
public:
  uuid() = default;

  explicit uuid(const std::string &uuid);

  static auto generateRandomUuid() -> uuid;

  [[nodiscard]] auto ToString() const -> std::string;

  auto operator<=>(const uuid &) const = default;

private:
  std::array<std::uint8_t, 16> m_octets = {};
};

#endif // UUID_H