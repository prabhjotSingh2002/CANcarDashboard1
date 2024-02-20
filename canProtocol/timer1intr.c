void timer1ISR() __irq
{	
	IODIR0|=LED1|LED2|LED3|BUZ;
	delayms(100);
	IOCLR0|=LED1|LED2|LED3;	
	
	IOSET0|=BUZ|LED1|LED2|LED3;

	T1IR=1;//CLEAR TIMER0 INTERRUPT FLAG
	VICVectAddr=0X0	;

}

void configVicTimer(void)
{
 	VICIntSelect=0;
	VICVectCntl1=5|(1<<5);
	VICVectAddr1=(int)timer1ISR;
	VICIntEnable|=(1<<5);
}