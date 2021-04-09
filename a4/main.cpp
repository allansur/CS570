#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "semaphore.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char **argv)
{
    int Option;
    int idx;
    int numberOfCandies;

    while ((Option = getopt(argc, argv, "E:L:f:e")) != -1)
    {
        //Check if either (n || o) || (n && o) is input into the command line
        switch (Option)
        {
            if (optarg)
            {
                // rSum = true;
            }
        case 'E':
             numberOfCandies = atoi(optarg);
        case 'L':
             numberOfCandies = atoi(optarg); 
        case 'f':
             numberOfCandies = atoi(optarg);
        case 'e':
             numberOfCandies = atoi(optarg);
        default:
            //print something about the usage and die...
            cout << "Does not exist" << endl;
            exit(0);
            break;
        }
    }
    //Retrieve the file path from commandline
    idx = optind;
}