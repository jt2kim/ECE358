#include "lab2.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;
struct Queue *Queue_Head = NULL;
double C;
double A;
double L;  /* Avg length of packets */
double Prop_Delay;
double Time_Out;
double FER;
int Window_Size;
int N; /* Total number of packets */
int *P = NULL;
double ticks = 0;
long packetNum = 0;

struct pkt {
	Event e;
	bool receivedAck;
};

vector<pkt> buffer;	// Buffer to keep track of acks

int ext_expected_frame = 0;
int last_in_order_frame = 0;

void Sender(Event Current_Event) {
	int lowestAcked = -1;
	if (Current_Event.Type == START_SEND) {
		if (buffer.size() < Window_Size) {
			// Do something
			printf("START_SEND \n");
			Current_Event.Pkt_Num = packetNum;
			Current_Event.Seq_Num = Current_Event.Pkt_Num % (Window_Size + 1);
			pkt p;
			p.e = Current_Event;
			p.receivedAck = false;
			Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, ticks);
			packetNum++; // Increment packet number
		}
	}
	// If received acknowledgement is corrupted, resend previous frame
	else if (Current_Event.Type == RECEIVE_ACK) {
		if (Current_Event.Error == 1) {		// Error
			// Do nothing
		}
		else {
			// Iterate through vector to find correct packet and mark it acknowledged
			for (int i = 0; i < buffer.size(); i++)
			{
				if (buffer[i].e.Seq_Num == Current_Event.Seq_Num)
				{
					buffer[i].receivedAck = true;
					break;
				}
			}
			// Go through buffer and remove the first sequential 
			while (buffer.size() != 0) {
				if (buffer.at(0).receivedAck) {
					buffer.erase(buffer.begin());
				}
				else
					break;
			}			
		}
	}
	else if (Current_Event.Type == TIMEOUT) {
		printf("TIMEOUT \n");
		cout << ticks << endl;
		// Retransmit
		int index = -1;
		for (int i = 0; i < buffer.size(); i++)
		{
			if (buffer[i].e.Seq_Num == Current_Event.Seq_Num)
			{
				index = i;
			}
			if (index != -1) {
				Channel(SEND_FRAME, buffer[i].e.Seq_Num, buffer[i].e.Pkt_Num, ticks);
			}
		}			
	}
}

void Receiver(Event Current_Event) {
	
	/* Your receiver code here */
    
    
    //RECEIVER CODE FOR ABP
    
    //if current_Event packet has an error, or if it is out of order, discard it
    
    //if ( (Current_Event.Error == 1) || (Current_Event.Seq_Num != ext_expected_frame) ) {
	//	printf("RECEIVED_ERROR \n");
    //    return;
     //}
    //Otherwise, send ACK, and deliver
    //else
    //{
	//	printf("RECEIVED_SUCCESS \n");
    //    //Send ACK
    //    Channel( SEND_ACK, Current_Event.Seq_Num, 0, /*time*/ 0.0);
    //    Deliver( Current_Event, /*time*/ 0.0);
        
        //Update the ext_expected_frame
    //    ext_expected_frame = ( ext_expected_frame + 1 ) % 1;
   // }
    
    //RECEIVER CODE FOR GBN
    //If there is no error, and the frame is the expected frame
    //updated the last in order frame number and update the ext_expected_frame
    
    //If correctly received
    if(Current_Event.Error == 0)
    {
        //If the frame is in order, update the last in order frame
        if(Current_Event.Seq_Num == ext_expected_frame)
        {
            last_in_order_frame = ext_expected_frame;
            ext_expected_frame = (ext_expected_frame + 1)%(Window_Size +1);
            Deliver( Current_Event,  Current_Event.Time);
			cout << "Received and Acknowledged " << last_in_order_frame + " "  << endl;
        }
        Channel( SEND_ACK, last_in_order_frame, 0 , ticks);
    }
    
    
    /*if ( (Current_Event.Error == 0) && (Current_Event.Seq_Num == ext_expected_frame) )
    {
        last_in_order_frame = ext_expected_frame;
        ext_expected_frame = (ext_expected_frame + 1)%(Window_Size +1);
        
        //Send ACK to sender
        Channel( SEND_ACK, last_in_order_frame, 0 , 0.0);
        Deliver( Current_Event,  0.0);
    }*/
    
    
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
		ticks+= 0.000001;
	}
	
	return 0;
}
