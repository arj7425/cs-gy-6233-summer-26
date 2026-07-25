

# **handle\_request\_arrival\_fcfs**

## **Case 1: published test case**

| input/output | parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | EMPTY |
| input | queue\_cnt | 0 |
| input | current\_request | \[RID:51, AT:1, CYL:53, ADDR:53, PID:51\] |
| input | new\_request | \[RID:52, AT:2, CYL:54, ADDR:54, PID:52\] |
| input | timestamp | 2 |
| output | request\_queue | \[RID:52, AT:2, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID:51, AT:1, CYL:53, ADDR:53, PID:51\] |

## **Case 2: return RCB of currently serviced request, add new request to queue (different values)**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | EMPTY |
| input | queue\_cnt | 0 |
| input | current\_request | \[RID: 52, AT:2, CYL:54, ADDR:54, PID:52\] |
| input | new\_request | \[RID: 53, AT:3, CYL:45, ADDR:60, PID:53\] |
| input | timestamp | 3 |
| output | request\_queue | \[RID: 53, AT:3, CYL:45, ADDR:60, PID:53\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID: 52, AT:2, CYL:54, ADDR:54, PID:52\] |

## **Case 3: return RCB of currently serviced request, add new request to queue (different values)**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] |
| input | queue\_cnt | 1 |
| input | current\_request | \[RID: 50, AT:1, CYL:52, ADDR:52, PID:50\] |
| input | new\_request | \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| input | timestamp | 3 |
| output | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 2 |
| output | RCB | \[RID: 50, AT:1, CYL:52, ADDR:52, PID:50\] |

# **handle\_request\_completion\_fcfs**

## **Case 1: published test case**

| input/output | parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID:1, AT:10, CYL:124323, ADDR:124323, PID:1\] |
| input | queue\_cnt | 1 |
| output | request\_queue | EMPTY |
| output | queue\_cnt | 0 |
| output | RCB | \[RID:1, AT:10, CYL:124323, ADDR:124323, PID:1\] |

## **Case 2: request queue is not empty, different values than sample**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 4, AT:2, CYL:53, ADDR:53, PID:4\] \[RID: 5, AT:3, CYL:54, ADDR:54, PID:5\] \[RID: 6, AT:5, CYL:51, ADDR:59, PID:6\] |
| input | queue\_cnt | 3 |
| output | request\_queue | \[RID: 5, AT:3, CYL:54, ADDR:54, PID:5\] \[RID: 6, AT:5, CYL:51, ADDR:59, PID:6\]  |
| output | queue\_cnt | 2 |
| output | RCB | \[RID: 4, AT:2, CYL:53, ADDR:53, PID:4\] |

## **Case 3: request queue is not empty, different values than sample**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| input | queue\_cnt | 2 |
| output | request\_queue | \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] |

# **handle\_request\_arrival\_sstf**

## **Case 1: published test case**

| input/output | parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | EMPTY |
| input | queue\_cnt | 0 |
| input | current\_request | \[RID:51, AT:1, CYL:53, ADDR:53, PID:51\] |
| input | new\_request | \[RID:52, AT:2, CYL:54, ADDR:54, PID:52\] |
| input | timestamp | 2 |
| output | request\_queue | \[RID:52, AT:2, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID:51, AT:1, CYL:53, ADDR:53, PID:51\] |

## **Case 2: return RCB of currently serviced request, add new request to queue (different values)**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | EMPTY |
| input | queue\_cnt | 0 |
| input | current\_request | \[RID: 52, AT:2, CYL:54, ADDR:54, PID:52\] |
| input | new\_request | \[RID: 53, AT:3, CYL:45, ADDR:60, PID:53\] |
| input | timestamp | 3 |
| output | request\_queue | \[RID: 53, AT:3, CYL:45, ADDR:60, PID:53\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID: 52, AT:2, CYL:54, ADDR:54, PID:52\] |

## **Case 3: return RCB of currently serviced request, add new request to queue (different values)**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] |
| input | queue\_cnt | 1 |
| input | current\_request | \[RID: 50, AT:1, CYL:52, ADDR:52, PID:50\] |
| input | new\_request | \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| input | timestamp | 3 |
| output | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 2 |
| output | RCB | \[RID: 50, AT:1, CYL:52, ADDR:52, PID:50\] |

# **handle\_request\_completion\_sstf**

## **Case 1: published test case**

| input/output | parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID:1, AT:72, CYL:45, ADDR:45, PID:1\], \[RID:2, AT:71, CYL:47, ADDR:47, PID:2\], \[RID:3, AT:73, CYL:43, ADDR:43, PID:3\] |
| input | queue\_cnt | 3 |
| input | current\_cylinder | 48 |
| output | request\_queue | \[RID:1, AT:72, CYL:45, ADDR:45, PID:1\], \[RID:3, AT:73, CYL:43, ADDR:43, PID:3\] |
| output | queue\_cnt | 2 |
| output | RCB | \[RID:2, AT:71, CYL:47, ADDR:47, PID:2\] |

## **Case 2: request queue is not empty, different values than sample**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 4, AT:2, CYL:53, ADDR:53, PID:4\] \[RID: 5, AT:3, CYL:54, ADDR:54, PID:5\] \[RID: 6, AT:5, CYL:51, ADDR:59, PID:6\] |
| input | queue\_cnt | 3 |
| input | current\_cylinder | 57 |
| output | request\_queue | \[RID: 4, AT:2, CYL:53, ADDR:53, PID:4\] \[RID: 6, AT:5, CYL:51, ADDR:59, PID:6\]  |
| output | queue\_cnt | 2 |
| output | RCB | \[RID: 5, AT:3, CYL:54, ADDR:54, PID:5\] |

## **Case 3: request queue is not empty, different values than sample**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:15, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| input | queue\_cnt | 4 |
| input | current\_cylinder | 25 |
| output | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:15, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] |
| output | queue\_cnt | 3 |
| output | RCB | \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |

# **handle\_request\_arrival\_look**

## **Case 1: published test case**

| input/output | parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | EMPTY |
| input | queue\_cnt | 0 |
| input | current\_request | \[RID:51, AT:1, CYL:53, ADDR:53, PID:51\] |
| input | new\_request | \[RID:52, AT:2, CYL:54, ADDR:54, PID:52\] |
| input | timestamp | 2 |
| output | request\_queue | \[RID:52, AT:2, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID:51, AT:1, CYL:53, ADDR:53, PID:51\] |

## **Case 2: return RCB of currently serviced request, add new request to queue (different values)**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | EMPTY |
| input | queue\_cnt | 0 |
| input | current\_request | \[RID: 52, AT:2, CYL:54, ADDR:54, PID:52\] |
| input | new\_request | \[RID: 53, AT:3, CYL:45, ADDR:60, PID:53\] |
| input | timestamp | 3 |
| output | request\_queue | \[RID: 53, AT:3, CYL:45, ADDR:60, PID:53\] |
| output | queue\_cnt | 1 |
| output | RCB | \[RID: 52, AT:2, CYL:54, ADDR:54, PID:52\] |

## **Case 3: return RCB of currently serviced request, add new request to queue (different values)**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] |
| input | queue\_cnt | 1 |
| input | current\_request | \[RID: 50, AT:1, CYL:52, ADDR:52, PID:50\] |
| input | new\_request | \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| input | timestamp | 3 |
| output | request\_queue | \[RID: 51, AT:2, CYL:53, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:54, ADDR:54, PID:52\] |
| output | queue\_cnt | 2 |
| output | RCB | \[RID: 50, AT:1, CYL:52, ADDR:52, PID:50\] |

# **handle\_request\_completion\_look**

## **Case 1: published test case**

| input/output | parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID:1, AT:52, CYL:58, ADDR:58, PID:1\], \[RID:2, AT:51, CYL:58, ADDR:58, PID:2\], \[RID:3, AT:53, CYL:58, ADDR:58, PID:3\] |
| input | queue\_cnt | 3 |
| input | current\_cylinder | 58 |
| input | scan\_direction | 1 |
| output | request\_queue | \[RID:1, AT:52, CYL:58, ADDR:58, PID:1\], \[RID:3, AT:53, CYL:58, ADDR:58, PID:3\] |
| output | queue\_cnt | 2 |
| output | RCB | \[RID:2, AT:51, CYL:58, ADDR:58, PID:2\] |

## **Case 2: request queue is not empty, scan direction 0, smaller requests present**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:15, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| input | queue\_cnt | 4 |
| input | current\_cylinder | 27 |
| input | scan\_direction | 0 |
| output | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| output | queue\_cnt | 3 |
| output | RCB | \[RID: 52, AT:3, CYL:15, ADDR:54, PID:52\]  |

## **Case 3: request queue is not empty, scan direction 0, no smaller requests present**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:57, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| input | queue\_cnt | 4 |
| input | current\_cylinder | 27 |
| input | scan\_direction | 0 |
| output | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:57, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] |
| output | queue\_cnt | 3 |
| output | RCB | \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |

## **Case 4: request queue is not empty, scan direction 1, larger requests are present**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:57, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| input | queue\_cnt | 4 |
| input | current\_cylinder | 80 |
| input | scan\_direction | 1 |
| output | request\_queue | \[RID: 52, AT:3, CYL:57, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| output | queue\_cnt | 3 |
| output | RCB | \[RID: 51, AT:1, CYL:90, ADDR:53, PID:51\] |

## **Case 5: request queue is not empty, scan direction 1, no larger requests present**

| Input/output | Parameter | value |
| :---- | :---- | :---- |
| input | request\_queue | \[RID: 51, AT:1, CYL:20, ADDR:53, PID:51\] \[RID: 52, AT:3, CYL:57, ADDR:54, PID:52\] \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| input | queue\_cnt | 4 |
| input | current\_cylinder | 80 |
| input | scan\_direction | 1 |
| output | request\_queue | \[RID: 51, AT:1, CYL:20, ADDR:53, PID:51\]  \[RID: 53, AT:4, CYL:45, ADDR:55, PID:53\] \[RID: 54, AT:7, CYL:28, ADDR:56, PID:54\] |
| output | queue\_cnt | 3 |
| output | RCB | \[RID: 52, AT:3, CYL:57, ADDR:54, PID:52\] |

