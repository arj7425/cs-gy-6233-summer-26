#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oslabs.h"

static int is_null_block(struct MEMORY_BLOCK b) {
    return b.start_address == 0 && b.end_address == 0 && b.segment_size == 0 && b.process_id == 0;
}

static void shift_map(struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int start_index) {
    for (int i = start_index; i + 1 < *map_cnt; ++i) {
        memory_map[i] = memory_map[i + 1];
    }
    (*map_cnt)--;
}

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    int best_index = -1;
    int best_size = 0x7fffffff;

    for (int i = 0; i < *map_cnt; ++i) {
        if (memory_map[i].process_id == 0 && memory_map[i].segment_size >= request_size) {
            int size = memory_map[i].segment_size;
            if (best_index < 0 || size < best_size) {
                best_index = i;
                best_size = size;
            }
        }
    }

    if (best_index < 0) {
        struct MEMORY_BLOCK null_block;
        memset(&null_block, 0, sizeof(null_block));
        return null_block;
    }

    struct MEMORY_BLOCK block = memory_map[best_index];
    struct MEMORY_BLOCK original_block = block;
    if (block.segment_size == request_size) {
        block.process_id = process_id;
        memory_map[best_index] = block;
        return block;
    }

    block.process_id = process_id;
    block.end_address = block.start_address + request_size - 1;
    block.segment_size = request_size;
    memory_map[best_index] = block;

    struct MEMORY_BLOCK remainder;
    memset(&remainder, 0, sizeof(remainder));
    remainder.start_address = block.end_address + 1;
    remainder.end_address = original_block.end_address;
    remainder.segment_size = original_block.segment_size - request_size;
    remainder.process_id = 0;

    if (remainder.segment_size > 0) {
        for (int i = *map_cnt; i > best_index + 1; --i) {
            memory_map[i] = memory_map[i - 1];
        }
        memory_map[best_index + 1] = remainder;
        (*map_cnt)++;
    }

    return block;
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    int best_index = -1;
    for (int i = 0; i < *map_cnt; ++i) {
        if (memory_map[i].process_id == 0 && memory_map[i].segment_size >= request_size) {
            best_index = i;
            break;
        }
    }

    if (best_index < 0) {
        struct MEMORY_BLOCK null_block;
        memset(&null_block, 0, sizeof(null_block));
        return null_block;
    }

    struct MEMORY_BLOCK block = memory_map[best_index];
    struct MEMORY_BLOCK original_block = block;
    if (block.segment_size == request_size) {
        block.process_id = process_id;
        memory_map[best_index] = block;
        return block;
    }

    block.process_id = process_id;
    block.end_address = block.start_address + request_size - 1;
    block.segment_size = request_size;
    memory_map[best_index] = block;

    struct MEMORY_BLOCK remainder;
    memset(&remainder, 0, sizeof(remainder));
    remainder.start_address = block.end_address + 1;
    remainder.end_address = original_block.end_address;
    remainder.segment_size = original_block.segment_size - request_size;
    remainder.process_id = 0;

    if (remainder.segment_size > 0) {
        for (int i = *map_cnt; i > best_index + 1; --i) {
            memory_map[i] = memory_map[i - 1];
        }
        memory_map[best_index + 1] = remainder;
        (*map_cnt)++;
    }

    return block;
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    int best_index = -1;
    int best_size = -1;

    for (int i = 0; i < *map_cnt; ++i) {
        if (memory_map[i].process_id == 0 && memory_map[i].segment_size >= request_size) {
            int size = memory_map[i].segment_size;
            if (size > best_size) {
                best_index = i;
                best_size = size;
            }
        }
    }

    if (best_index < 0) {
        struct MEMORY_BLOCK null_block;
        memset(&null_block, 0, sizeof(null_block));
        return null_block;
    }

    struct MEMORY_BLOCK block = memory_map[best_index];
    struct MEMORY_BLOCK original_block = block;
    if (block.segment_size == request_size) {
        block.process_id = process_id;
        memory_map[best_index] = block;
        return block;
    }

    block.process_id = process_id;
    block.end_address = block.start_address + request_size - 1;
    block.segment_size = request_size;
    memory_map[best_index] = block;

    struct MEMORY_BLOCK remainder;
    memset(&remainder, 0, sizeof(remainder));
    remainder.start_address = block.end_address + 1;
    remainder.end_address = original_block.end_address;
    remainder.segment_size = original_block.segment_size - request_size;
    remainder.process_id = 0;

    if (remainder.segment_size > 0) {
        for (int i = *map_cnt; i > best_index + 1; --i) {
            memory_map[i] = memory_map[i - 1];
        }
        memory_map[best_index + 1] = remainder;
        (*map_cnt)++;
    }

    return block;
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id, int last_address) {
    int start_index = 0;
    for (int i = 0; i < *map_cnt; ++i) {
        if (memory_map[i].start_address >= last_address) {
            start_index = i;
            break;
        }
    }

    for (int offset = 0; offset < *map_cnt; ++offset) {
        int i = (start_index + offset) % *map_cnt;
        if (memory_map[i].process_id == 0 && memory_map[i].segment_size >= request_size) {
            struct MEMORY_BLOCK block = memory_map[i];
            struct MEMORY_BLOCK original_block = block;
            if (block.segment_size == request_size) {
                block.process_id = process_id;
                memory_map[i] = block;
                return block;
            }

            block.process_id = process_id;
            block.end_address = block.start_address + request_size - 1;
            block.segment_size = request_size;
            memory_map[i] = block;

            struct MEMORY_BLOCK remainder;
            memset(&remainder, 0, sizeof(remainder));
            remainder.start_address = block.end_address + 1;
            remainder.end_address = original_block.end_address;
            remainder.segment_size = original_block.segment_size - request_size;
            remainder.process_id = 0;

            if (remainder.segment_size > 0) {
                for (int j = *map_cnt; j > i + 1; --j) {
                    memory_map[j] = memory_map[j - 1];
                }
                memory_map[i + 1] = remainder;
                (*map_cnt)++;
            }
            return block;
        }
    }

    struct MEMORY_BLOCK null_block;
    memset(&null_block, 0, sizeof(null_block));
    return null_block;
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt) {
    int target_index = -1;
    for (int i = 0; i < *map_cnt; ++i) {
        if (memory_map[i].start_address == freed_block.start_address && memory_map[i].end_address == freed_block.end_address &&
            memory_map[i].segment_size == freed_block.segment_size && memory_map[i].process_id == freed_block.process_id) {
            target_index = i;
            break;
        }
    }

    if (target_index < 0) {
        return;
    }

    memory_map[target_index].process_id = 0;

    if (target_index > 0 && memory_map[target_index - 1].process_id == 0) {
        memory_map[target_index - 1].end_address = memory_map[target_index].end_address;
        memory_map[target_index - 1].segment_size += memory_map[target_index].segment_size;
        shift_map(memory_map, map_cnt, target_index);
        target_index--; 
    }

    if (target_index + 1 < *map_cnt && memory_map[target_index + 1].process_id == 0) {
        memory_map[target_index].end_address = memory_map[target_index + 1].end_address;
        memory_map[target_index].segment_size += memory_map[target_index + 1].segment_size;
        shift_map(memory_map, map_cnt, target_index + 1);
    }
}
