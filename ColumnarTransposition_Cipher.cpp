#include "ColumnarTranspositioncipher.h"
#include "GLOBALS.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cctype>

using namespace std;

// Функция для заполнения таблицы для алгоритма Columnar Transposition
vector<vector<char>> fillTable(const string& text, const string& key) {
    int len_key = key.length();
    int len_msg = text.length();

    // Вычисляем количество строк
    int no_rows = len_msg / len_key;
    if (len_msg % len_key != 0) {
        no_rows++;
    }

    // Создаем таблицу
    vector<vector<char>> table(no_rows, vector<char>(len_key, ' '));  // Используем пробел вместо '_'

    int x = 0;  // Индекс для текста
    // Заполняем таблицу символами из текста
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
    int no_rows = table.size();  // Количество строк
    string result = "";

    // Создаем массив пар (символ ключа, индекс) для сортировки
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < len_key; i++) {
        sortedKey.push_back({ key[i], i });
    }

    // Сортируем пары по символам ключа
    sort(sortedKey.begin(), sortedKey.end());

    // Чтение столбцов в отсортированном порядке
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

    // Вычисляем количество строк
    int no_rows = len_msg / len_key;
    if (len_msg % len_key != 0) {
        no_rows++;
    }

    // Создаем таблицу для расшифровки
    vector<vector<char>> table(no_rows, vector<char>(len_key, ' '));  // Используем пробел

    int x = 0;  // Индекс для зашифрованного текста
    // Сортируем столбцы по ключу
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < len_key; i++) {
        sortedKey.push_back({ key[i], i });
    }
    sort(sortedKey.begin(), sortedKey.end());

    // Заполняем таблицу с учетом порядка столбцов
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

// Шифрующая функция
string columnarTranspositionEncrypt(const string& text, const string& key) {
    // Заполняем таблицу с текстом
    vector<vector<char>> table = fillTable(text, key);

    // Читаем столбцы в отсортированном порядке по ключу
    string cipher = readColumnsInSortedOrder(table, key);

    return cipher;
}

    // Функция для расшифровки текста
    string columnarTranspositionDecrypt(const string & cipher, const string & key) {
        // Восстанавливаем таблицу
        vector<vector<char>> table = fillTableForDecryption(cipher, key);

        // Чтение строк в исходном порядке
        string result = "";
        int len_key = key.length();
        int no_rows = table.size();

        for (int i = 0; i < no_rows; i++) {
            for (int j = 0; j < len_key; j++) {
                result += table[i][j];
            }
        }

        // Убираем пробелы в конце строки (если они были добавлены)
        result.erase(result.find_last_not_of(' ') + 1);

        return result;
    }