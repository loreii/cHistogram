Intro
======

This utility written in C, permit to display a distribution graph
on terminal, the input MUST be provided as integer once for line. 
The utility permit to do a cat from logs (ie. containings execution time) and generate a terminal 
timing rapresentation as example. It's a real quick and dirty solution 
you will probably look for R for some more advanced statistical solution. 
But for a quick term solution is not so bad.

     while true;
       echo "         TITLE GRAPH          "
       do tail -n 100 PMS.log|grep Logic|grep -v WSDL|awk 'BEGIN { FS = ";" } ; { print $6 }'|a,out
      sleep 10
     done

First column rapresent the hit rate for the first interval, ie 0-1000, on the left is display a recup for each interval.

      a.out [column_rage] [x_size] [y_size]

      lore@ReApEr:~/workspace/c/distribution/chistogram$ cat in.txt | a.out 1000 45 |tail -n 51

