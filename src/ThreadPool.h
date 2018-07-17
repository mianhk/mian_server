#pragma once
#include "RequestData.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

const int THREADPOOL_INVALID = -1;
const int THREADPOOL_LOCK_FAILURE = -2;
const int THREADPOOL_QUEUE_FULL = -3;
const int THREADPOOL_SHUTDOWN = -4;
const int THREADPOOL_THREAD_FAILURE = -5;
const int THREADPOOL_GRACEFUL = 1;

const int MAX_THREADS = 1024; //限制的最大线程数
const int MAX_QUEUE = 65535;  //限制的队列最大长度

typedef enum
{
    immediate_shutdown = 1,
    graceful_shutdown = 2
} threadpool_shutdown_t;

struct ThreadPoolTask
{
    std::function<void(std::shared_ptr<void>)> fun;
    std::shared_ptr<void> args;
};

void my_handler(std::shared_ptr<void> req);
class ThreadPool
{
  private:
    static pthread_mutex_t lock;
    static pthread_cond_t notify;
    static std::vector<pthread_t> threads;
    static std::vector<ThreadPoolTask> queue;
    static int thread_count;
    static int queue_size;
    static int head;
    // tail 指向尾节点的下一节点
    static int tail;
    static int count;
    static int shutdown;
    static int started;

  public:
    static int threadpool_create(int _thread_count, int _queue_size);
    static int threadpool_add(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> fun = my_handler);
    static int threadpool_destroy();
    static int threadpool_free();
    static void *threadpool_thread(void *args);
};
