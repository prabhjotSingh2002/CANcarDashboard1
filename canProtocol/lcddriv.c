#include"header.h"

#define RS (1<<17)//p1.17
#define RW (1<<18)//p1.18
#define EN (1<<19)//p1.19



void lcddata(unsigned char data)
{
 	unsigned int temp;
	IOCLR1=0X00FE0000;
	temp=(data&0xf0)<<16;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delayms(2);
	IOCLR1=EN;

	IOCLR1=0X00FE0000;
	temp=(data&0x0f)<<20;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delayms(2);
	IOCLR1=EN;
}

void lcdcmd(unsigned char data)
{
 	unsigned int temp;
	IOCLR1=0X00FE0000;
	temp=(data&0xf0)<<16;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delayms(2);
	IOCLR1=EN;

	IOCLR1=0X00FE0000;
	temp=(data&0x0f)<<20;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delayms(2);
	IOCLR1=EN;

}

void lcdinit()
{
	IODIR1|=0x00fe0000;
 	PINSEL2=0;

	 lcdcmd(0x02);
	 lcdcmd(0x03);
	 lcdcmd(0x28);
	 lcdcmd(0x0E);
	 lcdcmd(0x01);

}

void lcdString(char *ptr)
{
 	while(*ptr)
	{
	 	lcddata(*ptr);
		ptr++;
	}
}

unsigned char a[8]={0x00,0x02,0x04,0x08,0x04,0x02,0x00};
void leftcgram(void)
{
	int i;
 	lcdcmd(0x40);
	for(i=0;i<8;i++)
	{
		lcddata(a[i]); 	
	}
}

unsigned char b[8]={0x00,0x08,0x04,0x02,0x04,0x08,0x00};
void rightcgram(void)
{
	int i;
 	lcdcmd(0x48);
	for(i=7;i>=0;i--)
	{
		lcddata(b[i]); 	
	}
}

unsigned char c[8]={0x04,0x15,0x0E,0x04,0x04,0x0E,0x15,0x04};
void headcgram(void)
{
	int i;
 	lcdcmd(0x50);
	for(i=7;i>=0;i--)
	{
		lcddata(c[i]); 	
	}
}

unsigned char d[8]={0};
void clearcgram(void)
{
	int i;
 	lcdcmd(0x58);
	for(i=7;i>=0;i--)
	{
		lcddata(d[i]); 	
	}
}


