#include "lab1.h"
#include <iostream>
#include <string>

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
int bufferSize = -1;
int ticks = 100;
int packetIndex = 0;
string parsedTokens[5] = { "", "", "", "", ""};

int main(int argc, char* argv[]) {
    char* input = argv[1];			//input, such as G/G/1/K/FIFO 
	char* tokens;					//tokenizer
	
	int tokenIndex = 0;
	tokens = strtok(input, "/");	// tokenize

	parsedTokens[0] = tokens; 		// first input, such as, G
	
	for (int a = 1; a < 5; a++) {
		tokens = strtok(NULL, "/");
		parsedTokens[a] = tokens;
	}
	
	if (parsedTokens[3] != "") {
		bufferSize = atoi(parsedTokens[3].c_str());
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
}

void startSimulation(int ticks) {
	for (int t = 1; t <= ticks; t++) {
    //if buffer empty
       /// idle += 1.0
		arrival(t);
		departure(t);
	}
	
}

int arrival(int t) {
	if (t % t_arrival == 0) {
		cout << "Packet Generated" << endl;
		cout << "packetIndex value is " << packetIndex << endl;
        
        //getSize of the queue, and push to the averageInQueue list
        
        //if buffer is currently empty
            // save the current idle time in a list
        
			//If buffer is not full, add packet to buffer
			if (buffer.size() != bufferSize)
				buffer.push(packetIndex);
                
	}
	packetIndex++;
		
}

int departure (int t) {
    int queueSize = buffer.size();
    if(queueSize == 0)
        return 0;
    else
    {
        if( (t % t_departure) == 0)
        {
            averageInQueue.push_back(queueSize);
            buffer.pop();
            if(buffer.size() == 0)                
                idle = 0;
                
            cout << "Packed popped."<< endl;
        }        
    }

}

void computePerformances() {
	double averageSizeOfQueue = getAverage(averageInQueue);
    double averageDelay = getAverage(averageInQueue);
    double averageIdle = getAverage(averageInQueue);
}

template <typename T>
double getAverage( List<T> list ) {
double sum = 0.0;
    for(std::vector<T>::iterator j=vector.begin();j!=vector.end();++j)
        sum += (double)*j;
        
    return sum/(double)list.size();
};

Packet::getStartTick(){
    return this->startTick;
}

Packet::Packet(double start){
    this->startTick = start;
}
