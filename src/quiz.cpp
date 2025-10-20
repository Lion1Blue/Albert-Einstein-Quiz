#include <chrono>
#include <iomanip>
#include <iostream>
#include <set>

#include "quiz.h"

Quiz::Quiz() {
  street_ = {};
  // Rule 11
  street_[0].nationality = Nationality::NORWAY;
  availableNations_.erase(Nationality::NORWAY);
  //  Rule 12
  street_[1].color = Color::BLUE;
  availableColors_.erase(Color::BLUE);
  //   Rule 15
  street_[2].drink = Drink::MILK;
  availableDrinks_.erase(Drink::MILK);
}

bool Quiz::solve() {
  const auto start = std::chrono::system_clock::now();
  bool sucess = solve(0);
  const auto end = std::chrono::system_clock::now();
  std::chrono::duration<double, std::ratio<1, 1000>> time_ms = end - start;
  std::cout << "Calculation time " << time_ms.count() << "ms" << std::endl;
  return sucess;
}

bool Quiz::solve(int houseIdx) {
  if (houseIdx == 5)
    return checkNeighbourRules(street_);

  House &house = street_[houseIdx];
  House original = house;

  auto colorsLeft = availableColors_;
  auto nationsLeft = availableNations_;
  auto drinksLeft = availableDrinks_;
  auto cigsLeft = availableCigs_;
  auto petsLeft = availablePets_;

  // Color
  auto colorsToTry = (original.color != Color::NOTHING)
                         ? std::set<Color>{original.color}
                         : colorsLeft;

  for (auto color : colorsToTry) {
    house.color = color;

    // Nation
    auto nationsToTry = (original.nationality != Nationality::NOTHING)
                            ? std::set<Nationality>{original.nationality}
                            : nationsLeft;

    for (auto nationality : nationsToTry) {
      house.nationality = nationality;

      if (checkRule5(color, nationality))
        continue;

      // Drinks
      auto drinksToTry = (original.drink != Drink::NOTHING)
                             ? std::set<Drink>{original.drink}
                             : drinksLeft;

      for (auto drink : drinksToTry) {
        house.drink = drink;

        if (checkRule7(nationality, drink) || checkRule9(color, drink))
          continue;

        // Cigs
        auto cigsToTry = (original.cigarette != Cigarette::NOTHING)
                             ? std::set<Cigarette>{original.cigarette}
                             : cigsLeft;

        for (auto cigarette : cigsToTry) {
          house.cigarette = cigarette;

          if (checkRule8(nationality, cigarette) ||
              checkRule10(cigarette, drink) || checkRule13(color, cigarette))
            continue;

          // Pets
          auto petsToTry = (original.pet != Pet::NOTHING)
                               ? std::set<Pet>{original.pet}
                               : petsLeft;

          for (auto pet : petsToTry) {
            house.pet = pet;

            if (checkRule6(nationality, pet) || checkRule14(cigarette, pet))
              continue;

            if (!checkNeighbourRules(street_))
              continue;

            // remove chosen values temporarily
            availableColors_.erase(color);
            availableNations_.erase(nationality);
            availableDrinks_.erase(drink);
            availableCigs_.erase(cigarette);
            availablePets_.erase(pet);

            if (solve(houseIdx + 1))
              return true;

            // add values back
            availableColors_.insert(color);
            availableNations_.insert(nationality);
            availableDrinks_.insert(drink);
            availableCigs_.insert(cigarette);
            availablePets_.insert(pet);
          }
        }
      }
    }
  }

  house = original;
  return false;
}

void Quiz::prettyPrintStreet() {
  std::cout << "\n====================== Solution =======================\n";
  std::cout << std::left << std::setw(6) << "Haus" << std::setw(10) << "Farbe"
            << std::setw(12) << "Nation" << std::setw(10) << "Drink"
            << std::setw(12) << "Cigarette" << std::setw(10) << "Tier"
            << "\n-------------------------------------------------------\n";

  int i = 1;
  for (auto &h : street_) {
    std::cout << std::left << std::setw(6) << i++ << std::setw(10)
              << enumToString(h.color) << std::setw(12)
              << enumToString(h.nationality) << std::setw(10)
              << enumToString(h.drink) << std::setw(12)
              << enumToString(h.cigarette) << std::setw(10)
              << enumToString(h.pet) << "\n";
  }
  std::cout << "=======================================================\n";
}

template <typename T, typename Member>
bool Quiz::checkUnique(Street &street, Member member, T nothingValue) {
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

bool Quiz::checkNeighbourRules(Street &street) {
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

  // Rule 17–19: (Marlboro / Water / Pferd)
  for (int i = 0; i < 5; ++i) {
    const auto &h = street[i];

    // Marlboro next to Cat
    if (h.cigarette == Cigarette::MARLBORO) {
      bool valid = false;
      if (i > 0 &&
          (street[i - 1].pet == Pet::NOTHING || street[i - 1].pet == Pet::CAT))
        valid = true;
      if (i < 4 &&
          (street[i + 1].pet == Pet::NOTHING || street[i + 1].pet == Pet::CAT))
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

bool Quiz::checkRule5(Color color, Nationality nationality) {
  return (nationality == Nationality::BRITAIN && color != Color::RED) ||
         (color == Color::RED && nationality != Nationality::BRITAIN);
}

bool Quiz::checkRule6(Nationality nationality, Pet pet) {
  return (nationality == Nationality::SWEDEN && pet != Pet::DOG) ||
         (pet == Pet::DOG && nationality != Nationality::SWEDEN);
}

bool Quiz::checkRule7(Nationality nationality, Drink drink) {
  return (nationality == Nationality::DENMARK && drink != Drink::TEA) ||
         (drink == Drink::TEA && nationality != Nationality::DENMARK);
}

bool Quiz::checkRule8(Nationality nationality, Cigarette cigarette) {
  return (nationality == Nationality::GERMAN &&
          cigarette != Cigarette::ROTHMANNS) ||
         (cigarette == Cigarette::ROTHMANNS &&
          nationality != Nationality::GERMAN);
}

bool Quiz::checkRule9(Color color, Drink drink) {
  return (color == Color::GREEN && drink != Drink::COFFEE) ||
         (drink == Drink::COFFEE && color != Color::GREEN);
}

bool Quiz::checkRule10(Cigarette cigarette, Drink drink) {
  return (cigarette == Cigarette::WINFIELD && drink != Drink::BEER) ||
         (drink == Drink::BEER && cigarette != Cigarette::WINFIELD);
}

bool Quiz::checkRule13(Color color, Cigarette cigarette) {
  return (color == Color::YELLOW && cigarette != Cigarette::DUNHILL) ||
         (cigarette == Cigarette::DUNHILL && color != Color::YELLOW);
}

bool Quiz::checkRule14(Cigarette cigarette, Pet pet) {
  return (cigarette == Cigarette::PALMAL && pet != Pet::BIRD) ||
         (pet == Pet::BIRD && cigarette != Cigarette::PALMAL);
}