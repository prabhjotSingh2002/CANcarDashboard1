#include <LPC21xx.H>
#include<stdio.h>

typedef struct CAN1_MSG
{
   unsigned int id;
   unsigned char rtr;
   unsigned char dlc;
   unsigned int byteA;
   unsigned int byteB;

}CAN1	;

void can1_init(void);
void can1_tx(CAN1 v);
void can1_rx(CAN1 *ptr);
void en_CAN1_interrupt(void);


void uart0init(unsigned int baud);
 void uart0tx(unsigned char data);
 unsigned char uart0rx(void);
 void uart0rxString(unsigned char*p,unsigned int bytes );
  void uart0txString(unsigned char *p);


void lcddata(unsigned char data);
void lcdcmd(unsigned char data);
void lcdinit(void);

void delayms(unsigned int ms);

 void adc_init(void);
 int adc_read(int ch_num);

void clearstr(unsigned char *s,int n);
int sprintf1(char *s,int num);
 int hextodeci(int num);

void configVicExt0(void);
void configVicExt1(void);
void configVicExt2(void);

void  enableExtIntr2(void);
void  enableExtIntr1(void);
void  enableExtIntr0(void);

void clearcgram(void);
void headcgram(void);
void rightcgram(void);
void leftcgram(void);

 void lcdString(char *ptr);

