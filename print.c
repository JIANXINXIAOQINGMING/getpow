#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include "getpow_read.h"
#include "address.h"

#define COMPUTE(x) log10(x / 21474.83648) - 5
#define ELIXIN(y) 10 * y + 3.01
#define DECIDE(x) \
    if (x > 100)  \
    {             \
        x = 100;  \
    }

char *sync_name[8] = {"TXSYNC_A", "RXSYNC_A", "TXSYNC_B", "RXSYNC_B", "TXSYNC_C", "RXSYNC_C", "TXSYNC_D", "RXSYNC_D"};

void getpow(int *addr)
{
    int i;
    while (1)
    {
        system("clear");
        if (*addr == 1)
        {
            uint32_t offset;
            volatile uint32_t ret;
            volatile long double t;
            long double num;
            printf("DL_CH_POW:\n");
            for (i = 0; i < 32; i++)
            {
                offset = i * CH_OFFSET;
                ret = register_read(DL_CH_BASE + offset);
                t = COMPUTE(ret);
                num = ELIXIN(t);
                printf("\tDL_CH_POW%d:\t%lf dBFs\n", i, num);
            }
        }
        if (*(addr + 1) == 1)
        {
            uint32_t offset;
            volatile uint32_t ret;
            volatile long double t;
            long double num;
            printf("UL_CH_POW:\n");
            for (i = 0; i < 32; i++)
            {
                offset = i * CH_OFFSET;
                ret = register_read(UL_CH_BASE + offset);
                t = COMPUTE(ret);
                num = ELIXIN(t);
                printf("\tUL_CH_POW%d:\t%lf dBFs\n", i, num);
            }
        }
        if (*(addr + 2) == 1)
        {
            uint32_t offset;
            volatile uint32_t ret;
            volatile long double t;
            long double num;
            printf("PORT_DL_POWER\n");
            for (i = 0; i < 8; i++)
            {
                offset = i * PORT_OFFSET;
                ret = register_read(PORT_DL_BASE + offset);
                t = COMPUTE(ret);
                num = ELIXIN(t);
                printf("\tPORT_DL_POWER%d:\t%lf dBFs\n", i, num);
            }
        }
        if (*(addr + 3) == 1)
        {
            uint32_t offset;
            volatile uint32_t ret;
            volatile long double t;
            long double num;
            printf("PORT_UL_POWER\n");
            for (i = 0; i < 8; i++)
            {
                offset = i * PORT_OFFSET;
                ret = register_read(PORT_UL_BASE + offset);
                t = COMPUTE(ret);
                num = ELIXIN(t);
                printf("\tPORT_UL_POWER%d:\t%lf dBFs\n", i, num);
            }
        }
        if (*(addr + 4) == 1)
        {
            volatile uint32_t offset, sync_addr;
            printf("SYNC\n");
            for (i = 0; i < 8; i++)
            {
                sync_addr = i * SYNC_OFFSET;
                printf("\t%s:\t", sync_name[i]);
                printf("0x0000%lX\n", register_read(SYNC_BASE + sync_addr));
            }
        }
        if (*(addr + 5) == 1)
        {
            volatile uint32_t offset, pwm_sp, sum_fan, sum_pwm;
            volatile uint32_t retl[3], pwm_re[3];
            volatile long double tm;
            volatile uint32_t fan[3] = {0x31, 0x431, 0x831};
            volatile uint32_t pwm[3] = {0x21, 0x421, 0x821};
            if ((register_read(FAN1_BASE + 0x20 * FAN_OFFSET) && register_read(FAN2_BASE + 0x20 * FAN_OFFSET) && register_read(FAN3_BASE + 0x20 * FAN_OFFSET)) == 1)
            {
                printf("FAN RPM and FPGA Temperature:\n");
                for (i = 0; i < 3; i++)
                {
                    offset = fan[i] * FAN_OFFSET;
                    pwm_sp = pwm[i] * FAN_OFFSET;
                    retl[i] = register_read(FAN1_BASE + offset);
                    pwm_re[i] = register_read(FAN1_BASE + pwm_sp);
                    fan[i] = retl[i] * 30;
                    sum_fan = fan[i] / 43;
                    sum_pwm = pwm_re[i] / 43;
                    DECIDE(sum_fan);
                    DECIDE(sum_pwm);
                    printf("\tFAN RPM %d:\t%d rpm  \t  转速百分比:%d% \t  PWM占空比:%d%\n", i, fan[i], sum_fan, sum_pwm);
                }
                retl[4] = register_read(FAN1_BASE + 0x32 * FAN_OFFSET);
                tm = retl[4] * 502.9098 / 4096 / 16 - 273.8195;
                printf("\tFPGA Temperature:\t%4.2lf ℃\n", tm);
            }
            else
            {
                system("sudo devmem 0xA0018080 32 0x01");
                system("sudo devmem 0xA0019080 32 0x01");
                system("sudo devmem 0xA001A080 32 0x01");
            }
        }
        sleep(1);
    }
}