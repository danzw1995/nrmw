#include <stdio.h>
#include <string.h>
#include "./lib/func/func.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    return 0;
  }

  const char* p = argv[1];
  const char* ls_str = "ls";
  const char* use_str = "use";
  if (strcmp(p, ls_str) == 0) {
    ls();
  } else if (strcmp(p, use_str) == 0) {
    char* params = argv[2];
    use(params);
  }
  return 0;
}