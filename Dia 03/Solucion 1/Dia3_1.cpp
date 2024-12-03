#include <string>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

long long int sumaTotal = 0;

// Función para procesar coincidencias y calcular el resultado
void addMul(const smatch& Coincidencias) {
    int n1 = stoi(Coincidencias[1].str());
    int n2 = stoi(Coincidencias[2].str());
    sumaTotal += n1 * n2;
}

// Función para buscar y procesar las coincidencias en el texto
void searchAndAdd(const string& texto) {
    regex Patron(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch Coincidencias;
    string linea = texto;

    while (regex_search(linea, Coincidencias, Patron)) {
        addMul(Coincidencias);
        // Continuar buscando en el resto de la línea
        linea = Coincidencias.suffix().str();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <archivo>" << std::endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        searchAndAdd(line);
    }

    cout << "La suma total es: " << sumaTotal << endl;
    return 0;
}
