#include "memory_manager.h"


void mm_pool_init(struct mm_pool *pool)
{
    memset(pool->memory, 0, mem_size(pool->block_size, pool->nr_blocks)); /*This sets the contents of the memory pool by Zeros*/
    pool->first_free = (struct mm_block_hdr *)pool->memory;
    
    struct mm_block_hdr * current_block = pool->first_free;

    for(int i = 0; i < (pool->nr_blocks)-1; i++){
        current_block->next = (struct mm_block_hdr *)(((char *)(current_block + 1)) + pool->block_size);
        current_block = current_block->next;
        pool->nr_free_blocks++; 
    }

    current_block->next = NULL;
    pool->nr_free_blocks++; 
    
}
void * mm_allocate(struct mm_pool *pool)
{
    void *data = NULL;
    if(pool->nr_free_blocks > 0 ){
        data = (void *)(((char *)(pool->first_free)) + sizeof(struct mm_block_hdr));
        pool->first_free = pool->first_free->next;
        pool->nr_free_blocks--;
    }
    return data;
}
void mm_free(void * data, struct mm_pool *pool)
{   
    if(pool->nr_free_blocks < pool->nr_blocks){
        struct mm_block_hdr *block = (struct mm_block_hdr *)(((char *)data) - sizeof(struct mm_block_hdr));
        block->next = pool->first_free;
        pool->first_free = block;
        pool->nr_free_blocks++;
        
    }
}
void mm_show_stats(struct mm_pool *pool)
{
    printf("Number of Free Blocks is: %d\n", pool->nr_free_blocks);
    struct mm_block_hdr *block = pool->first_free;
    while(block != NULL){
        printf("%p\n", block);
        block = block->next;
    }

}