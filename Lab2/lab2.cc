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
long packetNum = 0;

struct pkt {
	Event e;
	bool receivedAck;
};

vector<pkt> buffer;	// Buffer to keep track of acks

int ext_expected_frame = 0;
int last_in_order_frame = 0;

void Sender(Event Current_Event) {
	if (packetNum < N) {
		if (Current_Event.Type == START_SEND) {
			if (buffer.size() < Window_Size) {
				// Do something
				//printf("START_SEND \n");
				Current_Event.Pkt_Num = packetNum;
				Current_Event.Seq_Num = Current_Event.Pkt_Num % (Window_Size + 1);
				pkt p;
				p.e = Current_Event;
				p.receivedAck = false;
				buffer.push_back(p);
				Channel(SEND_FRAME, Current_Event.Seq_Num, Current_Event.Pkt_Num, Current_Event.Time + L/C);
				packetNum++; // Increment packet number
                
			}
		}
		// If received acknowledgement is corrupted, resend previous frame
		else if (Current_Event.Type == RECEIVE_ACK) {
			if (Current_Event.Error != 1) {
                if(buffer[0].e.Seq_Num == Current_Event.Seq_Num)
                {
                    buffer.erase(buffer.begin());
                    
                    Event New_Event;
					New_Event.Pkt_Num = packetNum;
					New_Event.Seq_Num = New_Event.Pkt_Num % (Window_Size + 1);
					pkt p;
					p.e = New_Event;
					p.receivedAck = false;
					buffer.push_back(p);
					Channel(SEND_FRAME, New_Event.Seq_Num, New_Event.Pkt_Num, Current_Event.Time + L/C);
					packetNum++;
                }
			}
		}
		else if (Current_Event.Type == TIMEOUT) {
			// Retransmit
			int index = -1;
			for (int i = 0; i < buffer.size(); i++)
			{
				
				if ( (buffer[i].e.Pkt_Num == Current_Event.Pkt_Num) && (index == -1))
				{
					index = i;
				}
				if (index != -1)  {
					//cout << "TIMEOUT and retransmit: " << buffer[i].e.Pkt_Num << endl;
					Channel(SEND_FRAME, buffer[i].e.Seq_Num, buffer[i].e.Pkt_Num, Current_Event.Time + L/C);
				}
			}			
		}
	}
}

void Receiver(Event Current_Event) {
	    
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
			//cout << "Received and Acknowledged " << last_in_order_frame  << endl;
        }
        Channel( SEND_ACK, Current_Event.Seq_Num, 0, Current_Event.Time + A/C);
        //cout << "Received Packet Number: " << Current_Event.Pkt_Num << endl;
    }  
}


int main(int argc, char* argv[])
{
	//unsigned long initial_time = clock();
	FER = 0.05;
	Window_Size = 5;
	string strFER(argv[1]);
	string strWS(argv[2]);
	FER = ((double) atoi(strFER.c_str())) / 100.0;
	Window_Size = atoi(strWS.c_str());
	Event Current_Event;
	
	/**********************************************/
	/* Remember to change the following variables */
	
	N = 500000;		
	C = 1000000;			/* bps */
	L = 1500*8;			/* bits, Avg length of pkts */
	A = 54*8;			/* bits */
	Prop_Delay = 0.05;		/* seconds */
	
	Time_Out = (L/C) + (A/C) + 2.1*Prop_Delay;
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
	//unsigned long final_time = clock() - initial_time;
	//cout << "Time it took to send " << N << " packets: " << final_time << endl;
	
	return 0;
}
