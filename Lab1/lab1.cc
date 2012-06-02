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
int transmissionTime;
int bufferSize = -1;
int ticks = 5000;

double runningQueueSizeSum = 0.0;
double queueSizeCtr = 0.0;

double runningDelaySizeSum = 0.0;
double delaySizeCtr = 0.0;

double runningIdleSizeSum = 0;
double idleSizeCtr = 0;
double idleTime = 0;

double currentlyServing = -1;
double u;

//GET THESE AS USER INPUTS 
double lambda = 1000;
double L = 2000;
double C = 1; 				//Transmission rate of the output link (get it as bits per second but conver to bits per microsecond)

//Convert str to double
int strToDbl (const string &str) {
	stringstream ss(str);
	int n;
	ss >> n;
	return n;
}

int main(int argc, char* argv[]) {

	// Get input in the format M/D/1 n lambda L C
	string queueType(argv[1]);				// M/D/1 or M/D/1/K
	string ticksString(argv[2]);			// ticks
	string lambdaString(argv[3]);			// lambda
	string LString(argv[4]);				// L
	string CString(argv[5]);				// C

	// Check if input is of type M/D/1 or M/D/1/K
	istringstream ss;
	if (queueType.size() > 5) {
		// If its of type M/D/1/K, read in and update bufferSize
		bufferSize = strToDbl(queueType.substr(6));
	}
	
	// Convert n, lambda, L, C to int values
	ticks = strToDbl(ticksString);
	lambda = strToDbl(lambdaString);
	L = strToDbl(LString);
	C = strToDbl(CString);

	// Seed random number generator
	sgenrand(4557);
    u = genrand();
    
    transmissionTime = L / C;
    
	// Randomly generate arrival time
	t_arrival = (int)((-1/lambda)*log(1-u) * 1000000);
	t_departure = t_arrival;
    t_leave = transmissionTime;
    
	startSimulation(ticks);
	computePerformances();
	cout << "done" << endl;
}

void startSimulation(int ticks) {    
	// Runs 5 billion times
	// Two numbers make it easy to store and manage number of runs
	for (double t = 1.0; t < (double)ticks*1000000; t+=1.0) {	
        
        // Check queue size and add up its value
        runningQueueSizeSum += (double)(buffer.size());       
        queueSizeCtr += 1.0;
        
			// If buffer is empty, increment idleTime
			if (buffer.size() == 0) {
				//idleTime++;
			}            
            
			arrival(t);
			departure(t);
		
		// Each t is worth a 1000000
		//cout << t << endl;
	}
}

void arrival(double t) {
	// Check if we have randomly generated arrival time has passed
    t_arrival--;
    if(t_arrival <= 0 ){
		
        //if buffer is empty and nothing is being served, the packet goes directly to the server
		if( (bufferSize == -1) || (bufferSize > buffer.size()) )
        {
            if(currentlyServing == -1)
            {
                currentlyServing = t;
                t_leave = transmissionTime;
            }
            buffer.push(t);
        }
        
        runningIdleSizeSum += idleTime;
        idleSizeCtr += 1.0;
        
        idleTime = 0;
        
        u = genrand();
        t_arrival =  (int)((-1/lambda)*log(1-u) * 1000000);
    }
    
}

void departure (double t) {

	// Store buffer size
	int queueSize = buffer.size();
	
    if(queueSize != 0)
    {
        if(currentlyServing != -1)
        {
            t_leave--;
            if(t_leave == 0 )
            {
                runningDelaySizeSum += t - currentlyServing;
                delaySizeCtr += 1.0;
                currentlyServing = -1;
                buffer.pop();
            }
        }
        else
        {
            currentlyServing = buffer.front();
            t_leave = transmissionTime;
        }
    }
    else
    {
        idleTime++;
    }
}

void computePerformances() {
	cout << "Average Size of Queue is :    " << runningQueueSizeSum/queueSizeCtr << endl;
	cout << "Average Delay is         :    " << runningDelaySizeSum/delaySizeCtr << endl;
	cout << "Average Idle time is     :    " << runningIdleSizeSum/idleSizeCtr << endl;
}
