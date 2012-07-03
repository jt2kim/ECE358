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

int ext_expected_frame = 0;
int last_in_order_frame = 0;

void Sender(Event Current_Event) {}
void Receiver(Event Current_Event) {}

int main() {
	Initialization();

	return 0;
}
