#!/bin/bash
#Shellskript to let the work.c work 

rm -f rand_t.dat
echo
echo "Process startet, work.c will be executet 25 times"
echo "For 1, 2, 3, 4, 5 Seconds,"
echo "and for every Second for additional 0, 200, 400, 600, 800 Milliseconds"
echo "That are 85 Seconds of Waittime"
for i in {1..5};					
 do for j in {0..800..200};			
  do ./work $i $j >> rand_t.dat;	#write the Outcome from work into rand_t.dat
 done;
done;
echo
echo "Thanks for the waiting!"

gnuplot < stat1.gp;		#read the rand_t.dat and make the plot
#gnuplot < stat.gp;