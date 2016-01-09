#include <limits.h>
#include <stdio.h>

#define N 100

typedef struct {
    int heap[N];
    int i; // number of elements in a heap, first element at i=1, element at i=0 is a sentinel
} heap;


static int parent_id(int i) {
    return i / 2;
}


static int left_id(int i) {
    return 2 * i;
}


static int right_id(int i) {
    return 2 * i + 1;
}

static void print_heap(heap *h) {
    for(int i = 1; i <= h->i; ++i)
        printf("%d ", h->heap[i]);
    printf("\n");
}


static void upheap(heap *h, int iter) {
    int val = h->heap[iter];
    h->heap[0] = INT_MAX;
    while(h->heap[parent_id(iter)] < val) {
        h->heap[iter] = h->heap[parent_id(iter)];
        iter = parent_id(iter);
    }
    h->heap[iter] = val;
}


static void insert(heap *h, int elem) {
    h->i += 1;
    h->heap[h->i] = elem;
    upheap(h, h->i);
}


static void downheap(heap *h, int iter) {
    int val = h->heap[iter];
    int swap_id = left_id(iter);
    while(left_id(iter) <= h->i) {
        if(right_id(iter) <= h->i && h->heap[right_id(iter)] > h->heap[left_id(iter)])
            swap_id = right_id(iter);
        if(h->heap[swap_id] > val) {
            h->heap[iter] = h->heap[swap_id];
            iter = swap_id;
            swap_id = left_id(iter);
        }
        else
            break;
    }
    h->heap[iter] = val;

}


static void delete_max(heap *h) {
    h->heap[1] = h->heap[h->i];
    h->i -= 1;
    downheap(h, 1);
}


static int max(heap *h) {
    return h->heap[1];
}


int main(int argc, char **argv) {
    // usage example
    heap h;
    h.i = 0;

    int V[] = {3, 3, 3, 9, 18, 9, 12, 11, 9};
    for(int i = 0; i < 9; ++i)
        insert(&h, V[i]);
    print_heap(&h);

    delete_max(&h);
    print_heap(&h);

    printf("Max = %d\n", max(&h));
    
    return 0;
}
