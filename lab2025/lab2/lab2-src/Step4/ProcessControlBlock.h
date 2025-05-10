#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include <string>

class ProcessControlBlock {
private:
    int process_name;
    int create_time;
    int estimate_running_time;
    std::string status; // R: Ready, C: Complete, W: Wait
    ProcessControlBlock* next_block;

public:
    // 构造函数声明
    ProcessControlBlock(int name, int create_time, int running_time, std::string stat);
    
    // 方法声明
    void run();
    
    // Getter方法声明
    int getProcessName() const;
    int getCreateTime() const;
    int getEstimateRunningTime() const;
    std::string getStatus() const;
    ProcessControlBlock* getNextBlock() const;
    
    // Setter方法声明
    void setStatus(const std::string& new_status);
    void setNextBlock(ProcessControlBlock* next);
    
    // 析构函数声明
    ~ProcessControlBlock();
};

#endif // PROCESSCONTROLBLOCK_H
