#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include "getpow_read.h"
#include "address.h"

char *sync_name[8] = {"TXSYNC_A", "RXSYNC_A", "TXSYNC_B", "RXSYNC_B", "TXSYNC_C", "RXSYNC_C", "TXSYNC_D", "RXSYNC_D"};

void DL_CH_POW(void)
{
    int i;
    uint32_t offset;
    volatile uint32_t ret;
    volatile long double t;
    long double num;
    while (1)
    {
        system("clear");
        printf("DL_CH_POW\n");
        for (i = 0; i < 32; i++)
        {
            offset = i * CH_OFFSET;
            ret = register_read(DL_CH_BASE + offset);
            t = log10(ret / 21474.83648) - 5;
            num = 10 * t;
            printf("\tDL_CH_POW%d:\t%lf\n", i, num);
        }
        sleep(1);
    }
}
void UL_CH_POW(void)
{
    int i;
    uint32_t offset;
    volatile uint32_t ret;
    volatile long double t;
    long double num;
    while (1)
    {
        system("clear");
        printf("UL_CH_POW\n");
        for (i = 0; i < 32; i++)
        {
            offset = i * CH_OFFSET;
            ret = register_read(UL_CH_BASE + offset);
            t = log10(ret / 21474.83648) - 5;
            num = 10 * t;
            printf("\tUL_CH_POW%d:\t%lf\n", i, num);
        }
        sleep(1);
    }
}
void PO_DL_POW(void)
{
    int i;
    uint32_t offset;
    volatile uint32_t ret;
    volatile long double t;
    long double num;
    while (1)
    {
        system("clear");
        printf("PORT_DL_POWER\n");
        for (i = 0; i < 8; i++)
        {
            offset = i * PORT_OFFSET;
            ret = register_read(PORT_DL_BASE + offset);
            t = log10(ret / 21474.83648) - 5;
            num = 10 * t;
            printf("\tPORT_DL_POWER%d:\t%lf\n", i, num);
        }
        sleep(1);
    }
}
void PO_UL_POW(void)
{
    int i;
    uint32_t offset;
    volatile uint32_t ret;
    volatile long double t;
    long double num;
    while (1)
    {
        system("clear");
        printf("PORT_UL_POWER\n");
        for (i = 0; i < 8; i++)
        {
            offset = i * PORT_OFFSET;
            ret = register_read(PORT_UL_BASE + offset);
            t = log10(ret / 21474.83648) - 5;
            num = 10 * t;
            printf("\tPORT_UL_POWER%d:\t%lf\n", i, num);
        }
        sleep(1);
    }
}
void SYNC_POW(void)
{
    int i;
    volatile uint32_t offset, addr;
    while (1)
    {
        system("clear");
        printf("SYNC\n");
        for (i = 0; i < 8; i++)
        {
            addr = i * SYNC_OFFSET;
            printf("\t%s:\t", sync_name[i]);
            printf("0x%lX\n", register_read(SYNC_BASE + addr));
        }
        sleep(1);
    }
}