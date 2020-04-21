#!/bin/bash

arecord -d 5 -f S16_LE -t wav -D hw:1,0 -c 1 -r 44100 bees.wav
./th_collect
./hive_process
