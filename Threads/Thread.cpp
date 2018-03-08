#include <iostream>
#include <vector>
#include <thread>

#define MAX_NUM_OF_THREADS      2
#define MAX_PRINT_LIMIT         10

typedef uint32_t uint32;

std::mutex mtx;
uint32 NumberLimit;

void Thread1 (int arg)
{
    // std::cout << "Thread In " << arg << std::endl;
    while(NumberLimit < MAX_PRINT_LIMIT)
    {
        mtx.lock();
        if(NumberLimit < MAX_PRINT_LIMIT)
        {
            NumberLimit++; 
        }
        std::cout << "Thread ID : " 
                  << arg << " Num : "
                  << NumberLimit << std::endl;
        mtx.unlock();
    }
    // std::cout << "Thread " << arg << " exiting" << std::endl;
} // Thread1

void Do_Join(std::thread &t)
{
    t.join();
}

int main(int argc, char *argv[])
{
    uint32 NumOfThread;

    std::cout << "Hello! " << argc << std::endl;
    if(argc == 2)
    {
      try
      {
          NumOfThread = std::stoi(argv[1]);
          std::cout << "Conv done" << std::endl;
      }
      catch(const std::exception & e)
      {
          std::cout << "Exception Caught! " << e.what() << std::endl;
          NumOfThread = MAX_NUM_OF_THREADS;
      }
    }
    else
    {
        NumOfThread = MAX_NUM_OF_THREADS;
    }
    
    std::vector<std::thread> Threads;
    Threads.resize(NumOfThread);
    for(uint32 i = 0; i < Threads.size(); i++)
    {
        Threads[i] = std::thread(Thread1, i);
    }
    
    std::for_each(Threads.begin(), Threads.end(), [](std::thread &t){t.join();}/*Do_Join*/);
    std::cout << "All Threads joined" << std::endl;
    return 0;
}
