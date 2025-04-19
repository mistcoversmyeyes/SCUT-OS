import matplotlib.pyplot as plt
from collections import deque

# 作业数据（作业名，到达时间，运行时间）
jobs = [
    ("A", 0, 8),
    ("B", 1, 4),
    ("C", 2, 10),
    ("D", 5, 2),
    ("E", 6, 3)
]
time_quantum = 4

# 初始化队列和剩余时间
queue = deque()
remaining_time = {job[0]: job[2] for job in jobs}
schedule = []
current_time = 0
next_job_idx = 0  # 用于按到达时间顺序添加作业

# 模拟时间片轮转调度
while True:
    # 将已到达的作业加入队列
    while next_job_idx < len(jobs) and jobs[next_job_idx][1] <= current_time:
        job = jobs[next_job_idx]
        queue.append(job[0])
        next_job_idx += 1

    if not queue:
        if next_job_idx >= len(jobs):
            break  # 所有作业处理完成
        else:
            current_time = jobs[next_job_idx][1]  # 快进到下一个作业到达时间
            continue

    current_job = queue.popleft()
    run_time = min(remaining_time[current_job], time_quantum)
    start_time = current_time
    end_time = current_time + run_time
    schedule.append((current_job, start_time, end_time))
    remaining_time[current_job] -= run_time
    current_time = end_time

    # 将未完成的作业重新加入队列
    if remaining_time[current_job] > 0:
        queue.append(current_job)

# 计算周转时间
completion_time = {}
for job in jobs:
    name = job[0]
    # 找到作业的最后结束时间
    for seg in reversed(schedule):
        if seg[0] == name:
            completion_time[name] = seg[2]
            break

turnaround_time = {name: completion_time[name] - job[1] for job in jobs for name in [job[0]]}
avg_turnaround = sum(turnaround_time.values()) / len(turnaround_time)

# 绘制甘特图
fig, ax = plt.subplots(figsize=(10, 3))
colors = {'A': 'tab:blue', 'B': 'tab:orange', 'C': 'tab:green', 'D': 'tab:red', 'E': 'tab:purple'}

for seg in schedule:
    name, start, end = seg
    ax.barh(y=0, width=end - start, left=start, height=0.5, color=colors[name], edgecolor='black')
    ax.text((start + end)/2, 0, name, ha='center', va='center', color='white')
    ax.text(end, 0, f'{end}', ha='left', va='center', fontsize=8)

ax.set_xlabel('Time (ms)')
ax.set_yticks([])
ax.set_title(f'RR Scheduling Gantt Chart (Quantum=4)\nAverage Turnaround Time = {avg_turnaround:.1f}')
plt.grid(axis='x')
plt.show()
