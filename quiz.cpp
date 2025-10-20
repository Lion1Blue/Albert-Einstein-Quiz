#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <set>
#include <unordered_set>

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

  std::unordered_set<Color> usedColors_;
  std::unordered_set<Nationality> usedNations_;
  std::unordered_set<Drink> usedDrinks_;
  std::unordered_set<Cigarette> usedCigs_;
  std::unordered_set<Pet> usedPets_;

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
    for (size_t i = 0; i < 4; ++i) {
      if (street[i].color == Color::GREEN) {
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

  bool checkAllRulesOptimized(Street &street) {
    // Rule 12: Norway next to blue House
    for (int i = 0; i < 5; ++i) {
      if (street[i].nationality == Nationality::NORWAY) {
        if (i > 0 && street[i - 1].color != Color::NOTHING &&
            street[i - 1].color != Color::BLUE)
          return false;
        if (i < 4 && street[i + 1].color != Color::NOTHING &&
            street[i + 1].color != Color::BLUE)
          return false;
      }
    }

    // Rule 16: green left to white
    for (int i = 0; i < 4; ++i) {
      if (street[i].color == Color::GREEN) {
        if (street[i + 1].color != Color::NOTHING &&
            street[i + 1].color != Color::WHITE)
          return false;
      }
    }

    // Rule 17–19: (Marlboro / Wasser / Pferd)
    for (int i = 0; i < 5; ++i) {
      const auto &h = street[i];

      // Marlboro next to Cat
      if (h.cigarette == Cigarette::MARLBORO) {
        bool valid = false;
        if (i > 0 && (street[i - 1].pet == Pet::NOTHING ||
                      street[i - 1].pet == Pet::CAT))
          valid = true;
        if (i < 4 && (street[i + 1].pet == Pet::NOTHING ||
                      street[i + 1].pet == Pet::CAT))
          valid = true;
        if (!valid)
          return false;
      }

      // Marlboro next to Water
      if (h.cigarette == Cigarette::MARLBORO) {
        bool valid = false;
        if (i > 0 && (street[i - 1].drink == Drink::NOTHING ||
                      street[i - 1].drink == Drink::WATER))
          valid = true;
        if (i < 4 && (street[i + 1].drink == Drink::NOTHING ||
                      street[i + 1].drink == Drink::WATER))
          valid = true;
        if (!valid)
          return false;
      }

      // Horse next to Dunhill
      if (h.pet == Pet::HORSE) {
        bool valid = false;
        if (i > 0 && (street[i - 1].cigarette == Cigarette::NOTHING ||
                      street[i - 1].cigarette == Cigarette::DUNHILL))
          valid = true;
        if (i < 4 && (street[i + 1].cigarette == Cigarette::NOTHING ||
                      street[i + 1].cigarette == Cigarette::DUNHILL))
          valid = true;
        if (!valid)
          return false;
      }
    }

    return true;
  }

public:
  Quiz() {
    street_ = {};
    // Rule 11
    street_[0].nationality = Nationality::NORWAY;
    usedNations_.insert(Nationality::NORWAY);
    // Rule 12
    street_[1].color = Color::BLUE;
    // usedColors_.insert(Color::BLUE);
    //  Rule 15
    street_[2].drink = Drink::MILK;
    usedDrinks_.insert(Drink::MILK);
  }

  bool solve() {
    const auto start = std::chrono::system_clock::now();
    bool sucess = solve(0);
    const auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Calculation time:" << diff.count() << std::endl;
    return sucess;
  }

  bool solve(int houseIdx) {
    if (houseIdx == 5)
      return checkAllRulesOptimized(street_);

    House &house = street_[houseIdx];

    // safe original to bracktrack
    House original = house;

    for (auto color : colors_) {
      if (usedColors_.count(color) ||
          (original.color != Color::NOTHING && color != original.color))
        continue;
      if (original.color == Color::NOTHING) {
        house.color = color;
        usedColors_.insert(color);
      }

      for (auto nationality : nations_) {
        if (/*usedNations_.count(nationality) ||*/
            original.nationality != Nationality::NOTHING &&
            nationality != original.nationality)
          continue;
        if (original.nationality == Nationality::NOTHING) {
          house.nationality = nationality;
          // usedNations_.insert(nationality);
        }

        // Rule 5
        if ((nationality == Nationality::BRITAIN && color != Color::RED) ||
            (color == Color::RED && nationality != Nationality::BRITAIN))
          continue;

        for (auto drink : drinks_) {
          if (/*usedDrinks_.count(drink) ||*/
              original.drink != Drink::NOTHING && drink != original.drink)
            continue;
          if (original.drink == Drink::NOTHING) {
            house.drink = drink;
            // usedDrinks_.insert(drink);
          }

          // Rule 7
          if ((nationality == Nationality::DENMARK && drink != Drink::TEA) ||
              (drink == Drink::TEA && nationality != Nationality::DENMARK))
            continue;
          // Rule 9
          if ((color == Color::GREEN && drink != Drink::COFFEE) ||
              (drink == Drink::COFFEE && color != Color::GREEN))
            continue;

          for (auto cigarette : cig_) {
            if (/*usedCigs_.count(cigarette) ||*/
                original.cigarette != Cigarette::NOTHING &&
                cigarette != original.cigarette)
              continue;
            if (original.cigarette == Cigarette::NOTHING) {
              house.cigarette = cigarette;
              // usedCigs_.insert(cigarette);
            }

            // Rule 8
            if ((nationality == Nationality::GERMAN &&
                 cigarette != Cigarette::ROTHMANNS) ||
                (cigarette == Cigarette::ROTHMANNS &&
                 nationality != Nationality::GERMAN))
              continue;
            // Rule 13
            if ((color == Color::YELLOW && cigarette != Cigarette::DUNHILL) ||
                (cigarette == Cigarette::DUNHILL && color != Color::YELLOW))
              continue;
            // Rule 10
            if ((cigarette == Cigarette::WINFIELD && drink != Drink::BEER) ||
                (drink == Drink::BEER && cigarette != Cigarette::WINFIELD))
              continue;

            for (auto pet : pets_) {
              if (original.pet != Pet::NOTHING && pet != original.pet)
                continue;
              if (original.pet == Pet::NOTHING)
                house.pet = pet;

              // Rule 6
              if ((nationality == Nationality::SWEDEN && pet != Pet::DOG) ||
                  (pet == Pet::DOG && nationality != Nationality::SWEDEN))
                continue;
              // Rule 14
              if ((cigarette == Cigarette::PALMAL && pet != Pet::BIRD) ||
                  (pet == Pet::BIRD && cigarette != Cigarette::PALMAL))
                continue;

              if (!checkAllUniques(street_))
                continue;
              if (!checkAllRulesOptimized(street_))
                continue;

              if (solve(houseIdx + 1))
                return true;
            }
            // usedCigs_.erase(cigarette);
          }
          // usedDrinks_.erase(drink);
        }
        // usedNations_.erase(nationality);
      }
      usedColors_.erase(color);
    }

    // Backtrack: reset house to original
    house = original;
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
