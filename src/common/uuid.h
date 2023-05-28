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

  bool operator==(const uuid &) const = default;

private:
  std::array<std::uint8_t, 16> _octets = {}; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
};

template <>
struct std::hash<uuid> {
  std::size_t operator()(uuid const &id) const noexcept {
    return std::hash<std::string>{}(id.ToString());
  }
};

#endif // UUID_H