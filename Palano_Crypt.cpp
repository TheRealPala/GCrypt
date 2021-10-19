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
int interParam(int argc, char** argv){
    char* file = NULL;
    char* chiave = NULL;    
    if(argc < 5){
        cout << "Errore nell'inserimento dei parametri!";
        return -1;
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
    cout << "\nFile: \t" << file;
    cout << "\nChiave: \t" << chiave ;
}
int main(int argc, char** argv){
    provaReadParam(argc, argv);
    interParam(argc, argv);
    return 0;
}