#include <x86/GDT.h>

GDT_entry_t GDT_entries[5];
GDT_ptr_t GDT_ptr;

void GDT_init(){
    GDT_ptr.limit = (sizeof(GDT_entry_t) * 5) - 1;
    GDT_ptr.base  = (uint32) &GDT_entries;

    GDT_set_gate(0, 0, 0, 0, 0);                // Null segment
    GDT_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    GDT_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    GDT_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    GDT_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    GDT_flush((uint32) &GDT_ptr);
}

// Set the value of one GDT entry.
void GDT_set_gate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran){
    GDT_entries[num].base_low    = (base & 0xFFFF);
    GDT_entries[num].base_middle = (base >> 16) & 0xFF;
    GDT_entries[num].base_high   = (base >> 24) & 0xFF;

    GDT_entries[num].limit_low   = (limit & 0xFFFF);
    GDT_entries[num].granularity = (limit >> 16) & 0x0F;

    GDT_entries[num].granularity |= gran & 0xF0;
    GDT_entries[num].access      = access;
}
