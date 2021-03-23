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
#include "byutr.h"
#include "output_mode_helpers.h"
#include <vector>
// extern "C" int NextAddress(FILE, p2AddrTr);
using namespace std;

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
    vector<int> addys;
    bool nFlag = false, bFlag = false, l2PFlag = false, p2FFlag = false, ofFlag = false, rSum = false;
    //**************************** FOR TESTING PURPOSES ONLY **************************
    // int bits = 20;

    int levelCount = 5;
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
            cout << "We got #:" << numberOfAddresses;
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
        default:
            //print something about the usage and die...
            cout << "Does not exist";
            exit(1);
    
        }
    }

    string filename = argv[optind];
    FILE *fp;
     fopen(filename.c_str(), "r"); 
    p2AddrTr trace_item;  /* Structure with trace information */
  bool done = false;
    if (fp == NULL) { 
        //Fail to read
        fprintf(stderr, "Unable to open & read file: %s\n", filename.c_str());
        exit(1);
    } 

  while (! done) {
    // Grabs the next address
    int bytesread = NextAddress(fp, &trace_item);
    // Check if we actually got something
    done = bytesread == 0;
    if (! done) 
      printf("Address %x\n", trace_item.addr);
  }


    return 0;
}

// ./pagetable -n 10000 trace.sample.tr 8 7 4