/*ilke başak baydar-150140709*/

#include <stddef.h>
#include "../include/min_heap.h"

MinHeap* heap_create(size_t capacity, size_t element_size, int (*compare)(const void*, const void*)){
    MinHeap* heap =(MinHeap*)malloc(sizeof(MinHeap));
    if(!heap) return NULL;

    heap->data = malloc(capacity*element_size);
    if(!heap->data) {
        free(heap);
        return NULL;
    }

    heap->capacity = capacity;
    heap->compare = compare;
    heap->element_size = element_size;
    heap->size = 0;

    return heap;
}

void heap_destroy(MinHeap* heap){
    if(heap) {
        free(heap->data);
        free(heap);
    }
}

int heap_insert(MinHeap* heap, const void* element){
    if(!heap || !element) return 0;

    //size extansion
    if(heap->size == heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        void* new_data = realloc(heap->data, new_capacity * heap->element_size);
        if(!new_data) return 0;

        heap->data = new_data;
        heap->capacity= new_capacity;
    }

    //insertion
    void* target =((char*)heap->data + (heap->size * heap->element_size));
    memcpy(target, element, heap->element_size);
    size_t curr = heap->size++;

    //reheap up

    while(curr>0){
        size_t parent = (curr-1) /2;
        void* parent_ptr = ((char*)heap->data + (parent * heap->element_size));
        if(heap->compare(target, parent_ptr)>= 0) break; 

        for(size_t i = 0; i<heap->element_size; i++) {
            char temp= ((char*)target)[i];
            ((char*)target)[i] = ((char*)parent_ptr) [i];
            ((char*)parent_ptr) [i] = temp;
        }

        curr=parent;
        target = parent_ptr;
    }
    return 1;
}

int heap_extract_min(MinHeap* heap, void* result){
    if(!heap || !result || heap->size == 0) return 0;

    memcpy(result, heap->data, heap->element_size);

    void* last = ((char*)heap->data + (--heap->size * heap->element_size));
    memcpy(heap->data, last, heap->element_size);

    size_t curr = 0;

    while(1) {
        size_t left = 2* curr +1;
        size_t right = 2* curr+2;
        size_t min = curr;

        if(left< heap->size && heap->compare((void*)((char*)heap->data +(left * heap->element_size)),
                (void*)((char*)heap->data +(min * heap->element_size)))<0) {
            min=left;
        }
        if(right< heap->size && heap->compare((void*)((char*)heap->data +(right * heap->element_size)),
                (void*)((char*)heap->data +(min * heap->element_size)))<0) {
            min=right;
        }

        if(min==curr) break;

        void* curr_ptr = (void*)((char*)heap->data + (curr * heap->element_size));
        void* min_ptr = (void*)((char*)heap->data + (min * heap->element_size));

        char temp [heap->element_size];
        memcpy(temp, curr_ptr,heap->element_size);
        memcpy(curr_ptr, min_ptr, heap->element_size);
        memcpy(min_ptr, temp, heap->element_size);

        curr=min;
    }

    return 1;
}

int heap_peek(const MinHeap* heap, void* result){
    if(heap->size == 0) return 0;
    memcpy(result, heap->data, heap->element_size);
    return 1;
}

size_t heap_size(const MinHeap* heap){
    return heap->size;
}

int heap_merge(MinHeap* heap1, const MinHeap* heap2){
    if(heap1->compare != heap2->compare || heap1->element_size != heap2->element_size) return 0;

    size_t new_capacity = heap1->size + heap2->size;
    if(new_capacity>heap1->capacity) {
        void* new_data= realloc(heap1->data, new_capacity * heap1->element_size);
        if(!new_data) return 0;
        heap1->data= new_data;
        heap1->capacity= new_capacity;
    }


    for(size_t i =0; i<heap2->size; i++){
        void* element = (void*)((char*)heap2->data + (i*heap2->element_size));
        if(!heap_insert(heap1, element)) return 0;
    }

    //reheap heap1 after merge
    size_t curr = 0;
    while(curr< heap1->size) {
        size_t left = 2* curr +1;
        size_t right = 2* curr+2;
        size_t min = curr;

        if(left< heap1->size && heap1->compare((char*)heap1->data + left * heap1->element_size, 
                (char*)heap1->data + min * heap1->element_size) <0) {
            min = left;
        } 
        if(right< heap1->size && heap1->compare((char*)heap1->data + right * heap1->element_size, 
                (char*)heap1->data + min * heap1->element_size) <0) {
            min = right;
        } 
        if(min==curr) break;

        void* temp = malloc(heap1->element_size);
        if(!temp) return 0;

        memcpy(temp, (char*)heap1->data + curr * heap1->element_size, heap1->element_size);
        memcpy((char*)heap1->data + curr * heap1->element_size, (char*)heap1->data + min * heap1->element_size, heap1->element_size);
        memcpy((char*)heap1->data + min * heap1->element_size, temp, heap1->element_size);
        free(temp);

        curr=min; // continue reheap down
    }
    
    return 1;
}