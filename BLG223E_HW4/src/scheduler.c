/*ilke başak baydar-150140709*/

#include <stdlib.h>
#include "../include/scheduler.h"

int compare_process(const void* a, const void* b){
    const Process* p1 = (const Process*)a;
    const Process* p2 = (const Process*)b;
    return p1->vruntime - p2->vruntime;
}

Scheduler* create_scheduler(int capacity){
    if(capacity<= 0) return NULL;

    Scheduler* scheduler = (Scheduler*)malloc(sizeof(Scheduler));
    if(!scheduler) return NULL;

    scheduler->process_queue = heap_create(capacity, sizeof(Process), compare_process);
    if(!scheduler->process_queue){
        free(scheduler);
        return NULL;
    }

    scheduler->current_process = NULL;
    scheduler->time_slice = 10; //Fixed time slice instead of dynamic
    return scheduler; 
}

void destroy_scheduler(Scheduler* scheduler){
    if(scheduler) {
        if(scheduler->current_process){
         free(scheduler->current_process);
        }
        heap_destroy(scheduler->process_queue);
        free(scheduler);
    }
}

void schedule_process(Scheduler* scheduler, Process process){
    if(!scheduler) return;
    process.is_running = false;
    heap_insert(scheduler->process_queue, &process);
}


Process* get_next_process(Scheduler* scheduler){
    if(!scheduler || heap_size(scheduler->process_queue) == 0) return NULL;

    if(scheduler->current_process) {
        scheduler->current_process->is_running = false;
        schedule_process(scheduler, *scheduler->current_process);
        scheduler->current_process = NULL;
    }

    Process* next = (Process*)malloc(sizeof(Process));
    if(!next || !heap_extract_min(scheduler->process_queue, next)) {
        free(next);
        return NULL;
    }
    next->is_running = true;
    scheduler->current_process = next;
    return next;
}

void tick(Scheduler* scheduler){
    if(!scheduler || !scheduler->current_process) return;

    scheduler->current_process->is_running = false;
    update_vruntime(scheduler->current_process, scheduler->time_slice);
    schedule_process(scheduler, *scheduler->current_process);
    free(scheduler->current_process);
    scheduler->current_process = NULL;
}




