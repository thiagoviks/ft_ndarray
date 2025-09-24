#include <unistd.h>
#include <stddef.h> //to use size_t
#include <stdio.h>

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))


/**
 *Memory Management Functions:

    ft_malloc: Allocates memory for the requested size, using sbrk to request more memory if needed. It searches through a linked list of free blocks and returns the first available one.
    free: Marks the block as free and attempts to merge adjacent free blocks to reduce fragmentation.
    calloc: Allocates memory and initializes it to 0 by calling malloc and using memset.
    realloc: Resizes the allocated memory block. If the current block is large enough, it returns the same block; otherwise, it allocates a new block, copies the data, and frees the old block.

ft_write Function:

    This function converts an integer to a string and writes it to the standard output using the write system call. It handles both positive and negative integers.

    ft_memset:

    It initializes a block of memory with a specific byte value. The ptr is treated as a pointer to a byte, and we iterate over the memory block to set each byte to the value passed.
    The function returns the original ptr for convenience, as is the standard behavior in the C library memset.

ft_memcpy:

    This function copies num bytes from the src memory block to the dest memory block. Both src and dest are treated as pointers to unsigned char (byte pointers), and we iterate over each byte to copy the values.
    It returns the dest pointer, which is also standard behavior for memcpy.

Main Function:

    It tests the memory management functions (malloc, free, calloc, realloc) by allocating, initializing, resizing, and freeing memory. It also prints the values of the allocated memory using ft_write.
 */

// Function declaration for custom write function
void ft_write(int num);
void *ft_memset(void *ptr, int value, size_t num);
void *ft_memcpy(void *dest, const void *src, size_t num);
void *ft_malloc(size_t size);
void ft_free(void *ptr);
void *ft_calloc(size_t nmemb, size_t size);
void *ft_realloc(void *ptr, size_t size);
void ft_print_heap();

// Structure for memory blocks
typedef struct s_block {
    size_t size;       // Size of the memory block
    struct s_block *next; // Pointer to the next block
    int free;          // 1 if the block is free, 0 if it's allocated
} t_block;

#define BLOCK_SIZE sizeof(t_block) // Size of the header for each block

static t_block *global_base = NULL; // Global base pointer to the first block

// Custom memset implementation
void *ft_memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;  // Treat the pointer as a byte pointer
    while (num--) {
        *p = (unsigned char)value;  // Set each byte to the given value
        p++;  // Move to the next byte
    }
    return ptr;  // Return the original pointer
}

// Custom memcpy implementation
void *ft_memcpy(void *dest, const void *src, size_t num) {
    unsigned char *d = dest;  // Destination pointer
    const unsigned char *s = src;  // Source pointer
    while (num--) {
        *d = *s;  // Copy each byte from source to destination
        d++;  // Move to the next byte in the destination
        s++;  // Move to the next byte in the source
    }
    return dest;  // Return the destination pointer
}

// Custom malloc implementation
void *ft_malloc(size_t size) {
    if (size <= 0) return NULL; // If the size is 0 or negative, return NULL

    t_block *current = global_base, *last = NULL;
    
    // Look for a free block with enough space
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0; // Mark the block as allocated
            return (void*)(current + 1); // Return the memory block (after the header)
        }
        last = current;
        current = current->next;
    }

    // If no suitable free block was found, request more memory using sbrk()
    t_block *new_block = (t_block*)sbrk(BLOCK_SIZE + size);
    if (new_block == (void*)-1) return NULL; // If sbrk() fails, return NULL

    // Initialize the new block
    new_block->size = size;
    new_block->free = 0;
    new_block->next = NULL;

    // Link the new block to the last block in the list
    if (last) last->next = new_block;
    else global_base = new_block;

    return (void*)(new_block + 1); // Return memory block (after the header)
}

// Custom free implementation
void ft_free(void *ptr) {
    if (!ptr) return; // If the pointer is NULL, do nothing

    t_block *block = (t_block*)ptr - 1; // Get the header of the block
    block->free = 1; // Mark the block as free

    // Attempt to merge with next block if free
    if (block->next && block->next->free) {
        block->size += BLOCK_SIZE + block->next->size;
        block->next = block->next->next;
    }

    // Traverse the memory blocks and merge adjacent free blocks
    t_block *current = global_base;
    while (current) {
        // Merge with previous block if free
        if (current->next == block && current->free) {
            current->size += BLOCK_SIZE + block->size;
            current->next = block->next;
            break;  // No need to continue after merging
        }

        // Merge with next block if free
        if (current->free && current->next && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size; // Merge the blocks
            current->next = current->next->next; // Link to the next non-free block
        }

        current = current->next;
    }
}


// Custom calloc implementation
void *ft_calloc(size_t nmemb, size_t size) {
    size_t total_size = nmemb * size; // Calculate total size required
    void *ptr = ft_malloc(total_size); // Allocate memory using malloc
    if (ptr) ft_memset(ptr, 0, total_size); // Initialize the allocated memory to 0
    return ptr;
}

// Custom realloc implementation
void *ft_realloc(void *ptr, size_t size) {
    if (!ptr) return ft_malloc(size); // If the pointer is NULL, behave like malloc()
    if (size == 0) { ft_free(ptr); return NULL; } // If size is 0, free the memory and return NULL

    t_block *block = (t_block*)ptr - 1;
    if (block->size >= size) return ptr; // If the current block is already large enough, return the same pointer

    // If the block cannot be expanded, allocate a new block with the requested size
    void *new_ptr = ft_malloc(size);
    if (!new_ptr) return NULL; // If malloc fails, return NULL

    // Copy the data from the old block to the new block
    //ft_memcpy(new_ptr, ptr, block->size);
    // // Copy only the minimum of the two sizes to prevent overflow
    // ft_memcpy(new_ptr, ptr, (block->size < size) ? block->size : size);
    size_t copy_size;
    if (block->size < size) {
        copy_size = block->size;
    } else {
        copy_size = size;
    }
    ft_memcpy(new_ptr, ptr, copy_size);
    ft_free(ptr); // Free the old block
    return new_ptr; // Return the new block
}

// Custom function to write an integer to the standard output
void ft_write(int num) {
    char buffer[20];  // Buffer to hold the integer as a string
    int i = 0, j;
    int is_negative = 0; // Flag to check if the number is negative

    if (num == 0) {
        buffer[i++] = '0'; // If the number is 0, write '0'
    } else {
        if (num < 0) {
            is_negative = 1; // Mark as negative
            num = -num; // Make the number positive for easier processing
        }

        // Convert integer to string (digit by digit)
        while (num > 0) {
            buffer[i++] = (num % 10) + '0'; // Get the last digit and store it as a character
            num /= 10; // Remove the last digit
        }

        if (is_negative) {
            buffer[i++] = '-'; // If the number was negative, add the '-' sign
        }

        // Reverse the string (since digits were added in reverse order)
        int j = 0;
        while (j < i / 2) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
            j++;
        }
    }

    write(1, buffer, i); // Write the string to standard output
}

//for debug
void ft_print_heap() {
    t_block *current = global_base;
    while (current) {
        printf("[Block: %p | Size: %zu | Free: %d]\n", current, current->size, current->free);
        current = current->next;
    }
}


// Main function to test malloc, free, calloc, realloc
// int main() {
//     int *arr = (int*) ft_malloc(5 * sizeof(int)); // Allocate memory for 5 integers
//     int i = 0;

//     // Initialize the array with values using while loop
//     while (i < 5) {
//         arr[i] = i; 
//         i++;
//     }

//     // Print the array using ft_write
//     i = 0;
//     while (i < 5) {
//         ft_write(arr[i]);
//         i++;
//     }
//     write(1, "\n", 1); // Print a newline

//     ft_free(arr); // Free the allocated memory

//     // Test realloc
//     int *arr2 = (int*) ft_malloc(3 * sizeof(int)); // Allocate memory for 3 integers
//     i = 0;

//     // Initialize the array with values using while loop
//     while (i < 3) {
//         arr2[i] = i * 2;
//         i++;
//     }

//     // Print the array using ft_write
//     i = 0;
//     while (i < 3) {
//         ft_write(arr2[i]);
//         i++;
//     }
//     write(1, "\n", 1); // Print a newline

//     ft_free(arr2); // Free the allocated memory

//     // Test calloc
//     int *buffer = (int*) ft_calloc(5, sizeof(int)); // Allocate and initialize memory with zeros
//     i = 0;
//     while (i < 5) {
//         ft_write(buffer[i]);
//         i++;
//     }
//     write(1, "\n", 1); // Print a newline

//     // Test realloc with new size
//     buffer = (int*) ft_realloc(buffer, 10 * sizeof(int)); // Resize the array
//     i = 0;
//     while (i < 10) {
//         buffer[i] = i * 2; // Initialize the new elements
//         i++;
//     }

//     // Print the resized array using ft_write
//     i = 0;
//     while (i < 10) {
//         ft_write(buffer[i]);
//         i++;
//     }
//     write(1, "\n", 1); // Print a newline

//     ft_free(buffer); // Free the allocated memory
//     return 0; // Exit the program
// }
