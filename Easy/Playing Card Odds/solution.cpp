#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string suits = "CDHS";
  string ranks = "23456789TJQKA";

  vector<string> pool;
  float sizeToFind = 0.0f;
  for (char s : suits) {
    for (char r : ranks) {
      pool.push_back(string(1, r) + s);
    }
  }
  int r;
  int s;
  cin >> r >> s;
  cin.ignore();

  vector<string> poolToRemove;
  for (int i = 0; i < r; i++) {
    string removed;
    getline(cin, removed);

    int index = 0;
    for (char c : removed) {
      if (ranks.find(c) != string::npos)
        index++;
      if (suits.find(c) != string::npos)
        break;
    }

    string rankToRemove = removed.substr(0, index);
    string suitsToRemove = removed.substr(index++, string::npos);

    if (rankToRemove == "")
      rankToRemove = ranks;
    if (suitsToRemove == "")
      suitsToRemove = suits;

    for (char s : suitsToRemove) {
      for (char r : rankToRemove) {
        poolToRemove.push_back(string(1, r) + s);
      }
    }

    for (const auto &card : poolToRemove) {
      pool.erase(remove(pool.begin(), pool.end(), card), pool.end());
    }

    cerr << "ToRemove: " << endl;
    for (auto f : poolToRemove)
      cerr << f << ' ';
    cerr << endl;
  }

  vector<string> poolToFind;
  for (int i = 0; i < s; i++) {
    string sought;
    getline(cin, sought);

    int index = 0;
    for (char c : sought) {
      if (ranks.find(c) != string::npos)
        index++;
      if (suits.find(c) != string::npos)
        break;
    }

    string rankToFind = sought.substr(0, index);
    string suitsToFind = sought.substr(index++, string::npos);

    if (rankToFind == "")
      rankToFind = ranks;
    if (suitsToFind == "")
      suitsToFind = suits;

    for (char s : suitsToFind) {
      for (char r : rankToFind) {
        poolToFind.push_back(string(1, r) + s);
      }
    }

    sort(poolToFind.begin(), poolToFind.end());
    poolToFind.erase(unique(poolToFind.begin(), poolToFind.end()),
                     poolToFind.end());

    for (const auto &card : poolToRemove) {
      poolToFind.erase(remove(poolToFind.begin(), poolToFind.end(), card), poolToFind.end());
    }

    cerr << "ToFind: " << i << endl;
    for (auto f : poolToFind)
      cerr << f << ' ';
    cerr << endl;

    sizeToFind = poolToFind.size();
  }

  cerr << sizeToFind << " | " << pool.size() << endl;
  cout << round((sizeToFind * 1.0f) / pool.size() * 100) << "%" << endl;
}