#ifndef HEAP
#define HEAP

// Heap utility macros
#define heap_child_1(n) ((2*(n))+1)
#define heap_child_2(n) ((2*(n))+2)
#define heap_parent(n) (((n+1)/2)-1)
#define heap_value(x) (x).parameters.price

#endif // HEAP
