#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

using namespace std;
int main(int argc, char *argv[]) {
   int opt;
   DIR *dr;
   struct dirent *en;

    // check if second argument is -h or not 
   if(strcmp(argv[1], "-h") == 0 ) {
   while((opt = getopt(argc, argv, ":h:")) != -1) { //check if -h has args or not
    switch(opt) 
    {
      case 'h': 
        dr = opendir(optarg); //open directory specified after -h
        if (dr) {
        cout<< "Directory: " << optarg << "\n";
        while ((en = readdir(dr)) != NULL) {
             cout<< en->d_name<<"\n"; //print all files
        }
        closedir(dr); //close directory
        } else {
         cout << "Directory " << optarg << " not found\n";
        }
        break;
      default: // no args after -h
        cout << "Directory " << optarg << " not found";
        break;
     }
   }
   } else {
      dr = opendir(argv[optind]); //open directory specified
      if (dr) {
      cout<< "Directory: " << argv[optind] << "\n";
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.'){
              continue;
            }
            else{
            cout<< en->d_name<<"\n"; //print all NON-HIDDEN Files
            }
          }
      closedir(dr); //close directory
      } else {
         cout << "Directory " << argv[optind] << " not found\n";
      }
   }

    return 0;
}