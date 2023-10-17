# PthreadSubString
This program creates multiple threads using the pthread library that all search through an assigned section in a string (s1) to find the number of substrings that match s2.



# Logic
This is done by first reading in the file with the readf() function. Once the data for s1 and s2 (and n1 and n2) is received, 20 threads are created that run the function calSubStringThread(). 

This results in each thread calculating the number of substrings they find in a specific section of s1, with the function num_stubstring(). This function divides the work of the search onto different threads. This is done by creating the parameters of startpos and endpos , which are ints. These int variables keep track of where each thread should start and end their search in a loop, which is dependent on the thread number (thread id). Therefore, each thread will search a different part of s1 concurrently. This allows all 20 threads to have their own equal section to search. If a thread finds a match in its section, (when count == n2) the total substrings found for that thread is incremented. 

Finally, the total substrings found in each thread are added onto the final total number of substrings through countArray in a loop. The number of substrings found in each thread is printed, along with the total number of substrings. The total number of substrings found in the parallel program is equal to the number found in the serial program.




