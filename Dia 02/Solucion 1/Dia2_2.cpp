#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

// Compruba que un vector de numeros es seguro
bool is_safe(const std::vector<int>& numeros) {
    if (numeros.size() < 2) return false;

    int direction = (numeros[1] > numeros[0]) ? 1 : -1;  // Determina si es ascendente o descendente
    for (size_t i = 0; i < numeros.size() - 1; ++i) {
        int diff = numeros[i + 1] - numeros[i];
        if (std::abs(diff) < 1 || std::abs(diff) > 3) return false;
        if ((diff > 0 && direction < 0) || (diff < 0 && direction > 0)) return false; 
    }
    return true;
}

// Prueba las combinaciones eliminando 1 elemento para ver si son seguras
bool is_safe_with_dampener(const std::vector<int>& numeros) {
    for (size_t i = 0; i < numeros.size(); ++i) {
        // Crear una copia del vector sin el nivel en la posición i
        std::vector<int> modified = numeros;
        modified.erase(modified.begin() + i);
        if (is_safe(modified)) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }

    int safeCounter = 0;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> numeros;
        int num;

        // Leer los números de la línea
        while (iss >> num) {
            numeros.push_back(num);
        }

        // Verifica si es segura
        if (is_safe(numeros) || is_safe_with_dampener(numeros)) {
            safeCounter++;
        }
    }

    std::cout << "Lineas seguras: " << safeCounter << std::endl;

    return 0;
}
