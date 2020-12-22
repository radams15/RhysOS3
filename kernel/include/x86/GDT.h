#ifndef GDT_H_INCLUDED
#define GDT_H_INCLUDED

#include <Types.h>

extern void GDT_flush(uint32);

// Internal function prototypes.
void GDT_init();
void GDT_set_gate(uint32, uint32, uint32, uint8, uint8);

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct GDT_entry_struct {
    uint16 limit_low;           // The lower 16 bits of the limit.
    uint16 base_low;            // The lower 16 bits of the base.
    uint8 base_middle;         // The next 8 bits of the base.
    uint8 access;              // Access flags, determine what ring this segment can be used in.
    uint8 granularity;
    uint8 base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct GDT_entry_struct GDT_entry_t;

// This struct describes a GDT pointer. It points to the start of
// our array of GDT entries, and is in the format required by the
// lgdt instruction.
struct GDT_ptr_struct {
    uint16 limit;               // The upper 16 bits of all selector limits.
    uint32 base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));
typedef struct GDT_ptr_struct GDT_ptr_t;

#endif // GDT_H_INCLUDED
