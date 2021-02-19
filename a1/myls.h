/* 
Names: Allan Sur, Jason Songvilay
RedIDs: 821444631, 821071661
Course: CS530-03-Spring2021
Assignmt 1: Part II
*/

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

class myls {
    public: 
        string get_cur_dir(void); // get name of current directory for no arg use
        int main(int argc, char* argv[]); // main driver of program
};
