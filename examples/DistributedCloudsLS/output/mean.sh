#!/bin/bash

sum=$(ls -l *.csvnew | wc -l)
paste -d" " *.csvnew | nawk -v s="$sum" '{
    for(i=0;i<=s-1;i++)
    {
        t1 = 2+(i*9)
        temp1 = temp1 + $t1
    }
    print $1" "temp1/s"  "
temp1=0
temp2=0
temp3=0
}'
