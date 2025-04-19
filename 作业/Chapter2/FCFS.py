import matplotlib.pyplot as plt
import matplotlib.patches as patches

# 进程数据 (进程名, 执行时间, 到达时间)
processes = [("P1", 10, 0), ("P2", 1, 0), ("P3", 2, 0), ("P4", 1, 0), ("P5", 5, 0)]

# 按到达时间和输入顺序排序（FCFS）
sorted_processes = processes.copy()  # 本题中已按顺序到达

# 计算每个进程的开始和结束时间
current_time = 0
schedule = []
for p in sorted_processes:
    schedule.append((p[0], current_time, current_time + p[1]))
    current_time += p[1]

# 绘制甘特图
fig, ax = plt.subplots(figsize=(10, 2))
for idx, (name, start, end) in enumerate(schedule):
    ax.barh(y=0, width=end - start, left=start, height=0.5, align='center', label=name)
    ax.text((start + end)/2, 0, name, ha='center', va='center', color='white')
    ax.text(end, 0, f'{end}', ha='left', va='center')

ax.set_xlabel('Time (ms)')
ax.set_yticks([])
ax.set_title('FCFS Scheduling Gantt Chart')
plt.grid(axis='x')
plt.show()
