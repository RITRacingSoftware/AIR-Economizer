#! /bin/bash
# ./set_fuses.sh (upload port)
avrdude -c avrisp -p t85 -P $1 -b 19200 -U lfuse:w:0xe2:m
