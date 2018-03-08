#include <iostream>
#include <thread>
#include <vector>

#define MAX_THREADS       2
#define MAX_LIMIT         10

typedef uint32_t uint32

class ThreadExample
{
  public:

    ThreadExample(std::string ThreadName,\
                  uint32 MaxLimit = MAX_LIMIT, \
                  uint32 MaxThreads = MAX_THREADS);
    
    ~ThreadExample();

    void Start();

  protected:

  private:

    std::string   mInstanceName;

    uint32        mMaxLimit;

    uint32        mMaxThreads;

    std::vector<std::thread> mThreads;
};

ThreadExample::ThreadExample(std::string ThreadName,\
    uint32 MaxLimit, uint32 MaxThreads)
  :mInstanceName(ThreadName),
  mMaxLimit(MaxLimit),
  mMaxThreads(MaxThreads)
{
    mThreads.resize(mMaxLimit);

} // ThreadExample
