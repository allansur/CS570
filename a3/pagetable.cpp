
#include "pagetable.h"
using namespace std;



void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame){

}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift) {
    return (LogicalAddress & Mask) >> Shift; // We got 1 down!
}

int PageLookUp(unsigned int address) {

}

unsigned int calcBitmask(int start, int length){
    unsigned int mask = (1 << length) - 1;
    mask <<= (start-length);
    return mask;
}

//Move Main some other time
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
