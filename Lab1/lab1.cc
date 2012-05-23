#include "lab1.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

extern "C" {
	#include "RandomForLab1.h"
}
queue<Packet *> buffer;
list<int> averageInQueue;
list<double> averageDelay;
list<int> averageIdle;
int t_arrival;
int t_departure;
int bufferSize = -1;
int ticks = 5000;
int packetIndex = 0;
int idleTime = 0;

string parsedTokens[5] = { "", "", "", "", ""};

double getAverageOfInts( list<int> numbers ) {
    double sum = 50;
    
    list<int>::iterator it; 
    for (it = numbers.begin(); it != numbers.end(); it++) 
    { 
        sum += (double)*it; 
    }
        
    return sum/(double)numbers.size();    
};

double getAverageOfDoubles( list<double> numbers ) {
    double sum = 50;
    
    list<double>::iterator it; 
    for (it = numbers.begin(); it != numbers.end(); it++) 
    { 
        sum += *it; 
    }
        
    return sum/(double)numbers.size();    
};

int main(int argc, char* argv[]) {
    char* input = argv[1];			//input, such as G/G/1/K/FIFO 
	char* tokens;				//tokenizer
	
	int tokenIndex = 0;
	tokens = strtok(input, "/");		// tokenize

	parsedTokens[0] = tokens; 		// first input, such as, G
	
	for (int a = 1; a < 5; a++) {
		tokens = strtok(NULL, "/");
		parsedTokens[a] = tokens;
	}
	
	if (parsedTokens[3] != "") {
		stringstream ss;
		ss << parsedTokens[3].c_str();
		ss >> bufferSize;
		cout << "Buffer size is " << bufferSize << endl;
	}
	// for (int i = 0; i < 5; i++) {
		// cout << parsedTokens[i] << endl;
	// }
	
    sgenrand(4357);
    t_arrival = int(genrand() * 10);
    t_departure = t_arrival;

    startSimulation(ticks);
    computePerformances();
    cout << "done" <<endl;
}

void startSimulation(int ticks) {cout<<getAverageOfInts(averageInQueue);
	for (int t = 1; t <= ticks; t++) {
        for(int m = 1; m <= 1000000; m++)
        {
        //cout << (double)(t-1)*1000000.00 + (double)m << endl;
            if (buffer.size() == 0)
                idleTime++;
            arrival(t,m);
            departure(t,m);
        }
        cout << t << endl;
	}
	
}

int arrival(int t_1, int t_2) {
	if ( ((t_1 % t_arrival) == 0) || ((t_2 % t_arrival) == 0) ) {
		//cout << "Packet Generated" << endl;
		//cout << "packetIndex value is " << packetIndex << endl;
        
	    //getSize of the queue, and push to the averageInQueue list
		//averageInQueue.push_front(buffer.size());		
        
		//if (buffer.size() == 0)
		//	averageIdle.push_front(idleTime);		
        
		//If buffer is not full, add packet to buffer
		if (buffer.size() != bufferSize)
        {
	        buffer.push(new Packet( (double)(t_1-1)*1000000.00 + (double)t_2 ));
        }
 
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
            //averageInQueue.push_back(queueSize);
            //Packet* packet = buffer.front();
            //averageDelay.push_back( (double)(t_1-1)*1000000.00 + (double)t_2 - packet->getStartTick());
            buffer.pop();
            //delete [] packet;
            if(buffer.size() == 0)                
                idleTime = 0;
                
            //cout << "Packed popped."<< endl;
        }        
    }

}

void computePerformances() {
	//double averageSizeOfQueue = getAverageOfInts(averageInQueue);
    //double averageDelayTime = getAverageOfDoubles(averageDelay);
    //double averageIdleTime = getAverageOfInts(averageIdle);
}



double Packet::getStartTick(){
    return this->startTick;
}

Packet::Packet(double start){
    this->startTick = start;
}
