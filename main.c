#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>//For struct itimerval
#include <sys/signal.h>// for signal Interruption
#include <errno.h>
#include "MCP9808.h"//Capacitive Sensor
//-------------Capacitive Buttons variables---------------//
const char* I2CDEV = "/dev/i2c-1"; //i2c-1 pour Raspberry
struct mcp9808 temp_sensor;

//------------Capacitive Buttons function----------//New Add
#define ERREXIT(str) {printf("err %s, %s\n", str, strerror(errno)); return -1;}
#define die_if(a, msg) do { do_die_if( a , msg, __LINE__); } while(0);
void do_die_if(int b, char* msg, int line)
{
	if(!b)
		return;
	fprintf(stderr, "Error at line %d: %s\n", line, msg);
	fprintf(stderr, "sysmsg: %s\n", strerror(errno));
	exit(1);
}

static int write_to_mcp9808(struct mcp9808 *e, int addr, char data )
{
	int i;
	for(i=0 ; i<16; i++)
	{
		fflush(stdout);
		die_if(mcp9808_write_byte(e, addr, data), "write error");
                addr++;
	}
	fprintf(stderr, "\n\n");
	return 0;
}


static int read_from_mcp9808(struct mcp9808 *e, int addr, int size, int *buf)
{
	int i;
	
	for(i = 0; i < size; ++i, ++addr)
	{
		(*buf) = mcp9808_read_byte(e, addr);
		buf++;
	}
	return 0;
}

 

int main()
{
  while (mcp9808_open(I2CDEV, MCP9808_ADR, &temp_sensor));
  printf ("Device checked with sucess!!!\n");
 

   while (1)
  {        
    float t = mcp9808_read_temperature(&temp_sensor);
    printf("temperature in celsius: %0.2f\n", t);
    sleep(2);      
  }

}

