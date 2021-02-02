#include <drivers/ata/ata.h>

uint16* ATA_PIO_read_sect(uint32 LBA, uint8 sector_count){
    ATA_PIO_wait_BSY();

    outb(0x1F6,0xE0 | ((LBA >>24) & 0xF));
    outb(0x1F2,sector_count);
    outb(0x1F3, (uint8) LBA);
    outb(0x1F4, (uint8)(LBA >> 8));
    outb(0x1F5, (uint8)(LBA >> 16));
    outb(0x1F7,0x20); //Send the read command

    uint16* target = kcalloc(sector_count*ATA_CHUNK, sizeof(uint16));

    for (int j=0 ; j<sector_count ; j++){
        ATA_PIO_wait_BSY();
        ATA_PIO_wait_DRQ();

        for(int i=0 ; i<ATA_CHUNK ; i++) {
            target[i] = inw(0x1F0);
        }

        //target += ATA_CHUNK;
    }

    return target;
}

void ATA_PIO_write_sect(uint32 LBA, uint8 sector_count, uint32* bytes){
    ATA_PIO_wait_BSY();
    outb(0x1F6,0xE0 | ((LBA >>24) & 0xF));
    outb(0x1F2,sector_count);
    outb(0x1F3, (uint8) LBA);
    outb(0x1F4, (uint8)(LBA >> 8));
    outb(0x1F5, (uint8)(LBA >> 16));
    outb(0x1F7,0x30); //Send the write command

    for (int j=0 ; j<sector_count ; j++){
        ATA_PIO_wait_BSY();
        ATA_PIO_wait_DRQ();

        for(int i=0;i<ATA_CHUNK;i++){
            outl(0x1F0, bytes[i]);
        }
    }
}

void ATA_PIO_wait_BSY(){
    while(inb(0x1F7)&STATUS_BSY);
}

void ATA_PIO_wait_DRQ(){
    while(!(inb(0x1F7)&STATUS_RDY));
}