#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "print.h"

#define version 1.1
int num[7];

void print_usage(FILE *stream, int exit_code)
{
    printf("\tgetpow version: %d\n", version);
    fprintf(stream,
            "\t-h  --help     Display this usage information\n"
            "\t-d  --dlch     DL channal power (DL carrier power x24)\n"
            "\t-u  --ulch     UL channal power (UL carrier power x24)\n"
            "\t-s  --sync     JESD sync status\n"
            "\t-i  --podl     DL PORT input power (Data from ADC , input power)\n"
            "\t-o  --poul     UL PORT output power (Data to DAC , output power)\n"
            "\t-t  --time     Refresh times\n"
            "\t-f  --fan      FAN RPM and FPGA Temperature\n");
    exit(exit_code);
}

int main(int argc, char *argv[])
{
    int next_option = 1;
    int re_val;

    const char *const short_options = "hdusiot:f";
    const struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"dlch", 0, NULL, 'd'},
        {"ulch", 0, NULL, 'u'},
        {"sync", 0, NULL, 's'},
        {"podl", 0, NULL, 'i'},
        {"poul", 0, NULL, 'o'},
        {"time", 1, NULL, 't'},
        {"fan", 0, NULL, 'f'},
        {NULL, 0, NULL, 0}};

    while (next_option != -1)
    {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (next_option)
        {
        case 'h':
            print_usage(stdout, 0);
        case 'd':
            num[0] = 1;
            break;
        case 'u':
            num[1] = 1;
            break;
        case 'i':
            num[2] = 1;
            break;
        case 'o':
            num[3] = 1;
            break;
        case 's':
            num[4] = 1;
            break;
        case 'f':
            num[5] = 1;
            break;
        case 't':
            num[6] = atoi(optarg);
            break;
        }
    }
    getpow(&num[0]);
}