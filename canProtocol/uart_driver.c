 #include"header.h"

void uart0init(unsigned int baud)
{
 	int a[]={15,60,30,15,15};
	unsigned int pclk=a[VPBDIV]*1000000;
	unsigned int result=0;
	result=pclk/(16*baud);

	PINSEL0|=0X05;
	U0LCR=0X83;
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=0X03;
}

 #define THRE ((U0LSR>>5)&1)
 void uart0tx(unsigned char data)
 {
  	U0THR=data;
	while(THRE==0);
 }

#define RDR	(U0LSR&1)
unsigned char uart0rx()
{
	unsigned char temp;
 	while(RDR==0);
	temp=U0RBR;
	return temp;
}

void uart0rxString(unsigned char*p,unsigned int bytes )
{
 	int i;
	for(i=0;i<bytes;i++)
	{
	 	while(RDR==0);
		p[i]=U0RBR;
		if(p[i]=='\r')
		      break;
		 U0THR=p[i];
		 while(THRE==0);
		
	}
	p[i]='\0';
}

 void uart0txString(unsigned char *p)
 {
  	while(*p)
	{
	 	U0THR=*p;
		while(THRE==0);
		p++;
	}
 }

 void strrev2(char *p,char *q)
{
		char t;
 		while(p<q)
		{
		 	t=*p;
			*p=*q;
			*q=t;
			p++;q--;
		}
}

void sprintf2(char *s,float n)
{
	int num=n,i;
	i=sprintf1(s,num);
	s[i++]='.';
	num=n*1000;
	num=num%1000;
	sprintf1(s+i,num);
}


int sprintf1(char *s,int num)
{
	int i=0;
 	char *p=s,*q=0;
	if(num==0)
	{
	 	s[0]='0';
		s[1]=0;
		return 1;
	}

	if(num<0)
	{
		s[0]='-';
		num=-num;
	      i=1;
		p=s+1;
	}
	while(num)
	{
	 	s[i]=(num%10)+'0';
		i++;
		num=num/10;
	}
	q=s+i-1;
	strrev2(p,q);
	s[i]='\0';
	return i;
}

void clearstr(unsigned char *s,int n)
{
	int i;
   for(i=0;i<n;i++)
   {
		s[i]=0;
   }
}

int hextodeci(int num)
{
 	int deci=0;
	int i;
	int div=1,mul=1;
	for(i=0;i<8;i++)
	{	
	 	deci=deci + ((num/div)%0x10)*mul;
		div=div*0x10;
		mul=mul*10;
	}
	return deci;
}
