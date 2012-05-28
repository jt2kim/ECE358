#include "lab1.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

extern "C" {
#include "RandomForLab1.h"
}
queue<double> buffer;
int t_arrival;
int t_departure;
int t_leave;
int bufferSize = -1;
int ticks = 5000;
int idleTime = 0;

long long runningQueueSizeSum = 0;
long queueSizeCtr = 0;

long long runningDelaySizeSum = 0;
long delaySizeCtr = 0;

long long runningIdleSizeSum = 0;
long idleSizeCtr = 0;

int main(int argc, char* argv[]) {
	// Get input
	char* input = argv[1];

	// Conver char* to string
	string bufferS(input);

	// Check if input is of type M/D/1 or M/D/1/K
	if (bufferS.size() > 5) {
		// If its of type M/D/1/K, read in and update bufferSize
		istringstream ss(bufferS.substr(6));
		ss >> bufferSize;
	}

	// Seed random number generator
	sgenrand(4357);

	// Randomly generate arrival time
	t_arrival = int(genrand() * 1000000);
	t_departure = t_arrival;
    t_leave = t_departure;

	startSimulation(ticks);
	computePerformances();
	cout << "done" <<endl;
}

void startSimulation(int ticks) {
	// Runs 5 billion times
	// Two numbers make it easy to store and manage number of runs
	for (int t = 1; t < ticks; t++) {
		for(int m = 1; m <= 1000000; m++)
		{
			// If buffer is empty, increment idleTime
			if (buffer.size() == 0) {
				idleTime++;
			}
            t_arrival--;
            t_leave--;
			arrival(t,m);
			departure(t,m);
		}
		// Each t is worth a 1000000
		cout << t << endl;
	}

}

int arrival(int t_1, int t_2) {
	// Check if we have randomly generated arrival time has passed
	//if ( ((t_1 % t_arrival) == 0) || ((t_2 % t_arrival) == 0) ) {
    if(t_arrival <= 0 ){
		if (buffer.size() == 0)
		{
			runningIdleSizeSum += idleTime;
			idleSizeCtr++;
		}            
		// If buffer is not full, add packet to buffer
		if ( (bufferSize == -1) || (bufferSize > buffer.size()) ) {
			buffer.push( (double)(t_1 - 1)*1000000.00 + (double)t_2 );					
		}
        // Since buffer is no longer idle, set idleTime to 0
	    idleTime = 0;	
        // Generate a new arrival time for package
	    t_arrival = (int)(genrand() * 1000000);
        
    }
}

int departure (int t_1, int t_2) {
	// Store buffer size
	int queueSize = buffer.size();
	
	// If buffer is empty, do nothing
	if(queueSize == 0)

		return 0;
		
	// If buffer is not empty	
	else
	{
		// Check that set departure time has passed
		if( t_leave <=0 /*(t_1 % t_departure) == 0 || (t_2 % t_departure) == 0 */)
		{
			// Remove packet from queue and send to server
			double packetBeingServiced = buffer.front();
			buffer.pop();
			
			// Check queue size and add up its value
			runningQueueSizeSum += (double)(queueSize - 1);            
			queueSizeCtr += 1;

			// Get arrival time of packetBeingServiced
			runningDelaySizeSum +=  ( (double)(t_1 - 1)*1000000.0 + (double)t_2 ) - packetBeingServiced;
			delaySizeCtr += 1;
            t_leave = t_departure;
		}        
	}

}

void computePerformances() {
cout << queueSizeCtr << "    lol     " << runningQueueSizeSum<<endl;
	cout << "Average Size of Queue is :    " << runningQueueSizeSum/(double)queueSizeCtr << endl;
	cout << "Average Delay is         :    " << runningDelaySizeSum/delaySizeCtr << endl;
	cout << "Average Idle time is     :    " << runningIdleSizeSum/idleSizeCtr << endl;
}
