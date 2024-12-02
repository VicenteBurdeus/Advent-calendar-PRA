#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

bool is_safe(const std::vector<int>& numeros) {
    if (numeros.size() < 2) return false;  // No tiene suficientes elementos para analizar
    
    int direccion = (numeros[1] > numeros[0]) ? 1 : -1;  // Determina si es ascendente o descendente
    for (size_t i = 0; i < numeros.size() - 1; ++i) {
        int diff = numeros[i + 1] - numeros[i];
        if (std::abs(diff) < 1 || std::abs(diff) > 3) return false;  // Diferencia inválida
        if ((diff > 0 && direccion < 0) || (diff < 0 && direccion > 0)) return false;  // Cambio de dirección
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        exit(1);
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

        // Verificar si la línea es segura
        if (is_safe(numeros)) {
            ++safeCounter;
        }
    }

    std::cout << "Lineas seguras: " << safeCounter << std::endl;

    return 0;
}
