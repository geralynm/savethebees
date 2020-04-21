//temperature and humidity collection program
//This program reads signals from the temperature and humidity sensor
//and writes them to a CSV file to later be read by the processing program.

#include <stdio.h>
#include <stdlib.h>
 #include <errno.h>
 #include <stdint.h>
 #include <string.h>
 #include <sys/mman.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <math.h>
 #include <sys/time.h>
 #include <time.h>

#include "pi_dht_read.h"
#include "pi_mmio.h"

int main (int argc, char** argv) {
	FILE* fp;
	time_t m_time = time(NULL);
	struct tm *timestamp;
	timestamp = localtime(&m_time);
	int type = 11;
	float temperature_float = 0;
	float humidity_float = 0;
	printf("DHT read return: %d\n", pi_dht_read(type, 4, &humidity_float, &temperature_float));
	fp = fopen("hivedata.txt", "a+");
	if (!fp) {
     printf("error opening file\n");
     exit(1);
    }
    //convert to fahrenheit and multiply by 100
    int temperature = (int)(100*((temperature_float*9/5)+32));
    int humidity = (int) (humidity_float*100);
    
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%04d-%02d-%02d %02d:%02d ", timestamp->tm_year, timestamp->tm_mon, timestamp->tm_mday, timestamp->tm_hour, timestamp->tm_min);
    fprintf(fp, "%04d %04d", humidity, temperature);
    
	fclose(fp);
	return 0;
}
