#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

void provaReadParam(int argc, char** argv){
    cout << "numero parameri: " << argc; 
    cout << "\nStampa: ";
    for (int i = 0; i < argc; ++i){
        cout << "\n" << (i +1) << ": \t" << argv[i];
    }
}

void interParam(int argc, char** argv, char** param){
    char* file = NULL;
    char* chiave = NULL;    
    if (argc < 5){
        cout << "Errore nell'inserimento dei parametri!";
    }
    else {
        for (int i = 1; i < argc; ++i){
            if (!strcmp(argv[i], "-f")){
                file = argv[i + 1]; 
            }
            if (!strcmp(argv[i], "-c")){
                chiave = argv[i + 1]; 
            }
        }
        
    }
    if(*file == NULL)
        strcpy(file, "File non inserito");
    if(*chiave == NULL)
        strcpy(chiave, "Chiave non inserita");
    
    param[1] = chiave;
    param[0] = file;
}

void initAlfa(char* a){
    for (int i = 0; i < 26; ++i){
        a[i] = 'A' + i;
    }
}

void shift (char aShift [][26], char* alfa, char* chiave){
    int lenChiave = strlen(chiave);
    int c;
    for (int i = 0; i < lenChiave; ++i){
        c = chiave[i] - '0'; //Trasformo le cifre della chiave da char ad int
        for (int j = 0; j < strlen(alfa); ++j){
            int pos = (j + c) % 26; //calcolo posizione di shift dell'alfabeto
            aShift[i][j] = alfa[pos];
        }
    }
}

int main(int argc, char** argv){
    char** param = new char* [2];
    interParam(argc, argv, param);
    cout << "\nFile: " << param[0];
    cout << "\nChiave: " << param[1];
    cout << "\nLunghezza chiave: " << strlen(param[1]);
    char alfa [26];
    initAlfa(alfa);
    cout << "\nAlfabeto:\n";
    for (int i = 0; i < 26; ++i){
       printf("%c ", alfa[i]);
    }
    char alfaShift [strlen(param[1])][26]; //Tabella di tante righe quante sono le cifre della chiave e tante colonne quante le lettere dell'alfabeto
    shift(alfaShift, alfa, param[1]);
    cout << "\nLista Alfabeti modificati: \n\n";
    for (int i = 0; i < strlen(param[1]); ++i){
        for (int j = 0; j < strlen(alfa); ++j){
            cout << alfaShift[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}