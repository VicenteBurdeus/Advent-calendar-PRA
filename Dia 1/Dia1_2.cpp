#include <iostream>
#include <vector>
std::vector<int> Left = {0};
std::vector<int> Right = {0};

using namespace std;
//Declaracion de funciones
void cargarDatos(char* path);
void bubbleShort(vector<int> &A);
unsigned long long int buscadorRepeticiones(vector<int> A,vector<int> B);
std::pair<int, int> counter(vector<int> A, int n);
int searchBin(vector<int> A, int n);




void cargarDatos(char* path){
    
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("No se pudo abrir el archivo");
        exit(1);
    }
    int i = 0;
    int a,b;
    while(fscanf(file, "%d %d", &a, &b) != EOF){
        Left.push_back(a);
        Right.push_back(b);
        i++;
    }
    fclose(file);
    return;
}


void bubbleShort(vector<int> &A){
    int n = A.size();
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(A[j] > A[j+1]){
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}

unsigned long long int buscadorRepeticiones(vector<int> A,vector<int> B){
    unsigned long long int sum = 0;
    int n = A.size();
    int last = 0, lastValue = 0;
    for (int i = 0; i <n; i++){
        if (A[i] == last){//Al tener el vector ordenado, esto dota de una "memoria" para hacer la busqueda solo una vez
            sum += lastValue;
            continue;
        }
        std::pair<int, int> p = counter(B, A[i]);
        sum += (p.second*A[i]);
        last = A[i];
        lastValue = (p.second*A[i]);
    }
    return sum;
}
//esta funcion devuelve la primera posicion en la cual se encuentra el valor n del vector
//en caso de que no se encuentre, devuelve -1
//en caso de que haya mas de un valor igual, devuelve la primera posicion

std::pair<int, int> counter(vector<int> A, int n){
    int count = 0;
    int index = searchBin(A, n);
    if (index != -1) {
        for (int i = index; i < A.size() && A[i] == n; ++i) {
            count++;
        }
    }
    return std::make_pair(index, count);
}

int searchBin(vector<int> A, int n){
    int l = 0;
    int r = A.size()-1;
    int m = 0;
    while (l <= r){//busca el valor n en el vector A
        m = l + (r-l)/2;
        if (A[m] == n){
                while (1){//busca la primera posicion en la que se encuentra el valor n
                    if (m == 0){
                        return 0;
                    }else if (A[m-1] != n){
                        return m;
                    }else{
                        m--;
                }
            }
        }
        if (A[m] < n){
            l = m + 1;
        }
        else{
            r = m - 1;
        }
    }
    
    return -1;

}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Falta el path del archivo");
        return 1;
    }
    char* path = argv[1];
    cargarDatos(path);
    bubbleShort(Right);
    bubbleShort(Left);
    cout << buscadorRepeticiones(Left, Right);
    return 0;
}