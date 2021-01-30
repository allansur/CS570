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

/* Get name of current directory by substringing last index of "/" */
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

    // check if command line has at least 2 args
  if (argc >= 2){
   if(strcmp(argv[1], "-h") == 0 ) {
     if (argc == 2){ // if arg contains -h and is exactly 2 args
       dr = opendir("."); 
      if (dr) {
      cout<< get_cur_dir() << "\n";
        while ((en = readdir(dr)) != NULL) {
            cout<< en->d_name<<"\n";  // if input is exactly myls -h, print all files
        }
      closedir(dr); //close dir
    }
     }
   for(; optind < argc; optind++){ // iterates through listed non-hidden directories
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
      closedir(dr); 
      } else { //error case: directory NOT FOUND
         cout << "Cannot access " << argv[optind] << "\n";
      }
    }
   }
   }
   else { // in case command line is not two args (-h, or multiple directories)
     for(; optind < argc; optind++){ // iterates through listed non-hidden directories
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
      closedir(dr); 
      } else { //error case: NOT FOUND
         cout << "Cannot access " << argv[optind] << "\n";
      }
   }
   }
  }
  else { // if not any of these cases, check if arg is at greater than 1
    if (argc > 1){
      dr = opendir("."); 
      if (dr) {
      cout<< get_cur_dir() << "\n";
        while ((en = readdir(dr)) != NULL) {
            cout<< en->d_name<<"\n";  // case of usage with non -h single arg 
        }
      closedir(dr); //close dir
    }
    }
    else {
      dr = opendir("."); 
      if (dr) {
      cout<< get_cur_dir() << "\n";
        while ((en = readdir(dr)) != NULL) {
          if (en->d_name[0] == '.'){
            continue;   // in case of myls usage only
          }
          else{
            cout<< en->d_name<<"\n";
          }
        }
      closedir(dr); 
      } else { //error case: NOT FOUND
         cout << "Cannot access " << argv[optind] << "\n";
      }
    }
  }
  
    return 0;
}