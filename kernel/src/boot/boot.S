.set MBALIGN,  1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    MBALIGN | MEMINFO  /* this is the Multiboot 'flag' field */ // add "| 0x4" for graphics mode
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.global mboot
.global code
.global bss
.global mem_end

mboot:
    .align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

    .long mboot
    .long code
    .long bss
    .long mem_end
    .long start
    /*.long 0 // for graphics mode
    .long 1024 #1920;
    .long 768  #1080;
    .long 32*/

.global start
start:
	push %ebx
	cli
	call kmain
	jmp loop

loop:
    hlt
	jmp loop
