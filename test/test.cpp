// Hari Ganesan 7/20/13
// zombie-roll testing

#include <iostream>
#include <cstdlib>
#include <math.h>

using std::cout;
using std::endl;
using std::string;

void calculateDamage(int att, int def);
void calculateHitPercent(int s1, int s2);
void getLevel(int level);

int main() {
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			calculateDamage(i*5+5, j*5+5);
			//getLevel(i*10+j);
		}
	}

	return EXIT_SUCCESS;
}

void calculateDamage(int att, int def) {
	unsigned int total;

	total = (pow(att, 2)*15+5*rand()%att)/(def*15+5*rand()%def+20);
	
	cout << "A: " << att;
	cout << ", D: " << def;
	cout << ", DMG: " << total << endl;
}

void calculateHitPercent(int s1, int s2) {
	double hitP;

	hitP = 2/M_PI*atan(7*s1/s2);

	cout << "S1: " << s1;
	cout << ", S2: " << s2;
	cout << ", PCT: " << hitP << endl;
}

void getLevel(int level) {
	// f() = A * e^(B*level)
	int maxLevelCount = 100;
	int reqXPInitLevel = 50;
	int reqXPMaxLevel = 10000;

	double B = log((double)reqXPMaxLevel/reqXPInitLevel)/(maxLevelCount-2);
	double A = (double)reqXPInitLevel/(exp(B)-1.0);

  int newXP = round(A*(exp(B*(level-1))-1));

	cout << level << ": " << (newXP) << endl;
}
