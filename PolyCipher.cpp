#include "ADFGVXcipher.h"
#include "Playfaircipher.h"
#include "ColumnarTranspositioncipher.h"
#include "GLOBALS.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


using namespace std;

string savedPassword = "PolyCipher";

int main()
{
	string password;
	/*while (true) {
		cout << "Enter password: ";
		cin >> password;
        if (password == savedPassword) {
            cout << "Password is correct!" << endl;
            break;
        }
        else {
            cout << "Incorrect password, try again!" << endl;
        }
    }*/

    cout << "Welcome" << endl;
    int modeOption;
    int cipherOption;
    //while (true) {
    cout << "Select encryption or decryption mode:\n" <<"1. Encryption\n"<<"2. Decryption\n"<< "Enter your choice (1/2): ";
    cin >> modeOption;
    switch (modeOption)
    {
        case 1:
            cout << "Select a cipher :\n" << "1. ADFGVX Cipher\n" << "2. Playfair Cipher\n" << "3. Columnar Transposition Cipher\n";
            cout << "Enter your choice (1/2/3): ";
            cin >> cipherOption;
            switch (cipherOption) {
                case 1:
                case 2:
                case 3:
                default: break;

            }
            break;

        case 2:
            cout << "Select a cipher :\n" << "1. ADFGVX Cipher\n" << "2. Playfair Cipher\n" << "3. Columnar Transposition Cipher\n";
            cout << "Enter your choice (1/2/3): ";
            cin >> cipherOption;
              switch (cipherOption) {
                case 1:
                case 2:
                case 3:
                default: break;

            }

            break;

        default: break;
        //}
    }  
        

}

