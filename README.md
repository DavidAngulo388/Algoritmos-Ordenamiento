
## Medición de tiempo para distintos algoritmos de ordenamiento

# Descripción
Este programa ha sido desarrollado con el propósito de medir el tiempo de ejecución de diferentes algoritmos de ordenamiento en C++. Los algoritmos implementados son los siguientes:

- **Ordenamiento por Inserción**  
- **Ordenamiento de Burbuja**  
- **Ordenamiento por Montículos (Heap Sort)**  
- **Shell Sort**  
- **Ordenamiento por Selección**  
- **Ordenamiento por Mezcla (Merge Sort)**  
- **Quick Sort**  

# Requisitos del sistema
Las específicaciones del sistema con las que se hicieron pruebas fueron las siguientes:
- **Procesador: Intel Core i7-1185G7**
- **Memoria RAM: 16GB**
- **Tarjeta Gráfica: Intel Iris XE Graphics**
- **Sistema Operativo: Windows 11 Pro**

# Compilación
Para la compilación del código, se uso el compilador g++, para su uso desde terminal tendría que ir a la dirección del archivo desde la terminal, desde ahí, poner 'g++' junto la dirección del archivo seguido de '-o' y el nombre del archivo ejecutable, el archivo ejecutable lo puede abrir desde la terminal o desde el ejecutable creado

**Recomendación para su ejecución:** No deje ningún proceso externo activo de preferencia, para impedir que el procesador de su dispositivo este sobrecargado, esto puede llegar a afectar de forma significativa en su velocidad de ejecución

# Descripción de algoritmos
- **Ordenamiento por Inserción:** Este algoritmo recibe una sucesión y ordena sus elementos en orden no decreciente comparando un valor inicial con los siguientes valores en la sucesión hasta encontrar uno menor, después de esto compara ese valor menor con todos los valores anteriores de la sucesión para encontrar en donde se debe posicionar.

- **Ordenamiento de Burbuja:** Método simple que recorre repetidamente una lista, compara elementos adyacentes y los intercambia si están en el orden incorrecto. El algoritmo recibe como entrada una sucesión y ordena sus elementos en orden no decreciente.

- **Heap Sort:** Este algoritmo de ordenamiento utiliza una estructura de datos llamada montículo (o heap en inglés) para ordenar los elementos. Un montículo es un árbol binario casi completo que satisface la propiedad de montículo.

- **Shell Sort:** Similar al algoritmo de inserción, este supera algunas de sus limitaciones al permitir el intercambio de elementos distantes al poder ordenar elementos separados por una cierta distancia (también llamado gap), reduciendo progresivamente esta distancia hasta el gap sea 1.

- **Ordenamiento por selección:** Este método divide la lista de entrada en dos partes: una sublista ya ordenada y una lista por ordenar. El algoritmo busca repetidamente el elemento mínimo de la parte no ordenada y lo coloca al final de la parte ordenada.

- **Merge Sort:** El algoritmo divide la sucesión en mitades recursivamente hasta obtener subsucesiones, que son trivialmente ordenadas. Luego combina estas sublistas para producir nuevas subsucesiones ordenadas hasta que solo queda una sucesión completa ordenada.

- **Quick Sort:** Este algoritmo selecciona un elemento de la sucesión como pivote y particiona el arreglo alrededor del pivote, colocando todos los elementos menores al pivote a su izquierda y todos los mayores a su derecha. Luego, recursivamente ordena los dos subsucesiones resultantes.

# Gráfica comparativa
![imagen](https://github.com/user-attachments/assets/daf5eaa3-ddce-457e-8bec-703dce4ece9c)

Por razones de que el algoritmo de ordenamiento de burbuja y selección generan demasiado ruido para los otros algoritmos, se tiene una gráfica mas, para ver esos elementos "perdidos" en la gráfica original.

![imagen](https://github.com/user-attachments/assets/0d31089a-4ff9-4e4a-b61a-8eaff76f4fa6)

# Análisis de resultados
Se podrían mencionar los diferentes casos
- El **algoritmo de burbuja** fue el más lento de todos, tomando en total 3.52 milisegundos (3587158.4 nanosegundos) en promedio en el tamaño 1000, una diferencia de 2 milisegundos con el segundo peor tiempo en tamaño 1000 con el **algoritmo de selección**.
- El **Quick Sort** fue el más rápido de todos, tomando en total 0.103 milisegundos (103261 nanosegundos) en promedio en el tamaño 1000, una diferencia de 0.02 milisegundos con el segundo mejor tiempo en tamaño 1000 con el **Shell Sort**.
- El **Merge Sort** y **Shell Sort** son los algoritmos con mayor ruido en sus gráficas, esto puede ser causado por problema en el procesador o ruido generado por el sistema operativo, esto es más notable con **Merge Sort** que en algunos puntos anteriores al tamaño 1000 tarda mayor tiempo en ordenar los datos.

# Conclusión
Desde los inicios de la computación, se han desarrollado numerosos algoritmos de ordenamiento, cada uno con sus ventajas y desventajas en términos de eficiencia y velocidad. En este proyecto, se analizó el desempeño de varios algoritmos clásicos, confirmando la eficiencia de algoritmos como Quick Sort y la ineficiencia de otros como el de burbuja.

Esta práctica permitió comprender no solo su implementación en código, sino también su comportamiento lógico y eficiencia computacional.





