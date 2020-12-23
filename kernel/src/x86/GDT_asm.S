.global GDT_flush
.global IDT_flush

GDT_flush:
    mov 4(%esp), %eax
    
    lgdt (%eax)

    mov $0x10, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %gs
    mov %ax, %fs
    mov %ax, %es
    
    ret


IDT_flush:
    mov 4(%esp), %eax  # Get the pointer to the IDT, passed as a parameter.
    lidt (%eax)        # Load the IDT pointer.
    ret
