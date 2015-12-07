#!/bin/bash

for FILE in ./*.csv
do
	uniq -w 3 $FILE | sed "2d" > $FILE"new"
done
