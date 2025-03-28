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
principal como en el CSV (para los tiempos)*/
void EjecutarYRegistrar(void (*algoritmo)(int[], int), const string& nombreArchivo, const string& nombreAlgoritmo) {
    ofstream archivo(nombreArchivo);
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
            algoritmo(s, k); //Aunque lleve el nombre solamente "algoritmo", desde la función se llamo un puntero a función el cuál llama al algoritmo
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
    archivo.close();
}
/**-----------------Algoritmo de Mezcla/Merge Sort-----------------**/
void AlgoritmoDeMezcla(int s[], int inicio, int fin) {
    if (inicio >= fin) return;
    int medio = (inicio + fin) / 2;
    AlgoritmoDeMezcla(s, inicio, medio);
    AlgoritmoDeMezcla(s, medio + 1, fin);
    Mezcla(s, inicio, medio, fin);
}

void Mezcla(int s[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;
    int* L = new int[n1]; //En lugar de tomar crear los punteros de forma "normal" para el Merge, se crearon como punteros para mayor rapidez
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = s[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = s[medio + 1 + j];
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) s[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) s[k++] = L[i++];
    while (j < n2) s[k++] = R[j++];
    delete[] L;
    delete[] R;
}

/**-----------------Algoritmo de Inserción-----------------**/
void AlgoritmoDeInsercion(int s[], int n) {
    for (int m = 1; m < n; ++m) {
        int val = s[m];
        int j = m - 1;
        while (j >= 0 && s[j] > val) {
            s[j + 1] = s[j];
            --j;
        }
        s[j + 1] = val;
    }
}

/**-----------------Algoritmo de Burbuja/Bubble Sort-----------------**/
void AlgoritmoDeBurbuja(int s[], int n) {
    for (int i = 0; i < n - 1; i++) {
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
    int izquierdo = 2 * i + 1;
    int derecho = 2 * i + 2;
    int mayor = i;
    if (izquierdo < n && s[izquierdo] > s[mayor]) {
        mayor = izquierdo;
    }
    if (derecho < n && s[derecho] > s[mayor]) {
        mayor = derecho;
    }
    if (mayor != i) {
        swap(s[i], s[mayor]);
        MaxHeapify(s, mayor, n);
    }
}

/**-----------------Algoritmo de Shell/Shell Sort-----------------**/
void ShellSort(int s[], int n) {
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
void SelectionSort(int s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j] < s[min_idx]) {
                min_idx = j;
            }
        }
        swap(s[i], s[min_idx]);
    }
}

void QuickSort(int s[], int inicio, int fin) {
    if (inicio >= fin) return;
    int pivote_idx = Partition(s, inicio, fin);
    QuickSort(s, inicio, pivote_idx - 1);
    QuickSort(s, pivote_idx + 1, fin);
}

int Partition(int s[], int inicio, int fin) {
    int pivote = s[fin];
    int i = inicio - 1;
    for (int j = inicio; j < fin; j++) {
        if (s[j] <= pivote) {
            swap(s[++i], s[j]);
        }
    }
    swap(s[i + 1], s[fin]);
    return i + 1;
}
