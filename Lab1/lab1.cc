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
int t_arrival;
int t_departure;
int bufferSize;
int ticks = 100;
int i = 0;
int main() {
    /* Initialization */
    sgenrand(4357);
    t_arrival = int(genrand() * 10);
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
	i++;
	if (t % t_arrival == 0) {
		cout << "Packet Generated" << endl;
		cout << "i value is " << i << endl;
	}
	
		
}

int departure (int t) {


}


void computePerformances() {
	
}

