#include<reg51.h>

sbit in1=P2^0;
sbit in2=P2^1;
sbit en1=P2^2;
sbit en2=P2^3;
sbit in3=P2^4;
sbit in4=P2^5;
sbit flam_sens=P2^6;

void forward1();
void forward2();

void main()
{
	unsigned int j;
	if(flam_sens == 0)
	{
    en1=1;
    en2=1;
    for(j = 0;j<10;j++)
		{
        forward1();
        forward2();
    }
	}
}

void forward1()
{
    in1=1;
    in2=0;
}

void forward2()
{
    in3=1;
    in4=0;
}