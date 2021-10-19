#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

void provaReadParam(int argc, char** argv){
    cout << "numero parameri: " << argc; 
    cout << "\nStampa: ";
    for(int i = 0; i < argc; ++i){
        cout << "\n" << (i +1) << ": \t" << argv[i];
    }
}

void interParam(int argc, char** argv, char** param){
    char* file = NULL;
    char* chiave = NULL;    
    if(argc < 5){
        cout << "Errore nell'inserimento dei parametri!";
    }
    else{
        for(int i = 1; i < argc; ++i){
            if(!strcmp(argv[i], "-f")){
                file = argv[i + 1]; 
            }
            if(!strcmp(argv[i], "-c")){
                chiave = argv[i + 1]; 
            }
        }
        
    }
    if(*file == NULL)
        strcpy(file, "File non inserito");
    if(*chiave == NULL)
        strcpy(chiave, "Chiave non inserita");
    
    param[0] = chiave;
    param[1] = file;
}

int main(int argc, char** argv){
    char** param = new char* [2];
    interParam(argc, argv, param);
    cout << "\nFile: " << param[0];
    cout << "\nChiave: " << param[1] ;
    return 0;
}