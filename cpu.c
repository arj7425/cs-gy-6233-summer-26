#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oslabs.h"

static int is_null_pcb(struct PCB p) {
    return p.process_id == 0 && p.arrival_timestamp == 0 && p.total_bursttime == 0 &&
           p.execution_starttime == 0 && p.execution_endtime == 0 && p.remaining_bursttime == 0 &&
           p.process_priority == 0;
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp) {
    if (is_null_pcb(current_process)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }

    if (new_process.process_priority >= current_process.process_priority) {
        if (*queue_cnt < QUEUEMAX) {
            new_process.execution_starttime = 0;
            new_process.execution_endtime = 0;
            new_process.remaining_bursttime = new_process.total_bursttime;
            ready_queue[*queue_cnt] = new_process;
            (*queue_cnt)++;
        }
        return current_process;
    }

    if (*queue_cnt < QUEUEMAX) {
        int elapsed = timestamp - current_process.execution_starttime;
        int remaining = current_process.remaining_bursttime - elapsed;
        if (remaining < 0) {
            remaining = 0;
        }
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime = remaining;
        ready_queue[*queue_cnt] = current_process;
        (*queue_cnt)++;
    }

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = timestamp + new_process.total_bursttime;
    new_process.remaining_bursttime = new_process.total_bursttime;
    return new_process;
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {
    if (*queue_cnt <= 0) {
        struct PCB null_pcb;
        memset(&null_pcb, 0, sizeof(null_pcb));
        return null_pcb;
    }

    int best_index = 0;
    for (int i = 1; i < *queue_cnt; ++i) {
        if (ready_queue[i].process_priority < ready_queue[best_index].process_priority) {
            best_index = i;
        }
    }

    struct PCB next = ready_queue[best_index];
    for (int i = best_index; i + 1 < *queue_cnt; ++i) {
        ready_queue[i] = ready_queue[i + 1];
    }
    (*queue_cnt)--;

    next.execution_starttime = timestamp;
    next.execution_endtime = timestamp + next.remaining_bursttime;
    return next;
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp) {
    if (is_null_pcb(current_process)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }

    if (new_process.total_bursttime >= current_process.remaining_bursttime) {
        if (*queue_cnt < QUEUEMAX) {
            new_process.execution_starttime = 0;
            new_process.execution_endtime = 0;
            new_process.remaining_bursttime = new_process.total_bursttime;
            ready_queue[*queue_cnt] = new_process;
            (*queue_cnt)++;
        }
        return current_process;
    }

    if (*queue_cnt < QUEUEMAX) {
        int elapsed = timestamp - current_process.execution_starttime;
        int remaining = current_process.remaining_bursttime - elapsed;
        if (remaining < 0) {
            remaining = 0;
        }
        current_process.execution_starttime = 0;
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime = remaining;
        ready_queue[*queue_cnt] = current_process;
        (*queue_cnt)++;
    }

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = timestamp + new_process.total_bursttime;
    new_process.remaining_bursttime = new_process.total_bursttime;
    return new_process;
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {
    if (*queue_cnt <= 0) {
        struct PCB null_pcb;
        memset(&null_pcb, 0, sizeof(null_pcb));
        return null_pcb;
    }

    int best_index = 0;
    for (int i = 1; i < *queue_cnt; ++i) {
        if (ready_queue[i].remaining_bursttime < ready_queue[best_index].remaining_bursttime) {
            best_index = i;
        }
    }

    struct PCB next = ready_queue[best_index];
    for (int i = best_index; i + 1 < *queue_cnt; ++i) {
        ready_queue[i] = ready_queue[i + 1];
    }
    (*queue_cnt)--;

    next.execution_starttime = timestamp;
    next.execution_endtime = timestamp + next.remaining_bursttime;
    return next;
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum) {
    if (is_null_pcb(current_process)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + (time_quantum < new_process.total_bursttime ? time_quantum : new_process.total_bursttime);
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }

    if (*queue_cnt < QUEUEMAX) {
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        (*queue_cnt)++;
    }
    return current_process;
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum) {
    if (*queue_cnt <= 0) {
        struct PCB null_pcb;
        memset(&null_pcb, 0, sizeof(null_pcb));
        return null_pcb;
    }

    int best_index = 0;
    for (int i = 1; i < *queue_cnt; ++i) {
        if (ready_queue[i].arrival_timestamp < ready_queue[best_index].arrival_timestamp) {
            best_index = i;
        }
    }

    struct PCB next = ready_queue[best_index];
    for (int i = best_index; i + 1 < *queue_cnt; ++i) {
        ready_queue[i] = ready_queue[i + 1];
    }
    (*queue_cnt)--;

    next.execution_starttime = timestamp;
    next.execution_endtime = timestamp + (time_quantum < next.remaining_bursttime ? time_quantum : next.remaining_bursttime);
    return next;
}
