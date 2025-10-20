#include "quiz.h"
#include <iostream>

int main() {
  Quiz quiz{};
  if (quiz.solve()) {
    std::cout << "Lösung gefunden!\n";
    quiz.printSolution();
  } else {
    std::cout << "Keine Lösung.\n";
  }
}
