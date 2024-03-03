/*This is a Fixed block size memory manager*/
#include "memory_manager.h"

#define Nr_Blocks   8
#define Block_Size 16

char my_memory[mem_size(Block_Size,Nr_Blocks)];
struct mm_pool Memory_Pool = {.memory = my_memory, .nr_blocks = Nr_Blocks, .block_size = Block_Size};

int main(void){

    mm_pool_init(&Memory_Pool);
    mm_show_stats(&Memory_Pool);

    void *b1 = mm_allocate(&Memory_Pool);
    void *b2 = mm_allocate(&Memory_Pool);
    mm_show_stats(&Memory_Pool);
    mm_free(b1, &Memory_Pool);
    mm_show_stats(&Memory_Pool);
    mm_free(b2, &Memory_Pool);
    mm_show_stats(&Memory_Pool);
    
    
}

