#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct PaqueteTuristico {
    int id;
    string destino;
    float precio;
    int duracionDias;
    bool disponible;
};

// Estructura para almacenar información del cliente
struct Cliente {
    int edad;
    float descuento;
    string tipoPago;
};

// Archivo donde se guardan los datos
const string archivo = "paquetes.txt";

// Función para cargar los datos desde el archivo
vector<PaqueteTuristico> cargarPaquetes() {
    vector<PaqueteTuristico> paquetes;
    ifstream fin(archivo);
    PaqueteTuristico p;

    while (fin >> p.id) {
        fin.ignore(); // ignorar salto
        getline(fin, p.destino);
        fin >> p.precio >> p.duracionDias >> p.disponible;
        paquetes.push_back(p);
    }

    fin.close();
    return paquetes;
}

// Guardar todos los paquetes al archivo
void guardarPaquetes(const vector<PaqueteTuristico>& paquetes) {
    ofstream fout(archivo);
    for (const auto& p : paquetes) {
        fout << p.id << endl;
        fout << p.destino << endl;
        fout << p.precio << " " << p.duracionDias << " " << p.disponible << endl;
    }
    fout.close();
}

// Crear un nuevo paquete
void crearPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    PaqueteTuristico nuevo;

    cout << "Ingrese ID: ";
    cin >> nuevo.id;
    cin.ignore();
    cout << "Destino: ";
    getline(cin, nuevo.destino);
    cout << "Precio: ";
    cin >> nuevo.precio;
    cout << "Duración (días): ";
    cin >> nuevo.duracionDias;
    cout << "Disponible (1=Sí, 0=No): ";
    cin >> nuevo.disponible;

    // Preguntar por la edad del cliente
    Cliente cliente;
    cout << "Ingrese su edad: ";
    cin >> cliente.edad;

    // Aplicar descuento si es necesario
    if (cliente.edad < 5 || cliente.edad > 65) {
        nuevo.precio *= 0.9; // 10% de descuento
        cout << "Descuento aplicado. Nuevo precio: " << nuevo.precio << endl;
    }

    // Preguntar por el tipo de pago
    cout << "Tipo de pago (1=Efectivo, 2=Transferencia, 3=Tarjeta): ";
    int tipoPagoOpcion;
    cin >> tipoPagoOpcion;

    switch (tipoPagoOpcion) {
        case 1: cliente.tipoPago = "Efectivo"; break;
        case 2: cliente.tipoPago = "Transferencia"; break;
        case 3: cliente.tipoPago = "Tarjeta"; break;
        default: cliente.tipoPago = "No especificado"; break;
    }

    paquetes.push_back(nuevo);
    guardarPaquetes(paquetes);

    cout << "Paquete creado exitosamente.\n";
}

// Mostrar todos los paquetes
void mostrarPaquetes() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    cout << left << setw(5) << "ID" << setw(20) << "Destino" << setw(10)
         << "Precio" << setw(10) << "Días" << setw(12) << "Disponible" << endl;

    for (const auto& p : paquetes) {
        cout << left << setw(5) << p.id << setw(20) << p.destino
             << setw(10) << p.precio << setw(10) << p.duracionDias
             << (p.disponible ? "Sí" : "No") << endl;
    }
}

// Modificar un paquete
void modificarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    int id;
    cout << "Ingrese el ID del paquete a modificar: ";
    cin >> id;
    bool encontrado = false;

    for (auto& p : paquetes) {
        if (p.id == id) {
            encontrado = true;
            cin.ignore();
            cout << "Nuevo destino: ";
            getline(cin, p.destino);
            cout << "Nuevo precio: ";
            cin >> p.precio;
            cout << "Nueva duración (días): ";
            cin >> p.duracionDias;
            cout << "¿Está disponible? (1=Sí, 0=No): ";
            cin >> p.disponible;
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

// Eliminar un paquete
void eliminarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();
    int id;
    cout << "Ingrese el ID del paquete a eliminar: ";
    cin >> id;
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

// Menú principal
void menu() {
    int opcion;
    do {
        cout << "\n--- GESTIÓN DE PAQUETES TURÍSTICOS ---\n";
        cout << "1. Crear paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout << "3. Modificar paquete\n";
        cout << "4. Eliminar paquete\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: crearPaquete(); break;
            case 2: mostrarPaquetes(); break;
            case 3: modificarPaquete(); break;
            case 4: eliminarPaquete(); break;
            case 5: cout << "Usted esta saliendo del sistema \n"; break;
            default: cout << "La opciónes incorrecta vuelva a intentarlo nuevamente.\n"; break;
        }
    } while (opcion != 5);
}

int main() {
    setlocale(LC_ALL "Spanish");
    menu();
    return 0;
}
