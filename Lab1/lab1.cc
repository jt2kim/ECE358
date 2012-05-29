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
int ticks = 6000;

double runningQueueSizeSum = 0;
double queueSizeCtr = 0;

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
        queueSizeCtr += 1;
        
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
	//if ( ((t_1 % t_arrival) == 0) || ((t_2 % t_arrival) == 0) ) {
    t_arrival--;
    if(t_arrival <= 0 ){
		
        //if buffer is empty and nothing is being served, the packet goes directly to the server
		if ( (currentlyServing == -1)  && ( buffer.size() == 0) )
		{
            currentlyServing = t;
		}

        //// Since buffer is no longer idle, set idleTime to 0
	    //idleTime = 0;	
	    
	    //// Use a new seed everytime - verified working
	    //sgenrand(seedCtr);
	    
        //// Generate a new arrival time for package
	    //t_arrival = (int)(genrand() * 1000000);
	    //seedCtr++;       

        else
        {
            // If buffer is not full, add packet to buffer
            if ( (bufferSize == -1) || (bufferSize > buffer.size()) ) {
                buffer.push( t );					
            }
            // Since buffer is no longer idle, set idleTime to 0
            //idleTime = 0;	
            // Generate a new arrival time for package
            
        }
        u = genrand();
        t_arrival =  (int)((-1/lambda)*log(1-u) * 1000000);
    }
}

void departure (double t) {

	// Store buffer size
	int queueSize = buffer.size();
	
	// If buffer is empty, do nothing
	//if(queueSize == 0)
	//	return 0;
        //increment idle here
	if(queueSize > 0 )
    {
        if ( ( fmod(t , (double)t_departure) <= 0) && (currentlyServing == -1) )
        {
            currentlyServing = buffer.front();
            buffer.pop();
        }
    }
    
    if(currentlyServing != -1)
    {
        t_leave--;
        if( t_leave <= 0 )
        {            
            currentlyServing = -1;
            t_leave = transmissionTime;
        }
    }


}

void computePerformances() {
	cout << "Average Size of Queue is :    " << runningQueueSizeSum/queueSizeCtr << endl;
	//cout << "Average Delay is         :    " << runningDelaySizeSum/delaySizeCtr << endl;
	//cout << "Average Idle time is     :    " << runningIdleSizeSum/idleSizeCtr << endl;
}
