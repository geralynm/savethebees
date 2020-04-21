OBJS = kiss_fft.o kiss_fftr.o hive_process.o

KISS_DIR = ../kiss_fft130
KISS_TOOL_DIR = $(KISS_DIR)/tools

INCDIRS = -I$(KISS_DIR) -I$(KISS_TOOL_DIR)

hive_process: $(OBJS)
	$(CC) $(INCDIRS) $(OBJS) -o hive_process -lm

hive_process.o: hive_process.c
	$(CC) -c $(INCDIRS) $< -o $@

kiss_fftr.o: $(KISS_TOOL_DIR)/kiss_fftr.c
	$(CC) -c $(INCDIRS) $< -o $@

kiss_fft.o: $(KISS_DIR)/kiss_fft.c
	$(CC) -c $(INCDIRS) $< -o $@

clean:
	rm -f hive_process $(OBJS)
