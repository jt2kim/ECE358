#include "lab1.h"

using namespace std;

extern "C" {
	#include "RandomForLab1.h"
}
queue<int> buffer;
list<int> averageInQueue;
list<double> averageDelay;
list<double> average idleTIme;

int main() {
	int j;
	double u,lambda=100,x,sum=0,Mean,var1=0,Variance;

	sgenrand(4357); /* any nonzero integer can be used as a seed */
		    	
	for (j=0; j<1000; j++) {
		u = genrand();
		x=(-1/lambda)*log(1-u);
		printf("urand = %5f \n", genrand());
		printf("exp. rv = %5f\n ",x);
		sum = sum +x;
		var1=var1 + x*x;		
		if (j%8==7) printf("\n");
	}
	Mean = sum/1000;
	Variance = 0.001*var1-(Mean*Mean);
	printf("Mean = %5f\n",Mean);
	printf("Variance = %5f\n",Variance);
	printf("\n");
}

void startSimulation(int ticks) {
	for (int t = 1; t <= ticks; t++) {
		Arrival(t);
		Departure(t);
	}
}

void arrival(int t) {
	
}

void departure (int t) {

}


void computePerformances() {
	
}

