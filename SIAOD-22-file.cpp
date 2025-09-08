#include <string>
#include <fstream>
#include <iostream>
#include <format>
using namespace std;

/*
Для работы с кириллицей сохранить исходный файл в кодировке 1251 и вызвать функции:
SetConsoleCP(1251); //#include <windows.h>
SetConsoleOutputCP(1251);
setlocale(LC_ALL, "Russian");
*/

100000001 << 2
000000100 >>3
000000000
00000000000000000000000000000+0+0000
|
000000000000000000000000000001010000

int func1(int x, int mask=0b000000000000000000000000000001010000){
	return x|mask;
}

int func5(int x, int n){
	if (n<0||n>31) return -1;
	mask1=1;
	mask1=mask1<<n;
	x|mask1;
}

int function(string filename, int someparameter) {
	fstream fs(filename);
	if (!fs.is_open()) { //https://en.cppreference.com/w/cpp/io/basic_ios/good
		return -1;
	}

	//function

	if (fs.good()) {
		fs.close();
		return 0;
	} else {
		fs.close();
		return -2;
	}

}

int main() {
	/*TEXT*/
	string filename = "filetext.txt";
	fstream fs;

	cout << boolalpha;
	cout << "fs.is_open() = " << fs.is_open() << '\n';

	if (!fs.is_open()) {
		fs.open(filename, ios::in);
		ios::in; //1
		ios::out; //2
		ios::ate; //4
		ios::app; //8
		ios::trunc; //16
		ios::binary; //32
		cout << "fs.is_open() = " << fs.is_open() << '\n';
	}

	cout << "fs.get(): " << (char)fs.get() << endl;

	char buffer[100] = "";
	fs.read(buffer, 3);
	cout << "fs.read(buffer, 3): " << buffer << endl;

	fs.getline(buffer, sizeof(buffer), '\n');
	cout << "fs.getline(buffer, 3): " << buffer << endl;

	fs.getline(buffer, sizeof(buffer), ',');
	cout << "fs.getline(buffer, 3): " << buffer << endl;

	cout << "fs.gcount(): " << fs.gcount() << endl;

	fs.ignore(3);
	fs.getline(buffer, sizeof(buffer), '\n');
	cout << "fs.ignore(3): " << buffer << endl;

	fs.ignore(INT_MAX, ',');
	fs.getline(buffer, sizeof(buffer), '\n');
	cout << "fs.ignore(INT_MAX, ','): " << buffer << endl;

	fs.seekg(0);
	fs.getline(buffer, sizeof(buffer), '\n');
	cout << "fs.seekg(0): " << buffer << endl;

	fs.seekg(0, ios_base::beg);
	fs.getline(buffer, sizeof(buffer), '\n');
	cout << "fs.seekg(0, ios_base::beg): " << buffer << endl;

	fs.seekg(-25, ios_base::end);
	fs.getline(buffer, sizeof(buffer), '\n');
	cout << "fs.seekg(-25, ios_base::end): " << buffer << endl;

	cout << "rest of file:\n";
	fs >> cout.rdbuf();
	cout << endl << endl;
	fs.close();

	fs.open(filename, ios::out | ios::app);
	fs << 1 << " " << 2 << " " << 3 << " " << 456 << endl;
	fs.close();

	fs.open(filename, ios::in);
	int searchnumber = 5, counter = 0, tempnumber = 0;
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	while (counter < searchnumber) {
		fs >> tempnumber;
		if (fs.fail()) break;
		else counter++;
	}
	fs.close();
	cout << format("number {} is: {}\n", counter, tempnumber);

	fs.open("filetext.txt", ios::in);
	fstream fs2("filetext2.txt", ios::out);
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	fs.getline(buffer, sizeof(buffer));
	while (!fs.eof()) {
		fs >> tempnumber;
		if (fs.fail()) break;
		else fs2 << tempnumber * 2 << " ";
	}
	fs.close();
	fs2.close();

	/*BINARY*/
	float xx = (int)5.5; //явное приведение к типу
	fs.open("filebin.txt", ios::out | ios::binary);
	int x = 0xA3B; //2619
	fs.write(reinterpret_cast<char*>(&x), sizeof(x));
	//fs.write((char*)(&x), sizeof(x));

	struct mystruct {
		int x = 0;
		char c = '0';
		float f = 0.0;
	};

	struct vuz {
		char spec[10];//key
		char name[20]; //я осознаю, что должен использовать строки константного размера или самому разбираться с последствиями
		char namespec[20];
	};

	/*
	Специализация вуза: код специальности, название вуза, название специальности.
	1. Сформировать список вузов, которые ведут подготовку специалистов по специальности с указанным номером. Список представить в текстовом файле.
	2. Изменить код специальности по названи специальности.
	09.03.01;MIREA;PI
	09.03.01;MIREA;PI
	09.03.01;MIREA;PI
	09.03.01;MIREA;PI
	*/

	mystruct ms1 = { 0x5C,'f',(float)-0.712345 };
	fs.write(reinterpret_cast<char*>(&ms1), sizeof(ms1));
	//fs.write((char*)(&ms1), sizeof(ms1));
	fs.close();

	fs.open("filebin.txt", ios::in | ios::binary);
	int x2 = 0;
	mystruct ms2;
	cout << format("x2={:x}, ms2.x={:x}, ms2.c={}, ms2.f={}\n", x2, ms2.x, ms2.c, ms2.f);
	fs.read(reinterpret_cast<char*>(&x2), sizeof(x2));
	fs.read(reinterpret_cast<char*>(&ms2), sizeof(ms2));
	fs.close();
	cout << format("readed from file:\nx2={:x}, ms2.x={:x}, ms2.c={}, ms2.f={}", x2, ms2.x, ms2.c, ms2.f);

	system("pause");
}