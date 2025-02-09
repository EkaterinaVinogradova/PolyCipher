#pragma once
#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>
#include <vector>

using namespace std;

vector<vector<char>> generatePlayfairSquare(const string& key);
pair<int, int> findCharPosition(const vector<vector<char>>& matrix, char character);
string prepareText(const string& text);
vector<pair<char, char>> createBigrams(const string& text, vector<int>& insertedXPositions);
string encryptPlayfair(const string& text, const string& key, vector<int>& insertedXPositions);
string decryptPlayfair(const string& encryptedText, const string& key, const vector<int>& insertedXPositions);

#endif 
