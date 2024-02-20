#include"header.h"

unsigned char speed[4]={0};
unsigned char temp[3]={0};

int byteA=0,byteB=0;

CAN1 frame;
int flag;

int li=0,ri=0,head=0;


int main()
{

 	can1_init();
	uart0init(9600);
	lcdinit();
//	en_CAN1_interrupt()	;
	uart0txString("node B\r\n");
	lcdcmd(0x01);
	while(1)
	{
	
	uart0txString("node B\r\n");
	  can1_rx(&frame);
	  lcdcmd(0x01);	
		if(frame.rtr==0)
		{
		   	uart0txString("node B:data frame\r\n");
			
			byteA=hextodeci(frame.byteA);		
			byteB=frame.byteB;
          ///////////////////left indicator///////////////////////////
			
			if(byteA%100==10)
			{
			 		uart0txString("left indicator on\r\n");
					li=1;
			}
			else if(byteA%100==11)
			{
					uart0txString("left indicator off\r\n");
					li=0;
			}

			  ///////////////right indicator////////////


			if((byteA/100)%100==10)
			{
			 		uart0txString("right indicator on\r\n");
					ri=1;
			}
			else if((byteA/100)%100==11)
			{
					ri=0;
					uart0txString("right indicator off\r\n");
			}

		  //////////////head light//////////////

			if((byteA/10000)%100==10)
			{
					head=1;
			 		uart0txString("headlight on\r\n");
			}
			else if((byteA/10000)%100==11)
			{
					head=0;
					uart0txString("headlight off\r\n");
			}

			/////////////speed////////
			
			sprintf(speed,"%d",hextodeci((frame.byteB>>8)&0xfff));	
			uart0txString("speed-- ");
			uart0txString(speed);
			uart0txString("km/hr");
			
			lcdcmd(0x80);
			lcdString(speed);
			lcdString("kmph");

			//////////////temp////////

			sprintf(temp,"%d",hextodeci(frame.byteB&0xff));	
			uart0txString("temp-- ");
			uart0txString(temp);
			uart0txString("deg.\r\n");

			lcdcmd(0x89);
			lcdString(temp);
			lcdString("deg");


			////////////////////////////////
		  
		   clearstr(temp,3);
		   clearstr(speed,4);
		}
		else
		   uart0txString("node B:remote frame\r\n");

	  
		uart0txString("out of if \r\n");


		if(ri && !li)
		{
			 
			 lcdcmd(0xC0);
			 lcddata(' ');
			
			 rightcgram();//calling cgran
			 lcdcmd(0xC1);
			 lcddata(1);
			 	
			 delayms(150);

			 clearcgram();//calling cgran
			 lcdcmd(0xC1);
			 lcddata(3);
			 delayms(150);

		}
		
		if(!ri && li)
		{
			
			 lcdcmd(0xC1);
			 lcddata(' ');

			 leftcgram();//calling cgran
			 lcdcmd(0xC0);
			 lcddata(0);

			 delayms(150);

			 clearcgram();//calling cgran
			 lcdcmd(0xC0);
			 lcddata(3);
			 delayms(150);
		}

		if(!ri && !li)
		{
			 lcdcmd(0xc0);
			 lcdString("  ");
		}

		if(head)
		{
			 headcgram();//calling cgran
			 lcdcmd(0xC6);
			 lcddata(2);
		}
		else
		{
			
			 clearcgram();//calling cgran
			 lcdcmd(0xC6);
			 lcddata(3);
		
		}

	}
}





													