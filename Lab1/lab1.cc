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
long seedCtr = 0;

int lambda = -1;
int L = -1;
int C = -1;

long long runningQueueSizeSum = 0;
long queueSizeCtr = 0;

long long runningDelaySizeSum = 0;
long delaySizeCtr = 0;

long long runningIdleSizeSum = 0;
long idleSizeCtr = 0;

long long packetsGenerated = 0;
long packetSeconds = 0; // just using ticks for now

int strToInt (const string &str) {
	stringstream ss(str);
	int n;
	ss >> n;
	return n;
}

int main(int argc, char* argv[]) {
	// Get input in the format M/D/1 n lambda L C
	string queueType(argv[1]);		// M/D/1 or M/D/1/K
	string ticksString(argv[2]);				// n
	string lambdaString(argv[3]);			// lambda
	string LString(argv[4]);				// L
	string CString(argv[5]);				// C

	// Check if input is of type M/D/1 or M/D/1/K
	istringstream ss;
	if (queueType.size() > 5) {
		// If its of type M/D/1/K, read in and update bufferSize
		bufferSize = strToInt(queueType.substr(6));
	}
	
	// Convert n, lambda, L, C to int values
	ticks = strToInt(ticksString);
	lambda = strToInt(lambdaString);
	L = strToInt(LString);
	C = strToInt(CString);
	
	cout << "ticks " << ticks << endl;
	cout << "lambda " << lambda << endl;
	cout << "L " << L << endl;
	cout << "C " << C << endl;

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
		//cout << t << endl;
	}

}

int arrival(int t_1, int t_2) {
	// Check if we have randomly generated arrival time has passed
	//if ( ((t_1 % t_arrival) == 0) || ((t_2 % t_arrival) == 0) ) {
    if(t_arrival <= 0 ){
		
		// To calculate lambda
		packetsGenerated++;
		
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
	    
	    // Use a new seed everytime - verified working
	    sgenrand(seedCtr);
	    
        // Generate a new arrival time for package
	    t_arrival = (int)(genrand() * 1000000);
	    seedCtr++;       
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
	cout << "Lambda is                :    " << packetsGenerated/ticks; 
}
