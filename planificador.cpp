#include <iostream>  
#include <fstream>   // Para leer el archivo plan.txt
#include <sstream>   // Para separar los textos de cada línea
#include <vector>    // Para guardar nuestras actividades dinámicamente
#include <string>    // Para manejar textos
#include <cstdlib>   // Para funciones como exit() o stoi()
#include <unistd.h>  // Aquí vive la syscall fork()
#include <sys/wait.h>// Aquí vive la syscall waitpid()
#include <random>    // Para generar tiempos aleatorios si faltan

using namespace std;

// Estructura que representa un nodo de nuestro Grafo (DAG)
struct Actividad {
    string id;
    string nombre;
    int tiempo_ms;
    vector<string> dependencias; // Guarda los IDs de las tareas que deben terminar antes
};

int main(int argc, char* argv[]) {
    // 1. Validar que el usuario nos pase exactamente 3 argumentos
    // (Ejemplo: ./planificador plan.txt 3)
    if (argc != 3) {
        cerr << "Error de uso. Forma correcta: " << argv[0] << " <archivo.txt> <K>" << endl;
        return 1; // Salimos con error
    }

    // 2. Guardar los argumentos en variables amigables
    string nombre_archivo = argv[1];
    int limite_K = stoi(argv[2]); // stoi convierte de texto ("3") a número (3)

    // 3. Validar que K tenga sentido
    if (limite_K <= 0) {
        cerr << "Error: El límite de concurrencia K debe ser mayor a 0." << endl;
        return 1;
    }

    // Un mensajito para ver que vamos bien
    cout << "Iniciando simulador con K=" << limite_K << " y archivo: " << nombre_archivo << endl;

    // 4. Abrir el archivo plan.txt
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << endl;
        return 1;
    }

    vector<Actividad> lista_actividades;
    string linea;

    // 5. Leer línea por línea
    while (getline(archivo, linea)) {
        if (linea.empty()) continue; // Ignorar líneas en blanco

        stringstream ss(linea);
        string id, nombre, tiempo_str, deps_str;

        // Extraer los campos separados por ':'
        getline(ss, id, ':');
        getline(ss, nombre, ':');
        getline(ss, tiempo_str, ':');
        getline(ss, deps_str); // El resto son las dependencias

        Actividad nueva_act;
        nueva_act.id = id;
        nueva_act.nombre = nombre;

        // Limpiar espacios en blanco del tiempo
        tiempo_str.erase(0, tiempo_str.find_first_not_of(" "));
        tiempo_str.erase(tiempo_str.find_last_not_of(" ") + 1);

        // Si no hay tiempo, generar uno aleatorio entre 100 y 5000 ms (Regla de la rúbrica)
        if (tiempo_str.empty()) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(100, 5000);
            nueva_act.tiempo_ms = dis(gen);
        } else {
            nueva_act.tiempo_ms = stoi(tiempo_str);
        }

        // TODO: Procesar dependencias (deps_str) y guardarlas en el vector
        
        lista_actividades.push_back(nueva_act);
        cout << "Actividad cargada -> ID: " << nueva_act.id << " | Nombre: " << nueva_act.nombre 
             << " | Tiempo: " << nueva_act.tiempo_ms << "ms" << endl;
    }

    archivo.close();

    return 0; // Termina el programa con éxito
}
