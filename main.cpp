#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define FILE_PATH ".nrmwrc"

class Config {
public:
  Config (string k, string v) {
    key = k;
    value = v;
  }
  string key;
  string value;
};

string getName() {
  string home_path = getenv("homepath");
  return "C:" + home_path + "\\" + FILE_PATH;
}

void ls() {
  string s;
  string strLine;
  ifstream f(getName(), ios::in);
  if (!f.is_open()) {
    s = "npm";
  } else {
    while (!f.eof()) {
      getline(f, strLine);
      size_t p = strLine.find("=");
      string key = strLine.substr(0, p);
      if (key == "home") {
        string value = strLine.substr(p + 1);
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

  cout << (s == "npm" ? "* " : "  ") << "npm -----  https://registry.npmjs.org/" << endl;
  cout << (s == "yarn" ? "* " : "  ") << "yarn ----- https://registry.yarnpkg.com" << endl;
  cout << (s == "cnpm" ? "* " : "  ") << "cnpm ----  http://r.cnpmjs.org/" << endl;
  cout << (s == "taobao" ? "* " : "  ") << "taobao --  https://registry.npm.taobao.org/" << endl;
  cout << (s == "nj" ? "* " : "  ") << "nj ------  https://registry.nodejitsu.com/" << endl;
  cout << (s == "skimdb" ? "* " : "  ") << "skimdb --  https://skimdb.npmjs.com/registry" << endl;
}

void use(string key) {
  string home;
  string registry;
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
    cout << "no this choose" << endl;
    return;
  }

  ifstream ifs;
  int size = 0;
  ifs.open(getName(), ios::in);

  if (!ifs.is_open()) {
    ifs.close();
    ofstream ofs;
    ofs.open(getName(), ios::out);
    ofs << "home=" << home << endl;
    ofs << "registry=" << registry << endl;
    ofs.close();
  } else {
    vector <Config> vc;
    string str;

    while (!ifs.eof()) {
      getline(ifs, str);
      size_t p = str.find("=");
      if (p == -1) {
        continue;
      }
      string key = str.substr(0, p);
      string value;
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

    ofstream ofs;
    ofs.open(getName(), ios::out);
    size_t size = vc.size();
    for (size_t i = 0; i < size; i++) {
      ofs << vc[i].key << "=" << vc[i].value << endl;
    }
    ofs.close();
  }
}

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