#include <string.h>
#include "oslabs.h"

static void clear_entry(struct PTE *entry) {
    entry->is_valid = 0;
    entry->frame_number = -1;
    entry->arrival_timestamp = -1;
    entry->last_access_timestamp = -1;
    entry->reference_count = -1;
}

static void clear_lfu(struct PTE *entry) {
    entry->is_valid = 0;
    entry->frame_number = -1;
    entry->arrival_timestamp = 0;
    entry->last_access_timestamp = 0;
    entry->reference_count = 0;
}

static void push_frame(int pool[POOLMAX], int *count, int frame) {
    if (*count < POOLMAX) {
        pool[*count] = frame;
        (*count)++;
    }
}

static int pop_frame(int pool[POOLMAX], int *count) {
    if (*count <= 0) {
        return -1;
    }

    int frame = pool[0];
    for (int i = 0; i + 1 < *count; ++i) {
        pool[i] = pool[i + 1];
    }
    (*count)--;
    return frame;
}

static int pick_fifo_replacement(struct PTE table[TABLEMAX], int size) {
    int best = -1;
    int best_time = 0x7fffffff;
    for (int i = 0; i < size; ++i) {
        if (table[i].is_valid && table[i].arrival_timestamp < best_time) {
            best_time = table[i].arrival_timestamp;
            best = i;
        }
    }
    return best;
}

static int pick_lru_replacement(struct PTE table[TABLEMAX], int size) {
    int best = -1;
    int best_time = 0x7fffffff;
    for (int i = 0; i < size; ++i) {
        if (table[i].is_valid && table[i].last_access_timestamp < best_time) {
            best_time = table[i].last_access_timestamp;
            best = i;
        }
    }
    return best;
}

static int pick_lfu_replacement(struct PTE table[TABLEMAX], int size) {
    int best = -1;
    int best_ref = 0x7fffffff;
    int best_arrival = 0x7fffffff;
    for (int i = 0; i < size; ++i) {
        if (!table[i].is_valid) continue;
        int refs = table[i].reference_count;
        int at = table[i].arrival_timestamp;
        if (best < 0 || refs < best_ref || (refs == best_ref && at < best_arrival)) {
            best = i;
            best_ref = refs;
            best_arrival = at;
        }
    }
    return best;
}

static int serve(struct PTE table[TABLEMAX], int *size, int page, int pool[POOLMAX], int *count, int now, int mode) {
    if (page < 0 || page >= *size) return -1;

    struct PTE *entry = &table[page];
    if (entry->is_valid) {
        entry->last_access_timestamp = now;
        entry->reference_count += 1;
        return entry->frame_number;
    }

    int frame = pop_frame(pool, count);
    if (frame >= 0) {
        entry->is_valid = 1;
        entry->frame_number = frame;
        entry->arrival_timestamp = now;
        entry->last_access_timestamp = now;
        entry->reference_count = 1;
        return frame;
    }

    int replacement_index = -1;
    if (mode == 0) replacement_index = pick_fifo_replacement(table, *size);
    else if (mode == 1) replacement_index = pick_lru_replacement(table, *size);
    else replacement_index = pick_lfu_replacement(table, *size);

    if (replacement_index < 0) return -1;

    struct PTE *replacement_entry = &table[replacement_index];
    int freed = replacement_entry->frame_number;
    if (mode == 2) clear_lfu(replacement_entry);
    else clear_entry(replacement_entry);

    entry->is_valid = 1;
    entry->frame_number = freed;
    entry->arrival_timestamp = now;
    entry->last_access_timestamp = now;
    entry->reference_count = 1;

    return entry->frame_number;
}

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    return serve(page_table, table_cnt, page_number, frame_pool, frame_cnt, current_timestamp, 0);
}

int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    struct PTE work[TABLEMAX];
    int pool[POOLMAX];
    int count = frame_cnt;
    memcpy(work, page_table, sizeof(work));
    memcpy(pool, frame_pool, sizeof(pool));

    int faults = 0;
    for (int i = 0; i < reference_cnt; ++i) {
        int page = refrence_string[i];
        int was_present = work[page].is_valid;
        int frame = process_page_access_fifo(work, &table_cnt, page, pool, &count, i + 1);
        if (frame >= 0 && !was_present) faults++;
    }
    return faults;
}

int process_page_access_lru(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    return serve(page_table, table_cnt, page_number, frame_pool, frame_cnt, current_timestamp, 1);
}

int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    struct PTE work[TABLEMAX];
    int pool[POOLMAX];
    int count = frame_cnt;
    memcpy(work, page_table, sizeof(work));
    memcpy(pool, frame_pool, sizeof(pool));

    int faults = 0;
    for (int i = 0; i < reference_cnt; ++i) {
        int page = refrence_string[i];
        int was_present = work[page].is_valid;
        int frame = process_page_access_lru(work, &table_cnt, page, pool, &count, i + 1);
        if (frame >= 0 && !was_present) faults++;
    }
    return faults;
}

int process_page_access_lfu(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    return serve(page_table, table_cnt, page_number, frame_pool, frame_cnt, current_timestamp, 2);
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    struct PTE work[TABLEMAX];
    int pool[POOLMAX];
    int count = frame_cnt;
    memcpy(work, page_table, sizeof(work));
    memcpy(pool, frame_pool, sizeof(pool));

    int faults = 0;
    for (int i = 0; i < reference_cnt; ++i) {
        int page = refrence_string[i];
        int was_present = work[page].is_valid;
        int frame = process_page_access_lfu(work, &table_cnt, page, pool, &count, i + 1);
        if (frame >= 0 && !was_present) faults++;
    }
    return faults;
}
