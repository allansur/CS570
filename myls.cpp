#include "myls.h";

using namespace std;
namespace fs = std::experimental::filesystem;

bool flag = false;
int main(int argc, char* argv[]) {
    if (argv[2] == "-h"){
        bool flag = true;
        if (argc > 2){
            for (int i = 2; i < argv.size() - 1; i++){
                string dir = fs::current_path();
                dir.append("/" + argv[i]);
                opendir(dir);
                printCurDir(flag);
            }
        }
        else {
            printCurDir(flag);
        }
        
    }
    else { //Case for no -h flag
        printCurDir(flag);
    }
    
    return 0;
}

int getCurDir(void){
    int name_size;
    string dirName = fs::current_path();
    name_size = dirName.find_last_of("/");
    cout << dirName.substr(name_size + 1, dirName.size() - 1) << "\n";
    return 0;  
}

int printCurDir(bool h){
    DIR *in = opendir(".");
    struct dirent *en;
    getCurDir();
    if (in){
        if (h == false){
            while ((en = readdir(in)) != NULL){
                if (en -> d_name[0] != '.'){
                    continue;
                }
                else {
                    cout << en -> d_name << "\n";
                }
            }   
        }
        else {
           while ((en = readdir(in)) != NULL){
               cout << en -> d_name << "\n";
            }
        }
        closedir(in);
    }
    else {
        cout << "Cannot access " << getCurDir << "\n";
    }
    return 0;
}





