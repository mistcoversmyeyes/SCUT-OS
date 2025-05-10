#include "ProcessScheduleController.h"
#include "ProcessControlBlock.h"
#include <iostream>
#include <vector>

int main() {
    // 1. 创建进程调度控制器实例
    ProcessScheduleController scheduler;

    // 2. 创建 ProcessControlBlock 实例
    // ProcessControlBlock(int name, int create_time, int running_time, std::string stat)
    // 假设初始状态为 "R" (Ready)
    std::vector<ProcessControlBlock*> processes;
    processes.push_back(new ProcessControlBlock(1, 0, 5, "R"));
    processes.push_back(new ProcessControlBlock(2, 1, 3, "R"));
    processes.push_back(new ProcessControlBlock(3, 2, 4, "R"));
    processes.push_back(new ProcessControlBlock(4, 3, 2, "R"));

    // 3. 将进程添加到调度器
    for (ProcessControlBlock* pcb : processes) {
        scheduler.addProcess(pcb);
    }

    // 4. 启动调度模拟
    std::cout << "开始时间片轮转调度模拟..." << std::endl;
    scheduler.startSchedule();
    std::cout << "调度模拟结束。" << std::endl;

    // 5. 清理动态分配的 ProcessControlBlock 对象
    // 由于 ProcessQueue 和 ProcessScheduleController 不负责删除这些对象，
    // main 函数作为创建者，需要负责释放它们。
    for (ProcessControlBlock* pcb : processes) {
        delete pcb;
    }
    processes.clear();

    return 0;
}