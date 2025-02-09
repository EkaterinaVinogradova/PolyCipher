#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

const int MATRIX_SIZE = 6;
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
vector<char> ADFGVX_COORDINATES = { 'A', 'D', 'F', 'G', 'V', 'X' };

// ��������� �������� �������
vector<vector<char>> polybiusSquareGeneration(const string& line) {
    unordered_set<char> usedChars;
    vector<vector<char>> matrix(MATRIX_SIZE, vector<char>(MATRIX_SIZE));
    string combinedKey = line + ALPHABET;  // ���� + �������
    int index = 0;

    for (char c : combinedKey) {
        c = toupper(c);  // ����������� � ������� �������
        if (usedChars.find(c) == usedChars.end()) {  // ���� ������ ��� �� ����������
            matrix[index / MATRIX_SIZE][index % MATRIX_SIZE] = c;
            usedChars.insert(c);
            index++;
        }
    }
    return matrix;
}

// ����� �������� �������
void printPolybiusSquare(const vector<vector<char>>& polybiusSquare) {
    cout << "\n������� �������:\n";
    for (const auto& row : polybiusSquare) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// ��������� ��� ADFGVX
string adfgvxPairsGeneration(const string& clearText, const vector<vector<char>>& keySquare) {
    string resultTemp;
    string adfgx = "ADFGX";

    for (char c : clearText) {
        for (size_t row = 0; row < keySquare.size(); row++) {
            for (size_t col = 0; col < keySquare[row].size(); col++) {
                if (keySquare[row][col] == c) {
                    resultTemp += adfgx[row];  // ��������� ������ ������
                    resultTemp += adfgx[col];  // ��������� ������ �������
                    break;  // ������ ������, ��������� � ����������
                }
            }
        }
    }
    return resultTemp;
}

// ���������� ������������
string columnTransposition(const string& keyWord, const string& text) {
    vector<string> charMatrix(keyWord.length());

    // 1. �������������� ������� ��������� �������
    for (size_t i = 0; i < keyWord.length(); i++) {
        charMatrix[i] = string(1, keyWord[i]);  // ����������� ������ � ������
    }

    // 2. ������������ ������� ������ �� �������� ��������
    int idx = 0;
    for (char c : text) {
        charMatrix[idx] += c;
        idx = (idx + 1) % charMatrix.size();  // ���������� ����������� �������������
    }

    // 3. ��������� ������� �� ������ �����
    sort(charMatrix.begin(), charMatrix.end());

    // 4. ��������� ���������, ������ ������ ����� ������ �������
    string result;
    for (const string& s : charMatrix) {
        result += s.substr(1);
    }

    return result;
}

// �������� ������� ��� ���������� ADFGVX
string adfgvxEncryption(const string& clearText, const string& keyWord) {
    // ��� 1: ��������� �������� �������
    vector<vector<char>> keySquare = polybiusSquareGeneration(clearText);

    // ��� 2: ��������� ��� ADFGVX
    string adfgvxPairs = adfgvxPairsGeneration(clearText, keySquare);

    // ��� 3: ���������� ������������
    string encryptedText = columnTransposition(keyWord, adfgvxPairs);

    return encryptedText;
}

int main() {
    string keyWord = "KEY";
    string clearText = "HELLOWORLD";

    string encrypted = adfgvxEncryption(clearText, keyWord);
    cout << "������������� �����: " << encrypted << endl;

    return 0;
}
