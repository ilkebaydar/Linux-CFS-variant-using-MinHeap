#CFS Variant Using Min-Heap (BLG 223E - Project 4)
This project is a simplified implementation of the Linux Completely Fair Scheduler (CFS) using a Min-Heap instead of a Red-Black Tree. The goal is to fairly allocate CPU time among processes based on their virtual runtime (vruntime).

##Overview: 
The project consists of two main components:
Min-Heap Implementation: A generic Min-Heap data structure that supports insertion, deletion, merging, and retrieval of the smallest element.
Process Scheduler: A scheduler that manages processes using the Min-Heap, selecting the process with the lowest vruntime for execution.

##Features: 
Implementation of virtual runtime (vruntime) tracking for fairness.
Nice values (-20 to +19) to adjust process priority dynamically.
Efficient process scheduling using a Min-Heap (O(log n) complexity).
Custom test framework to validate the correctness of the scheduler.

#Implementation Details: 
Language: C (Standard C, no STL usage)
Heap Operations: Implemented in min_heap.c
Scheduler Logic: Implemented in scheduler.c
Memory Management: Ensured through Valgrind testing.
Testing: Provided test framework with additional hidden test cases for evaluation.

#Compilation & Debugging: 
Compile with make and run tests using make test.
Check for memory leaks using make valgrind.
Debugging supported via VS Code configurations.

#Notes: 
This project is part of the BLG 223E - Data Structures course at Istanbul Technical University (ITU). It is prepared by  Res. Assist. M. Alpaslan Tavukçu.
The implementation adheres to the provided skeleton and constraints.
