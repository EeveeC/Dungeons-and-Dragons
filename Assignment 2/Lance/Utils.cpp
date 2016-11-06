//! @file
//! @brief Implementation file for the Map class
//!
#include <string>
#include <sstream>
#include <vector>
#include "Utils.h"

using std::getline;
using std::string;
using std::stringstream;
using std::vector;

void Utils::split(const string &s, char delim, vector<string> &elems) {
  stringstream ss;
  ss.str(s);
  string item;
  while (getline(ss, item, delim)) {
      elems.push_back(item);
  }
}

