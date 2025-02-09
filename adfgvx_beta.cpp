#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int maxValue = 6;
vector<char> ADFGVX_COORDINATES = { 'A', 'D', 'F', 'G', 'V', 'X' };

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void polybiusSquareGeneration(vector<vector<string>>& matrix, const string& line);
unordered_map<char, string> adfgvxTableGeneration(const vector<vector<string>>& matrix);
unordered_map<string, char> reverseKeyTableGeneration(const vector<vector<string>>& polybiusSquare);
string intermediateLineGeneration(const string& line, const unordered_map<char, string>& adfgvxTable);
vector<vector<char>> keyTableGeneration(const string& line, int keyLength);
string columnTransposition(const vector<vector<char>>& table, const string& keyLine, bool encrypt);
string decodeIntermediateLineGeneration(const string& intermediateLine, const unordered_map<string, char>& reverseKeyTable);

void polybiusSquareGeneration(vector<vector<string>>& matrix, const string& line) {
    //line.erase(remove(line.begin(), line.end(), ' '), line.end());
    int letterIndex = 0;
    unordered_set<char> usedCharacters;

    for (int rowIndex = 0; rowIndex < maxValue && letterIndex < line.length(); rowIndex++) {
        for (int col = 0; col < maxValue && letterIndex < line.length(); col++) {
            while (letterIndex < line.length() && line[letterIndex] == ' ') {
                letterIndex++;
            }
            if (letterIndex >= line.length()) break;
            char character = toupper(line[letterIndex]);

            if (!usedCharacters.count(character)) {
                matrix[rowIndex][col] = string(1, character);
                usedCharacters.insert(character);
            }
            else {
                col--;
            }
            letterIndex++;
        }
    }

    int alphabetIndex = 0;
    for (int rowIndex = 0; rowIndex < maxValue; rowIndex++) {
        for (int col = 0; col < maxValue; col++) {
            if (matrix[rowIndex][col] == "*") {
                while (alphabetIndex < alphabet.length() && usedCharacters.count(alphabet[alphabetIndex])) {
                    alphabetIndex++;
                }
                if (alphabetIndex < alphabet.length()) {
                    matrix[rowIndex][col] = string(1, alphabet[alphabetIndex++]);
                }
            }
        }
    }
}

string adfgvxEncryption(const string& inputLine, const string& key) {
    vector<vector<string>> polybiusSquare(maxValue, vector<string>(maxValue, "*"));
    polybiusSquareGeneration(polybiusSquare, alphabet);
    unordered_map<char, string> adfgvxTable = adfgvxTableGeneration(polybiusSquare);
    string intermediateLine = intermediateLineGeneration(inputLine, adfgvxTable);
    vector<vector<char>> keyTable = keyTableGeneration(intermediateLine, key.length());

    return columnTransposition(keyTable, key, true);
}

string adfgvxDecryption(const string& inputLine, const string& key) {
    vector<vector<string>> polybiusSquare(maxValue, vector<string>(maxValue, "*"));
    polybiusSquareGeneration(polybiusSquare, alphabet);
    unordered_map<string, char> reverseKeyTable = reverseKeyTableGeneration(polybiusSquare);

    vector<vector<char>> keyTable = keyTableGeneration(inputLine, key.length());
    string intermediateLine = columnTransposition(keyTable, key, false);

    return decodeIntermediateLineGeneration(intermediateLine, reverseKeyTable);
}

unordered_map<char, string> adfgvxTableGeneration(const vector<vector<string>>& matrix) {
    unordered_map<char, string> adfgvxTable;
    for (int rowIndex = 0; rowIndex < maxValue; rowIndex++) {
        for (int col = 0; col < maxValue; col++) {
            char symbol = matrix[rowIndex][col][0];
            adfgvxTable[symbol] = string(1, ADFGVX_COORDINATES[rowIndex]) + string(1, ADFGVX_COORDINATES[col]);
        }
    }
    return adfgvxTable;
}


unordered_map<string, char> reverseKeyTableGeneration(const vector<vector<string>>& polybiusSquare) {
    unordered_map<string, char> reverseKeyTable;
    for (int rowIndex = 0; rowIndex < maxValue; rowIndex++) {
        for (int col = 0; col < maxValue; col++) {
            char symbol = polybiusSquare[rowIndex][col][0];
            string coordinates = string(1, ADFGVX_COORDINATES[rowIndex]) + string(1, ADFGVX_COORDINATES[col]);
            reverseKeyTable[coordinates] = symbol;
        }
    }
    return reverseKeyTable;
}

string intermediateLineGeneration(const string& line, const unordered_map<char, string>& adfgvxTable) {
    string intermediateLine;
    for (char character : line) {
        if (character != ' ') {
            if (adfgvxTable.find(toupper(character)) != adfgvxTable.end()) {
                intermediateLine += adfgvxTable.at(toupper(character));
            }
        }
    }
    return intermediateLine;
}

vector<vector<char>> keyTableGeneration(const string& line, int keyLength) {
    int rowsNumber = (line.length() + keyLength - 1) / keyLength;
    vector<vector<char>> keyTable(rowsNumber, vector<char>(keyLength, '*'));

    int lineIndex = 0;
    for (int rowIndex = 0; rowIndex < rowsNumber; rowIndex++) {
        for (int col = 0; col < keyLength; col++) {
            if (lineIndex < line.length()) {
                keyTable[rowIndex][col] = line[lineIndex++];
            }
        }
    }
    return keyTable;
}

string columnTransposition(const vector<vector<char>>& table, const string& keyLine, bool encrypt) {
    vector<pair<char, int>> sortedKey;
    for (int keyIndex = 0; keyIndex < keyLine.length(); keyIndex++) {
        sortedKey.push_back({ toupper(keyLine[keyIndex]), keyIndex });
    }
    sort(sortedKey.begin(), sortedKey.end());

    string outputLine;
    if (encrypt) {
        for (const auto& pair : sortedKey) {
            int columnIndex = pair.second;
            for (int rowIndex = 0; rowIndex < table.size(); rowIndex++) {
                if (table[rowIndex][columnIndex] != '*') {
                    outputLine += table[rowIndex][columnIndex];
                }
            }
        }
    }
    else {
        int rowsNumber = table.size();
        int columnsNumber = keyLine.length();
        vector<vector<char>> sortedTable(rowsNumber, vector<char>(columnsNumber, '*'));

        int index = 0;
        for (const auto& pair : sortedKey) {
            int columnIndex = pair.second;
            for (int rowIndex = 0; rowIndex < rowsNumber; rowIndex++) {
                if (index < table.size() * table[0].size()) {
                    sortedTable[rowIndex][columnIndex] = table[index / columnsNumber][index % columnsNumber];
                    index++;
                }
            }
        }

        for (int rowIndex = 0; rowIndex < rowsNumber; rowIndex++) {
            for (int columnIndex = 0; columnIndex < columnsNumber; columnIndex++) {
                if (sortedTable[rowIndex][columnsNumber] != '*') {
                    outputLine += sortedTable[rowIndex][columnsNumber];
                }
            }
        }
    }
    return outputLine;
}

string decodeIntermediateLineGeneration(const string& intermediateLine, const unordered_map<string, char>& reverseKeyTable) {
    string originalMessage = "";
    for (size_t i = 0; i < intermediateLine.length(); i += 2) {
        string pair = intermediateLine.substr(i, 2);
        if (reverseKeyTable.find(pair) != reverseKeyTable.end()) {
            originalMessage += reverseKeyTable.at(pair);
        }
        else {
            originalMessage += '?';
        }
    }
    return originalMessage;
}

int main() {
    string keyLine, inputLine, outputLine;

    cout << "Enter line: ";
    cin >> inputLine;
    cout << "Enter key: ";
    cin >> keyLine;
    outputLine = adfgvxEncryption(inputLine, keyLine);
    cout << "Encrypted: " << outputLine << endl;

    cout << "Enter encrypted line: ";
    cin >> inputLine;
    cout << "Enter key: ";
    cin >> keyLine;
    outputLine = adfgvxDecryption(inputLine, keyLine);
    cout << "Decrypted: " << outputLine << endl;

    return 0;
}