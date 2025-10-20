#pragma once
#include <array>

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

public:
  Quiz();
  void printSolution();
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
  bool checkAllUniques(Street &street);

private:
  Street street_;
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
};