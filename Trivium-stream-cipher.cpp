#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

int main()
{
	int registerA[93];
	int registerB[84];
	int registerC[111];
	int Key[288];
	int tempA, tempB, tempC;
	int random;
	srand((unsigned)time(0));

	cout << "Register A(93 bits):" << endl;
	for (int a = 0; a < 93; a++)
	{
		random = 0 + (rand() % 2);
		registerA[a] = random;
		cout << registerA[a];
	}
	cout << endl << "Register B(84 bits):" << endl;
	for (int b = 0; b < 84; b++)
	{
		random = 0 + (rand() % 2);
		registerB[b] = random;
		cout << registerB[b];
	}
	cout << endl << "Register C(111 bits):" << endl;
	for (int c = 0; c < 111; c++)
	{
		random = 0 + (rand() % 2);
		registerC[c] = random;
		cout << registerC[c];
	}
	cout << endl << "Key stream is: " << endl;
	for (int k = 0; k < 288; k++)
	{
		tempA = registerA[90] & registerA[91];	//evaluating AND for A's final output
		tempA = tempA ^ registerA[65];
		tempA = tempA ^ registerA[92]; // A's final XORed output

		tempB = registerB[81] & registerA[82];	//evaluating AND for B's final output
		tempB = tempB ^ registerB[68];
		tempA = tempA ^ registerA[83]; // B's final XORed output

		tempC = registerC[108] & registerC[109];	//evaluating AND for C's final output
		tempC = tempC ^ registerC[65];
		tempC = tempC ^ registerC[110]; // C's final XORed output

		Key[k] = tempA ^ tempB;
		Key[k] = Key[k] ^ tempC;	// XORing A,B,C's final output to get key stream bit
		//cout << endl << Key[k] << endl;

		//cout << "\n iteration no " << k << endl;
		registerA[0] = tempC ^ registerA[68];
		for (int shifta = 92; shifta > 0; shifta--)
		{
			registerA[shifta] = registerA[shifta - 1];
		}
		registerB[0] = tempA ^ registerB[77];
		for (int shiftb = 83; shiftb > 0; shiftb--)
		{
			registerB[shiftb] = registerB[shiftb - 1];
		}
		registerC[0] = tempB ^ registerC[86];
		for (int shiftc = 110; shiftc > 0; shiftc--)
		{
			registerC[shiftc] = registerC[shiftc - 1];
		}
		cout << Key[k];
	}
	int input[288], encryption[288], data, count = 0;
	for (int i = 0; i < 288; i++)
	{
		input[i] = 0;
		//cout << input[i];
	}
	cout << endl << "Enter the bits(only 0s and 1s) you want to encrypt and press any other number to stop. Maximum capacity is 288(PRESS ENTER AFTER EVERY INPUT):" << endl;
	cin >> data;
	while (data == 0 || data == 1)
	{
		input[count] = data;
		count = count + 1;
		cin >> data;
		if (count == 28)
		{
			break;
		}
	}
	cout << endl;
	for (int i = 0; i < count; i++)
	{
		cout << input[i];
	}
	cout << "\nencrypted cipher is:\n";
	for (int i = 0; i < count; i++)
	{
		encryption[i] = input[i] * Key[i];
		cout << encryption[i];
	}

	cout << "\ndecrypted plain data is:\n";
	for (int i = 0; i < count; i++)
	{
		input[i] = encryption[i] * Key[i];
		cout << input[i];
	}
}