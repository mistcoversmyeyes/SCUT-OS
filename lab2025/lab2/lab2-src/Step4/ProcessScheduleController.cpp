#include "ProcessScheduleController.h"

ProcessScheduleController::ProcessScheduleController() {
    // 构造函数
}

void ProcessScheduleController::addProcess(ProcessControlBlock* pcb) { // 新增方法实现
    if (pcb) {
        this->scheduleQueue.enqueue(pcb);
    }
}

void ProcessScheduleController::popAndRun (){
    ProcessControlBlock* curProcess = this->scheduleQueue.dequeue();
    if (!curProcess) return; // 检查空指针
    curProcess->run();
    if (curProcess->getEstimateRunningTime() > 0){
        this->scheduleQueue.enqueue(curProcess);
    }
    else{
        curProcess->setStatus("C"); // 标记为完成
        // 注意：这里没有 delete curProcess，因为它的所有权在 main 函数中
    }
}

bool ProcessScheduleController::haveProcess(){
    return !this->scheduleQueue.is_empty();
}

void ProcessScheduleController::startSchedule(){
    size_t round = 0;
    while (haveProcess()){
        round++;
        std::cout << "时间片" << round << ":" << std::endl;
        std:: cout << "运行前:" << std::endl;
        this->scheduleQueue.visualize_queue();
        popAndRun();
        std:: cout << "运行后:" << std::endl; 
        this->scheduleQueue.visualize_queue();
    }
}

ProcessScheduleController::~ProcessScheduleController() {
    // 析构函数
}