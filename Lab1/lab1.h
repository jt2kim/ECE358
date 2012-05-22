#ifndef LAB_ONE
#define LAB_ONE
#include <queue>
#include <list>
#include <math.h>
void startSimulation(int ticks);
int arrival(int t);
int departure(int t);
void computePerformances();

class Packet
{
public:
    double startTick;
    double getStartTick();
    Packet(double start);
};

#endif
