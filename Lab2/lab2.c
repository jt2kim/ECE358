#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

struct Queue *Queue_Head = NULL;
double C;
double A;
double L;  /* Avg length of packets */
double Prop_Delay;
double Time_Out;
double FER;
int Window_Size;
int N; /* Total number of packets */

int ext_expected_frame;

void Sender(Event Current_Event) {
	
	/* You sender code here */
}

void Receiver(Event Current_Event) {
	
	/* Your receiver code here */
    
    
    //RECEIVER CODE FOR ABP
    
    //if current_Event packet has an error, or if it is out of order, discard it
    if ( (Current_Event.Error == 0) || (Current_Event.Seq_Num != ext_expected_frame) )
        return;
    //Otherwise, send ACK, and deliver
    else
    {
        //Send ACK
        Channel( SEND_ACK, Current_Event.Seq_Num, 0, /*time*/ 0.0);
        Deliver( Current_Event, /*time*/ 0.0);
    }
}


int main()
{
	Event Current_Event;
	
	/**********************************************/
	/* Remember to change the following variables */
	
	N = 25;		
	C = 1000000;			/* bps */
	L = 1500*8;			/* bits, Avg length of pkts */
	A = 54*8;			/* bits */
	Prop_Delay = 50;		/* seconds */
	Window_Size = 5;
	FER = 0.01;
	Time_Out = 10;
	/**********************************************/
	ext_expected_frame = 0;
	Initialization();
	
	while (Queue_Head != NULL)
	{
		Dequeue(&Current_Event);
		
		if (    (Current_Event.Type == RECEIVE_ACK)
			|| (Current_Event.Type == START_SEND)
			|| (Current_Event.Type == TIMEOUT))
		{
			Print(Current_Event);
			Sender(Current_Event);
		}
		else if (Current_Event.Type == RECEIVE_FRAME)
		{
			Print(Current_Event);
			Receiver(Current_Event);
		}
	}
	
	return 0;
}
