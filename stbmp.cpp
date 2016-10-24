#pragma once

#include <iostream>
#include "bmp.h"

using namespace std;
bool encrypt(string path, string message, int encryptway);
string decrypt(const char* path, const unsigned char stop_symbol, int encryptway);

int main(int argc, char* argv[]) {

	string path, message, ini;
	unsigned char stop_char = '@';
	int encryptway = SimpleLSB;

	if (argc > 1) { 
		ini = argv[1];
	}
	if (ini == "--help" || ini == "-help" || ini == "-h") {
		cout << "You can encrypt or decrypt some message" << endl;
		cout << "Hint: you can use command line with args:" << endl;
		cout << "stbmp -d [PATH [decrptyway,stopsymbol= ] ]\n"
				"      -e [PATH MESSAGE [encrptyway,stopsymbol= ] ]" << endl;
		return 0;
	}
	if (argc > 2) {
		if (ini == "-d") {
			switch (argc) 
			{
			case 3:
				cout << decrypt(argv[2], stop_char, encryptway);
				return 0;
			case 4:
				encryptway = argv[3][0]-'0';
				cout<< decrypt(argv[2], stop_char,encryptway);
			case 5:
				encryptway = argv[3][0] - '0';
				stop_char = argv[3][9];
				cout << decrypt(argv[2], stop_char, encryptway);
				return 0;
			default:
				cout << "Bad argument number " << argc << endl;
				return 5;
			}
		}
		else if (ini == "-e") 
		{
			switch (argc) {
			case 4:
				path = argv[2];
				message = argv[3];
				break;
			case 5:
				path = argv[2];
				message = argv[3];
				encryptway = argv[4][0] - '0';
				break;
			case 6:
				path = argv[2];
				message = argv[3];
				encryptway = argv[4][0] - '0';
				stop_char = argv[5][9];
				break;
			default:
				cout << "Bad argument number " << argc << endl;
				return 5;
			}
			message += stop_char;
			if (encrypt(path, message,encryptway)) 
			{
				cout << "\tOK" << endl;
			} 
			else
			{
				cout << "Error" << endl;
				return 2;
			}
			return 0;
		} 
		else
		{
			cout << "Bad argument " << ini << endl;
			return 5;
		}
	}

	cout << "You can encrypt or decrypt some message" << endl;
	cout << "Hint: you can use command line with args:" << endl;
	cout << "stbmp -d [PATH [ stopsymbol= ] ]\n"
			"      -e [PATH MESSAGE [ stopchar= ] ]\n"
			"     [-h | --help | -help ]" << endl;

	if (argc < 2) {
		cout << ">>> To decrypt or to encrypt? input: 'd' or 'e'" << endl;
		cin >> ini;
	}

	cout << ">>> Path to your picture?" << endl;
	cin.ignore();
	getline(cin, path, '\n');

	cout << ">>> way to encrypt?\n 1.simplelsb \n 2.multiplelsb with 2bits in a pixel\n 3.multiplelsb with 3bits in a pixel\n 4.encryptedlsb \n" << endl;
	cin >> encryptway;
	cin.ignore();

	cout << ">>> Any stop char? (default '@')" << endl;
	cin >> stop_char;
	cin.ignore();

	if (ini == "d" || ini == "-d") {
		cout << decrypt(path.c_str(), stop_char,encryptway);
		return 0;
	}

	if (ini != "-e" && ini != "e") {
		cout << "Bad input" << endl;
		return 3;
	}

	cout << ">>> Input message" << endl;
	getline(cin, message, '\n');
	message += stop_char;

	if (encrypt(path.c_str(), message,encryptway)) {
		cout << "\nOK\n" << endl;
		return 0;
	} else {
		cout << "Error" << endl;
		return 2;
	}

	return 0;
}
