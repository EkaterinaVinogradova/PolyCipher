#include "ColumnarTranspositioncipher.h"
#include "GLOBALS.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cctype>

using namespace std;

// ������� ��� ���������� ������� ��� ��������� Columnar Transposition
vector<vector<char>> fillTable(const string& text, const string& key) {
    int len_key = key.length();
    int len_msg = text.length();

    // ��������� ���������� �����
    int no_rows = len_msg / len_key;
    if (len_msg % len_key != 0) {
        no_rows++;
    }

    // ������� �������
    vector<vector<char>> table(no_rows, vector<char>(len_key, ' '));  // ���������� ������ ������ '_'

    int x = 0;  // ������ ��� ������
    // ��������� ������� ��������� �� ������
    for (int i = 0; i < no_rows; i++) {
        for (int j = 0; j < len_key; j++) {
            if (x < len_msg) {
                table[i][j] = text[x++];
            }
        }
    }

    return table;
}

string readColumnsInSortedOrder(const vector<vector<char>>& table, const string& key) {
    int len_key = key.length();
    int no_rows = table.size();  // ���������� �����
    string result = "";

    // ������� ������ ��� (������ �����, ������) ��� ����������
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < len_key; i++) {
        sortedKey.push_back({ key[i], i });
    }

    // ��������� ���� �� �������� �����
    sort(sortedKey.begin(), sortedKey.end());

    // ������ �������� � ��������������� �������
    for (auto& p : sortedKey) {
        int col = p.second;
        for (int i = 0; i < no_rows; i++) {
            result += table[i][col];
        }
    }

    return result;
}

vector<vector<char>> fillTableForDecryption(const string& cipher, const string& key) {
    int len_key = key.length();
    int len_msg = cipher.length();

    // ��������� ���������� �����
    int no_rows = len_msg / len_key;
    if (len_msg % len_key != 0) {
        no_rows++;
    }

    // ������� ������� ��� �����������
    vector<vector<char>> table(no_rows, vector<char>(len_key, ' '));  // ���������� ������

    int x = 0;  // ������ ��� �������������� ������
    // ��������� ������� �� �����
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < len_key; i++) {
        sortedKey.push_back({ key[i], i });
    }
    sort(sortedKey.begin(), sortedKey.end());

    // ��������� ������� � ������ ������� ��������
    for (auto& p : sortedKey) {
        int col = p.second;
        for (int i = 0; i < no_rows; i++) {
            if (x < len_msg) {
                table[i][col] = cipher[x++];
            }
        }
    }

    return table;
}

// ��������� �������
string columnarTranspositionEncrypt(const string& text, const string& key) {
    // ��������� ������� � �������
    vector<vector<char>> table = fillTable(text, key);

    // ������ ������� � ��������������� ������� �� �����
    string cipher = readColumnsInSortedOrder(table, key);

    return cipher;
}

    // ������� ��� ����������� ������
    string columnarTranspositionDecrypt(const string & cipher, const string & key) {
        // ��������������� �������
        vector<vector<char>> table = fillTableForDecryption(cipher, key);

        // ������ ����� � �������� �������
        string result = "";
        int len_key = key.length();
        int no_rows = table.size();

        for (int i = 0; i < no_rows; i++) {
            for (int j = 0; j < len_key; j++) {
                result += table[i][j];
            }
        }

        // ������� ������� � ����� ������ (���� ��� ���� ���������)
        result.erase(result.find_last_not_of(' ') + 1);

        return result;
    }