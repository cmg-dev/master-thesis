#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// int fibonacci(int n)
// {
//     if (n < 3) return 1;
//     return fibonacci(n-1) + fibonacci(n-2);
// }
 
int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

//     int result = fibonacci(42);
    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 50;     /* 35000 Mikrosekunden = 35 Millisekunden */
    select(0, NULL, NULL, NULL, &tv);
    
    end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>
                             (end-start).count();
			     
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds << "s\n";

}