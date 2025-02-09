#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

const int MATRIX_SIZE = 6;
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
vector<char> ADFGVX_COORDINATES = { 'A', 'D', 'F', 'G', 'V', 'X' };

// Генерация квадрата Полибия
vector<vector<char>> polybiusSquareGeneration(const string& line) {
    unordered_set<char> usedChars;
    vector<vector<char>> matrix(MATRIX_SIZE, vector<char>(MATRIX_SIZE));
    string combinedKey = line + ALPHABET;  // Ключ + алфавит
    int index = 0;

    for (char c : combinedKey) {
        c = toupper(c);  // Преобразуем в верхний регистр
        if (usedChars.find(c) == usedChars.end()) {  // Если символ ещё не встречался
            matrix[index / MATRIX_SIZE][index % MATRIX_SIZE] = c;
            usedChars.insert(c);
            index++;
        }
    }
    return matrix;
}

// Вывод квадрата Полибия
void printPolybiusSquare(const vector<vector<char>>& polybiusSquare) {
    cout << "\nКвадрат Полибия:\n";
    for (const auto& row : polybiusSquare) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Генерация пар ADFGVX
string adfgvxPairsGeneration(const string& clearText, const vector<vector<char>>& keySquare) {
    string resultTemp;
    string adfgx = "ADFGX";

    for (char c : clearText) {
        for (size_t row = 0; row < keySquare.size(); row++) {
            for (size_t col = 0; col < keySquare[row].size(); col++) {
                if (keySquare[row][col] == c) {
                    resultTemp += adfgx[row];  // Добавляем символ строки
                    resultTemp += adfgx[col];  // Добавляем символ столбца
                    break;  // Найден символ, переходим к следующему
                }
            }
        }
    }
    return resultTemp;
}

// Столбцовая транспозиция
string columnTransposition(const string& keyWord, const string& text) {
    vector<string> charMatrix(keyWord.length());

    // 1. Инициализируем столбцы ключевыми буквами
    for (size_t i = 0; i < keyWord.length(); i++) {
        charMatrix[i] = string(1, keyWord[i]);  // Преобразуем символ в строку
    }

    // 2. Распределяем символы текста по колонкам циклично
    int idx = 0;
    for (char c : text) {
        charMatrix[idx] += c;
        idx = (idx + 1) % charMatrix.size();  // Улучшенное циклическое распределение
    }

    // 3. Сортируем колонки по первой букве
    sort(charMatrix.begin(), charMatrix.end());

    // 4. Формируем результат, убирая первую букву каждой колонки
    string result;
    for (const string& s : charMatrix) {
        result += s.substr(1);
    }

    return result;
}

// Основная функция для шифрования ADFGVX
string adfgvxEncryption(const string& clearText, const string& keyWord) {
    // Шаг 1: Генерация квадрата Полибия
    vector<vector<char>> keySquare = polybiusSquareGeneration(clearText);

    // Шаг 2: Генерация пар ADFGVX
    string adfgvxPairs = adfgvxPairsGeneration(clearText, keySquare);

    // Шаг 3: Столбцовая транспозиция
    string encryptedText = columnTransposition(keyWord, adfgvxPairs);

    return encryptedText;
}

int main() {
    string keyWord = "KEY";
    string clearText = "HELLOWORLD";

    string encrypted = adfgvxEncryption(clearText, keyWord);
    cout << "Зашифрованный текст: " << encrypted << endl;

    return 0;
}
