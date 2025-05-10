#include "ProcessQueue.h"
#include <iostream>

void ProcessQueue::enqueue(ProcessControlBlock* blockNode){
    // 确保新节点的next指针为空
    blockNode->setNextBlock(nullptr);
    
    // 如果队列为空，front和back都指向新节点
    if (is_empty()) {
        front = blockNode;
        back = blockNode;
    } else {
        // 队列不为空，将当前back的next指向新节点，然后更新back
        back->setNextBlock(blockNode);
        back = blockNode;
    }
    
    size++;
}

ProcessControlBlock* ProcessQueue::dequeue(){
    if (is_empty()) {
        return nullptr;
    }
    
    // 保存当前front节点作为返回值
    ProcessControlBlock* result = front;
    
    // 更新front为下一个节点
    front = front->getNextBlock();
    
    // 如果队列变为空，也需要更新back指针
    if (front == nullptr) {
        back = nullptr;
    }
    
    size--;
    
    // 断开result与队列的连接
    result->setNextBlock(nullptr);
    return result;
}

ProcessControlBlock* ProcessQueue::peek(){
    return front;
}

void ProcessQueue::visualize_queue(){
    // 遍历并打印队列中的所有进程
    ProcessControlBlock* current = front;
    std::cout << "Queue contents (size " << size << "):" << std::endl;
    
    while (current != nullptr) {
        std::cout << "Process " << current->getProcessName() 
                  << ", Status: " << current->getStatus()
                  << ", Remaining time: " << current->getEstimateRunningTime() 
                  << std::endl;
        current = current->getNextBlock();
    }
    
    if (is_empty()) {
        std::cout << "Queue is empty" << std::endl;
    }
}