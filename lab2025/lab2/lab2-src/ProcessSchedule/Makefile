# 编译器设置
CXX = g++ 

# 编译选项
CXXFLAGS = -std=c++11

# 源文件
SRCS = $(wildcard *.cpp)

# 目标可执行文件
TARGET = process_scheduler

# 设定Makefile 执行的主要命令
all : $(TARGET) run

run : $(TARGET)
	./$(TARGET)

# 编译所有但是不链接
compile_all_but_not_link : $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS)


# 构建规则
$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(CXXFLAGS)

# 清理规则
clean:  
	rm -f $(TARGET)

# 伪目标声明
.PHONY : clean all compile_all_but_not_link