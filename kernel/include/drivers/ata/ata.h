#ifndef RHYSOS_ATA_H
#define RHYSOS_ATA_H

#include <Types.h>
#include <x86/io.h>
#include <memory.h>

#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

#define ATA_CHUNK 256

uint16* ATA_PIO_read_sect(uint32 LBA, uint8 sector_count);
void ATA_PIO_write_sect(uint32 LBA, uint8 sector_count, uint32* bytes);

void ATA_PIO_wait_BSY();
void ATA_PIO_wait_DRQ();

#endif //RHYSOS_ATA_H