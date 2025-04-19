from collections import deque
import matplotlib.pyplot as plt
import matplotlib.patches as patches

processes = [("P1", 10, 0), ("P2", 1, 0), ("P3", 2, 0), ("P4", 1, 0), ("P5", 5, 0)]

# 初始化队列和剩余时间
queue = deque(processes)
time_quantum = 1
current_time = 0
schedule_rr = []
remaining_time = {p[0]: p[1] for p in processes}

# 模拟RR调度
while queue:
    p = queue.popleft()
    name, duration, _ = p
    if remaining_time[name] > 0:
        run_time = min(time_quantum, remaining_time[name])
        schedule_rr.append((name, current_time, current_time + run_time))
        remaining_time[name] -= run_time
        current_time += run_time
        if remaining_time[name] > 0:
            queue.append(p)

# 绘制甘特图（需处理重叠片段）
fig, ax = plt.subplots(figsize=(15, 2))
colors = {'P1': 'tab:blue', 'P2': 'tab:orange', 'P3': 'tab:green', 'P4': 'tab:red', 'P5': 'tab:purple'}
for idx, (name, start, end) in enumerate(schedule_rr):
    ax.barh(y=0, width=end - start, left=start, height=0.5, color=colors[name], edgecolor='black')
    ax.text((start + end)/2, 0, name, ha='center', va='center', color='white')
    ax.text(end, 0, f'{end}', ha='left', va='center')

ax.set_xlabel('Time (ms)')
ax.set_yticks([])
ax.set_title('RR Scheduling Gantt Chart (Time Quantum=1)')
plt.grid(axis='x')
plt.show()
