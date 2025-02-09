#include "Playfaircipher.h"
#include "GLOBALS.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cctype>

using namespace std;

vector<vector<char>> generatePlayfairSquare(const string& key) {
    unordered_set<char> usedChars;
    vector<vector<char>> matrix(GLOBALS_H::MATRIX_SIZE, vector<char>(GLOBALS_H::MATRIX_SIZE));
    string combinedKey = key + GLOBALS_H::ALPHABET;
    int index = 0;

    for (char c : combinedKey) {
        c = toupper(c);
        if (usedChars.find(c) == usedChars.end()) {
            matrix[index / GLOBALS_H::MATRIX_SIZE][index % GLOBALS_H::MATRIX_SIZE] = c;
            usedChars.insert(c);
            index++;
        }
    }
    return matrix;
}


pair<int, int> findCharPosition(const vector<vector<char>>& matrix, char character) {
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            if (matrix[row][col] == character) {
                return { row, col };
            }
        }
    }
    return { -1, -1 };
}

// Подготовка текста
string prepareText(const string& text) {
    string processedText;
    for (char c : text) {
        if (isalnum(c)) {
            processedText += toupper(c);
        }
    }
    return processedText;
}

// Разбиение на биграммы с учётом повторяющихся букв
vector<pair<char, char>> createBigrams(const string& text, vector<int>& insertedXPositions) {
    vector<pair<char, char>> bigrams;
    string processedText = prepareText(text);

    // Разбиение на биграммы с учётом повторяющихся символов
    for (size_t i = 0; i < processedText.length(); i++) {
        char first = processedText[i];
        char second;

        // Если два символа одинаковые подряд, вставляем "X" между ними
        if (i + 1 < processedText.length() && processedText[i] == processedText[i + 1]) {
            second = 'X';
            insertedXPositions.push_back(bigrams.size());
            i++;  // Пропускаем второй символ, так как он заменен на 'X'
        }
        else if (i + 1 < processedText.length()) {
            second = processedText[i + 1];
            i++;  // Переходим ко второму символу биграммы
        }
        else {
            // Если длина строки нечётная, добавляем "X" в конец
            second = 'X';
            insertedXPositions.push_back(bigrams.size());
        }

        bigrams.push_back({ first, second });
    }

    return bigrams;
}

// Шифрование
string encryptPlayfair(const string& text, const string& key, vector<int>& insertedXPositions) {
    vector<vector<char>> matrix = generatePlayfairSquare(key);
    vector<pair<char, char>> bigrams = createBigrams(text, insertedXPositions);
    string encryptedText;

    for (auto& bigram : bigrams) {
        pair<int, int> pos1 = findCharPosition(matrix, bigram.first);
        pair<int, int> pos2 = findCharPosition(matrix, bigram.second);
        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        if (row1 == row2) {
            encryptedText += matrix[row1][(col1 + 1) % MATRIX_SIZE];
            encryptedText += matrix[row2][(col2 + 1) % MATRIX_SIZE];
        }
        else if (col1 == col2) {
            encryptedText += matrix[(row1 + 1) % MATRIX_SIZE][col1];
            encryptedText += matrix[(row2 + 1) % MATRIX_SIZE][col2];
        }
        else {
            encryptedText += matrix[row1][col2];
            encryptedText += matrix[row2][col1];
        }
    }
    return encryptedText;
}

// Расшифрование
string decryptPlayfair(const string& encryptedText, const string& key, const vector<int>& insertedXPositions) {
    vector<vector<char>> matrix = generatePlayfairSquare(key);
    string decryptedText;

    for (size_t i = 0; i < encryptedText.length(); i += 2) {
        char first = encryptedText[i];
        char second = encryptedText[i + 1];

        pair<int, int> pos1 = findCharPosition(matrix, first);
        pair<int, int> pos2 = findCharPosition(matrix, second);
        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        if (row1 == row2) {
            decryptedText += matrix[row1][(col1 - 1 + MATRIX_SIZE) % MATRIX_SIZE];
            decryptedText += matrix[row2][(col2 - 1 + MATRIX_SIZE) % MATRIX_SIZE];
        }
        else if (col1 == col2) {
            decryptedText += matrix[(row1 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col1];
            decryptedText += matrix[(row2 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col2];
        }
        else {
            decryptedText += matrix[row1][col2];
            decryptedText += matrix[row2][col1];
        }
    }

    // Удаление вставленных "X" и восстановление строки
    string finalText;
    size_t xIndex = 0;
    bool isXAtEnd = (decryptedText.back() == 'X');

    for (size_t i = 0; i < decryptedText.length(); i++) {
        // Если мы нашли последний "X", проверим, был ли он вставлен для исправления длины
        if (isXAtEnd && i == decryptedText.length() - 1) {
            break; // Пропускаем последний "X"
        }
        // Если "X" был вставлен между одинаковыми символами, восстанавливаем исходную букву
        if (xIndex < insertedXPositions.size() && i / 2 == insertedXPositions[xIndex]) {
            if (decryptedText[i] == 'X') {
                finalText += decryptedText[i - 1];  // Вставляем повторяющийся символ вместо "X"
                xIndex++;
                continue;
            }
        }
        finalText += decryptedText[i];
    }

    return finalText;
}