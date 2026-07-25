#include <stdio.h>
#include <string.h>
#include "oslabs.h"

static struct RCB make_rcb(int id, int at, int cyl, int addr, int pid) {
    struct RCB r;
    memset(&r, 0, sizeof(r));
    r.request_id = id;
    r.arrival_timestamp = at;
    r.cylinder = cyl;
    r.address = addr;
    r.process_id = pid;
    return r;
}

static int is_null_rcb(struct RCB r) {
    return r.request_id == 0 && r.arrival_timestamp == 0 && r.cylinder == 0 && r.address == 0 && r.process_id == 0;
}

static void expect_rcb(const char *label, struct RCB actual, struct RCB expected) {
    if (actual.request_id != expected.request_id || actual.arrival_timestamp != expected.arrival_timestamp ||
        actual.cylinder != expected.cylinder || actual.address != expected.address || actual.process_id != expected.process_id) {
        printf("FAIL: %s\n", label);
        printf("  expected: RID=%d AT=%d CYL=%d ADDR=%d PID=%d\n", expected.request_id, expected.arrival_timestamp,
               expected.cylinder, expected.address, expected.process_id);
        printf("  actual:   RID=%d AT=%d CYL=%d ADDR=%d PID=%d\n", actual.request_id, actual.arrival_timestamp,
               actual.cylinder, actual.address, actual.process_id);
    } else {
        printf("PASS: %s\n", label);
    }
}

int main(void) {
    printf("Starting disk scheduling tests...\n");
    fflush(stdout);

    struct RCB queue[QUEUEMAX];
    int queue_cnt = 0;
    memset(queue, 0, sizeof(queue));

    struct RCB current = make_rcb(51, 1, 53, 53, 51);
    struct RCB new_req = make_rcb(52, 2, 54, 54, 52);
    struct RCB result = handle_request_arrival_fcfs(queue, &queue_cnt, current, new_req, 2);
    expect_rcb("FCFS arrival returns current request while enqueueing new request", result, current);
    if (queue_cnt != 1 || queue[0].request_id != 52) {
        printf("FAIL: FCFS arrival queue contents\n");
    } else {
        printf("PASS: FCFS arrival queue contents\n");
    }

    memset(queue, 0, sizeof(queue));
    queue_cnt = 0;
    queue[0] = make_rcb(1, 10, 124323, 124323, 1);
    queue_cnt = 1;
    result = handle_request_completion_fcfs(queue, &queue_cnt);
    expect_rcb("FCFS completion returns queued request", result, make_rcb(1, 10, 124323, 124323, 1));
    if (queue_cnt != 0) {
        printf("FAIL: FCFS completion queue count\n");
    } else {
        printf("PASS: FCFS completion queue count\n");
    }

    memset(queue, 0, sizeof(queue));
    queue_cnt = 0;
    queue[0] = make_rcb(1, 72, 45, 45, 1);
    queue[1] = make_rcb(2, 71, 47, 47, 2);
    queue[2] = make_rcb(3, 73, 43, 43, 3);
    queue_cnt = 3;
    result = handle_request_completion_sstf(queue, &queue_cnt, 48);
    expect_rcb("SSTF completion picks closest cylinder", result, make_rcb(2, 71, 47, 47, 2));
    if (queue_cnt != 2) {
        printf("FAIL: SSTF completion queue count\n");
    } else {
        printf("PASS: SSTF completion queue count\n");
    }

    memset(queue, 0, sizeof(queue));
    queue_cnt = 0;
    queue[0] = make_rcb(1, 52, 58, 58, 1);
    queue[1] = make_rcb(2, 51, 58, 58, 2);
    queue[2] = make_rcb(3, 53, 58, 58, 3);
    queue_cnt = 3;
    result = handle_request_completion_look(queue, &queue_cnt, 58, 1);
    expect_rcb("LOOK completion picks earliest same-cylinder request", result, make_rcb(2, 51, 58, 58, 2));

    memset(queue, 0, sizeof(queue));
    queue_cnt = 0;
    queue[0] = make_rcb(51, 1, 90, 53, 51);
    queue[1] = make_rcb(52, 3, 15, 54, 52);
    queue[2] = make_rcb(53, 4, 45, 55, 53);
    queue[3] = make_rcb(54, 7, 28, 56, 54);
    queue_cnt = 4;
    result = handle_request_completion_look(queue, &queue_cnt, 27, 0);
    expect_rcb("LOOK completion picks closest smaller cylinder when scanning downward", result, make_rcb(52, 3, 15, 54, 52));

    printf("Disk scheduling tests complete.\n");
    fflush(stdout);
    return 0;
}
