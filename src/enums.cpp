#include "enums.h"

template <> std::string enumToString(Color value) {
  switch (value) {
  case Color::RED:
    return "Red";
  case Color::GREEN:
    return "Green";
  case Color::BLUE:
    return "Blue";
  case Color::WHITE:
    return "White";
  case Color::YELLOW:
    return "Yellow";
  default:
    return "None";
  }
}

template <> std::string enumToString(Nationality value) {
  switch (value) {
  case Nationality::BRITAIN:
    return "Britain";
  case Nationality::SWEDEN:
    return "Sweden";
  case Nationality::DENMARK:
    return "Denmark";
  case Nationality::GERMAN:
    return "German";
  case Nationality::NORWAY:
    return "Norway";
  default:
    return "None";
  }
}

template <> std::string enumToString(Drink value) {
  switch (value) {
  case Drink::MILK:
    return "Milk";
  case Drink::TEA:
    return "Tea";
  case Drink::BEER:
    return "Beer";
  case Drink::COFFEE:
    return "Coffee";
  case Drink::WATER:
    return "Water";
  default:
    return "None";
  }
}

template <> std::string enumToString(Cigarette value) {
  switch (value) {
  case Cigarette::PALLMAL:
    return "Pallmal";
  case Cigarette::ROTHMANNS:
    return "Rothmanns";
  case Cigarette::MARLBORO:
    return "Marlboro";
  case Cigarette::DUNHILL:
    return "Dunhill";
  case Cigarette::WINFIELD:
    return "Windfield";
  default:
    return "None";
  }
}

template <> std::string enumToString(Pet value) {
  switch (value) {
  case Pet::DOG:
    return "Dog";
  case Pet::BIRD:
    return "Bird";
  case Pet::HORSE:
    return "Horse";
  case Pet::CAT:
    return "Cat";
  case Pet::FISH:
    return "Fish";
  default:
    return "None";
  }
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::ostream &>::type
operator<<(std::ostream &os, T value) {
  return os << enumToString(value);
}

std::ostream &operator<<(std::ostream &os, Color value) {
  return os << enumToString(value);
}

std::ostream &operator<<(std::ostream &os, Drink value) {
  return os << enumToString(value);
}

std::ostream &operator<<(std::ostream &os, Pet value) {
  return os << enumToString(value);
}

std::ostream &operator<<(std::ostream &os, Nationality value) {
  return os << enumToString(value);
}

std::ostream &operator<<(std::ostream &os, Cigarette value) {
  return os << enumToString(value);
}