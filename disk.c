#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oslabs.h"

static int is_null_rcb(struct RCB r) {
    return r.request_id == 0 && r.arrival_timestamp == 0 && r.cylinder == 0 && r.address == 0 && r.process_id == 0;
}

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {
    (void)timestamp;

    if (is_null_rcb(current_request)) {
        return new_request;
    }

    if (*queue_cnt < QUEUEMAX) {
        request_queue[*queue_cnt] = new_request;
        (*queue_cnt)++;
    }
    return current_request;
}

struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt) {
    if (*queue_cnt <= 0) {
        struct RCB null_rcb;
        memset(&null_rcb, 0, sizeof(null_rcb));
        return null_rcb;
    }

    struct RCB next = request_queue[0];
    for (int i = 1; i < *queue_cnt; ++i) {
        if (request_queue[i].arrival_timestamp < next.arrival_timestamp) {
            next = request_queue[i];
        }
    }

    int next_index = -1;
    for (int i = 0; i < *queue_cnt; ++i) {
        if (request_queue[i].request_id == next.request_id && request_queue[i].arrival_timestamp == next.arrival_timestamp &&
            request_queue[i].cylinder == next.cylinder && request_queue[i].address == next.address && request_queue[i].process_id == next.process_id) {
            next_index = i;
            break;
        }
    }

    if (next_index >= 0) {
        for (int i = next_index; i + 1 < *queue_cnt; ++i) {
            request_queue[i] = request_queue[i + 1];
        }
        (*queue_cnt)--;
    }

    return next;
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {
    (void)timestamp;

    if (is_null_rcb(current_request)) {
        return new_request;
    }

    if (*queue_cnt < QUEUEMAX) {
        request_queue[*queue_cnt] = new_request;
        (*queue_cnt)++;
    }
    return current_request;
}

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX], int *queue_cnt, int current_cylinder) {
    if (*queue_cnt <= 0) {
        struct RCB null_rcb;
        memset(&null_rcb, 0, sizeof(null_rcb));
        return null_rcb;
    }

    int best_index = 0;
    int best_distance = abs(request_queue[0].cylinder - current_cylinder);
    int best_arrival = request_queue[0].arrival_timestamp;

    for (int i = 1; i < *queue_cnt; ++i) {
        int distance = abs(request_queue[i].cylinder - current_cylinder);
        if (distance < best_distance || (distance == best_distance && request_queue[i].arrival_timestamp < best_arrival)) {
            best_index = i;
            best_distance = distance;
            best_arrival = request_queue[i].arrival_timestamp;
        }
    }

    struct RCB next = request_queue[best_index];
    for (int i = best_index; i + 1 < *queue_cnt; ++i) {
        request_queue[i] = request_queue[i + 1];
    }
    (*queue_cnt)--;
    return next;
}

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {
    (void)timestamp;

    if (is_null_rcb(current_request)) {
        return new_request;
    }

    if (*queue_cnt < QUEUEMAX) {
        request_queue[*queue_cnt] = new_request;
        (*queue_cnt)++;
    }
    return current_request;
}

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX], int *queue_cnt, int current_cylinder, int scan_direction) {
    if (*queue_cnt <= 0) {
        struct RCB null_rcb;
        memset(&null_rcb, 0, sizeof(null_rcb));
        return null_rcb;
    }

    int best_index = -1;

    int same_cylinder_count = 0;
    int same_cylinder_index = -1;
    for (int i = 0; i < *queue_cnt; ++i) {
        if (request_queue[i].cylinder == current_cylinder) {
            same_cylinder_count++;
            if (same_cylinder_index < 0 || request_queue[i].arrival_timestamp < request_queue[same_cylinder_index].arrival_timestamp) {
                same_cylinder_index = i;
            }
        }
    }

    if (same_cylinder_count > 0) {
        best_index = same_cylinder_index;
    } else {
        int candidates_found = 0;
        if (scan_direction == 1) {
            int closest_diff = 0x7fffffff;
            for (int i = 0; i < *queue_cnt; ++i) {
                if (request_queue[i].cylinder > current_cylinder) {
                    int diff = request_queue[i].cylinder - current_cylinder;
                    if (best_index < 0 || diff < closest_diff || (diff == closest_diff && request_queue[i].arrival_timestamp < request_queue[best_index].arrival_timestamp)) {
                        closest_diff = diff;
                        best_index = i;
                    }
                    candidates_found = 1;
                }
            }
            if (!candidates_found) {
                int closest_diff = 0x7fffffff;
                for (int i = 0; i < *queue_cnt; ++i) {
                    int diff = abs(request_queue[i].cylinder - current_cylinder);
                    if (best_index < 0 || diff < closest_diff || (diff == closest_diff && request_queue[i].arrival_timestamp < request_queue[best_index].arrival_timestamp)) {
                        closest_diff = diff;
                        best_index = i;
                    }
                }
            }
        } else {
            int closest_diff = 0x7fffffff;
            for (int i = 0; i < *queue_cnt; ++i) {
                if (request_queue[i].cylinder < current_cylinder) {
                    int diff = current_cylinder - request_queue[i].cylinder;
                    if (best_index < 0 || diff < closest_diff || (diff == closest_diff && request_queue[i].arrival_timestamp < request_queue[best_index].arrival_timestamp)) {
                        closest_diff = diff;
                        best_index = i;
                    }
                    candidates_found = 1;
                }
            }
            if (!candidates_found) {
                int closest_diff = 0x7fffffff;
                for (int i = 0; i < *queue_cnt; ++i) {
                    int diff = abs(request_queue[i].cylinder - current_cylinder);
                    if (best_index < 0 || diff < closest_diff || (diff == closest_diff && request_queue[i].arrival_timestamp < request_queue[best_index].arrival_timestamp)) {
                        closest_diff = diff;
                        best_index = i;
                    }
                }
            }
        }
    }

    struct RCB next = request_queue[best_index];
    for (int i = best_index; i + 1 < *queue_cnt; ++i) {
        request_queue[i] = request_queue[i + 1];
    }
    (*queue_cnt)--;
    return next;
}
