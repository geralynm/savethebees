//temperature and humidity processing program
//reads temp and humidity from csv and compares to thresholds.  
//adds columns to CSV with appropriate flags (ok, hi, low)

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

#define HUMIDITY_LOW 4500
#define HUMIDITY_HIGH 6500
#define TEMP_LOW 9300
#define TEMP_HIGH 9600

#define OK_FLAG 0
#define LOW_FLAG 1
#define HIGH_FLAG 2

#define OFFSET 27

struct hivedata{
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t hour;
	uint32_t minute;
	uint32_t humidity;
	uint32_t temperature;
	uint8_t humidity_flag;
	uint8_t temperature_flag;
};

int main (int argc, char** argv) {
	FILE* fp;
	struct hivedata hive;
	fp = fopen("hivedata.txt", "a+b");
	if (!fp) {
     printf("error opening file\n");
     exit(1);
    }
    
    fseek(fp, -OFFSET, SEEK_END);
    fscanf(fp, "%04d-%02d-%02d %02d:%02d ", &hive.year, &hive.month, &hive.day, &hive.hour, &hive.minute);
    fscanf(fp, "%d %d", &hive.humidity, &hive.temperature);
    
    printf("humidity read: %d\n", hive.humidity);
    printf("temp read: %d\n", hive.temperature);
	
	//this block writes the next entry in the file, which should be humidity flag.
	fseek(fp, 0, SEEK_END);
	if(hive.humidity > HUMIDITY_HIGH) {
		fprintf(fp, " %d ", HIGH_FLAG);
	}
	else if (hive.humidity < HUMIDITY_LOW) {
		fprintf(fp, " %d ", LOW_FLAG);
	}
	else {
		fprintf(fp, " %d ", OK_FLAG);
	}
	
	//this block writes the next entry in the file, which should be temperature flag.
	if(hive.temperature > TEMP_HIGH) {
		fprintf(fp, "%d ", HIGH_FLAG);
	}
	else if (hive.temperature < TEMP_LOW) {
		fprintf(fp, "%d ", LOW_FLAG);
	}
	else {
		fprintf(fp, "%d ", OK_FLAG);
	}


	fclose(fp);
	return 0;
}
