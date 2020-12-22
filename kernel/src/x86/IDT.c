//
// Created by rhys on 31/10/2020.
//

#include <x86/IDT.h>


idt_entry_t IDT_entries[256];
idt_ptr_t   IDT_ptr;

void IDT_init(){
    IDT_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    IDT_ptr.base  = (uint32)&IDT_entries;

    memset((uint8)&IDT_entries, 0, sizeof(idt_entry_t)*256);

    IDT_set_gate( 0, (uint32)isr0 , 0x08, 0x8E);
    IDT_set_gate( 1, (uint32)isr1 , 0x08, 0x8E);
    IDT_set_gate( 2, (uint32)isr2 , 0x08, 0x8E);
    IDT_set_gate( 3, (uint32)isr3 , 0x08, 0x8E);
    IDT_set_gate( 4, (uint32)isr4 , 0x08, 0x8E);
    IDT_set_gate( 5, (uint32)isr5 , 0x08, 0x8E);
    IDT_set_gate( 6, (uint32)isr6 , 0x08, 0x8E);
    IDT_set_gate( 7, (uint32)isr7 , 0x08, 0x8E);
    IDT_set_gate( 8, (uint32)isr8 , 0x08, 0x8E);
    IDT_set_gate( 9, (uint32)isr9 , 0x08, 0x8E);
    IDT_set_gate(10, (uint32)isr10, 0x08, 0x8E);
    IDT_set_gate(11, (uint32)isr11, 0x08, 0x8E);
    IDT_set_gate(12, (uint32)isr12, 0x08, 0x8E);
    IDT_set_gate(13, (uint32)isr13, 0x08, 0x8E);
    IDT_set_gate(14, (uint32)isr14, 0x08, 0x8E);
    IDT_set_gate(15, (uint32)isr15, 0x08, 0x8E);
    IDT_set_gate(16, (uint32)isr16, 0x08, 0x8E);
    IDT_set_gate(17, (uint32)isr17, 0x08, 0x8E);
    IDT_set_gate(18, (uint32)isr18, 0x08, 0x8E);
    IDT_set_gate(19, (uint32)isr19, 0x08, 0x8E);
    IDT_set_gate(20, (uint32)isr20, 0x08, 0x8E);
    IDT_set_gate(21, (uint32)isr21, 0x08, 0x8E);
    IDT_set_gate(22, (uint32)isr22, 0x08, 0x8E);
    IDT_set_gate(23, (uint32)isr23, 0x08, 0x8E);
    IDT_set_gate(24, (uint32)isr24, 0x08, 0x8E);
    IDT_set_gate(25, (uint32)isr25, 0x08, 0x8E);
    IDT_set_gate(26, (uint32)isr26, 0x08, 0x8E);
    IDT_set_gate(27, (uint32)isr27, 0x08, 0x8E);
    IDT_set_gate(28, (uint32)isr28, 0x08, 0x8E);
    IDT_set_gate(29, (uint32)isr29, 0x08, 0x8E);
    IDT_set_gate(30, (uint32)isr30, 0x08, 0x8E);
    IDT_set_gate(31, (uint32)isr31, 0x08, 0x8E);

    IDT_flush((uint32)&IDT_ptr);

    serial_write("Initialised IDTs\n");
}

void IDT_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags){
    IDT_entries[num].base_lo = base & 0xFFFF;
    IDT_entries[num].base_hi = (base >> 16) & 0xFFFF;

    IDT_entries[num].sel     = sel;
    IDT_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    IDT_entries[num].flags   = flags /* | 0x60 */;
}
