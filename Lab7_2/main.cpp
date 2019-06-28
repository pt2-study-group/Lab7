#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <crypt.h>
#include <iomanip>
#include <fstream>
#include <mutex>

using namespace std;

void findPass(string pass, const string& hash);

int main(int argc, char* argv[])
{
    int i = 0, j = 0;
    thread th;
    ifstream f("/root/Study/Lab7_1/hashs");
	
	f.seekg(0, ios::end);
	int fsize = f.tellg();//Размер файла
	f.seekg(0, ios::beg);
	
	char * buf = new char [fsize];
	char * save = new char[60];
	f.read(buf, fsize);
	
	for (i = 0; i < fsize; i++) {
		if (buf[i] == '\n' || i == (fsize-1))
		{
			save[j] = '\0';
            th = thread(findPass, "123456789", save);
            th.join();
			delete[] save;
			save = new char[60];
			j = 0;
		} else {
			save[j] = buf[i];
			j++;
		}
	}
	
	delete[] buf;
	delete[] save;
	
    return 0;
}

/*
 * Функция поиска пароля по известному хэшу перестановкой символов пароля
 * Параметры:
 *        startPass — начальное значение пароля
 *        hash  - хэш-функция от пароля
 * Функция использует следующие заголовочные файлы:
 *     algorithm — алгоритмы стандартной библиотеки
 *     crypt.h — криптографические функции Linux
 */
void findPass(string pass, const string& hash) {
	crypt_data *pCryptData = new crypt_data;
	size_t pos = hash.find_last_of('$');
	string hashHead = hash.substr(0,pos);
	do {
		string newHash(crypt_r(pass.data(),hashHead.data(),pCryptData));
		if (newHash == hash) {
			cout<<"Hash: "<<hash<<endl<<"Pass: "<<pass<<endl;
			break;
		}
	} while ( next_permutation( pass.begin(), pass.end() ) );
	delete pCryptData;
}
