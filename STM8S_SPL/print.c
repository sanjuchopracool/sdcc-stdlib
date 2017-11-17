#include "serial.h"
#include "print.h"
#include "common.h"

char charFromHex(unsigned char num)
{
    char ch = '0';
    if(num < 10)
        return ch + num ;
    switch(num)
    {
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    default:
        return 0;
    }
}

void sendString(const char *msg)
{
    while(*msg!='\0')
    {
        putchar(*msg);
        msg++;
    }
}

void sendBuffer(const char *msg,uint16_t num)
{
    int i = 0;
    while(i < num)
        putchar(msg[i++]);

}

void printInt(int32_t n, unsigned char base)
{
    char buffer[11] = {0};
    char i = 9;

    if( n < 0)
    {
        putchar('-');
        n = -n;
    }

    switch(base)
    {
    case 16:
        sendString("0x");
        break;
    default:
        break;
    }

    if(n == 0)
        putchar('0');

    while(n)
    {
        buffer[i--] = charFromHex(n % base);
        n /= base;
    }
    sendString(&buffer[i + 1]);
}

void printf(char* format,...)
{
    va_list ap;	/* points to each unnamed arg in turn */
    char *p,*sval;
    int32_t ival;

    va_start(ap,format);	/* make ap point to 1st unnamed arg */

    for(p=format;*p;p++)
    {
        if(*p != '%')
        {
            putchar(*p);
            continue;
        }

        switch(*++p)
        {
        case 'd':
            ival = va_arg(ap,int32_t);
            printInt(ival, 10);
            break;
        case 'X':
        case 'x':
            ival = va_arg(ap,int32_t);
            printInt(ival, 16);
            break;
        case 's':
            for(sval = va_arg(ap,char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            putchar(ival);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);	/* clean up when done */
}
