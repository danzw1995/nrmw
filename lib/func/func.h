#include <iostream>
#include <string>
using namespace std;

class Config {
  public:
    Config(){}
    string key;
    string value;
};

string getName();

void ls();

void use(const string &key);




