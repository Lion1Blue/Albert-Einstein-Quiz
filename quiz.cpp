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

  bool checkRule12(const Street &street) {
    auto it = std::find_if(street.begin(), street.end(), [](const House &h) {
      return h.nationality == Nationality::NORWAY;
    });

    if (it == street.end())
      return true;

    int idx = std::distance(street.begin(), it);

    // Prüfe nur, wenn Nachbar gesetzt ist
    if (idx > 0) {
      if (street[idx - 1].color != Color::NOTHING &&
          street[idx - 1].color != Color::BLUE)
        return false;
    }
    if (idx < 4) {
      if (street[idx + 1].color != Color::NOTHING &&
          street[idx + 1].color != Color::BLUE)
        return false;
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

  bool checkRule15(const Street &street) {
    if (street[2].drink != Drink::NOTHING)
      return street[2].drink == Drink::MILK;
    return true;
  }

  bool checkRule16(const Street &street) {
    for (size_t i = 0; i < 4;
         ++i) { // nur bis Haus 4, da 5 kein "rechts"-Haus hat
      if (street[i].color == Color::GREEN) {
        // Nur prüfen, wenn das rechte Haus schon gesetzt ist
        if (street[i + 1].color != Color::NOTHING &&
            street[i + 1].color != Color::WHITE) {
          return false;
        }
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
    if (!checkRule5(street)) {
      // std::cout << "Regel 5 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule6(street)) {
      //  std::cout << "Regel 6 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule7(street)) {
      // std::cout << "Regel 7 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule8(street)) {
      // std::cout << "Regel 8 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule9(street)) {
      // std::cout << "Regel 9 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule10(street)) {
      // std::cout << "Regel 10 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule11(street)) {
      // std::cout << "Regel 11 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule12(street)) {
      // std::cout << "Regel 12 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule13(street)) {
      // std::cout << "Regel 13 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule14(street)) {
      // std::cout << "Regel 14 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule15(street)) {
      // std::cout << "Regel 15 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule16(street)) {
      // std::cout << "Regel 16 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule17(street)) {
      // std::cout << "Regel 17 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule18(street)) {
      // std::cout << "Regel 18 fehlgeschlagen!\n";
      return false;
    }
    if (!checkRule19(street)) {
      // std::cout << "Regel 19 fehlgeschlagen!\n";
      return false;
    }

    return true;
  }

public:
  Quiz() {
    street_ = {};
    street_[0].nationality = Nationality::NORWAY;
    street_[1].color = Color::BLUE;
    street_[2].drink = Drink::MILK;
  }

  bool solve(int houseIdx = 0) {
    if (houseIdx == 5) {
      return checkAllRules(street_);
    }

    for (auto color : colors_)
      for (auto nationality : nations_)
        for (auto drink : drinks_)
          for (auto cigarette : cig_)
            for (auto pet : pets_) {
              street_[houseIdx] = {color, drink, pet, nationality, cigarette};

              if (!checkAllUniques(street_))
                continue;

              if (!checkAllRules(street_))
                continue;

              if (solve(houseIdx + 1))
                return true;
            }

    street_[houseIdx] = {};
    return false;
  }

  void printSolution() {
    int i = 1;
    for (auto &h : street_) {
      std::cout << "Haus " << i++ << ":\n";
      std::cout << "  Farbe: " << (int)h.color
                << "  Nation: " << (int)h.nationality
                << "  Drink: " << (int)h.drink
                << "  Cigarette: " << (int)h.cigarette
                << "  Pet: " << (int)h.pet << "\n";
    }
    std::cout << std::endl;
  }
};
