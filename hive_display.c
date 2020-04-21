//file to display information gathered from hive.
//takes the most recent content written to hivedata.txt and 
//prints a formatted version to command line.

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
	uint8_t bee_flags[4];
};

int main(int argc, char** argv) {
	FILE *fp;
	fp = fopen("hivedata.txt", "r");
	struct hivedata hive;
	fseek(fp, -(sizeof(hive)+11), SEEK_END);
	fscanf(fp, "%04d-%02d-%02d %02d:%02d ", &hive.year, &hive.month, &hive.day, &hive.hour, &hive.minute);
	fscanf(fp, "%04d %04d %d %d", &hive.humidity, &hive.temperature, &hive.humidity_flag, &hive.temperature_flag);
	fscanf(fp, "%d %d %d %d", &hive.bee_flags[0], &hive.bee_flags[1], &hive.bee_flags[2], &hive.bee_flags[3]);
	
	hive.year = hive.year + 1900;
	hive.month = hive.month + 1;
	printf("Date of sample: %02d/%02d/%04d\n", hive.month, hive.day, hive.year);
	printf("Time of sample: %04d:%02d\n", hive.hour, hive.minute);
	
	printf("Hive Humidity: %d percent\n", hive.humidity);
	printf("Hive Temperature: %.2f F \n", (float)hive.temperature);
	
	switch(hive.humidity_flag) {
		case 0:
			printf("Humidity of the hive is healthy!\n");
			break;
		case 1: 
			printf("Humidity in your hive is low.  Check honey supers in coming weeks.\n");
			break;
		case 2: 
			printf("Humidity in your hive is high.  May be risk of condensation inside the hive - inspect!\n");
			break;
	}
	switch(hive.temperature_flag) {
		case 0:
			printf("Temperature in the hive is healthy!\n");
			break;
		case 1:
			printf("Temperature in the hive is low.  Brood may not be developing properly, check for DWV\n");
			break;
		case 2:
			printf("Temperature in the hive is too high.  Check for proper air flow.\n");
			break;
	}
	switch(hive.bee_flags[0]) {
		case 0:
			printf("Healthy relative population of youngest bees.\n");
			break;
		case 1: 
			printf("Population of nurse bees is low.  Potential swarm within the next week.\n");
			break;
		case 2:
			printf("Population high.  Monitor health of brood to prevent DWV.\n");
			break;
	}
	switch(hive.bee_flags[1]) {
		case 0:
			printf("Healthy relative population of young bees.\n");
			break;
		case 1: 
			printf("Population low.  Check for DWV or other pests.\n");
			break;
		case 2:
			printf("Population high.  Your hive may be growing!\n");
			break;
	}
	switch(hive.bee_flags[2]) {
		case 0:
			printf("Healthy relative population of adult bees.\n");
			break;
		case 1: 
			printf("Population low.  Check for DWV or other pests\n");
			break;
		case 2:
			printf("Population high.  Ensure queen maintains healthy laying pattern.\n");
			break;
	}
	switch(hive.bee_flags[3]) {
		case 0:
			printf("Queen not detected in hive.  Monitor hive closely.\n");
			break;
		case 1: 
			printf("Queen detected in hive!\n");
			break;
	}
	
}
