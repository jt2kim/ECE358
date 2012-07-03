#include <stdio.h>
#include <stdlib.h>

#define STOP 0
#define START_SEND 1
#define RECEIVE_ACK 2
#define SEND_FRAME 3
#define RECEIVE_FRAME 4
#define SEND_ACK 5
#define TIMEOUT 6
#define CHECK 7

struct Queue
{
	struct Queue *Next;
	double Time;
	int Type;
	int Seq_Num;
	int Pkt_Num;
	int Error;
};

typedef struct
{
	double Time;
	int Type;
	int Seq_Num;
	int Pkt_Num;
	int Error;
}Event;


extern "C" void Initialization();
extern "C" void Print(Event Current_Event);
extern "C" void Dequeue(Event *Current_Event);
extern "C" void Channel(int Type, int SeqNum, int PktNum, double CTime);
extern "C" void Deliver(Event Current_Event, double CTime);
extern "C" void Sender_SRP(Event Current_Event);
extern "C" void Reciever_SRP(Event Current_Event);
