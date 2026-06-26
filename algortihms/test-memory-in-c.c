#include <stdio.h>
#include <stdlib.h>

int main() {

    int n;
    int* array;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    // allocate memory for the array
    array = (int*)malloc(n * sizeof(int));

    // print the size of the allocated memory
    printf("Size of allocated memory: %zu bytes\n", n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &array[i]);

        // print the address of the current element
        printf("Address of element %d: %p\n", i + 1, (void*)(array + i));

        // (array + i) is equivalent to &array[i]
        // which means the address of the i-th element in the array
    }

    // free the allocated memory
    free(array);

    return 0;
}