**Ordenamiento de paginación - Sorter**

**Contenidos del repositorio:** 

  sorter.cpp: implementación del programa principal para ordenar archivos binarios. 
  
  lectura.cpp: programa para leer y mostrar el contenido del archivo binario.
  
  generate_input.cpp: programa que genera un archivo binario con numeros enteros aleatorios.

**1. Compilar los programas:** en la terminal se compilan los tres archivos fuente para generar los ejecutables.
   
    g++ -o sorter sorter.cpp
  
    g++ -o lectura lectura.cpp
  
    g++ -o generate_input generate_input.cpp

**2. Generar archivo de entrada:** con esto se genera el input.bin, al ingresar el comando aparecera un mensaje de confirmación.
   
     ./generate_input

**3. Ejecutar el programa de ordenamiento:** con sorter se ordena el archivo binario, se elige entre los tres algorimos de ordenamiento, QuickSort, InsertionSort o BubbleSort
   
    ./sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITHM>

    ./sorter -input input.bin -output output.bin -alg QuickSort
  
    ./sorter -input input.bin -output output_is.bin -alg InsertionSort
  
    ./sorter -input input.bin -output output_bl.bin -alg BubbleSort

**4. Verificar el archivo ordenado"** para visualizar el contenido del archivo ya ordenado se utiliza lectura.cpp
   
     ./lectura sorted.bin > output.txt
   
     ./lectura sorted.bin > output_is.txt
   
     ./lectura sorted.bin > output_bl.txt

Al finalizar de ejecutar sorter se imprime un resumen del tiempo de ejecucion, el algoritmo utilizado y la cantidad de page faults vs page hits.




