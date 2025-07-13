#include <iostream>       // Para entrada/salida estándar (cin, cout)
#include <fstream>        // Para manejo de archivos (ifstream, ofstream)
#include <vector>         // Para usar la estructura de datos vector
#include <string>         // Para manejo de strings
#include <iomanip>        // Para formato de salida (setw, fixed)
#include <locale.h>       // Para configuración regional (setlocale)
#include <limits>         // Para límites de tipos (numeric_limits)
#include <cstdlib>        // Para funciones generales (rand, srand)
#include <ctime>          // Para funciones de tiempo (time)
#include <algorithm>      // Para algoritmos STL (transform, remove_if)


using namespace std;

struct PaqueteTuristico {
    int id;
    string destino;
    double precio;
    int duracionDias;
    string disponible;
};

struct Cliente {
    int edad;
    double descuento;
    string tipoPago;
};

const string archivo = "paquetes.txt";

string aMinusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

vector<PaqueteTuristico> cargarPaquetes() {
    vector<PaqueteTuristico> paquetes;
    ifstream fin(archivo);
    PaqueteTuristico p;

    if (!fin.is_open()) {
        cout << "No se pudo abrir el archivo para lectura." << endl;
        return paquetes;
    }

    while (fin >> p.id) {
        fin.ignore();
        getline(fin, p.destino);
        fin >> p.precio >> p.duracionDias >> p.disponible;
        paquetes.push_back(p);
    }

    fin.close();
    return paquetes;
}

void guardarPaquetes(const vector<PaqueteTuristico>& paquetes) {
    ofstream fout(archivo);
    
    if (!fout.is_open()) {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    for (const auto& p : paquetes) {
        fout << p.id << endl;
        fout << p.destino << endl;
        fout << fixed << setprecision(2) << p.precio << " " 
             << p.duracionDias << " " << p.disponible << endl;
    }
    fout.close();
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool idExiste(const vector<PaqueteTuristico>& paquetes, int id) {
    for (const auto& p : paquetes) {
        if (p.id == id) {
            return true;
        }
    }
    return false;
}

void crearPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    PaqueteTuristico nuevo;
    Cliente cliente;

    // Generar ID único
    do {
        nuevo.id = rand() % 1000 + 1;
    } while (idExiste(paquetes, nuevo.id));
    
    cout << "ID generado automáticamente: " << nuevo.id << endl;

    cout << "Destino: ";
    getline(cin >> ws, nuevo.destino);

    cout << "Precio: ";
    while (!(cin >> nuevo.precio) || nuevo.precio <= 0) {
        cout << "Precio inválido. Ingrese un valor positivo: ";
        limpiarBuffer();
    }

    cout << "Duración (días): ";
    while (!(cin >> nuevo.duracionDias) || nuevo.duracionDias <= 0) {
        cout << "Duración inválida. Ingrese un número positivo: ";
        limpiarBuffer();
    }

    cout << "¿Destino disponible? (si/no): ";
    while (cin >> nuevo.disponible && aMinusculas(nuevo.disponible) != "si" && aMinusculas(nuevo.disponible) != "no") {
        cout << "Entrada inválida. Ingrese 'si' o 'no': ";
        limpiarBuffer();
    }
    nuevo.disponible = aMinusculas(nuevo.disponible);

    cout << "Ingrese su edad: ";
    while (!(cin >> cliente.edad) || cliente.edad <= 0 || cliente.edad > 120) {
        cout << "Edad inválida. Intente de nuevo (1-120): ";
        limpiarBuffer();
    }

    if (cliente.edad < 5 || cliente.edad > 65) {
        nuevo.precio *= 0.9;
        cout << "Descuento del 10% aplicado. Nuevo precio: $" 
             << fixed << setprecision(2) << nuevo.precio << endl;
    }

    cout << "Tipo de pago (efectivo, transferencia o tarjeta): ";
    while (cin >> cliente.tipoPago && 
           aMinusculas(cliente.tipoPago) != "efectivo" &&
           aMinusculas(cliente.tipoPago) != "transferencia" &&
           aMinusculas(cliente.tipoPago) != "tarjeta") {
        cout << "Tipo de pago no válido. Intente nuevamente: ";
        limpiarBuffer();
    }

    paquetes.push_back(nuevo);
    guardarPaquetes(paquetes);

    cout << "Paquete creado exitosamente.\n";
}

void mostrarPaquetes() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    
    if (paquetes.empty()) {
        cout << "No hay paquetes turísticos registrados.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(20) << "Destino" << setw(12)
         << "Precio" << setw(10) << "Días" << setw(12) << "Disponible" << endl;
    cout << string(60, '-') << endl;

    for (const auto& p : paquetes) {
        cout << left << setw(5) << p.id << setw(20) << p.destino
             << "$" << fixed << setprecision(2) << setw(11) << p.precio
             << setw(10) << p.duracionDias << setw(12) 
             << (p.disponible == "si" ? "Sí" : "No") << endl;
    }
}

void modificarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    
    if (paquetes.empty()) {
        cout << "No hay paquetes para modificar.\n";
        return;
    }

    int id;
    cout << "Ingrese el ID del paquete a modificar: ";
    while (!(cin >> id)) {
        cout << "ID inválido. Intente de nuevo: ";
        limpiarBuffer();
    }

    bool encontrado = false;
    for (auto& p : paquetes) {
        if (p.id == id) {
            encontrado = true;
            
            cout << "Nuevo destino (actual: " << p.destino << "): ";
            getline(cin >> ws, p.destino);

            cout << "Nuevo precio (actual: " << p.precio << "): ";
            while (!(cin >> p.precio) || p.precio <= 0) {
                cout << "Precio inválido. Intente de nuevo: ";
                limpiarBuffer();
            }

            cout << "Nueva duración (días) (actual: " << p.duracionDias << "): ";
            while (!(cin >> p.duracionDias) || p.duracionDias <= 0) {
                cout << "Duración inválida. Intente de nuevo: ";
                limpiarBuffer();
            }

            cout << "¿Está disponible? (si/no) (actual: " << p.disponible << "): ";
            while (cin >> p.disponible && aMinusculas(p.disponible) != "si" && aMinusculas(p.disponible) != "no") {
                cout << "Entrada inválida. Ingrese 'si' o 'no': ";
                limpiarBuffer();
            }
            p.disponible = aMinusculas(p.disponible);

            break;
        }
    }

    if (encontrado) {
        guardarPaquetes(paquetes);
        cout << "Paquete actualizado correctamente.\n";
    } else {
        cout << "No se encontró el paquete con ID " << id << ".\n";
    }
}

void eliminarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    
    if (paquetes.empty()) {
        cout << "No hay paquetes para eliminar.\n";
        return;
    }

    int id;
    cout << "Ingrese el ID del paquete a eliminar: ";
    while (!(cin >> id)) {
        cout << "ID inválido. Intente de nuevo: ";
        limpiarBuffer();
    }

    auto it = remove_if(paquetes.begin(), paquetes.end(), 
                       [id](const PaqueteTuristico& p) { return p.id == id; });

    if (it != paquetes.end()) {
        paquetes.erase(it, paquetes.end());
        guardarPaquetes(paquetes);
        cout << "Paquete eliminado correctamente.\n";
    } else {
        cout << "No se encontró el paquete con ID " << id << ".\n";
    }
}

void menu() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));

    int opcion;
    do {
        cout << "\n--- GESTIÓN DE PAQUETES TURÍSTICOS ---\n";
        cout << "1. Crear paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout << "3. Modificar paquete\n";
        cout << "4. Eliminar paquete\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";

        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cout << "Opción inválida. Intente con un número entre 1 y 5: ";
            limpiarBuffer();
        }

        limpiarBuffer();

        switch (opcion) {
            case 1: crearPaquete(); break;
            case 2: mostrarPaquetes(); break;
            case 3: modificarPaquete(); break;
            case 4: eliminarPaquete(); break;
            case 5: cout << "Saliendo del programa...\n"; break;
        }
    } while (opcion != 5);
}

int main() {
    menu();
    return 0;
}