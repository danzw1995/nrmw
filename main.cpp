#include <iostream>
#ifdef LOAD_L
#elif DL_OPEN
#include <dlfcn.h>
#else
// #ifndef LOAD_L
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
  #elif DL_OPEN
  void* handle = dlopen("libdynfunc.so", RTLD_LAZY);
  if (!handle) {
    cerr << "Cannot open library: " << dlerror() << '\n';
    return 1;
  }
  typedef void(*ptrLs)();
  typedef void(*ptrUse)(const char*);
  
  ptrLs ls = (ptrLs) dlsym(handle, "ls");
  ptrUse use = (ptrUse) dlsym(handle, "use");

  #else
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
  #elif DL_OPEN
  dlclose(handle);
  #endif

  return 0;
}