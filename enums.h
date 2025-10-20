#pragma once
#include <ostream>
#include <string>

enum class Color { NOTHING = -1, RED, GREEN, BLUE, WHITE, YELLOW };
enum class Drink { NOTHING = -1, WATER, BEER, COFFEE, TEA, MILK };
enum class Pet { NOTHING = -1, DOG, HORSE, CAT, BIRD, FISH };
enum class Nationality {
  NOTHING = -1,
  BRITAIN,
  SWEDEN,
  DENMARK,
  GERMAN,
  NORWAY
};
enum class Cigarette {
  NOTHING = -1,
  ROTHMANNS,
  PALMAL,
  DUNHILL,
  WINFIELD,
  MARLBORO
};

template <typename T> std::string enumToString(T value);
std::ostream &operator<<(std::ostream &os, Color value);
std::ostream &operator<<(std::ostream &os, Drink value);
std::ostream &operator<<(std::ostream &os, Pet value);
std::ostream &operator<<(std::ostream &os, Nationality value);
std::ostream &operator<<(std::ostream &os, Cigarette value);
