//
// Created by rhys on 31/10/2020.
//

#include <memory.h>

uint32 mem_placement_address = (uint32) &mem_end;

void memset(uint8* dest, uint8 val, uint32 len){
    uint8* temp = dest;
    for ( ; len != 0; len--){
        *temp++ = val;
    }
}

void memncpy(void* a, void* b, uint32 len){
    for(; len != 0; len--){
        (&a)[len] = (&b)[len];
    }
}

void kfree(uint32 ptr){};

void* kmalloc(uint32 size){
    uint32* buf = NULL;
    return (void*) kmalloc_phys(size, FALSE, buf);
}

void* kcalloc(uint32 length, uint32 size){
    uint32* mem = (uint32*) kmalloc(length*size);

    for(int i=0 ; i<size ; i++) mem[i] = 0;

    return (void*) mem;
}

void* kmalloc_align(uint32 size){
    uint32* buf = NULL;
    return (void*) kmalloc_phys(size, TRUE, buf);
}

void* kmalloc_align_phys(uint32 size, uint32* physical_buf){
    return (void*) kmalloc_phys(size, TRUE, physical_buf);
}

void* kmalloc_phys(uint32 size, bool align, uint32* physical_buf) {
    if (align && (mem_placement_address & 0xFFFFF000)){ // If the address is not page-aligned, align it
        mem_placement_address &= 0xFFFFF000;
        mem_placement_address += 0x1000;
    }

    serial_write("Allocated %d bits, now at <%x>\n", size, mem_placement_address);

    if (physical_buf){
        *physical_buf = mem_placement_address;
    }
    uint32 tmp = mem_placement_address;
    mem_placement_address += size;

    return (void*) tmp;
}

void* krealloc(void* ptr, uint32 new_size){
    void* new_ptr = kmalloc(new_size);
    memncpy(new_ptr, ptr, new_size);
    return new_ptr;
}
