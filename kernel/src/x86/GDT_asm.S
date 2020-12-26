.global GDT_flush
GDT_flush:
    mov 4(%esp), %eax
    
    lgdt (%eax)

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    jmp $0x08, $flush

flush:
    ret


.global IDT_flush
IDT_flush:
    mov 4(%esp), %eax  # Get the pointer to the IDT, passed as a parameter.
    lidt (%eax)        # Load the IDT pointer.
    ret
