#!/bin/bash

for FILE in *.csv
do
	awk '!A[$1]++' $FILE > newoutput/$FILE
done
