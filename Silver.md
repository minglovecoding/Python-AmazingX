## 🧠 一、算法与思维基础

| 模块                  | 主要内容                                                     | 典型题型                                  |
| --------------------- | ------------------------------------------------------------ | ----------------------------------------- |
| **前缀和 / 差分**     | 一维、二维前缀和，快速求区间和；差分数组处理区间更新         | “Sleepy Cow Sorting”, “Counting Haybales” |
| **二分查找**          | 在有序数组中找边界、最值问题；“答案二分”（binary search on answer） | “Convention”, “Angry Cows”                |
| **双指针 / 滑动窗口** | 连续区间内满足条件的统计、最优子区间                         | “Diamond Collector”, “Subarray Sums II”   |
| **排序与离散化**      | 离散化坐标或数值后配合数组/树状数组使用                      | “Meetings”, “Haybale Stacking”            |
| **枚举 + 贪心思想**   | 贪心排队、最小花费、区间调度等                               | “Convention II”, “Stuck in a Rut”         |

------

## 🌲 二、图论与搜索

| 模块                                  | 主要内容                         | 典型题型                                     |
| ------------------------------------- | -------------------------------- | -------------------------------------------- |
| **DFS / BFS**                         | 树或图的连通块、最短路、模拟移动 | “Maze”, “Closing the Farm”, “Counting Rooms” |
| **Flood Fill / Connected Components** | 类似 DFS/BFS 的区域染色          | “MooTube”, “Where’s Bessie?”                 |
| **拓扑排序 / 有向图关系**             | 顺序依赖关系、优先队列拓扑       | “Milk Order”, “Factory”                      |
| **最短路 (Dijkstra)**                 | 带权图求最短路（部分金组边缘题） | “Pump Planning”                              |
| **Union-Find（并查集）**              | 判连通性、合并集合               | “Closing the Farm”, “MooTube”                |

------

## 📊 三、数据结构与技巧

| 模块                                | 主要内容                             | 典型题型                            |
| ----------------------------------- | ------------------------------------ | ----------------------------------- |
| **映射与计数 (map, unordered_map)** | 频率统计、差分、前缀出现次数         | “Subarray Sums II”                  |
| **优先队列 (heap)**                 | 按优先级动态取最大/最小元素          | “Convention II”, “Rental Service”   |
| **树状数组 / BIT**                  | 区间求和与单点修改（部分银题有涉及） | “Sleepy Cow Sorting” 进阶版         |
| **队列 / 栈应用**                   | BFS 队列、单调栈（少见）             | “Cowntagion”, “Rectangular Pasture” |

------

## 🧩 四、模拟与实现

| 类型                                                  | 内容 |
| ----------------------------------------------------- | ---- |
| **字符串模拟**：简单模式匹配、状态机式移动。          |      |
| **矩阵与方向模拟**：如农场移动、奶牛行走（R/L/U/D）。 |      |
| **事件排序模拟**：先排序后逐步模拟时间线。            |      |

------

## ⏱ 五、复杂度与优化

- 通常要求 **O(N log N)** 或更优；
- 要能分析时间复杂度、避免 O(N²)；
- 需熟练使用：
  - STL 容器（vector、set、map、priority_queue）；
  - 快速输入输出；
  - 二分查找模板与 lower_bound/upper_bound。

------

## 🎯 六、常见银组题型总结

| 类别     | 示例                          |
| -------- | ----------------------------- |
| 区间问题 | Counting Haybales, Convention |
| 图论搜索 | Closing the Farm, MooTube     |
| 前缀和   | Subarray Sums II              |
| 二分答案 | Angry Cows                    |
| 模拟     | Stuck in a Rut, Cowntagion    |
| 离散化   | Haybale Stacking              |
| 贪心排序 | Convention II                 |