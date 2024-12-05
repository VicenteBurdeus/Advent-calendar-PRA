#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>
#include <string.h>

using namespace std;


vector<pair<int, int>> Rules = {{-1, -1}};


void addRule(int a, int b);
void readRules(FILE *file);
vector<int> nextLine(FILE *file);
vector<int> ordenarLinea(vector<int> Linea);
int getMiddle(vector<int> Linea);
bool isSortedForRules(vector<int> Linea);


int SumTotal = 0;

void readRules(FILE *file) {
    int a, b;
    fseek(file, 0, SEEK_SET);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n') {
            break; // Detener si se detecta una línea vacía
        }
        sscanf(line, "%d|%d", &a, &b);
        addRule(a, b);
    }
}

void addRule(int a, int b) {
    if (Rules[0].first == -1) {
        Rules[0].first = a;
        Rules[0].second = b;
        return;
    }
    Rules.push_back(make_pair(a, b));
    printf("Regla agregada: %d|%d\n", a, b);
    return;
}

vector<int> nextLine(FILE *file){
    vector<int> Nums;
    Nums.clear();
    int a, b;
    //lee toda la linea
    char line[256];
    fgets(line, sizeof(line), file);
    //lee los numeros de la linea separados por ,
    char *token = strtok(line, ",");
    while (token != NULL) {
        sscanf(token, "%d", &a);
        Nums.push_back(a);
        token = strtok(NULL, ",");
    }
    return Nums;
}

bool isSortedForRules(vector<int> Linea){
    int posFirst = 0, posSecond = 0;
    for (int i = 0; i < Rules.size(); i++){
        posFirst = -1;
        posSecond = -1;
        for (int j = 0; j < Linea.size(); j++){
            if (Linea[j] == Rules[i].first){//encuentra el primer num
                posFirst = j;
            }
            if (Linea[j] == Rules[i].second){//encuentra el segundo num de la regla
                posSecond = j;
            }
        }
        if ((posFirst > posSecond)&&(posFirst != -1)&&(posSecond != -1)){//si no cumple la regla Finaliza la comprobacion
            cout << "Linea no ordenada: fallo regla "<< Rules[i].first << "|" << Rules[i].second << endl;
            return false;
        }
    }
    cout << "Linea ordenada resultado: "<< getMiddle(Linea) << endl;
    return true;//no a encontrado fallos
}

vector<int> ordenarLinea(vector<int> Linea){
    //coje el vector de numeros(linea) y lo ordena en funcion a las normas 
    //la norma de ordenacion es que el primer numero de regla a de estar delante del segundo cuando se ordena la linea
    bool ordenado = false;
    while (!ordenado)
    {
        ordenado = true;
        cout << "Linea en bucle: ";
        for (int i = 0; i < Rules.size(); i++){
            int posFirst = -1;
            int posSecond = -1;
            for (int j = 0; j < Linea.size(); j++){
                if (Linea[j] == Rules[i].first){//encuentra el primer num
                    posFirst = j;
                }
                if (Linea[j] == Rules[i].second){//encuentra el segundo num de la regla
                    posSecond = j;
                }
            }
            if ((posFirst > posSecond)&&(posFirst != -1)&&(posSecond != -1)){//si no cumple la regla Finaliza la comprobacion
                iter_swap(Linea.begin() + posFirst, Linea.begin() + posSecond);
                ordenado = false;
            }
        }
    }
    cout << "Linea reordenada: ";
    return Linea;
}

int getMiddle(vector<int> Linea){
    //devuelve el numero del medio de la linea
    return Linea[Linea.size()/2];
}

int main(int argc, char const *argv[]) {
    FILE *file = fopen(argv[1], "r");
    vector<int> Linea;
    readRules(file);
    while (!feof(file))
    {
        Linea = nextLine(file);
        if (!isSortedForRules(Linea)){ SumTotal += getMiddle(ordenarLinea(Linea));
        }
    }
    
    cout << "Suma de los que no cumplian la norma: "<< SumTotal << endl;
    
    fclose(file);
    return 0;
}