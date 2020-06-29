#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "print.h"

#define version 1.2

void print_usage(FILE *stream, int exit_code)
{
    printf("\tgetpow version: %02.02f\n", version);
    fprintf(stream,
            "\t-h  --help     Display this usage information\n"
            "\t-d  --dlch     DL channal power (DL carrier power x24)\n"
            "\t-u  --ulch     UL channal power (UL carrier power x24)\n"
            "\t-s  --sync     JESD sync status\n"
            "\t-i  --podl     DL PORT input power (Data from ADC , input power)\n"
            "\t-o  --poul     UL PORT output power (Data to DAC , output power)\n"
            "\t-t  --time     Refresh times\n"
            "\t-m  --mode     Display method\n"
            "\t-f  --fan      FAN RPM and FPGA Temperature\n");
    exit(exit_code);
}

int main(int argc, char *argv[])
{
    int next_option = 1;
    int num[8]={0};
    short flag=0;

    const char *const short_options = "hdusiot:fm";
    const struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"dlch", 0, NULL, 'd'},
        {"ulch", 0, NULL, 'u'},
        {"sync", 0, NULL, 's'},
        {"podl", 0, NULL, 'i'},
        {"poul", 0, NULL, 'o'},
        {"time", 1, NULL, 't'},
        {"mode", 0, NULL, 'm'},
        {"fan", 0, NULL, 'f'},
        {NULL, 0, NULL, 0}};

    while (1)
    {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        if(next_option==-1)
            break;
        else
            flag++;

        switch (next_option)
        {
        case 'h':
            print_usage(stdout, EXIT_SUCCESS);
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
        case 'm':
            num[7] = 1;
            break;
        }


    }
    if(flag!=0)
        getpow(num);
    else
        print_usage(stderr, EXIT_FAILURE);
}