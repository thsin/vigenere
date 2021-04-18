#include <iostream> 
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

string message;
string mappedKey;
int mode;
ifstream fin("input.doc");
ofstream fout("output.doc");

void messageAndKey() {
	string msg;

	if (mode == 0) {
		cout << "평문을 입력하세요" << endl;
	}
	else if (mode == 1) {
		cout << "암호문을 입력하세요 " << endl;
	}

	while (getline(fin, msg)); // 공백이 있는 입력파일을 msg에 입력

	if (mode == 0) {
		cout << "입력받은 평문은 " << msg << "입니다." << endl;
	}
	else if (mode == 1) {
		cout << "입력받은 암호문은 " << msg << "입니다." << endl;
	}
	// 입력받은 메시지 출력

	cin.ignore();

	string key;
	cout << "키를 입력하세요" << endl;
	getline(cin, key);
	cin.ignore();

	string keyMap = "";
	for (int i = 0, j = 0; i < msg.length();i++) {
		if (msg[i] == 32) {
			keyMap += 32;
		}
		else {
			if (j < key.length()) {
				keyMap += key[j];
				j++;
			}
			else {
				j = 0;
				keyMap += key[j];
				j++;
			}
		}
	}

	message = msg;
	mappedKey = keyMap;

}



int arr[26][26];
void table() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			int element;
			if ((i + 97) + j > 122) {
				element = ((i + 97) + j) - 26;
				arr[i][j] = element;
			}

			else {
				element = (i + 97) + j;
				arr[i][j] = element;
			}
		}
	}
}

void encrypt(string message, string mappedKey) {
	table();
	string encryptMsg = "";
	for (int i = 0; i < message.length(); i++) {
		if (message[i] == 32 && mappedKey[i] == 32) {
			encryptMsg += " ";

		}
		else {
			int x = (int)message[i] - 97;
			int y = (int)mappedKey[i] - 97;
			encryptMsg += (char)arr[x][y];
		}
	}

	cout << "암호문은 " << encryptMsg << " 입니다. ";
	fout << encryptMsg; // 암호문 파일 출력
}


int findCount(int key, int msg) {

	int count = 0;
	string findKey = "";

	for (int i = 0; i < 26; i++) {
		if (key + i > 122) {
			findKey += (char)(key + (i - 26));
		}
		else {
			findKey += (char)(key + i);
		}
	}

	for (int i = 0; i < findKey.length(); i++) {
		if (findKey[i] == msg) {
			break;
		}
		else {
			count++;
		}
	}
	return count;

}



void decrypt(string message, string mappedKey) {
	string decryptMsg = "";
	for (int i = 0; i < message.length(); i++) {
		if (message[i] == 32 && mappedKey[i] == 32) {
			decryptMsg += " ";
		}
		else {
			int num = findCount((int)mappedKey[i], (int)message[i]);
			decryptMsg += (char)(97 + num);
		}
	}

	cout << "평문은 " << decryptMsg << " 입니다. ";
	fout << decryptMsg;
}

int main() {

	cout << "평문과 키는 소문자만 입력할 수 있습니다. " << endl;
	cout << "모드를 선택하세요" << endl << "0 : 암호화 / 1 : 복호화" << endl;
	cin >> mode;
	cin.ignore();

	if (mode == 0) {
		cout << "암호화 모드입니다." << endl << endl;
		messageAndKey();
		encrypt(message, mappedKey);
	}

	else if (mode == 1) {
		cout << "복호화 모드입니다." << endl << endl;
		messageAndKey();
		decrypt(message, mappedKey);
	}

	else {
		cout << "잘못 입력하셨습니다 " << endl;
	}

	fin.close();
	fout.close();

	return 0;
}
