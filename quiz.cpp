#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <set>

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

struct House {
  Color color = Color::NOTHING;
  Drink drink = Drink::NOTHING;
  Pet pet = Pet::NOTHING;
  Nationality nationality = Nationality::NOTHING;
  Cigarette cigarette = Cigarette::NOTHING;
};

using Street = std::array<House, 5>;

class Quiz {
  Street street_;
  // Alle möglichen Werte für jede Eigenschaft
  std::array<Color, 5> colors_ = {Color::RED, Color::GREEN, Color::WHITE,
                                  Color::YELLOW, Color::BLUE};
  std::array<Nationality, 5> nations_ = {
      Nationality::BRITAIN, Nationality::SWEDEN, Nationality::DENMARK,
      Nationality::GERMAN, Nationality::NORWAY};
  std::array<Drink, 5> drinks_ = {Drink::TEA, Drink::COFFEE, Drink::MILK,
                                  Drink::BEER, Drink::WATER};
  std::array<Cigarette, 5> cig_ = {Cigarette::PALMAL, Cigarette::DUNHILL,
                                   Cigarette::MARLBORO, Cigarette::WINFIELD,
                                   Cigarette::ROTHMANNS};
  std::array<Pet, 5> pets_ = {Pet::DOG, Pet::BIRD, Pet::CAT, Pet::HORSE,
                              Pet::FISH};

  bool checkAllUniques(Street &street) {
    return checkUnique(street, &House::color, Color::NOTHING) &&
           checkUnique(street, &House::drink, Drink::NOTHING) &&
           checkUnique(street, &House::nationality, Nationality::NOTHING) &&
           checkUnique(street, &House::cigarette, Cigarette::NOTHING) &&
           checkUnique(street, &House::pet, Pet::NOTHING);
  }

  template <typename T, typename Member>
  bool checkUnique(Street &street, Member member, T nothingValue) {
    std::set<T> values;
    for (auto &house : street) {
      T value = house.*member;
      if (value == nothingValue)
        continue;
      if (values.find(value) != values.end())
        return false;
      values.insert(value);
    }

    return true;
  }

  bool checkRule5(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](House &house) {
          return house.nationality == Nationality::BRITAIN;
        });

    if (it != street.end()) {
      if (it->color != Color::NOTHING && it->color != Color::RED)
        return false;
    }

    return true;
  }

  bool checkRule6(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.nationality == Nationality::SWEDEN;
        });

    if (it != street.end()) {
      if (it->pet != Pet::NOTHING && it->pet != Pet::DOG)
        return false;
    }

    return true;
  }

  bool checkRule7(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.nationality == Nationality::DENMARK;
        });

    if (it != street.end()) {
      if (it->drink != Drink::NOTHING && it->drink != Drink::TEA)
        return false;
    }

    return true;
  }

  bool checkRule8(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.nationality == Nationality::GERMAN;
        });

    if (it != street.end()) {
      if (it->cigarette != Cigarette::NOTHING &&
          it->cigarette != Cigarette::ROTHMANNS)
        return false;
    }

    return true;
  }

  bool checkRule9(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.color == Color::GREEN;
        });

    if (it != street.end()) {
      if (it->drink != Drink::NOTHING && it->drink != Drink::COFFEE)
        return false;
    }

    return true;
  }

  bool checkRule10(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.cigarette == Cigarette::WINFIELD;
        });

    if (it != street.end()) {
      if (it->drink != Drink::NOTHING && it->drink != Drink::BEER)
        return false;
    }

    return true;
  }

  bool checkRule11(Street &street) {
    if (street[0].nationality != Nationality::NOTHING) {
      return street[0].nationality == Nationality::NORWAY;
    }

    return true;
  }

  bool checkRule12(Street &street) {
    if (street[1].color != Color::NOTHING) {
      return street[0].color == Color::BLUE;
    }

    return true;
  }

  bool checkRule13(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.color == Color::YELLOW;
        });

    if (it != street.end()) {
      if (it->cigarette != Cigarette::NOTHING &&
          it->cigarette != Cigarette::DUNHILL)
        return false;
    }

    return true;
  }

  bool checkRule14(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.cigarette == Cigarette::PALMAL;
        });

    if (it != street.end()) {
      if (it->pet != Pet::NOTHING && it->pet != Pet::BIRD)
        return false;
    }

    return true;
  }

  bool checkRule15(Street &street) {
    if (street[2].drink != Drink::NOTHING) {
      return street[0].drink == Drink::MILK;
    }

    return true;
  }

  bool checkRule16(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.color == Color::GREEN;
        });
    const auto nextIt = std::next(it);
    if (it != street.end() && nextIt != street.end()) {
      if (nextIt->color != Color::NOTHING && nextIt->color != Color::WHITE) {
        return false;
      }
    }

    return true;
  }

  bool checkRule17(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.cigarette == Cigarette::MARLBORO;
        });

    if (it == street.end()) {
      return true;
    }
    const auto idx = std::distance(street.begin(), it);

    bool hasLeft = idx > 0;
    bool hasRight = idx < 4;

    if (hasLeft && street[idx - 1].pet == Pet::CAT)
      return true;
    if (hasRight && street[idx + 1].pet == Pet::CAT)
      return true;

    if ((hasLeft && street[idx - 1].pet == Pet::NOTHING) ||
        (hasRight && street[idx + 1].pet == Pet::NOTHING))
      return true;

    return false;
  }

  bool checkRule18(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.cigarette == Cigarette::MARLBORO;
        });

    if (it == street.end()) {
      return true;
    }
    const auto idx = std::distance(street.begin(), it);

    bool hasLeft = idx > 0;
    bool hasRight = idx < 4;

    if (hasLeft && street[idx - 1].drink == Drink::WATER)
      return true;
    if (hasRight && street[idx + 1].drink == Drink::WATER)
      return true;

    if ((hasLeft && street[idx - 1].drink == Drink::NOTHING) ||
        (hasRight && street[idx + 1].drink == Drink::NOTHING))
      return true;

    return false;
  }

  bool checkRule19(Street &street) {
    const auto it =
        std::find_if(street.begin(), street.end(), [](const House &house) {
          return house.pet == Pet::HORSE;
        });

    if (it == street.end()) {
      return true;
    }
    const auto idx = std::distance(street.begin(), it);

    bool hasLeft = idx > 0;
    bool hasRight = idx < 4;

    if (hasLeft && street[idx - 1].cigarette == Cigarette::DUNHILL)
      return true;
    if (hasRight && street[idx + 1].cigarette == Cigarette::DUNHILL)
      return true;

    if ((hasLeft && street[idx - 1].cigarette == Cigarette::NOTHING) ||
        (hasRight && street[idx + 1].cigarette == Cigarette::NOTHING))
      return true;

    return false;
  }

  bool checkAllRules(Street &street) {
    return checkRule5(street) && checkRule6(street) && checkRule7(street) &&
           checkRule8(street) && checkRule9(street) && checkRule10(street) &&
           checkRule11(street) && checkRule12(street) && checkRule13(street) &&
           checkRule14(street) && checkRule15(street) && checkRule16(street) &&
           checkRule17(street) && checkRule18(street) && checkRule19(street);
  }

public:
  bool solve(Street &street, int houseIdx = 0) {
    if (houseIdx == 5) {
      return checkAllRules(street);
    }

    for (auto color : colors_)
      for (auto nationality : nations_)
        for (auto drink : drinks_)
          for (auto cigarette : cig_)
            for (auto pet : pets_) {
              street[houseIdx] = {color, drink, pet, nationality, cigarette};

              if (!checkAllUniques(street))
                continue;

              if (!checkAllRules(street))
                continue;

              if (solve(street, houseIdx + 1))
                return true;
            }

    street[houseIdx] = {};
    return false;
  }

  void printSolution(const Street &street) {
    int i = 1;
    for (auto &h : street) {
      std::cout << "Haus " << i++ << ":\n";
      std::cout << "  Farbe: " << (int)h.color
                << "  Nation: " << (int)h.nationality
                << "  Drink: " << (int)h.drink
                << "  Cigarette: " << (int)h.cigarette
                << "  Pet: " << (int)h.pet << "\n";
    }
  }
};
