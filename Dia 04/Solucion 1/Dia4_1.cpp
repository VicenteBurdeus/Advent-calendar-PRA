#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void leer_fichero(FILE *fichero);
int call_busqueda(int i, int j);
int Busqueda_xmas(int i, int j, int n,int dirX, int dirY);


char sopa[140][140]; 

int main(int argc, char *argv[])
{
FILE *fichero;
int Encontrados_xmas = 0;

    if (argc < 2)
    {
        cout << "Use: " << argv[0] << " <archivo>" << std::endl;
        exit(1);
    }
    if ((fichero = fopen(argv[1], "r")) == NULL)
    {
        cout << "Error abriendo el archivo" << std::endl;
        exit(2);
    }

    leer_fichero(fichero);
    fclose(fichero);
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {
               Encontrados_xmas += call_busqueda(i, j);
        }
    }

    

    cout << "Encontrados: " << Encontrados_xmas << endl;


    
}

void leer_fichero(FILE *fichero)
{
    char c;
    int i = 0;
    int j = 0;
    while ((c = fgetc(fichero)) != EOF)
    {
        if (c == '\n')
        {
            i++;
            j = 0;
        }
        else
        {
            sopa[i][j] = c;
            j++;
        }
    }
}

int call_busqueda(int i, int j)
{
    if (sopa[i][j] != 'X') return 0;
    else
    {   
        return (Busqueda_xmas(i+1, j, 1, 1, 0) + 
                Busqueda_xmas(i, j+1, 1, 0, 1) + 
                Busqueda_xmas(i-1, j, 1, -1, 0) + 
                Busqueda_xmas(i, j-1, 1, 0, -1) + 
                Busqueda_xmas(i+1, j-1, 1, 1, -1) + 
                Busqueda_xmas(i-1, j+1, 1, -1, 1) + 
                Busqueda_xmas(i+1, j+1, 1, 1, 1) + 
                Busqueda_xmas(i-1, j-1, 1, -1, -1));
    }
}

int Busqueda_xmas(int i, int j, int n, int dirX, int dirY) {
    if (i < 0 || i >= 140 || j < 0 || j >= 140) return 0; // Fuera de límites

    const char palabra[] = "XMAS";
    if (sopa[i][j] != palabra[n]) return 0;
    if (n == 3) return 1;

    // Continuar en la misma dirección
    return Busqueda_xmas(i + dirX, j + dirY, n + 1, dirX, dirY);
}
