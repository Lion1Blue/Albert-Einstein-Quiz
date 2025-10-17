#include "quiz.cpp"
#include <iostream>

int main() {
  Street street{};
  Quiz quiz{};
  if (quiz.solve(street)) {
    std::cout << "Lösung gefunden!\n";
    quiz.printSolution(street);
  } else {
    std::cout << "Keine Lösung.\n";
  }
}
