#include<reg51.h>
#include<stdio.h>

sbit sen1 = P1^0; //entry sensor
sbit sen2 = P1^1; //exit sensor
sbit rs = P1^2;
sbit rw = P1^3;
sbit en = P1^4;
sbit flam_sen = P1^5;
unsigned char z;
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delay();
void lcddis(unsigned char *s, unsigned char r);
void lcdconv(unsigned char );
void main()
{
	unsigned char x,y;
	lcdcmd(0x38);
	delay();
	lcdcmd(0x01);
	delay();
	lcdcmd(0x10);
	delay();
	lcdcmd(0x0c);
	delay();
	lcddis(" VISITOR",8);
	lcdcmd(0xc0);
	lcddis("COUNTER",7);
	delay();
	lcdcmd(0x01);
	delay();
	while(1)
	{
		if(sen1 == 0 & flam_sen == 1)
		{
			lcdcmd(0x80);
			delay();
			lcddis("ENTRY:",6);
			lcdcmd(0x87);
			x = x+1;
			lcdconv(x);
			delay();
			lcddis(" TOT:",5);
			z = x-y;
			lcdconv(z);
			delay();
		}
		if(sen2 == 0 & flam_sen == 1)
		{
			lcdcmd(0xc0);
			delay();
			lcddis("EXIT:",5);
			lcdcmd(0xc6);
			delay();
			y = y+1;
			lcdconv(y);
			lcdcmd(0x88);
			z = x-y;
			lcdconv(z);
			delay();
		}
		if (sen1 ==1  & sen2 ==1 & flam_sen == 0)
		{
			unsigned int t;
			for(t == 0; t<2; t++)
			{
				TMOD = 0x20;
				TH1 = 0xFD;
				SCON = 0x50;
				TR1 = 1;
				TI = 1;
				printf("at");
				printf("\n");
				printf("\r");
				delay();
				printf("at+cmgf=1");
				printf("\n");
				printf("\r");
				delay();
				printf("Fire Occurred,%c people stuck inside",z);
				printf("\n");
				printf("\r");
				delay();
				SBUF = 0x1A;
				while(TI == 0);
				TI = 0;
				delay();
			}
		}
	}
}

void lcdcmd(unsigned char val)
{
	P2 = val;
	rs = 0;
	rw = 0;
	en = 1;
	delay();
	en = 0;
}
void lcddat(unsigned char dat)
{
	P2 = dat;
	rs = 1;
	rw = 0;
	en = 1;
	delay();
	en = 0;
}
void lcddis(unsigned char *s, unsigned char r)
{
	unsigned char w;
	for (w = 0; w < r; w++)
	{
		lcddat(s[w]);
		delay();
	}
}
void lcdconv(unsigned char num)
{
	unsigned char p,n;
	p = num/10;
	n = num%10;
	p = p+0x30;
	n = n+0x30;
	lcddat(p);
	lcddat(n);
}
void delay()
{
	unsigned int k,l;
	for (k=0;k<1000;k++);
	for (l=0;l<100;l++);
}