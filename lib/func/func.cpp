#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "func.h"

#define FILE_PATH ".nrmwrc"
class Config {
  public:
    Config (const std::string &k, const std::string &v);
    std::string key;
    std::string value;
};

std::string getName();

Config::Config(const std::string &k, const std::string &v) {
  key = k;
  value = v;
}

std::string getName() {
  std::string fullPath = "";
  #ifdef __linux__
  fullPath = std::string(getenv("HOME")) + "/" + FILE_PATH;
  #endif
  #ifdef WIN32
  fullPath = "C:" + std::string(getenv("homepath")) + "\\" + FILE_PATH;
  #endif
  std::cout << "fullPath =" << fullPath << std::endl;
  return fullPath;
}

void ls() {
  std::string s;
  std::string strLine;
  std::ifstream f(getName(), std::ios::in);
  if (!f.is_open()) {
    s = "npm";
  } else {
    while (!f.eof()) {
      getline(f, strLine);
      size_t p = strLine.find("=");
      std::string key = strLine.substr(0, p);
      if (key == "home") {
        std::string value = strLine.substr(p + 1);
        if (value == "https://www.npmjs.org") {
          s = "npm";
        } else if (value == "https://yarnpkg.com") {
          s = "yarn";
        } else if (value == "https://cnpmjs.org") {
          s = "cnpm";
        } else if (value == "https://npm.taobao.org") {
          s = "taobao";
        } else if (value == "https://www.nodejitsu.com") {
          s = "nj";
        } else if (value == "https://skimdb.npmjs.com/") {
          s = "skimdb";
        } else {
          s = "npm";
        }
        break;
      }
    }
    f.close();
  }
  std::cout << (s == "npm" ? "* " : "  ") << "npm -----  https://registry.npmjs.org/" << std::endl;
  std::cout << (s == "yarn" ? "* " : "  ") << "yarn ----- https://registry.yarnpkg.com" << std::endl;
  std::cout << (s == "cnpm" ? "* " : "  ") << "cnpm ----  http://r.cnpmjs.org/" << std::endl;
  std::cout << (s == "taobao" ? "* " : "  ") << "taobao --  https://registry.npm.taobao.org/" << std::endl;
  std::cout << (s == "nj" ? "* " : "  ") << "nj ------  https://registry.nodejitsu.com/" << std::endl;
  std::cout << (s == "skimdb" ? "* " : "  ") << "skimdb --  https://skimdb.npmjs.com/registry" << std::endl;
}


void use(const char* k) {
  std::string home;
  std::string registry;
  std::string key = std::string(k);
  if (key == "npm") {
    home = "https://www.npmjs.org";
    registry = "https://registry.npmjs.org/";
  } else if (key == "yarn") {
    home = "https://yarnpkg.com";
    registry = "https://registry.yarnpkg.com";
  } else if (key == "cnpm") {
    home = "https://cnpmjs.org";
    registry = "http://r.cnpmjs.org/";
  } else if (key == "taobao") {
    home = "https://npm.taobao.org";
    registry = "https://registry.npm.taobao.org/";
  } else if (key == "nj") {
    home = "https://www.nodejitsu.com";
    registry = "https://registry.nodejitsu.com/";
  } else if (key == "skimdb") {
    home = "https://skimdb.npmjs.com/";
    registry = "https://skimdb.npmjs.com/registry";
  } else {
    std::cout << " Not find registry: " << key << std::endl;
    return;
  }

  std::ifstream ifs;
  int size = 0;
  ifs.open(getName(), std::ios::in);

  if (!ifs.is_open()) {
    ifs.close();
    std::ofstream ofs;
    ofs.open(getName(), std::ios::out);
    ofs << "home=" << home << std::endl;
    ofs << "registry=" << registry << std::endl;
    ofs.close();
  } else {
    std::vector <Config> vc;
    vc.reserve(6);
    std::string str;

    while (!ifs.eof()) {
      std::getline(ifs, str);
      size_t p = str.find("=");
      if (p == -1) {
        continue;
      }
      std::string key = str.substr(0, p);
      std::string value;
      if (key == "home") {
        value = home;
      } else if (key == "registry") {
        value = registry;
      } else {
        value = str.substr(p + 1);
      }
      vc.emplace_back(key, value);
    }

    ifs.close();

    std::ofstream ofs;
    ofs.open(getName(), std::ios::out);
    size_t size = vc.size();
    for (size_t i = 0; i < size; i++) {
      ofs << vc[i].key << "=" << vc[i].value << std::endl;
    }
    ofs.close();
    std::cout << "Registry has been set to: " << home << std::endl;
  }
}
