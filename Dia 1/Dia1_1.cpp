#include <iostream>
#include <vector>
std::vector<int> Left = {0};
std::vector<int> Right = {0};

using namespace std;

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



unsigned long long int addDiff(vector<int> A,vector<int> B){
    unsigned long long int sum = 0;
    int n = A.size();
    for (int i = 0; i < n; i++){
        sum += abs(A[i] - B[i]);
    }
    return sum;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Falta el path del archivo");
        return 1;
    }
    char* path = argv[1];
    cargarDatos(path);
    bubbleShort(Left);
    bubbleShort(Right);
    cout << addDiff(Left, Right);
    return 0;
}