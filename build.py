from os import system, mkdir
from os.path import exists, splitext
from shutil import copy, copytree, rmtree
from glob import glob

BUILD_DIRS = [
    "build",
    
    "build/kernel/",
    "build/kernel/boot",
    "build/kernel/x86",
    
    "build/iso",
    "build/iso/boot"
]

CC = "Tools/bin/i686-elf-gcc"
AS = "Tools/bin/i686-elf-as"
GRUB = "grub2-mkrescue"

STD = "gnu99"

BIN_FILE = "build/iso/boot/RhysOS.bin"
ISO_FILE = "build/RhysOS.iso"

KERNEL_LOGFILE = "kernel_log.txt"
MEMORY = 64

def run_cleanly(*args):
    print(args)
    assert system(*args) == 0

def clean():
    for d in filter(lambda x: exists(x), BUILD_DIRS):
        rmtree(d, ignore_errors=True)

def make_dirs():
    for d in filter(lambda x: not exists(x), BUILD_DIRS):
        mkdir(d)

def comp_kernel():
    obj_files = []

    system(f"{AS} kernel/src/boot/boot.S -o build/kernel/boot/boot.o")
    obj_files.append("build/kernel/boot/boot.o")
    
    asm_files = [f for f in glob("kernel/src/**/*.S", recursive=True) if f != "kernel/src/boot/boot.S"]
    
    c_files = glob("kernel/src/**/*.c", recursive=True)
    
    files = list(set(asm_files + c_files))

    for nasm_file in glob("kernel/src/**/*.nasm", recursive=True):
        obj_file = (splitext(nasm_file)[0]+".o").replace("kernel/src", "build/kernel")
        obj_files.append(obj_file)

        command = f"nasm -f elf32 -o {obj_file} {nasm_file}"

        run_cleanly(command)
    
    for c_file in files:
        obj_file = (splitext(c_file)[0]+".o").replace("kernel/src", "build/kernel")
        obj_files.append(obj_file)
        
        command = f"{CC} -std={STD} -ffreestanding -O2 -Wall -Wextra -c {c_file} -o {obj_file} -I kernel/include/"
        
        run_cleanly(command)


    return obj_files

def link_kernel(object_files):
    command = f"{CC} -g -m32 -T linker.ld -I kernel/include/ -ffreestanding -O2 -nostdlib -o {BIN_FILE} -lgcc "
    
    for o in object_files:
        command += o + " "
    
    run_cleanly(command)

def make_iso():
    copytree(f"grub/", "build/iso/boot/grub", False, None)
    
    run_cleanly(f"{GRUB} -o {ISO_FILE} build/iso")

def run_qemu():
    run_cleanly(f"qemu-system-i386 -cdrom {ISO_FILE} -m {MEMORY} -serial file:{KERNEL_LOGFILE}")

def check_iso():
    run_cleanly(f"grub2-file --is-x86-multiboot {BIN_FILE}")

if __name__ == "__main__":
    clean()
    make_dirs()
    
    objs = comp_kernel()
    link_kernel(objs)
    
    make_iso()
    check_iso()

    run_qemu()
