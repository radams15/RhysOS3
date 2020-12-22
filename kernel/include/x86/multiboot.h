#include <Types.h>

struct multiboot_header
{
    /* Must be MULTIBOOT_MAGIC - see above. */
    uint32 magic;

    /* Feature flags. */
    uint32 flags;

    /* The above fields plus this one must equal 0 mod 2^32. */
    uint32 checksum;

    /* These are only valid if MULTIBOOT_AOUT_KLUDGE is set. */
    uint32 header_addr;
    uint32 load_addr;
    uint32 load_end_addr;
    uint32 bss_end_addr;
    uint32 entry_addr;

    /* These are only valid if MULTIBOOT_VIDEO_MODE is set. */
    uint32 modeype;
    uint32 width;
    uint32 height;
    uint32 depth;
};

/* The symbol table for a.out. */
struct multiboot_aout_symbolable
{
    uint32 tabsize;
    uint32 strsize;
    uint32 addr;
    uint32 reserved;
};
typedef struct multiboot_aout_symbolable multiboot_aout_symbolable;

/* The section header table for ELF. */
struct multiboot_elf_section_headerable
{
    uint32 num;
    uint32 size;
    uint32 addr;
    uint32 shndx;
};
typedef struct multiboot_elf_section_headerable multiboot_elf_section_headerable;

struct multiboot_info
{
    uint32 flags;
    uint32 mem_lower;
    uint32 mem_upper;
    uint32 boot_device;
    uint32 cmdline;
    uint32 mods_count;
    uint32 mods_addr;
    union
    {
        multiboot_aout_symbolable aout_sym;
        multiboot_elf_section_headerable elf_sec;
    } u;
    uint32 mmap_length;
    uint32 mmap_addr;
    uint32 drives_length;
    uint32 drives_addr;
    uint32 configable;
    uint32 boot_loader_name;
    uint32 apmable;
    uint32 vbe_control_info;
    uint32 vbe_mode_info;
    uint16 vbe_mode;
    uint16 vbe_interface_seg;
    uint16 vbe_interface_off;
    uint16 vbe_interface_len;
    uint32 framebuffer_addr;
    uint32 framebuffer_pitch;
    uint32 framebuffer_width;
    uint32 framebuffer_height;
    uint8 framebuffer_bpp;
    uint8 framebufferype;
    union
    {
        struct
        {
            uint32 framebuffer_palette_addr;
            uint16 framebuffer_palette_num_colors;
        };
        struct
        {
            uint8 framebuffer_red_field_position;
            uint8 framebuffer_red_mask_size;
            uint8 framebuffer_green_field_position;
            uint8 framebuffer_green_mask_size;
            uint8 framebuffer_blue_field_position;
            uint8 framebuffer_blue_mask_size;
        };
    };
};
typedef struct multiboot_info multiboot_info;
struct multiboot_color
{
    uint8 red;
    uint8 green;
    uint8 blue;
};

struct multiboot_mmap_entry
{
    uint32 size;
    uint32 addr;
    uint32 len;
    uint32 type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map;

struct multiboot_mod_list
{
    /* the memory used goes from bytes ’mod_start’ to ’mod_end-1’ inclusive */      uint32 mod_start;
    uint32 mod_end;

    /* Module command line */
    uint32 cmdline;

    /* padding to take it to 16 bytes (must be zero) */
    uint32 pad;
};
typedef struct multiboot_mod_list multiboot_module;

/* APM BIOS info. */
struct multiboot_apm_info
{
    uint16 version;
    uint16 cseg;
    uint32 offset;
    uint16 cseg_16;
    uint16 dseg;
    uint16 flags;
    uint16 cseg_len;
    uint16 cseg_16_len;
    uint16 dseg_len;
};
