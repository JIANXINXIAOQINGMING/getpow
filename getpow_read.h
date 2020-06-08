#ifndef GETPOW_READ
#define GETPOW_READ

#include <stdint.h>
extern int register_read(uint32_t addr);
int get_system_open(char *cmd, char *data_buff);
int open_device(char *dev, char *data_buff, int where_start, int data_len);

#endif