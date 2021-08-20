#include<reg51.h>
#define lcd P3
 
sbit FLAME=P1^0;
 
sbit rs=P2^0; //register select
sbit rw=P2^1; //RW
sbit en=P2^2; //enable
 
void lcd_init();
void lcdcmd(unsigned char);
void dat(unsigned char);
void delay();
void lcd_string(char *s);
 
void main()
{
    lcd_init();
    lcd_string("  Flame Sensor   ");
    while(1) {
        if(FLAME == 0) {
            lcdcmd(0xc0);
            lcd_string("Flame Detected");
            delay();
        } else {
            lcdcmd(0xc0);
            lcd_string("                ");
        }
    }
}
 
void lcd_init()
{
    lcdcmd(0x38);
    lcdcmd(0x0e);
    lcdcmd(0x06);
    lcdcmd(0x01);
    lcdcmd(0x80);
}
 
void lcdcmd(unsigned char a)
{
    lcd=a;
    rs=0;
    rw=0;
    en=1;
    delay();
    en=0;
}
 
void dat(unsigned char b)
{
    lcd=b;
    rs=1;
    rw=0;
    en=1;
    delay();
    en=0;
}
 
void lcd_string(char *s)
{
    while(*s) {
       dat(*s++);
     }
}
 
void delay()
{
    unsigned int i;
    for(i=0;i<20000;i++);
}