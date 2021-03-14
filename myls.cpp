#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

string get_cur_dir(){
  char buff[256];
  getcwd(buff, 256);
  string curwdir(buff);
  curwdir = curwdir.substr(curwdir.find_last_of("/") + 1, curwdir.size() - 1);
  return curwdir;
}

int main(int argc, char *argv[]) {
   int opt;
   DIR *dr;
   struct dirent *en;

    // check if second argument is -h or not
  if (argc > 2){
   if(strcmp(argv[1], "-h") == 0 ) {
   for(; optind < argc; optind++){ //WORKING iterates through listed non-hidden directories
    if (strcmp(argv[optind], "-h") == 0){
      continue;
    }
    else {
      dr = opendir(argv[optind]); 
      if (dr) {
      cout<< argv[optind] << "\n";
        while ((en = readdir(dr)) != NULL) {
            cout<< en->d_name<<"\n";
            
        }
      closedir(dr); //close dir
      } else { //error case: NOT FOUND
         cout << "Cannot access " << argv[optind] << "\n";
      }
    }
   }
   }
   else {
     for(; optind < argc; optind++){ //WORKING iterates through listed non-hidden directories
      dr = opendir(argv[optind]); 
      if (dr) {
      cout<< argv[optind] << "\n";
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.'){
              continue;
            }
            else{
            cout<< en->d_name<<"\n";
            }
          }
      closedir(dr); //close dir
      } else { //error case: NOT FOUND
         cout << "Cannot access " << argv[optind] << "\n";
      }
   }
   }
  }
  else {
    if (argc > 2){
      dr = opendir("."); 
      if (dr) {
      cout<< get_cur_dir() << "\n";
        while ((en = readdir(dr)) != NULL) {
            cout<< en->d_name<<"\n";
        }
      closedir(dr); //close dir
    }
    }
    else {
      if(argc == 1 || strcmp(argv[1], "-h")==0){
      dr = opendir("."); 
      if (dr) {
      cout<< get_cur_dir() << "\n";
        while ((en = readdir(dr)) != NULL) {
          if (en->d_name[0] == '.'){
            continue;
          }
          else{
            cout<< en->d_name<<"\n";
          }
        }
      closedir(dr); //close dir
      }
      } else { //error case: NOT FOUND
        dr = opendir(argv[1]); 
      if (dr) {
      cout<< argv[1] << "\n";
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.'){
              continue;
            }
            else{
            cout<< en->d_name<<"\n";
            }
          }
      closedir(dr); //close dir
      } else { //error case: NOT FOUND
         cout << "Cannot access: " << argv[1] << "\n";
      }
      }
    }
  }
  
    return 0;
}