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
		cout << "���� �Է��ϼ���" << endl;
	}
	else if (mode == 1) {
		cout << "��ȣ���� �Է��ϼ��� " << endl;
	}

	while (getline(fin, msg)); // ������ �ִ� �Է������� msg�� �Է�

	if (mode == 0) {
		cout << "�Է¹��� ���� " << msg << "�Դϴ�." << endl;
	}
	else if (mode == 1) {
		cout << "�Է¹��� ��ȣ���� " << msg << "�Դϴ�." << endl;
	}
	// �Է¹��� �޽��� ���

	cin.ignore();

	string key;
	cout << "Ű�� �Է��ϼ���" << endl;
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

	cout << "��ȣ���� " << encryptMsg << " �Դϴ�. ";
	fout << encryptMsg; // ��ȣ�� ���� ���
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

	cout << "���� " << decryptMsg << " �Դϴ�. ";
	fout << decryptMsg;
}

int main() {

	cout << "�򹮰� Ű�� �ҹ��ڸ� �Է��� �� �ֽ��ϴ�. " << endl;
	cout << "��带 �����ϼ���" << endl << "0 : ��ȣȭ / 1 : ��ȣȭ" << endl;
	cin >> mode;
	cin.ignore();

	if (mode == 0) {
		cout << "��ȣȭ ����Դϴ�." << endl << endl;
		messageAndKey();
		encrypt(message, mappedKey);
	}

	else if (mode == 1) {
		cout << "��ȣȭ ����Դϴ�." << endl << endl;
		messageAndKey();
		decrypt(message, mappedKey);
	}

	else {
		cout << "�߸� �Է��ϼ̽��ϴ� " << endl;
	}

	fin.close();
	fout.close();

	return 0;
}
