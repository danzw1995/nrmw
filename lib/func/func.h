#include <iostream>
#include <string>
class Config {
  public:
    Config (const std::string &k, const std::string &v);
    std::string key;
    std::string value;
};

std::string getName();

void ls();

void use(const std::string &key);




