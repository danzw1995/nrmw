#include <iostream>

#include "./lib/func/func.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    return 0;
  }

  char** temp = argv;
  string p = *(++temp);
  if (p == "ls") {
    ls();
  } else if (p == "use") {
    use(*++temp);
  }

  return 0;
}