#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() { // funcion principal
    const size_t NUM_INTEGERS = 10000; // numero de enteros a generar
    const char* FILENAME = "input.bin"; // nombre del archivo binario de entrada

    // semilla para la generación de números aleatorios
    srand(static_cast<unsigned>(time(0)));

    // crear archivo binario para escritura
    ofstream outFile(FILENAME, ios::binary); //offstream abre el arcivo para escritura
    if (!outFile) {
        cerr << "Error: El archivo no se puede abrir." << endl;
        return 1;
    }

    // generacion y escritura de números enteros aleatorios
    for (size_t i = 0; i < NUM_INTEGERS; ++i) {
        int num = rand(); // genera un número aleatorio
        outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    // cerrar archivo
    outFile.close();
    cout << "Se ha generado correctamente" << endl;

    return 0;
}
