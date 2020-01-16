#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "print.h"

void print_usage(FILE *stream, int exit_code)
{
    fprintf(stream,
            "\t-h  --help     Display this usage information.\n"
            "\t-d  --dlch    \n"
            "\t-u  --ulch   \n"
            "\t-s  --sync    \n"
            "\t-r  --podl    \n"
            "\t-l  --poul    \n");
    exit(exit_code);
}

int main(int argc, char *argv[])
{
    int next_option = 1;
    int re_val;

    const char *const short_options = "hdusrl";
    const struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"dlch", 0, NULL, 'd'},
        {"ulch", 0, NULL, 'u'},
        {"sync", 0, NULL, 's'},
        {"podl", 0, NULL, 'r'},
        {"poul", 0, NULL, 'l'},
        {NULL, 0, NULL, 0}};

    while (next_option != -1)
    {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (next_option)
        {
        case 'h':
            print_usage(stdout, 0);
        case 'd':
            DL_CH_POW();
            break;
        case 'u':
            UL_CH_POW();
            break;
        case 's':
            SYNC_POW();
            break;
        case 'r':
            PO_DL_POW();
            break;
        case 'l':
            PO_UL_POW();
            break;
        }
    }
}