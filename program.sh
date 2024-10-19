#! /bin/bash

# ./program.sh (upload port)

# Fuses for ATtiny85: avrdude -c avrisp -p t85 -P $4 -b 19200 -U lfuse:w:0xe1:m

freq=8000000

avr-gcc -c -std=gnu99 -Os -Wall -ffunction-sections -fdata-sections -mmcu=attiny85 -DF_CPU=$freq economizer.c -o economizer.o
avr-gcc -Os -mmcu=attiny85 -ffunction-sections -fdata-sections -Wl,--gc-sections economizer.o -o economizer.elf
avr-objcopy -O ihex -R .eeprom economizer.elf economizer.ihex

# Terminate open screen sessions for uploading
screen -X "quit";

read -p "Press enter to upload"
echo "Uploading for ATtiny85"
avrdude -c avrisp -p t85 -P $1 -b 19200 -U flash:w:economizer.ihex


