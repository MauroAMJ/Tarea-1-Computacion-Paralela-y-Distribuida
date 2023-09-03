#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Funci�n para cargar el laberinto desde un archivo
vector<vector<char>> CargarLaberintoDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo); // Abrir el archivo para lectura
    vector<vector<char>> laberinto; // Crear una estructura de datos para almacenar el laberinto
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) { // Leer cada l�nea del archivo
            vector<char> fila(linea.begin(), linea.end()); // Convertir la l�nea en un vector de caracteres
            laberinto.push_back(fila); // Agregar la fila al laberinto
        }
        archivo.close(); // Cerrar el archivo despu�s de leerlo
    } else {
        cerr << "No se pudo abrir el archivo de entrada." << endl; // Mostrar un mensaje de error si no se puede abrir el archivo
    }

    return laberinto; // Devolver el laberinto como un vector de vectores de caracteres
}

// Funci�n para encontrar la entrada (E) y la salida (S) en el laberinto
pair<pair<size_t, size_t>, pair<size_t, size_t>> EncontrarEntradaSalida(const vector<vector<char>>& laberinto) {
    pair<size_t, size_t> entrada = {static_cast<size_t>(-1), static_cast<size_t>(-1)};
    pair<size_t, size_t> salida = {static_cast<size_t>(-1), static_cast<size_t>(-1)};

    for (size_t i = 0; i < laberinto.size(); ++i) {
        for (size_t j = 0; j < laberinto[i].size(); ++j) {
            if (laberinto[i][j] == 'E') { // Buscar la entrada (E) en el laberinto
                entrada = {i, j};
            } else if (laberinto[i][j] == 'S') { // Buscar la salida (S) en el laberinto
                salida = {i, j};
            }
        }
    }

    return {entrada, salida}; // Devolver las coordenadas de entrada y salida
}

// Funci�n para encontrar una ruta en el laberinto
bool EncontrarRutaEnLaberinto(vector<vector<char>>& laberinto, size_t fila, size_t columna) {
    size_t filasTotal = laberinto.size();
    size_t columnasTotal = laberinto[0].size();

    // Verificar si las coordenadas est�n fuera del laberinto
    if (fila < 0 || fila >= filasTotal || columna < 0 || columna >= columnasTotal) {
        return false;
    }

    // Verificar si se lleg� a la salida (S)
    if (laberinto[fila][columna] == 'S') {
        return true;
    }

    // Verificar si es una pared (#) o si ya ha sido visitado (*)
    if (laberinto[fila][columna] == '#' || laberinto[fila][columna] == '*' || laberinto[fila][columna] == 'X') {
        return false;
    }

    // Marcar la posici�n como visitada (*)
    laberinto[fila][columna] = '*';

    // Buscar en las cuatro direcciones posibles
    if (EncontrarRutaEnLaberinto(laberinto, fila - 1, columna) ||
        EncontrarRutaEnLaberinto(laberinto, fila, columna + 1) ||
        EncontrarRutaEnLaberinto(laberinto, fila + 1, columna) ||
        EncontrarRutaEnLaberinto(laberinto, fila, columna - 1)) {
        return true; // Si se encuentra una ruta en alguna direcci�n, retornar true
    }

    // Si no se encontr� ruta, desmarcar la posici�n
    laberinto[fila][columna] = ' ';
    return false;
}

// Funci�n para guardar la soluci�n en un archivo
void GuardarSolucionEnArchivo(const vector<vector<char>>& laberinto, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo); // Abrir el archivo para escritura

    if (archivo.is_open()) {
        for (const vector<char>& fila : laberinto) {
            for (char caracter : fila) {
                archivo << caracter; // Escribir cada caracter en el archivo
            }
            archivo << endl; // Agregar un salto de l�nea al final de cada fila
        }
        archivo.close(); // Cerrar el archivo despu�s de escribir la soluci�n
        cout << "Soluci�n guardada en '" << nombreArchivo << "'" << endl;
    } else {
        cerr << "No se pudo abrir el archivo de salida." << endl; // Mostrar un mensaje de error si no se puede abrir el archivo
    }
}

int main() {
    cout << "Inicio del programa" << endl;
    vector<vector<char>> laberinto = CargarLaberintoDesdeArchivo("laberinto.txt"); // Cargar el laberinto desde un archivo
    pair<pair<size_t, size_t>, pair<size_t, size_t>> entradaSalida = EncontrarEntradaSalida(laberinto); // Encontrar las coordenadas de entrada y salida

    if (entradaSalida.first != make_pair(static_cast<size_t>(-1), static_cast<size_t>(-1)) &&
        entradaSalida.second != make_pair(static_cast<size_t>(-1), static_cast<size_t>(-1))) {
            size_t filaEntrada = entradaSalida.first.first;
        size_t columnaEntrada = entradaSalida.first.second;

        EncontrarRutaEnLaberinto(laberinto, filaEntrada, columnaEntrada); // Encontrar la ruta en el laberinto
        laberinto[filaEntrada][columnaEntrada] = 'E'; // Marcar la entrada

        GuardarSolucionEnArchivo(laberinto, "solucion.txt"); // Guardar la soluci�n en un archivo

        cout << "Fin del programa" << endl;
    } else {
        cerr << "No se encontraron las coordenadas de entrada y salida en el laberinto. Es necesario marcar la entrada del laberinto con E y la salida con S, ambas en mayuscula" << endl; // Mostrar un mensaje de error si no se encuentran las coordenadas
    }

    return 0;
}
