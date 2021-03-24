#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <map>
#include "pagetable.h"
#include "output_mode_helpers.h"
#include <vector>
#include "byutr.h"
#include <cmath>
using namespace std;

unsigned createMask(unsigned int first, unsigned int last)
{
   unsigned int start = 0;
   for (unsigned int i = first; i <= last; i++)
       start |= 1 << i;

   return start;
}

int main(int argc, char **argv)
{
    int idx;
    int Option;
    int numberOfAddresses;
    char *outputMode;
    ifstream tracers;

    PAGETABLE *pt = new PAGETABLE;
    LEVEL *lv = new LEVEL;
    idx = optind;
    vector<unsigned int> addys;
    bool nFlag = false, bFlag = false, l2PFlag = false, p2FFlag = false, ofFlag = false, rSum = false;
    //**************************** FOR TESTING PURPOSES ONLY **************************
    // int bits = 20;

    
    // pt->rootPtr = lv;
    // pt->numOfLevels = levelCount;
    // cout << "numOfLevels: " << pt->numOfLevels << "\n";

    // pt->bitMaskArr = new unsigned int[levelCount];
    // pt->shifters = new unsigned int[levelCount];
    // pt->entryCount = new unsigned int[levelCount];
    // cout << "bitmaskArr: " << pt->bitMaskArr << "\n";
    // cout << pt->bitMaskArr[0] << "\n";
    // cout << "l2a: " << std::hex << LogicalToPage(0x3c654321, 0x0FC00000, 22) << "\n"; // 0x31 aka decimal 49

    // cout << "bitmask: " << calcBitmask(20, 8) << "\n";
    // cout << "creation: " << createPageTable(pt, 1) << "\n";
    // cout << "get before"
    //      << "\n";
    // cout << pt->frameCount << "\n";
    // PageInsert(pt, 0x3c654321, pt->frameCount);
    // PageInsert(pt, 0x3c654322, pt->frameCount);
    // PageInsert(pt, 0x3c654323, pt->frameCount);
    // PageInsert(pt, 0x3c654324, pt->frameCount);
    // PageInsert(pt, 0x3c654325, pt->frameCount);
    // PageInsert(pt, 0x3c654326, pt->frameCount);
    // PageInsert(pt, 0x3c654327, pt->frameCount);
    // cout << pt->frameCount << "\n";
    // cout << "PageLookup: " << PageLookup(pt, 0x3c654322) << endl;
    // // cout << map << endl;
    // cout << pt << "\n";
    // // testing out functions
//********************************************************************************

     while ((Option = getopt(argc, argv, "n:o:")) != -1)
    {
        switch (Option)
        {
        case 'n': //Number of addys to process
            //optarg will contain the string folliwng -n
            //Process appropriately (e.g. convert to integer atoi(optarg))
            numberOfAddresses = atoi(optarg);
            nFlag = true;
            break;
        case 'o': /*produce different outputs */
            //optarg contains the output method...
            outputMode = optarg;
            if (strcmp(outputMode, "bitmasks") == 0)
            {
                // report_bitmasks(levelCount, masks);
                bFlag = true;
            }
            else if (strcmp(outputMode, "logical2physical") == 0)
            {
                // report_logical2physical(pt->rootPtr->map->frameIndex, offset);
                l2PFlag = true;
            }
            else if (strcmp(outputMode, "page2frame") == 0)
            {
                // report_pagemap(uint32_t logical_addr, int levels,
                // uint32_t *pages, uint32_t frame);
                p2FFlag = true;
            }
            else if (strcmp(outputMode, "offset") == 0)
            {
                // report_logical2offset(uint32_t logical, uint32_t offset);
                ofFlag = true;
            }
            else{
                // report_summary(unsigned int page_size, unsigned int hits,
                // unsigned int addresses, unsigned int frames_used,
                // unsigned int bytes);
                rSum = true;
                }
            break;
        default:
            //print something about the usage and die...
            cout << "Does not exist" << endl;
            exit(0);
            break;
        }
    }
    
    // cout << "bFlag: " << bFlag << endl;
    string filename = argv[optind];
    FILE *fp = fopen(filename.c_str(), "r"); 
    p2AddrTr trace_item;  /* Structure with trace information */
  bool done = false;
    if (fp == NULL) { 
        //Fail to read
        fprintf(stderr, "Unable to open & read file: %s\n", filename.c_str());
        exit(1);
    } 
  
    int levelCount = argc - (optind + 1);
    pt -> numOfLevels = levelCount;
    int offset = 32 - createPageTable(pt, argv, argc-levelCount);
    unsigned int addyCount = 0;
    while (fp) {
         if (nFlag) {
             if(numberOfAddresses <= addyCount){
                 break;
             }
             if (NextAddress(fp, &trace_item)){
                 addys.push_back(trace_item.addr);
                 unsigned int addy = (unsigned int) trace_item.addr;
                 if (PageLookup(pt, addy) == NULL) {
                     pt -> misses++;
                     PageInsert(pt, addy, pt-> frameCount);
                     
                     //OFFSET OUTPUT WORKS NOW
                    
                 }
                 else {
                 pt -> hits++;
                }
                if (p2FFlag){
                         // ./pagetable -n 20 -o page2frame trace.sample.tr 4 4 12
                         unsigned int page = addy;
                         page >>= offset;
                         MAP *map = PageLookup(pt, addy);
                         printf("%08X: ", addy);
                         printf("%X ", page);
                         printf("-> %X\n", map -> frameIndex);

                     } 
                if(ofFlag) {
                         // ./pagetable -n 20 -o offset trace.sample.tr 4 4 12
                        //our create mask method basically just shifts a 1 in 0 - levelCount * 4 - 1 amount of times to create a mask to and to get the last x amount of bytes in the address as the offset
                        unsigned int mask = createMask(0, offset - 1);
                        unsigned int oHolder = addy & mask;
                        report_logical2offset(addy, oHolder);
                    }
                if (l2PFlag) {
                    // ./pagetable -n 20 -o logical2physical trace.sample.tr 28
                    MAP *map = PageLookup(pt, addy);
                    int hex = offset / 4;
                    unsigned int translation = map -> frameIndex * pow(16, hex);
                    unsigned int mask = createMask(0, offset - 1);
                    unsigned int oHolder = (addy & mask) + translation;
                    report_logical2physical(addy, oHolder);
                } 
             }
             addyCount++;
         }
    }
    if(bFlag) {
        // ./pagetable -n 10000 -o bitmasks trace.sample.tr 4 4 12
        /* show mask entry and move to next */
         report_bitmasks(pt -> numOfLevels, pt ->bitMaskArr);
    } else if(rSum) {
        // ./pagetable -n 100000 -o summary trace.sample.tr 20
        unsigned int page_size = sizeof(pt); // ?
        unsigned int bytes = 0; // ?
        printf("Page size: %d bytes\n", page_size);
        printf("Addresses processed: %d\n", addyCount);
        double hit_percent = (double) pt->hits / addyCount * 100.0;
        printf("Hits: %d (%.2f%%), Misses %d (%.2f%%)\n", 
	    pt->hits, hit_percent, pt->misses, 100 - hit_percent);
        printf("Frames allocated: %d\n", pt->frameCount);
        printf("Bytes used:  %d\n", bytes);
    }
  

//CALCULATE ALL ACCURACIES AND OUTPUT
 fclose(fp);
    return 0;
}

// ./pagetable -n 10000 trace.sample.tr 8 7 4
