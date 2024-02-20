/*CAN1 DRIVER INTERRUPT*/
#include "header.h"
extern CAN1 frame;
extern int flag;

void CAN1_rx_handler(void) __irq
{
 	frame.id=C2RID;
	frame.dlc=(C2RFS>>16)&0xf;//extract  dlc
	frame.rtr=(C2RFS>>30)&1;  //EXTRACT RTR

	if(frame.rtr==0)
	{
			frame.byteA=C2RDA;
			frame.byteB=C2RDB;
	}

	C2CMR=(1<<2);//RELEASE RECEIVER BUFFER
	flag=1;
	VICVectAddr=0;
}

void en_CAN1_interrupt(void)
{
 	VICIntSelect=0;
	VICVectCntl0=2|(1<<5);
	VICVectAddr0=(unsigned int)CAN1_rx_handler;
	VICIntEnable|=(1<<26);
	C2IER=1;//ENABLE CAN1 RECEIVE INTERRUPT
}