# Answers to HW
## Ref [link|http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf]

1. Run `process-run.py` with `-l 5:100,5:100`. What should CPU utilization be?
100%. The cpu has 5 tasks that are scheduled to run at 100% of cpu, and then 5 more tasks that are scheduled at 100% of cpu.
2. `process-run.py -l 4:100,1:0` flags specified mean 4 instructions that all use 100% cpu, and 1 instruction that issues I/O. How long does it take to complete both processes? 
5 instructions are ran in total, the first 4 successively uses 100% cpu,
in terms of processes:
p0 = 4active -> all done
p1 = 1 active ->(initiate IO)  
     4 inactive (wait) 
     1 active->Done
3. Switch the order to `-l 1:0,4:100`. What happens? Does order matter? 
Yes. This means that there are fewer states for the process stack. 
```
time pid: 0 pid: 1 cpu ios
1   RUN:IO  READY   1   
2   WAITING RUN:CPU 1   1
3   WAITING RUN:CPU 1   1
4   WAITING RUN:CPU 1   1
5   WAITING RUN:CPU 1   1
6   DONE    DONE         
```
4.Run the same process but with switching behavior set st we dont switch when doing IO
```
time pid: 0   pid: 1    cpu ios
1    RUN:IO   WAIT      1    
2    WAIT     WAIT          1
3    WAIT     WAIT          1
4    WAIT     WAIT          1
5    DONE     READY         1
6    DONE     RUN:CPU    1
7    DONE     RUN:CPU    1
8    DONE     RUN:CPU    1
9    DONE     RUN:CPU    1
```

5.  run the same process but `-l 1:0,4:100 -c -S SWITCH_ON_IO`
This will be the same as #3. We block the process and let the CPU do other work before the process is ready to be in a done state, when IO is finished. 

6. Run `process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO _I IO_RUN_LATER -c -p `. Is this an efficient use of resources? 
No because if we have 3 IO cycles to keep track of in the first process, this means that instead of returning the blocked process when IO is done to do the rest of the IO work (2 at this point). 
We end up running the next process pid=2, and RUN:CPU for 5 straight cycles, then the next process pid=3 does the same thing. Eventually the CPU is freed and goes back to first proc, pid=0, and then finally does the next IO task. Now it gets a bit hairy, cause this means that we have to spend cycles in wait state until the next IO operation, which repeats the cycle one last time(n=3). 

Overall we could be doing much better. Running the actual flags produces this result with an overall 27 cycles, 18 of those cycles where the CPU was busy (66.67%), and 12 on IO business (44.44%).

7. Run the same process but with `-I IO_RUN_IMMEDIATE`
This addresses the problem described above. CPU should be always busy! IO_RUN_IMMEDIATE will make 100% of CPU running, but IO is still same percentage. 

8. Now run random stuff like `-s l -l 3:50,3:50  and -s 2 -1 3:50,3:50 or -s 3 -l 3:50,3:50`
    a. `-s l -l 3:50,3:50` 
        This will have half chance in io or cpu:run. If IO_RUN_IMMEDIATE we efficiently use the cpu and keep it busy during IO blocking and return to the original . Run later will alternate because both have 3 cycles that require 50/50 IO and CPU:RUN split.  
    b. `-s 2 -1 3:50,3:50`  
