#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <locale.h>
#include <windows.h>
#include <limits>
#include <cstdlib>
#include <ctime>

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

//Sirve para que el usuario pueda escribir ‘Efectivo’, ‘EFECTIVO’ o como quiera, y el programa lo entienda igual.
string aMinusculas(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        texto[i] = tolower(texto[i]);  // Convierte cada letra a minúscula
    }
    return texto;  // Devuelve el texto ya en minúsculas
}




vector<PaqueteTuristico> cargarPaquetes() {
    vector<PaqueteTuristico> paquetes;
    ifstream fin(archivo);
    PaqueteTuristico p;

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
    for (const auto& p : paquetes) {
        fout << p.id << endl;
        fout << p.destino << endl;
        fout << p.precio << " " << p.duracionDias << " " << p.disponible << endl;
    }
    fout.close();
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void crearPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    PaqueteTuristico nuevo;

    // ID aleatorio entre 1 y 1000
    nuevo.id = rand() % 1000 + 1;
    cout << "ID generado automáticamente: " << nuevo.id << endl;

    cin.ignore();
    cout << "Destino: ";
    getline(cin, nuevo.destino);

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

    limpiarBuffer();
    cout << "Destino disponible: si o no ";
    getline(cin, nuevo.disponible);

    if (nuevo.disponible == "Si" || nuevo.disponible == "si") {
        cout << "Destino disponible" << endl;
    } else {
        cout << "Destino inalcanzable" << endl;
    }

    Cliente cliente;
    cout << "Ingrese su edad: ";
    while (!(cin >> cliente.edad) || cliente.edad <= 0) {
        cout << "Edad inválida. Intente de nuevo: ";
        limpiarBuffer();
    }

    if (cliente.edad < 5 || cliente.edad > 65) {
        nuevo.precio *= 0.9;
        cout << "Descuento del 10% aplicado. Nuevo precio: $" << fixed << setprecision(2) << nuevo.precio << endl;
    }
	
	///Tipo de pago
	
    // Preguntar por el tipo de pago (sin usar do while)
		cout << "Tipo de pago (efectivo, transferencia o tarjeta): ";
		cin >> cliente.tipoPago;
		cliente.tipoPago = aMinusculas(cliente.tipoPago);
		
		// Validar mientras lo que escribió no sea válido
		while (cliente.tipoPago != "efectivo" &&
		       cliente.tipoPago != "transferencia" &&
		       cliente.tipoPago != "tarjeta") {
		
		    cout << "? Tipo de pago no válido. Intente nuevamente.\n";
		    cout << "Tipo de pago (efectivo, transferencia o tarjeta): ";
		    cin >> cliente.tipoPago;
		    cliente.tipoPago = aMinusculas(cliente.tipoPago);
		}
	
	
	
    paquetes.push_back(nuevo);
    guardarPaquetes(paquetes);

    cout << "Paquete creado exitosamente.\n";
}

void mostrarPaquetes() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    cout << left << setw(5) << "ID" << setw(20) << "Destino" << setw(12)
         << "Precio" << setw(10) << "Días" << setw(12) << "Disponible" << endl;

    for (const auto& p : paquetes) {
        cout << left << setw(5) << p.id << setw(20) << p.destino
             << "$" << fixed << setprecision(2) << setw(11) << p.precio
             << setw(10) << p.duracionDias << p.disponible << endl;
    }
}

void modificarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
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
            cin.ignore();
            cout << "Nuevo destino: ";
            getline(cin, p.destino);

            cout << "Nuevo precio: ";
            while (!(cin >> p.precio) || p.precio <= 0) {
                cout << "Precio inválido. Intente de nuevo: ";
                limpiarBuffer();
            }

            cout << "Nueva duración (días): ";
            while (!(cin >> p.duracionDias) || p.duracionDias <= 0) {
                cout << "Duración inválida. Intente de nuevo: ";
                limpiarBuffer();
            }

            limpiarBuffer();
            cout << "¿Está disponible? (si o no): ";
            getline(cin, p.disponible);

            if (p.disponible == "Si" || p.disponible == "si") {
                cout << "Destino disponible" << endl;
            } else {
                cout << "Destino inalcanzable" << endl;
            }

            break;
        }
    }

    if (encontrado) {
        guardarPaquetes(paquetes);
        cout << "Paquete actualizado.\n";
    } else {
        cout << "Paquete no encontrado.\n";
    }
}

void eliminarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    int id;
    cout << "Ingrese el ID del paquete a eliminar: ";
    while (!(cin >> id)) {
        cout << "ID inválido. Intente de nuevo: ";
        limpiarBuffer();
    }

    bool eliminado = false;
    vector<PaqueteTuristico> nuevos;
    for (const auto& p : paquetes) {
        if (p.id != id) {
            nuevos.push_back(p);
        } else {
            eliminado = true;
        }
    }

    if (eliminado) {
        guardarPaquetes(nuevos);
        cout << "Paquete eliminado correctamente.\n";
    } else {
        cout << "No se encontró el paquete con ese ID.\n";
    }
}

void menu() {
    setlocale(LC_ALL, "ES_ES.UTF-8");

    int opcion;
    do {
        cout << "\n--- GESTIÓN DE PAQUETES TURÍSTICOS ---\n";
        cout << "1. Crear paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout << "3. Modificar paquete\n";
        cout << "4. Eliminar paquete\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";

        while (!(cin >> opcion)) {
            cout << "Entrada inválida. Intente con un número: ";
            limpiarBuffer();
        }

        switch (opcion) {
            case 1: crearPaquete(); break;
            case 2: mostrarPaquetes(); break;
            case 3: modificarPaquete(); break;
            case 4: eliminarPaquete(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 5);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "Spanish");

    srand(time(0)); // Inicializa generador aleatorio

    menu();
    return 0;
}
