#include <string>

class ProcessControlBlock {
private:
    int process_name;
    ProcessControlBlock* next_block;
    int creat_time;
    int estimate_running_time;
    std::string status;

public:
    // 构造函数
    ProcessControlBlock() 
        : process_name(0), next_block(nullptr), creat_time(0), 
          estimate_running_time(0), status("") {}

    ProcessControlBlock(int name, int create_time, int running_time, std::string stat)
        : process_name(name), creat_time(create_time), 
          estimate_running_time(running_time), status(stat), next_block(nullptr) {}

    // Getters
    int getProcessName() const { return process_name; }
    ProcessControlBlock* getNextBlock() const { return next_block; }
    int getCreateTime() const { return creat_time; }
    int getEstimateRunningTime() const { return estimate_running_time; }
    std::string getStatus() const { return status; }

    // Setters
    void setProcessName(int name) { process_name = name; }
    void setNextBlock(ProcessControlBlock* next) { next_block = next; }
    void setCreateTime(int time) { creat_time = time; }
    void setEstimateRunningTime(int time) { estimate_running_time = time; }
    void setStatus(const std::string& stat) { status = stat; }

    // 析构函数
    ~ProcessControlBlock() {
        // 如果 next_block 是动态分配的，需在此释放（根据实际需求决定）
        // delete next_block; 
    }
};
