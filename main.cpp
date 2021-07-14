#include <iostream>
#ifndef LOAD_L
#include "./lib/func/func.h"
#endif
using namespace std;

#ifdef LOAD_L
#include <windows.h>
typedef void(*ptrLs)();
typedef void(*ptrUse)(const char*);
#endif

int main(int argc, char** argv) {
  if (argc == 1) {
    return 0;
  }

  
  #ifdef LOAD_L
    HINSTANCE hdll;
    hdll = LoadLibrary("libdynfunc.dll");
    cout << "aasd" << endl;
    ptrLs ls;
    ptrUse use;
    if(hdll) {
      cout << "come in" << endl;
      ls = (ptrLs)GetProcAddress(hdll, "ls");
      use = (ptrUse)GetProcAddress(hdll, "use");
    }
  #endif

  char** temp = argv;
  string p = *(++temp);
  if (p == "ls") {
    if (ls != NULL) {
      ls();
    }
  } else if (p == "use") {
    const char* params = *++temp;
    if (use != NULL) {
      use(params);
    }
  }

  #ifdef LOAD_L
  FreeLibrary(hdll);
  #endif

  return 0;
}