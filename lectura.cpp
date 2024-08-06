#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nombre" << endl;
        return 1;
    }

    const char* FILENAME = argv[1];
    ifstream inFile(FILENAME, ios::binary);
    if (!inFile) {
        cerr << "Error: No se pudo abrir el archivo de lectura" << endl;
        return 1;
    }
 }