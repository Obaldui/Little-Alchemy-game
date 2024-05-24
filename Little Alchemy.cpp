#include <fstream>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {

  map<pair<string, string>, string> myMap;
  set<string> mySet;

  string line;
  ifstream infile("save.txt");
  while (getline(infile, line)) {
    mySet.insert(line);
  }
  infile.close();

  mySet.insert("Earth");
  mySet.insert("Air");
  mySet.insert("Water");
  mySet.insert("Fire");

  ifstream file_combinations("combinations.csv");
  if (file_combinations.is_open()) {
    string line;
    while (getline(file_combinations, line)) {
      size_t pos1 = line.find(',');
      size_t pos2 = line.find(',', pos1 + 1);
      if (pos1 != string::npos && pos2 != string::npos) {
        string el1 = line.substr(0, pos1);
        string el2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string result = line.substr(pos2 + 1);
        if (el1 > el2) swap(el1, el2);
        myMap[make_pair(el1, el2)] = result;
      }
    }
    file_combinations.close();
  } else {
    cout << "Unable to open file." << endl;
  }

  string el1, el2;
  while (true) {
    cin >> el1 >> el2;
    if (el1 > el2) swap(el1, el2);
    if (mySet.count(el1) && mySet.count(el2)) {
      if (myMap.count(make_pair(el1, el2))) {
        cout << myMap[make_pair(el1, el2)] << endl;
        mySet.insert(myMap[make_pair(el1, el2)]);
        cout << endl;
        cout << "unlocked elements:" << endl;
        string line;
        ofstream outfile("save.txt");
        for (const auto &element : mySet) {
          outfile << element << "\n";
        }
        outfile.close();
        for (const auto &element : mySet) {
          cout << element << endl;
        }
        cout << endl;
      } else {
        cout << "This combination does not exist, please try again" << endl;
      }
    } else {
      cout << "You haven't unlocked this item yet, you can't use it" << endl;
    }
  }

  return 0;
}
