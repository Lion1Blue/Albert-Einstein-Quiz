#pragma once
#include "enums.h"
#include <array>
#include <set>

struct House {
  Color color = Color::NOTHING;
  Drink drink = Drink::NOTHING;
  Pet pet = Pet::NOTHING;
  Nationality nationality = Nationality::NOTHING;
  Cigarette cigarette = Cigarette::NOTHING;
};

using Street = std::array<House, 5>;

class Quiz {

public:
  Quiz();
  void prettyPrintStreet();
  bool solve();

private:
  bool solve(int houseIdx);
  bool checkNeighbourRules(Street &street);
  bool checkRule5(Color color, Nationality nationality);
  bool checkRule6(Nationality nationality, Pet pet);
  bool checkRule7(Nationality nationality, Drink drink);
  bool checkRule8(Nationality nationality, Cigarette cigarette);
  bool checkRule9(Color color, Drink drink);
  bool checkRule10(Cigarette cigarette, Drink drink);
  bool checkRule13(Color color, Cigarette cigarette);
  bool checkRule14(Cigarette cigarette, Pet pet);
  template <typename T, typename Member>
  bool checkUnique(Street &street, Member member, T nothingValue);

private:
  Street street_;
  std::set<Color> availableColors_ = {Color::RED, Color::GREEN, Color::WHITE,
                                      Color::YELLOW, Color::BLUE};
  std::set<Nationality> availableNations_ = {
      Nationality::BRITAIN, Nationality::SWEDEN, Nationality::DENMARK,
      Nationality::GERMAN, Nationality::NORWAY};
  std::set<Drink> availableDrinks_ = {Drink::TEA, Drink::COFFEE, Drink::MILK,
                                      Drink::BEER, Drink::WATER};
  std::set<Cigarette> availableCigs_ = {
      Cigarette::PALMAL, Cigarette::DUNHILL, Cigarette::MARLBORO,
      Cigarette::WINFIELD, Cigarette::ROTHMANNS};
  std::set<Pet> availablePets_ = {Pet::DOG, Pet::BIRD, Pet::CAT, Pet::HORSE,
                                  Pet::FISH};
};