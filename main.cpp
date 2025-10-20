#include "src/quiz.h"
#include <iostream>

int main() {
  Quiz quiz{};
  if (quiz.solve()) {
    quiz.prettyPrintStreet();
  } else {
    std::cout << "No Solution.\n";
  }
}
