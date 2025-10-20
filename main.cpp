#include "quiz.h"
#include <iostream>

int main() {
  Quiz quiz{};
  if (quiz.solve()) {
    quiz.prettyPrintStreet();
  } else {
    std::cout << "Keine Lösung.\n";
  }
}
