# Phone-Line-Simulator
This program simulates a number of callers waiting for an available line, eventually speaking to an operator, and then
buying a ticket and hanging up. The number of callers is input by the user into argv.
The name of the executable is "tonightShow".
Larger numbers of callers will take longer. The max number of callers is 240.
If the line is busy, the thread will wait 1 second before trying again.
It will also wait 1 second while buying the ticket.
The program uses both binary and counting semaphores. 
