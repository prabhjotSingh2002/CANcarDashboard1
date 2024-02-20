#include"header.h"

#define LEFTINDICATOR ((IOPIN0>>14)&1)
#define RIGHTINDICATOR ((IOPIN0>>15)&1)
#define HEADLIGHT ((IOPIN0>>16)&1)

char s[10]={0};

float vout,tempr;
int speed;

CAN1 frame;
char flag;
CAN1 m1;

int left=0,right=0,head=0;
int num,num1;

int main()
{
	int adcval=0;
  adc_init();
  can1_init();
  uart0init(9600);

  enableExtIntr2();
  enableExtIntr1();
  enableExtIntr0();

  configVicExt2();
  configVicExt1();
  configVicExt0();
  //configVicTimer();
 while(1)
 {
 	num=0;
	num1=0;
	speed=0;
  	//left indicator
	frame.id=0x13A;
	frame.rtr=0;
	frame.dlc=8;

	if(left)		  
		num=0x10;			
	else
		num=0x11;

//right indicator

	if(right)
		num=num|0x1000;
	else
		num=num|0x1100;

//headlight

		if(head)
			 num=num|0x100000;
		else
			num=num|0x110000;


		frame.byteA=num; //byte A has been set

		///////////////////////////	temperature/////////////////////

		 adcval=adc_read(1);
		 vout=(adcval *3.3f)/1023.0f;
		tempr=(vout-0.5f)/0.01f;
		
		num1=((int)tempr)%100;
		num1=((num1/10)<<4)|(num1%10);
		
		//////////////////////// potentiometer-speed//////
			
		adcval=adc_read(2);
		vout=(adcval *3.3f)/1023.0f;
		speed=(int)((vout*180)/3.3f);

		 

		speed=((speed/100)<<8)|(((speed%100)/10)<<4)|(speed%10);
		num1=(speed<<8)|num1;

//		sprintf(s,"%x %d\r\n",speed,(int)tempr);		
//		 uart0txString("num1--");
//		uart0txString(s);
	   ///////////////////////////////////////////
	   frame.byteB=num1;
	    can1_tx(frame);//send data frame
	   delayms(1000);
 }

}
