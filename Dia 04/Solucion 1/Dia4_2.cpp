#include <iostream>
#include <cstdio>
using namespace std;

char sopa[140][140] = {0};

void leer_fichero(FILE *fichero);
bool call_XShapeMAS(int i, int j);
bool verificar_diagonal(int i, int j, int dirX1, int dirY1, int dirX2, int dirY2);

int main(int argc, char *argv[]) {
    FILE *fichero;
    int Encontrados_xmas = 0;

    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <archivo>" << endl;
        return 1;
    }

    if ((fichero = fopen(argv[1], "r")) == NULL) {
        perror("Error al abrir el archivo");
        return 2;
    }

    leer_fichero(fichero);
    fclose(fichero);

    // Iterar sobre las posiciones centrales (sin bordes)
    for (int i = 1; i < 139; i++) {
        for (int j = 1; j < 139; j++) {
            Encontrados_xmas += call_XShapeMAS(i, j);
        }
    }

    cout << "Encontrados: " << Encontrados_xmas << endl;
    return 0;
}

void leer_fichero(FILE *fichero) {
    char c;
    int i = 0, j = 0;

    while ((c = fgetc(fichero)) != EOF) {
        if (c == '\n') {
            i++;
            j = 0;
        } else {
            sopa[i][j] = c;
            j++;
        }
    }
}

bool  call_XShapeMAS(int i,int j){
    if (sopa[i][j] != 'A') return false;
    else {
        if (verificar_diagonal(i, j, -1, -1, 1, 1) && verificar_diagonal(i, j, -1, 1, 1, -1)) {
            return true;
        }else return false;
    }
}

bool verificar_diagonal(int i, int j, int dirX1, int dirY1, int dirX2, int dirY2) {
    if ((sopa[i + dirX1][j + dirY1] == 'M' && sopa[i + dirX2][j + dirY2] == 'S')||sopa[i + dirX1][j + dirY1] == 'S' && sopa[i + dirX2][j + dirY2] == 'M') {
        return true;
    } else {
        return false;
    }
}