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

//main helper function to get the amount of bits we want in a mask
//i.e if we want the first 3 bytes of an unsigned int we pass this function 0 - 11
//Kind of our workaround on how to create a bitmask for the offset grabbing specifically
unsigned createMask(unsigned int first, unsigned int last)
{
    //starts with unsigned int of 0
    unsigned int start = 0;
    //for the first -> last  bits, we shift in a 1 to create a mask
    for (unsigned int i = first; i < last + 1; i++)
        start |= 1 << i;

    return start; //return our mask
}

//start of our driver function
int main(int argc, char **argv)
{
    //initialization of input options
    int Option;
    int idx;
    int numberOfAddresses;
    char *outputMode;
    //Create an instance of a PAGETABLE pointer pt
    PAGETABLE *pt = new PAGETABLE;
    //Create instance of our first level pointer
    LEVEL *lv = new LEVEL;
    //Initialize a vector of all the addresses that are going to be pushed in
    vector<unsigned int> addys;
    //Set flags for all input parameters to false
    bool nFlag = false, bFlag = false, l2PFlag = false, p2FFlag = false, ofFlag = false, rSum = false, outputFlag = false;

    //While loop to grab our parameters and requirements from the user as given by the professor in pseudocode
    while ((Option = getopt(argc, argv, "n:o:")) != -1)
    {
        //Check if either (n || o) || (n && o) is input into the command line
        switch (Option)
        {
            if (optarg) {
                rSum = true;
            }
        case 'n': //Number of addys to process
            //optarg will contain the string folliwng -n
            //Process appropriately (e.g. convert to integer atoi(optarg))
            numberOfAddresses = atoi(optarg);
            nFlag = true;
            break;
        case 'o': /*produce different outputs */
            //optarg contains the output method...
            //set flags based on what output mode -o "..." is specified by the user
            outputMode = optarg;
            if (strcmp(outputMode, "bitmasks") == 0)
            {
                bFlag = true;
            }
            else if (strcmp(outputMode, "logical2physical") == 0)
            {
                l2PFlag = true;
            }
            else if (strcmp(outputMode, "page2frame") == 0)
            {
                p2FFlag = true;
            }
            else if (strcmp(outputMode, "offset") == 0)
            {
                ofFlag = true;
            }
            else
            {
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
    //Retrieve the file path from commandline
    idx = optind;
    string filename = argv[idx];
    FILE *fp = fopen(filename.c_str(), "r");
    //Create p2AddrTr from BYU tracefile to read in addresses
    p2AddrTr trace_item; /* Structure with trace information */
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file: %s\n", filename.c_str());
        exit(1);
    }

    //Counter to hold the number of addresses read
    unsigned int addyCount = 0;
    //Number of levels will be the last numeric arguments of command line inputs
    int numOfLevels = argc - (idx + 1);
    //set our number of levels for the page table to be what was calculated above
    pt->numOfLevels = numOfLevels;
    //calculate amount of bits used by calling the createPageTable function and setting it to our previously initialized PAGETABLE pointer pt
    int bitUsed = createPageTable(pt, argv, argc - numOfLevels);
    //calculate the offset by doing 32 - bits used returned from the createPageTable fucntion
    int offset = 32 - bitUsed;

    //Loop while the file is not done
    while (fp)
    {
        //If there is an -n flag detected, we make sure that we do not process more than the given amount
        if (nFlag)
        {
            if (numberOfAddresses <= addyCount)
            {
                break;
            }
        }
            //Check that there is another address given to us
        if (NextAddress(fp, &trace_item)){
                //Append the address into our array addys
                addys.push_back(trace_item.addr);
                unsigned int addy = (unsigned int)trace_item.addr;
                //Check if the page is in the table and if not
                if (PageLookup(pt, addy) == NULL)
                {
                    //increment misses for our pt
                    pt->misses++;
                    //insert the page into the pt
                    PageInsert(pt, addy, pt->frameCount);
                    //OFFSET OUTPUT WORKS NOW
                }
                else
                {
                    //the address is in our page table and we can increment hits
                    pt->hits++;
                }
                // if -n page2frame is passed in on command line
                if (p2FFlag)
                {
                    //This method is not fully functional
                    unsigned int page = addy;
                    page >>= offset;
                    MAP *map = PageLookup(pt, addy);
                    printf("%08X: ", addy);
                    printf("%X ", page);
                    printf("-> %X\n", map->frameIndex);
                }
                // if -n offset is passed in on command line
                if (ofFlag)
                {
                    // our create mask method basically just shifts a 1 in 0 - numOfLevels * 4 - 1 amount of times to create a mask to and to get the last x amount of bytes in the address as the offset
                    unsigned int mask = createMask(0, offset - 1);
                    unsigned int oHolder = addy & mask;
                    report_logical2offset(addy, oHolder);
                }
                // if -n logical2page is passed in on command line
                if (l2PFlag)
                {
                    //create a map pointer that will be pointing the page lookup of our given address
                    MAP *map = PageLookup(pt, addy);
                    int hex = offset / 4;
                    //calculate the amount of bytes we need
                    unsigned int translation = map->frameIndex * pow(16, hex);
                    //by calling our fraame number to frameIndex * 16^(hex) wee can insert the fraamea index before our aamount of offset bits
                    unsigned int mask = createMask(0, offset - 1);
                    //create a mask to grab our offset
                    unsigned int oHolder = (addy & mask) + translation;
                    //Add our offset to our translation and get correct physical address and pass it through to output function
                    report_logical2physical(addy, oHolder);
                }
            }
            //increment aaddress count to make sure we have not exceeded given -n number of addresses
            addyCount++;
    }
    // if -n bitmasks is passed in on command line
    if (bFlag)
    {
        /* show mask entry and move to next */
        report_bitmasks(pt->numOfLevels, pt->bitMaskArr);
    }
    // if -n summary is passed in on command line
    else if (rSum)
    {
            //display size in bytes of pagetable, allocation of arrays and structs
            //display hits, misses, percentage, number of addresses processed, and frames allocated
            unsigned int page_size = pow(2, sizeof(pt));
            unsigned int bytes = sizeof(pt) + sizeof(lv) + sizeof(addys);
            printf("Page size: %d bytes\n", page_size);
            printf("Addresses processed: %d\n", addyCount);
            double hit_percent = (double)pt->hits / addyCount * 100.0;
            printf("Hits: %d (%.2f%%), Misses %d (%.2f%%)\n",
                pt->hits, hit_percent, pt->misses, 100 - hit_percent);
            printf("Frames allocated: %d\n", pt->frameCount);
            printf("Bytes used:  %d\n", bytes);
        
    }
    //Finish reading addresses, close file
    fclose(fp);
    //end program successfully
    return 0;
}
