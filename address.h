#ifndef _address_h
#define _address_h

#define DEVMEM_MAP_SIZE 4096
#define DEVMEM_MAP_MASK (off_t)(DEVMEM_MAP_SIZE - 1)

#define SYNC_BASE 0x40008038
#define SYNC_OFFSET 0x1000

#define PORT_DL_BASE 0x40001044
#define PORT_UL_BASE 0x40001048
#define PORT_OFFSET 0x0040

#define UL_CH_BASE 0x40000850
#define DL_CH_BASE 0x40000050
#define CH_OFFSET 0x0040

#endif