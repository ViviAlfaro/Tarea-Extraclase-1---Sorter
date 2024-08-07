#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) { //funcion principal 
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nombre" << endl;
        return 1;
    }

    const char* FILENAME = argv[1];
    ifstream inFile(FILENAME, ios::binary);
    if (!inFile) {
        cerr << "Error: No se pudo abrir el archivo de lectura" << endl; //mensaje de error en caso de que no se cumpla
        return 1;
    }
 
    // lee y muestra los números enteros con formato
    int num;
    bool first = true;
    while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) { //lee datos del archivo en bloques del tamaño de un entero
        if (!first) {
            cout << ", ";
        }
        cout << num;
        first = false;
    }

    // cierra el archivo
    inFile.close();
    cout << endl;

    return 0;
}
