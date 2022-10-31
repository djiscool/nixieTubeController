// uses wiringPi library
// to compile add -lwiringPi

#include <wiringPi.h>
#include <unistd.h>
#include <iostream>

int main(void)
{

// Binary encoded numbers (Truth Table for k155ID1):
// BCD[Number][Input]
// i.e. BCD[0][1] === is input C for the number 0
// Inputs begin from D and go to A
// (The truth table in the spec has D on the furthest left,
// likely because the spec is russian, it is supposed to start 
// from the right. As long as we know I start at D, its not a problem)
bool BCD[10][4];
// 0
BCD[0][0] = 0;
BCD[0][1] = 0;
BCD[0][2] = 0;
BCD[0][3] = 0;
// 1
BCD[1][0] = 0;
BCD[1][1] = 0;
BCD[1][2] = 0;
BCD[1][3] = 1;
// 2
BCD[2][0] = 0;
BCD[2][1] = 0;
BCD[2][2] = 1;
BCD[2][3] = 0;
// 3
BCD[3][0] = 0;
BCD[3][1] = 0;
BCD[3][2] = 1;
BCD[3][3] = 1;
// 4
BCD[4][0] = 0;
BCD[4][1] = 1;
BCD[4][2] = 0;
BCD[4][3] = 0;
//5
BCD[5][0] = 0;
BCD[5][1] = 1;
BCD[5][2] = 0;
BCD[5][3] = 1;
// 6
BCD[6][0] = 0;
BCD[6][1] = 1;
BCD[6][2] = 1;
BCD[6][3] = 0;
// 7
BCD[7][0] = 0;
BCD[7][1] = 1;
BCD[7][2] = 1;
BCD[7][3] = 1;
// 8
BCD[8][0] = 1;
BCD[8][1] = 0;
BCD[8][2] = 0;
BCD[8][3] = 0;
// 9
BCD[9][0] = 1;
BCD[9][1] = 0;
BCD[9][2] = 0;
BCD[9][3] = 1;

// setup pin numbers for each tube:

const int numTubes = 4;

int tubes[numTubes][4];

const int A = 0;
const int B = 1;
const int C = 2;
const int D = 3;

// 1st tube
tubes[1][D] = 21; 
tubes[1][C] = 20;
tubes[1][B] = 16;
tubes[1][A] = 12;

// 2nd tube
tubes[2][D] = 26;
tubes[2][C] = 19;
tubes[2][B] = 13;
tubes[2][A] = 6;

// 3rd tube
tubes[3][D] = 7;
tubes[3][C] = 8;
tubes[3][B] = 25;
tubes[3][A] = 24;

// 4th tube
tubes[4][D] = 22;
tubes[4][C] = 27;
tubes[4][B] = 17;
tubes[4][A] = 4;



// setup gpio pins
	wiringPiSetupGpio();
for(int i = 0; i < numTubes; i++)
	{
		pinMode(tubes[i][D], OUTPUT); //D
		pinMode(tubes[i][C], OUTPUT); //C
		pinMode(tubes[i][B], OUTPUT); //B
		pinMode(tubes[i][A], OUTPUT); //A
	}

// loop through each number infintely waiting a set period before changing
	int curNum = 0; // current number being displayed
	for(;;)
	{
	
		for(int i = 0; i < numTubes; i++)
			{
			std::cout << "current Number: " << curNum << std::endl;
			// write code for current number
			if(BCD[curNum][0])
			{
				std::cout << "tube " << i << ":D - is HIGH" << std::endl;
				digitalWrite(tubes[i][D], HIGH);
			}
			else
			{
				std::cout << "tube " << i <<":D - is LOW" << std::endl;
				digitalWrite(tubes[i][D], LOW);
			}
		
			if(BCD[curNum][1])
			{
				std::cout << "tube " << i << ":C - HIGH"  << std::endl;
				digitalWrite(tubes[i][C], HIGH);
			}
			else
			{
				std::cout << "tube " << i << ":C - LOW" << std::endl;
				digitalWrite(tubes[i][C], LOW);
			}

			if(BCD[curNum][2])
			{
				std::cout << "tube " << i << ":B - HIGH" << std::endl;
				digitalWrite(tubes[i][B], HIGH);
			}
			else
			{
				std::cout << "tube "<< i << ":B - LOW" << std::endl;
				digitalWrite(tubes[i][B], LOW);
			}
	
			if(BCD[curNum][3])
			{
				std::cout << "tube " << i << ":A - HIGH" << std::endl;
				digitalWrite(tubes[i][A], HIGH);
			}
			else
			{
				std::cout << "tube " << i << ":A - LOW" << std::endl;
				digitalWrite(tubes[i][A], LOW);
			}
		}


		usleep(3000000);

		curNum = ((curNum + 1) % 10);

	}



}
