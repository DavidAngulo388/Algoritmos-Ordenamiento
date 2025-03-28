/*Aclaracion a falta de acentos de algunas palabras:
Por cosas de interpretacion de los caracteres especiales de algunos compiladores, estos no se pueden llegar a mostrar
esto incluye a los acentos. Aquellos simbolos de interrogacion que pueden llegar a salir son "enies"
*/

/*
Autor: David Angulo
Fecha de elaboracion: 27 de Marzo del 2025
*/
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>

#define NUM_PRUEBAS 1000
#define MIN_TAMANO 10
#define MAX_TAMANO 1000
#define INCREMENTO 10

using namespace std;

void AlgoritmoDeInsercion(int s[], int n);
void AlgoritmoDeBurbuja(int s[], int n);
void AlgoritmoDeMezcla(int s[], int inicio, int fin);
void Mezcla(int s[], int inicio, int medio, int fin);
void QuickSort(int s[], int inicio, int fin);
int Partition(int s[], int inicio, int fin);
void HeapSort(int s[], int n);
void BuildHeapSort(int s[], int n);
void MaxHeapify(int s[], int i, int n);
void ShellSort(int s[], int n);
void SelectionSort(int s[], int n);

void EjecutarYRegistrar(void (*algoritmo)(int[], int), const string& nombreArchivo, const string& nombreAlgoritmo);

int main() {
    srand(time(nullptr));
    /*
    La funcion 'main' se dedica solamente al manejo del resto de funciones y la impresion del ultimo mensaje, asegurando
    al usuario que se ejecuto el programa de manera correcta y que se generaron los archivos csv.
    */
    EjecutarYRegistrar(AlgoritmoDeInsercion, "1_Insercion_Ordenamiento.csv", "Insercion");
    EjecutarYRegistrar(AlgoritmoDeBurbuja, "2_Burbuja_Ordenamiento.csv", "Burbuja");
    EjecutarYRegistrar(HeapSort, "3_HeapSort_Ordenamiento.csv", "HeapSort");
    EjecutarYRegistrar(ShellSort, "4_ShellSort_Ordenamiento.csv", "ShellSort");
    EjecutarYRegistrar(SelectionSort, "5_SelectionSort_Ordenamiento.csv", "SelectionSort");
    EjecutarYRegistrar([](int s[], int n) { AlgoritmoDeMezcla(s, 0, n - 1); }, "6_Mezcla_Ordenamiento.csv", "Mezcla");
    EjecutarYRegistrar([](int s[], int n) { QuickSort(s, 0, n - 1); }, "7_QuickSort_Ordenamiento.csv", "QuickSort");
    
    cout << "Ejecucion completa. Verifique los archivos CSV generados." << endl;
    system("pause");
    return 0;
}
/*Esta función se encarga de la creación de los archivos CSV, las iteraciones y la impresión de los arreglos/tiempos, tanto en el programa
principal como en el CSV (para los tiempos), en general, es el corazon del programa*/
void EjecutarYRegistrar(void (*algoritmo)(int[], int), const string& nombreArchivo, const string& nombreAlgoritmo) {
    ofstream archivo(nombreArchivo); //Creacion del archivo CSV, donde se imprimira el tiempo tomado por cada iteracion junto al tamaño
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    archivo << "Iteraciones";
    for (int tamano = MIN_TAMANO; tamano <= MAX_TAMANO; tamano += INCREMENTO) {
        archivo << ",Tamano" << tamano;
    }
    archivo << endl;

    for (int i = 1; i <= NUM_PRUEBAS; ++i) {
        archivo << i;
        for (int k = MIN_TAMANO; k <= MAX_TAMANO; k += INCREMENTO) {
            int* s = new int[k];
            for (int j = 0; j < k; ++j) {
                s[j] = 1 + rand() % 1000;
            }
            
            if (i == 1 && k == MIN_TAMANO) {
                cout << "\nChequeo de funcionamiento del algoritmo " << nombreAlgoritmo << endl;
                cout << "Arreglo desordenado: [";
                for (int p = 0; p < k; p++) {
                    cout << s[p] << (p < k - 1 ? ", " : "");
                }
                cout << "]" << endl;
            }
            cout << "Ejecutando " << nombreAlgoritmo << " con tama" << static_cast<char>(164) << "o " << k << endl;


            auto inicio = chrono::high_resolution_clock::now(); //Cronometro que se encarga de registrar el tiempo que tardo cada iteración en completarse
            algoritmo(s, k); //Aunque lleve el nombre solamente "algoritmo", desde la función que ejecuta el programa se llamo un puntero a función el cuál llama al algoritmo
            auto fin = chrono::high_resolution_clock::now();
            chrono::duration<double, nano> duracion = fin - inicio;

            if (i == 1 && k == MIN_TAMANO) {
                cout << "\nChequeo de funcionamiento del algoritmo " << nombreAlgoritmo << endl;
                cout << "Arreglo ordenado: [";
                for (int p = 0; p < k; p++) {
                    cout << s[p] << (p < k - 1 ? ", " : "");
                }
                cout << "]" << endl;
            }

            cout << "Tiempo tomado: " << duracion.count() << "ns" << endl;
            archivo << "," << duracion.count();
            
            delete[] s;
        }
        archivo << endl;
    }
    archivo.close(); //Se cierra el archivo CSV, porque en caso de que no se cierre puede llegar a dar un error.
}
/**-----------------Algoritmo de Mezcla/Merge Sort-----------------**/
void AlgoritmoDeMezcla(int s[], int inicio, int fin) {
    if (inicio >= fin) return;
    int medio = (inicio + fin) / 2;
    AlgoritmoDeMezcla(s, inicio, medio); //Esta es la parte recursiva del algoritmo de mezcla, va dividiendo poco a poco en mitades el arreglo, esta es desde el s[0] a s[mitad]
    AlgoritmoDeMezcla(s, medio + 1, fin); //Esta es desde el s[mitad+1] a s[fin]
    Mezcla(s, inicio, medio, fin);
}

void Mezcla(int s[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;
    int* L = new int[n1]; //En lugar de tomar crear los punteros de forma "normal" para el Merge, se crearon como punteros para mayor rapidez
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = s[inicio + i]; //El algoritmo va comparando los valores de L y R, como estos ya estan ordenados el menor entre los 2 aunque sea de un tamaño mayor a 1 va a ser el menor en ese conjunto
    for (int j = 0; j < n2; j++) R[j] = s[medio + 1 + j];
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) s[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) s[k++] = L[i++]; //Los valores que lleguen a sobrar al momento de terminar de ordenar alguno de los 2 arreglos seran puestos en el nuevo arreglo
    while (j < n2) s[k++] = R[j++];
    delete[] L;
    delete[] R;
}

/**-----------------Algoritmo de Inserción-----------------**/
void AlgoritmoDeInsercion(int s[], int n) {
    for (int m = 1; m < n; ++m) {
        int val = s[m]; //Variable temporal para guardar el valor que se va a cambiar
        int j = m - 1; //Aqui sucede la comparacion hasta que se llegue a encontrar un numero menor
        while (j >= 0 && s[j] > val) {
            s[j + 1] = s[j];
            --j;
        }
        s[j + 1] = val;
    }
}

/**-----------------Algoritmo de Burbuja/Bubble Sort-----------------**/
void AlgoritmoDeBurbuja(int s[], int n) {
    for (int i = 0; i < n - 1; i++) { //Simplemente va comparando hasta llegar al tamaño maximo del arreglo, uno por uno, haciendolo poco eficaz
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}

/**-----------------Algoritmo de Monticulos/Heap Sort-----------------**/
void HeapSort(int s[], int n) {
    BuildHeapSort(s, n);
    for (int i = n - 1; i > 0; i--) {
        swap(s[0], s[i]);
        MaxHeapify(s, 0, i);
    }
}

void BuildHeapSort(int s[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(s, i, n);
    }
}

void MaxHeapify(int s[], int i, int n) {
    int izquierdo = 2 * i + 1; // Indice del hijo izquierdo
    int derecho = 2 * i + 2;   // Indice del hijo derecho
    int mayor = i; // Suponemos que la raiz es el mayor
    
    // Comparar con el hijo izquierdo
    if (izquierdo < n && s[izquierdo] > s[mayor]) {
        mayor = izquierdo;
    }
    // Comparar con el hijo derecho
    if (derecho < n && s[derecho] > s[mayor]) {
        mayor = derecho;
    }
    // Si el mayor no es la raiz, intercambiar y continuar
    if (mayor != i) {
        swap(s[i], s[mayor]);
        MaxHeapify(s, mayor, n); // Recursivamente asegurar la propiedad de monticulo
    }
}

/**-----------------Algoritmo de Shell/Shell Sort-----------------**/
void ShellSort(int s[], int n) {
    //Aqui se va haciendo mas pequeños los gaps con los que se comparan en el algoritmo de shell, hasta que llegue a un gap igual a 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = s[i];
            int j = i;
            while (j >= gap && s[j - gap] > temp) {
                s[j] = s[j - gap];
                j -= gap;
            }
            s[j] = temp;
        }
    }
}

/**-----------------Algoritmo de Selección/Selection Sort-----------------**/
// Recorre el arreglo y selecciona el menor elemento para colocarlo en su posición correcta
void SelectionSort(int s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j] < s[min_idx]) {
                min_idx = j;
            }
        }
        swap(s[i], s[min_idx]); // Intercambia el menor elemento encontrado con el actual
    }
}

/**-----------------Quick Sort-----------------**/
// Utiliza el esquema de particion para dividir el arreglo y ordenar de manera recursiva
void QuickSort(int s[], int inicio, int fin) {
    if (inicio >= fin) return;
    int pivote_idx = Partition(s, inicio, fin);
    QuickSort(s, inicio, pivote_idx - 1); // Ordena la parte izquierda
    QuickSort(s, pivote_idx + 1, fin);   // Ordena la parte derecha
}

// Función de particion utilizada en QuickSort
// Coloca el pivote en su posición correcta y reorganiza los elementos
int Partition(int s[], int inicio, int fin) {
    int pivote = s[fin]; // Se elige el ultimo elemento como pivote
    int i = inicio - 1;
    for (int j = inicio; j < fin; j++) {
        if (s[j] <= pivote) {
            swap(s[++i], s[j]);
        }
    }
    swap(s[i + 1], s[fin]); // Coloca el pivote en su posicion correcta
    return i + 1;
}

