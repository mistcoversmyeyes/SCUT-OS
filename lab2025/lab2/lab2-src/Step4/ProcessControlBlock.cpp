#include "ProcessControlBlock.h"
#include <iostream>

// 构造函数实现
ProcessControlBlock::ProcessControlBlock(int name, int create_time, int running_time, std::string stat) :
    process_name(name),
    create_time(create_time),
    estimate_running_time(running_time),
    status(stat),
    next_block(nullptr) {}

// run方法实现
void ProcessControlBlock::run() {
    if (estimate_running_time > 0) {
        estimate_running_time--;
        std::cout << "Process " << process_name << " is running, remaining time: " << estimate_running_time << std::endl;
    }
    if (estimate_running_time == 0) {
        status = "C"; // Mark as Complete if time runs out
        std::cout << "Process " << process_name << " has completed." << std::endl;
    }
}

// Getter方法实现
int ProcessControlBlock::getProcessName() const { 
    return process_name; 
}

int ProcessControlBlock::getCreateTime() const { 
    return create_time; 
}

int ProcessControlBlock::getEstimateRunningTime() const { 
    return estimate_running_time; 
}

std::string ProcessControlBlock::getStatus() const { 
    return status; 
}

ProcessControlBlock* ProcessControlBlock::getNextBlock() const { 
    return next_block; 
}

// Setter方法实现
void ProcessControlBlock::setStatus(const std::string& new_status) { 
    status = new_status; 
}

void ProcessControlBlock::setNextBlock(ProcessControlBlock* next) { 
    next_block = next; 
}

// 析构函数实现
ProcessControlBlock::~ProcessControlBlock() {
    // std::cout << "ProcessControlBlock for process " << process_name << " is being destroyed." << std::endl;
}