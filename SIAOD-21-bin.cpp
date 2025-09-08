/*
X	Y	X&Y	X|Y	X^Y ~X
0	0	0	0	0	1
0	1	0	1	1	1
1	0	0	1	1	0
1	1	1	1	1	0

X&0=0
X&1=X

X|0=X
X|1=1

X^0=X
X^1=~X
https://en.cppreference.com/w/cpp/language/operator_arithmetic
*/

#include <iostream>
#include <iomanip>
#include <format> //C++20
#include <bitset> //ban
#include <string>
using namespace std;

string bitout(unsigned int x, int b) {
	unsigned int xc = x;
	string result;
	for (int i = 0; i < b; i++) {
		if (x % 2 == 1) result = "1" + result;
		else result = "0" + result;
		x = x / 2;
	}
	return result + " " + to_string(xc);
}



int main() {
	//https://en.cppreference.com/w/cpp/language/integer_literal
	int d = 42;
	int X = 0X2A;
	int x = 0x2a;
	int o = 052;
	int b = 0b00101010;

	cout << "no formatting:\n" << d << endl << o << endl << x << endl << X << endl << b << endl << endl;

	cout << hex << showbase;
	cout << "hex and showbase:\n" << d << endl << o << endl << x << endl << X << endl << b << endl << endl;
	cout << dec;

	cout << format("format (c++ 20):\n{:b}\n{:b}\n{:b}\n{:b}\n{:b}\n\n", d, o, x, X, b);

	cout << "custom function:\n" << bitout(d, 16) << endl << bitout(o, 16) << endl << bitout(x, 16) << endl << bitout(X, 16) << endl << bitout(b, 16) << endl << endl;

	int c = 7;
	cout << "c=    " << setw(40) << bitout(c, 16) << endl;
	system("pause");

	c = c << 1;
	cout << "c<<1= " << setw(41) << bitout(c, 16) << endl;
	system("pause");

	c = c >> 3;
	cout << "c>>3= " << setw(40) << bitout(c, 16) << endl;
	system("pause");

	c = c >> 1;
	cout << "c>>1= " << setw(40) << bitout(c, 16) << endl;
	system("pause");

	//00101010
	//76543210
	//|0b10100000
	int mask1 = 0b1;
	for (int i = 0; i < 4; i++) mask1 = mask1 << 1;
	b = b | mask1;
	cout << "b+16= " << setw(41) << bitout(b, 16) << "  " << b << endl; //00111010
	system("pause");

	mask1 = ~mask1;
	b = b & mask1;
	cout << "b-16= " << setw(41) << bitout(b, 16) << "  " << b << endl; //00101010

	//ex.5
	unsigned int mask2 = 0x1 << 31;
	cout << "mask2=" << setw(49) << bitout(mask2, 32) << "  " << mask2 << endl;
	mask2 = mask2 >> (31 - 5);
	cout << "mask2=" << setw(41) << bitout(mask2, 32) << "  " << mask2 << endl;
	b = b ^ mask2;
	cout << "b+-32=" << setw(41) << bitout(b, 32) << "  " << b << endl; //00001010
	system("pause");

	mask2 = mask2 >> 1;
	cout << "mask2=" << setw(41) << bitout(mask2, 32) << "  " << mask2 << endl;
	b = b ^ mask2;
	cout << "b+-16=" << setw(41) << bitout(b, 32) << "  " << b << endl; //00011010
	system("pause");

	bitset<16> bs;
	bs = b;
	cout << "bitset:" << setw(37) << bs << "  " << bs.to_ulong() << endl; //00011010

	bs[0] = 1;
	cout << "bs+1=   " << setw(37) << bs << "  " << bs.to_ulong() << endl; //00011011

	if (bs[0] == 1) bs = bs << 2;
	cout << "bs<<2=  " << setw(37) << bs << "  " << bs.to_ulong() << endl; //01101100

	bitset<16> mask1bs = 1;
	mask1bs = mask1bs.flip();
	bs = bs | mask1bs;
	cout << "b=     " << setw(37) << bs << "  " << bs.to_ulong() << endl; //1111111111111110

}