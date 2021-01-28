#include "myls.h";
#include <experimental/filesystem>;
using namespace std; //I don't really wanna use this but i'm too lazy to not
namespace fs = std::experimental::filesystem;

bool flag;
int main(int argc, char* argv[]) {
    if (argv[2] == "-h"){
        bool flag = true;
        if (argc > 2){
            //list all directories
        }
        else {
            
        }
        //we have to use get opt or we can create another method to show hidden files
    }
    else { //Case for no -h flag
        printCurDir();
    }
    
    return 0;
}

int getCurDir(void){
    int name_size;
    string dirName = fs::current_path();
    name_size = dirName.find_last_of("/");
    cout << dirName.substr(name_size + 1, dirName.size() - 1);
    return 0;  
}

int printCurDir(bool h){
    DIR *in = opendir(".");
    struct dirent *en;

    if (in) {
        while ((en = readdir(in)) != NULL){
            if (en -> d_name[0] != '.'){
                continue;
            }else {
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





