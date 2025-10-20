#include <chrono>
#include <iostream>
#include <set>

#include "quiz.h"

Quiz::Quiz() {
  street_ = {};
  // Rule 11
  street_[0].nationality = Nationality::NORWAY;
  // Rule 12
  street_[1].color = Color::BLUE;
  //  Rule 15
  street_[2].drink = Drink::MILK;
}

bool Quiz::solve() {
  const auto start = std::chrono::system_clock::now();
  bool sucess = solve(0);
  const auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "Calculation time " << diff.count() << "s" << std::endl;
  return sucess;
}

bool Quiz::solve(int houseIdx) {
  if (houseIdx == 5)
    return checkNeighbourRules(street_);

  House &house = street_[houseIdx];

  // safe original to bracktrack
  House original = house;

  for (auto color : colors_) {
    if ((original.color != Color::NOTHING && color != original.color))
      continue;
    if (original.color == Color::NOTHING) {
      house.color = color;
    }

    for (auto nationality : nations_) {
      if (original.nationality != Nationality::NOTHING &&
          nationality != original.nationality)
        continue;
      if (original.nationality == Nationality::NOTHING) {
        house.nationality = nationality;
      }

      // Rule 5
      if (checkRule5(color, nationality))
        continue;

      for (auto drink : drinks_) {
        if (original.drink != Drink::NOTHING && drink != original.drink)
          continue;
        if (original.drink == Drink::NOTHING) {
          house.drink = drink;
        }

        // Rule 7, 9
        if (checkRule7(nationality, drink) || checkRule9(color, drink))
          continue;

        for (auto cigarette : cig_) {
          if (original.cigarette != Cigarette::NOTHING &&
              cigarette != original.cigarette)
            continue;
          if (original.cigarette == Cigarette::NOTHING) {
            house.cigarette = cigarette;
          }

          // Rule 8, 10, 13
          if (checkRule8(nationality, cigarette) ||
              checkRule10(cigarette, drink) || checkRule13(color, cigarette))
            continue;

          for (auto pet : pets_) {
            if (original.pet != Pet::NOTHING && pet != original.pet)
              continue;
            if (original.pet == Pet::NOTHING)
              house.pet = pet;

            // Rule 6, 14
            if (checkRule6(nationality, pet) || checkRule14(cigarette, pet))
              continue;

            if (!checkAllUniques(street_))
              continue;
            if (!checkNeighbourRules(street_))
              continue;

            if (solve(houseIdx + 1))
              return true;
          }
        }
      }
    }
  }

  // Backtrack: reset house to original
  house = original;
  return false;
}

void Quiz::printSolution() {
  int i = 1;
  for (auto &h : street_) {
    std::cout << "Haus " << i++ << ":\n";
    std::cout << "  Farbe: " << (int)h.color
              << "  Nation: " << (int)h.nationality
              << "  Drink: " << (int)h.drink
              << "  Cigarette: " << (int)h.cigarette << "  Pet: " << (int)h.pet
              << "\n";
  }
  std::cout << std::endl;
}

bool Quiz::checkAllUniques(Street &street) {
  for (int i = 0; i < 5; ++i) {
    std::set<int> seen;

    for (const auto &h : street) {
      int values[5] = {static_cast<int>(h.color), static_cast<int>(h.drink),
                       static_cast<int>(h.nationality),
                       static_cast<int>(h.cigarette), static_cast<int>(h.pet)};

      if (values[i] != -1) {
        if (!seen.insert(values[i]).second)
          return false; // Duplicate
      }
    }
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

  // Rule 17–19: (Marlboro / Wasser / Pferd)
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