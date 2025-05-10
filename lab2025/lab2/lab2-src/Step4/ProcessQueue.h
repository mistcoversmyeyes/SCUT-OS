#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include "ProcessControlBlock.h"
#include <iostream> // 确保包含 visualize_queue 所需的 iostream

class ProcessQueue
{
private:
    ProcessControlBlock* front;
    ProcessControlBlock* back;
    int size;

public:
    ProcessQueue(){}

    bool is_empty(){ return size == 0; } // 修正了 is_empty 的逻辑


    // 入队
    void enqueue(ProcessControlBlock* blockNode);

    // 出队
    ProcessControlBlock* dequeue();

    // 查看队列顶端元素
    ProcessControlBlock* peek();

    // 打印整个队列
    void visualize_queue();


    ~ProcessQueue(){}
};

// 构造函数和析构函数的实现应该在 .cpp 文件中，或者如果非常简单，可以内联在头文件中，
// 但为了保持一致性，最好将 ProcessQueue() 和 ~ProcessQueue() 的实现移到 ProcessQueue.cpp
// 如果你还没有 ProcessQueue.cpp，那么可以暂时保留它们在头文件中，但要注意这可能导致链接错误，如果这个头文件被多个 .cpp 文件包含。
// 假设你已经将实现移到了 .cpp 文件中。

#endif // PROCESSQUEUE_H
