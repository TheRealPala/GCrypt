#include <iostream>
#include <time.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

void provaReadParam(int argc, char** argv){
    cout << "numero parameri: " << argc; 
    cout << "\nStampa: ";
    for (int i = 0; i < argc; ++i){
        cout << "\n" << (i +1) << ": \t" << argv[i];
    }
}

void help(){
    cout << "\n\nExample:\tPalano_Crypt.exe -f filename.txt -c 1234\n\nElenco parametri accettati:\n-f:\tNome del file da criptare\n-c:\tChiave di cifratura (LA CHIAVE DEVE ESSERE NUMERICA)\n-h:\tStampa elenco dei parametri accettati dal programma (--help viene accettato)\n";
}

void interParam(int argc, char** argv, char** param){
    char EMPTY = 0;
    char* file = &EMPTY;
    char* chiave = &EMPTY; 

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
        help();
        exit(EXIT_FAILURE );
    }

    if (argc < 5){
        cout << "Errore nell'inserimento dei parametri!";
        help();
        exit(EXIT_FAILURE );
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
    if (*file == EMPTY){
        cout << "Errore nell'inserimento dei parametri!";
        help();
        exit(EXIT_FAILURE );
    }

    if (*chiave == EMPTY){
        cout << "Errore nell'inserimento dei parametri!";
        help();
        exit(EXIT_FAILURE );  
    }

    //Controllo validità chiave
    for (int i = 0; i < strlen(chiave); ++i){
         int c = chiave[i] - '0';
         if (c < 0 || c > 9){
            cout << "Chiave inserita non valida!\nLA CHIAVE DEVE ESSERE NUMERICA!\nIl programma terminera' sedutastante!\n";
            exit(EXIT_FAILURE ); 
         }   
    }
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

int getIndex(char chr, char* str){
   int index = -1;
   for (int i = 0; i < strlen(str); ++i){
       if (chr == str[i]){
           index = i;
           break;
       }
   }
   return index; 
}

char* getStringCrypt(char* str, char aShift[][26], char* alfa, int lenkey){
    cout << "\nLunghezza stringa: " << strlen(str) << endl;
    char* cryptStr = new char[strlen(str) + 1]; //Salvo la variabile nell'heap per evitare danni con il push/pop;
    bzero(cryptStr, strlen(str));
    cryptStr[strlen(cryptStr)] = '\0';
    int inK = -1;
    for (int i = 0; i < strlen(str); ++i){ 
        //Se trovo uno spazio metto uno spazio
        if (str[i] == ' '){
            cryptStr[i] = ' ';
        }
        else {
            inK = (inK + 1) % lenkey; //Calcolo di quale alfabeto shiftato devo utilizzare (dopo l'utilizzo dell'ultmo devo ricominciare con il primo)
            bool isMin = str[i] >= 'a' && str[i] <= 'z' ? true : false;
            if (!isMin){ //costrutto per gestire lettere minuscole
                int index = getIndex(str[i], alfa); //ottengo il numero dell'alfabeto NORMALE della iEsima lettera della stringa da cifrare
                cryptStr[i] = aShift[inK][index];
            }
            else { //i - ' ' ed i + ' ' sono per gestire le lettere minuscole perchè l'alfabeto generato è tutto in maiuscolo (' ' = 32(base 10))
                int index = getIndex(str[i] - ' ', alfa); //ottengo il numero dell'alfabeto NORMALE della iEsima lettera della stringa da cifrare
                cryptStr[i] = aShift[inK][index] + ' ';
            }
        }
    }
    cryptStr[strlen(str)] = '\0';
    return cryptStr;
}

int main(int argc, char** argv){
    char** param = new char* [2];
    interParam(argc, argv, param);
    //param[0]: filename |  param[1]: chiave
   
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
    //Inizio prova shift
    cout << "Inserire stringa da cifrare:" << endl;
    char str[30];
    cin.getline(str, 30);
    cout << "Stringa inserita: " << str << endl;
    cout << "Stringa cifrata: " <<  getStringCrypt(str, alfaShift, alfa, strlen(param[1]));
    delete(param);
    return 0;
}