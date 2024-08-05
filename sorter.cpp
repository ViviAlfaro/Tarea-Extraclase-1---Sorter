#include <iostream> //operaciones entrada salida
#include <fstream> //operaciones con archivos
#include <vector> 
#include <algorithm> //algoritmos como find
#include <chrono> //medir el tiempo
#include <cstring> //en relacion a cadenas y conversion
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Tamaño de las páginas (en número de enteros)
const size_t PAGE_SIZE = 1024;

// clase para manejar el arreglo paginado
class PagedArray {
public:
    PagedArray(const string& filePath, size_t totalSize)
        : filePath(filePath), totalSize(totalSize), pageFaults(0), pageHits(0) { //ruta del archivo que contiene los datos
        pages.resize(4, vector<int>(PAGE_SIZE));
        pageIndices.resize(4, -1); // vector que ratrea que paginas estan en que inidices, inicialmente todos estan en -1
    }

    int& operator[](size_t index) { //calcula el indice de la pagina y el desplazamiento dentro de la pagina
        size_t pageIndex = index / PAGE_SIZE;
        size_t offset = index % PAGE_SIZE;
        
        // buscar si la página está en una de las posiciones
        auto it = find(pageIndices.begin(), pageIndices.end(), pageIndex);
        if (it != pageIndices.end()) {
            // página está en memoria (page hit)
            ++pageHits;
            return pages[it - pageIndices.begin()][offset];
        } else {
            // página no está en memoria (page fault)
            ++pageFaults;
            loadPage(pageIndex);
            return pages[0][offset];  // siempre devuelve la primera página después de cargar
        }
    }

    void loadPage(size_t pageIndex) {
        // encuentra una página para reemplazar (si es necesario)
        size_t pageToReplace = 0;
        for (size_t i = 0; i < pageIndices.size(); ++i) {
            if (pageIndices[i] == -1) {
                pageToReplace = i;
                break;
            }
        }
        
        // reemplaza una página si todas están ocupadas
        if (pageIndices[pageToReplace] != -1) {
            // guardar la página vieja en el archivo
            savePage(pageIndices[pageToReplace], pageToReplace);
        }
        
        // cargar la nueva página
        pageIndices[pageToReplace] = pageIndex;
        ifstream file(filePath, ios::binary);
        file.seekg(pageIndex * PAGE_SIZE * sizeof(int));
        file.read(reinterpret_cast<char*>(pages[pageToReplace].data()), PAGE_SIZE * sizeof(int));
        file.close();
    }

    void savePage(size_t pageIndex, size_t pageToReplace) {
        ofstream file(filePath, ios::binary | ios::in | ios::out);
        file.seekp(pageIndex * PAGE_SIZE * sizeof(int));
        file.write(reinterpret_cast<const char*>(pages[pageToReplace].data()), PAGE_SIZE * sizeof(int));
        file.close();
    }

    size_t getPageFaults() const { return pageFaults; }
    size_t getPageHits() const { return pageHits; }

private:
    string filePath;
    size_t totalSize;
    vector<vector<int>> pages;
    vector<size_t> pageIndices;
    size_t pageFaults;
    size_t pageHits;
};

// Funciones de ordenamiento
void quickSort(PagedArray& arr, size_t left, size_t right);
void insertionSort(PagedArray& arr, size_t left, size_t right);
void bubbleSort(PagedArray& arr, size_t left, size_t right);
size_t partition(PagedArray& arr, size_t left, size_t right);

// Implementaciones de los algoritmos
void quickSort(PagedArray& arr, size_t left, size_t right) {
    if (left < right) {
        size_t pivot = partition(arr, left, right);
        if (pivot > 0) quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}

size_t partition(PagedArray& arr, size_t left, size_t right) { // reorganiza los elementos de forma q
//que los menores que el pivote estén a la izquierda y los mayores a la derecha.
    int pivot = arr[right];
    size_t i = left;
    for (size_t j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

void insertionSort(PagedArray& arr, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > left && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}