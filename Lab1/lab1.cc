#include "lab1.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

extern "C" {
	#include "RandomForLab1.h"
}
queue<double> buffer;
list<int> averageInQueue;
list<double> averageDelay;
list<int> averageIdle;
int t_arrival;
int t_departure;
int bufferSize = -1;
int ticks = 5000;
int packetIndex = 0;
int idleTime = 0;

long long runningQueueSizeSum = 0;
long queueSizeCtr = 0;

long long runningDelaySizeSum = 0;
long delaySizeCtr = 0;

long long runningIdleSizeSum = 0;
long idleSizeCtr = 0;

int main(int argc, char* argv[]) {
    char* input = argv[1];				//input, such as G/G/1/K/FIFO 
	string bufferS(input);

	if (bufferS.size() > 5) {
		istringstream ss(bufferS.substr(6));
		ss >> bufferSize;
	}

	// for (int i = 0; i < 5; i++) {
		// cout << parsedTokens[i] << endl;
	// }
	
    sgenrand(4357);
    t_arrival = (int)(genrand() * 1000000);
    t_departure = t_arrival;

    startSimulation(ticks);
    computePerformances();
    cout << "done" <<endl;
}

void startSimulation(int ticks) {
	for (int t = 1; t <= ticks; t++) {
        for(int m = 1; m <= 1000000; m++)
        {
        //cout << (double)(t-1)*1000000.00 + (double)m << endl;
            if (buffer.size() == 0) {
                idleTime++;
			}
            arrival(t,m);
            departure(t,m);
        }
        cout << t << endl;
	}
	
}

int arrival(int t_1, int t_2) {
	if ( t_arrival != 0 && ((t_1 % t_arrival) == 0) || ((t_2 % t_arrival) == 0) ) {
		//cout << "Packet Generated" << endl;
		//cout << "packetIndex value is " << packetIndex << endl;
        
	    //getSize of the queue, and push to the averageInQueue list
		//averageInQueue.push_front(buffer.size());		
        
		if (buffer.size() == 0)
        {
            runningIdleSizeSum += idleTime;
            idleSizeCtr++;
        }
		//	averageIdle.push_front(idleTime);		
        
        
		//If buffer is not full, add packet to buffer
		if (buffer.size() != bufferSize)
        {
	        //buffer.push(new Packet( (double)(t_1-1)*1000000.00 + (double)t_2 ));
            buffer.push( (double)(t_1-1)*1000000.00 + (double)t_2 );
			idleTime = 0;
        }
		t_arrival = (int)(genrand() * 1000000);
	}
	packetIndex++;
		
}

int departure (int t_1, int t_2) {
    int queueSize = buffer.size();
    if(queueSize == 0)
        return 0;
    else
    {
        if( (t_1 % t_departure) == 0 || (t_2 % t_departure) == 0 )
        {
        //cout <<buffer.size() << endl;
            //averageInQueue.push_back(queueSize);
            runningQueueSizeSum += (double)queueSize;
            queueSizeCtr += 1;
            //Packet* packet = buffer.front();
            double enterTick = buffer.front();
            runningDelaySizeSum +=  (t_1-1)*1000000 + t_2;
            delaySizeCtr += 1;
            //averageDelay.push_back( (double)(t_1-1)*1000000.00 + (double)t_2 - packet->getStartTick());
            buffer.pop();
                
            //cout << "Packed popped."<< endl;
        }        
    }

}

void computePerformances() {
	//double averageSizeOfQueue = getAverageOfInts(averageInQueue);
    cout << "average size of queue is " << runningQueueSizeSum/queueSizeCtr << endl;
    cout << "average delay is " << runningDelaySizeSum/delaySizeCtr << endl;
    cout << "average idle time is " << runningIdleSizeSum/idleSizeCtr << endl;
    //double averageDelayTime = getAverageOfDoubles(averageDelay);
    //double averageIdleTime = getAverageOfInts(averageIdle);
}



double Packet::getStartTick(){
    return this->startTick;
}

Packet::Packet(double start){
    this->startTick = start;
}
