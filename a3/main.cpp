#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
using namespace std;

void report_logical2offset(uint32_t logical, uint32_t offset) {
    fprintf(stdout, "%08X -> %08X\n", logical, offset);
}

void report_summary(unsigned int page_size, unsigned int hits, unsigned int addresses, unsigned int frames_used, unsigned int bytes) {
    unsigned int misses;
    double hit_percent;

    printf("Page size: %d bytes\n", page_size);
    misses = addresses - hits;
    hit_percent = (double) hits / addresses * 100.0;
    printf("Addresses processed: %d\n", addresses);
    printf("Hits: %d (%.2f%%), Misses %d (%.2f%%)\n", hits, hit_percent, misses, 100 - hit_percent);
    printf("Frames allocated: %d\n", frames_used);
    printf("Bytes used: %d\n", bytes);
}

void report_bitmasks(int levels, uint32_t *masks) {
    printf("Bitmasks\n");
    for (int i = 0; i < levels; i++){
        /* show mask entry and move to next */
        printf("level %d mask %08X\n", i, masks[i]);
    }
}

void report_pagemap(uint32_t logical_addr, int levels, uint32_t *pages, uint32_t frame) {
    printf("%08X: ", logical_addr);
    for(int i = 0; i < levels; i++) {
        printf("%X ", pages[i]);
    }
    printf("-> %X\n", frame);
}


int main(int argc, char **argv) {
    int idx;
    int Option;
    while ( (Option = getopt(argc, argv, "n:o:")) != -1){
        switch (Option) {
            case 'n':   //Number of addys to process
            //optarg will contain the string folliwng -n
            //Process appropriately (e.g. convert to integer atoi(optarg))
                break;
            case 'o': /*produce map of pages */
            //optarg contains the output method...
                break;
            default:
                //print something about the usage and die...
                exit(1); //BADFLAG is an error # defined in a header
        }
    }
    idx = optind;
    return 0;
}