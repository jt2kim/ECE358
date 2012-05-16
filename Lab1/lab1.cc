#include "lab1.h"
#include <iostream>

using namespace std;

extern "C" {
	#include "RandomForLab1.h"
}
queue<int> buffer;
list<int> averageInQueue;
list<double> averageDelay;
list<double> averageIdleTime;
double t_arrival;
double t_departure;
int bufferSize;
int ticks = 100;

int main() {
    /* Initialization */
    sgenrand(4357);
    t_arrival = genrand() * 1000000;
    t_departure = t_arrival;

    startSimulation(ticks);
    computePerformances();
}

void startSimulation(int ticks) {
	for (int t = 1; t <= ticks; t++) {
		arrival(t);
		departure(t);
	}
}

int arrival(int t) {
	cout << t_arrival << endl;

	
		
}

int departure (int t) {


}


void computePerformances() {
	
}

