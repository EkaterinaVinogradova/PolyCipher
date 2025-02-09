#ifndef COLUMNARTRANSPOSITION_H
#define COLUMNARTRANSPOSITION_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<char>> fillTable(const string& text, const string& key);
string readColumnsInSortedOrder(const vector<vector<char>>& table, const string& key);
vector<vector<char>> fillTableForDecryption(const string& cipher, const string& key);
string columnarTranspositionEncrypt(const string& text, const string& key);
string columnarTranspositionDecrypt(const string& cipher, const string& key);

#endif 
