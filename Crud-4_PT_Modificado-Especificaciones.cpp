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

// Estructura para almacenar información de paquetes turísticos
struct PaqueteTuristico {
    int id;               // ID único del paquete
    string destino;       // Nombre del destino turístico
    double precio;        // Precio del paquete
    int duracionDias;     // Duración en días
    string disponible;    // Disponibilidad (si/no)
};

// Estructura para almacenar información del cliente
struct Cliente {
    int edad;             // Edad del cliente
    double descuento;     // Descuento aplicable
    string tipoPago;      // Método de pago
};

const string archivo = "paquetes.txt";  // Nombre del archivo de datos

// Función para convertir un string a minúsculas
string aMinusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

// Función para cargar paquetes desde archivo
vector<PaqueteTuristico> cargarPaquetes() {
    vector<PaqueteTuristico> paquetes;  // Vector para almacenar paquetes
    ifstream fin(archivo);              // Objeto para lectura de archivo
    PaqueteTuristico p;                 // Variable temporal para paquetes

    if (!fin.is_open()) {               // Verificar si el archivo se abrió
        cout << "No se pudo abrir el archivo para lectura." << endl;
        return paquetes;                // Retorna vector vacío si hay error
    }

    // Leer archivo línea por línea
    while (fin >> p.id) {               // Leer ID
        fin.ignore();                   // Ignorar salto de línea
        getline(fin, p.destino);        // Leer destino
        fin >> p.precio >> p.duracionDias >> p.disponible;  // Leer resto de datos
        paquetes.push_back(p);          // Agregar paquete al vector
    }

    fin.close();                        // Cerrar archivo
    return paquetes;                    // Retornar vector con paquetes
}

// Función para guardar paquetes en archivo
void guardarPaquetes(const vector<PaqueteTuristico>& paquetes) {
    ofstream fout(archivo);             // Objeto para escritura de archivo
    
    if (!fout.is_open()) {              // Verificar si se pudo abrir archivo
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    // Escribir cada paquete en el archivo
    for (const auto& p : paquetes) {
        fout << p.id << endl;                   // Escribir ID
        fout << p.destino << endl;              // Escribir destino
        fout << fixed << setprecision(2)        // Formatear precio con 2 decimales
             << p.precio << " "                 // Escribir precio
             << p.duracionDias << " "           // Escribir duración
             << p.disponible << endl;           // Escribir disponibilidad
    }
    fout.close();                       // Cerrar archivo
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();                        // Limpiar flags de error
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar contenido restante
}

// Función para verificar si un ID ya existe
bool idExiste(const vector<PaqueteTuristico>& paquetes, int id) {
    for (const auto& p : paquetes) {    // Recorrer todos los paquetes
        if (p.id == id) {               // Si encuentra el ID
            return true;                // Retornar verdadero
        }
    }
    return false;                       // Si no lo encuentra, retornar falso
}

// Función para crear un nuevo paquete turístico
void crearPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();  // Cargar paquetes existentes
    PaqueteTuristico nuevo;            // Nuevo paquete a crear
    Cliente cliente;                   // Información del cliente

    // Generar ID único aleatorio
    do {
        nuevo.id = rand() % 1000 + 1;  // Generar número entre 1 y 1000
    } while (idExiste(paquetes, nuevo.id));  // Verificar que no exista
    
    cout << "ID generado automáticamente: " << nuevo.id << endl;

    // Solicitar información del paquete
    cout << "Destino: ";
    getline(cin >> ws, nuevo.destino);  // Leer destino (ws ignora espacios iniciales)

    // Validar precio (debe ser positivo)
    cout << "Precio: ";
    while (!(cin >> nuevo.precio) || nuevo.precio <= 0) {
        cout << "Precio inválido. Ingrese un valor positivo: ";
        limpiarBuffer();
    }

    // Validar duración (debe ser positiva)
    cout << "Duración (días): ";
    while (!(cin >> nuevo.duracionDias) || nuevo.duracionDias <= 0) {
        cout << "Duración inválida. Ingrese un número positivo: ";
        limpiarBuffer();
    }

    // Validar disponibilidad (solo si/no)
    cout << "¿Destino disponible? (si/no): ";
    while (cin >> nuevo.disponible && 
           aMinusculas(nuevo.disponible) != "si" && 
           aMinusculas(nuevo.disponible) != "no") {
        cout << "Entrada inválida. Ingrese 'si' o 'no': ";
        limpiarBuffer();
    }
    nuevo.disponible = aMinusculas(nuevo.disponible);  // Convertir a minúsculas

    // Solicitar edad del cliente
    cout << "Ingrese su edad: ";
    while (!(cin >> cliente.edad) || cliente.edad <= 0 || cliente.edad > 120) {
        cout << "Edad inválida. Intente de nuevo (1-120): ";
        limpiarBuffer();
    }

    // Aplicar descuento si corresponde
    if (cliente.edad < 5 || cliente.edad > 65) {
        nuevo.precio *= 0.9;  // Aplicar 10% de descuento
        cout << "Descuento del 10% aplicado. Nuevo precio: $" 
             << fixed << setprecision(2) << nuevo.precio << endl;
    }

    // Solicitar método de pago
    cout << "Tipo de pago (efectivo, transferencia o tarjeta): ";
    while (cin >> cliente.tipoPago && 
           aMinusculas(cliente.tipoPago) != "efectivo" &&
           aMinusculas(cliente.tipoPago) != "transferencia" &&
           aMinusculas(cliente.tipoPago) != "tarjeta") {
        cout << "Tipo de pago no válido. Intente nuevamente: ";
        limpiarBuffer();
    }

    paquetes.push_back(nuevo);         // Agregar nuevo paquete al vector
    guardarPaquetes(paquetes);         // Guardar todos los paquetes en archivo

    cout << "Paquete creado exitosamente.\n";
}

// Función para mostrar todos los paquetes
void mostrarPaquetes() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();  // Cargar paquetes
    
    if (paquetes.empty()) {            // Verificar si no hay paquetes
        cout << "No hay paquetes turísticos registrados.\n";
        return;
    }

    // Encabezado de la tabla
    cout << left << setw(5) << "ID" << setw(20) << "Destino" << setw(12)
         << "Precio" << setw(10) << "Días" << setw(12) << "Disponible" << endl;
    cout << string(60, '-') << endl;   // Línea separadora

    // Mostrar cada paquete
    for (const auto& p : paquetes) {
        cout << left << setw(5) << p.id << setw(20) << p.destino
             << "$" << fixed << setprecision(2) << setw(11) << p.precio
             << setw(10) << p.duracionDias << setw(12) 
             << (p.disponible == "si" ? "Sí" : "No") << endl;
    }
}

// Función para modificar un paquete existente
void modificarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();  // Cargar paquetes
    
    if (paquetes.empty()) {            // Verificar si no hay paquetes
        cout << "No hay paquetes para modificar.\n";
        return;
    }

    int id;  // Variable para ID a modificar
    cout << "Ingrese el ID del paquete a modificar: ";
    while (!(cin >> id)) {             // Validar que sea un número
        cout << "ID inválido. Intente de nuevo: ";
        limpiarBuffer();
    }

    bool encontrado = false;  // Bandera para saber si se encontró el paquete

    // Buscar paquete por ID
    for (auto& p : paquetes) {
        if (p.id == id) {
            encontrado = true;  // Marcar como encontrado
            
            // Solicitar nuevos datos
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
            while (cin >> p.disponible && 
                   aMinusculas(p.disponible) != "si" && 
                   aMinusculas(p.disponible) != "no") {
                cout << "Entrada inválida. Ingrese 'si' o 'no': ";
                limpiarBuffer();
            }
            p.disponible = aMinusculas(p.disponible);

            break;  // Salir del bucle una vez modificado
        }
    }

    if (encontrado) {
        guardarPaquetes(paquetes);     // Guardar cambios
        cout << "Paquete actualizado correctamente.\n";
    } else {
        cout << "No se encontró el paquete con ID " << id << ".\n";
    }
}

// Función para eliminar un paquete
void eliminarPaquete() {
    vector<PaqueteTuristico> paquetes = cargarPaquetes();  // Cargar paquetes
    
    if (paquetes.empty()) {            // Verificar si no hay paquetes
        cout << "No hay paquetes para eliminar.\n";
        return;
    }

    int id;  // Variable para ID a eliminar
    cout << "Ingrese el ID del paquete a eliminar: ";
    while (!(cin >> id)) {             // Validar que sea un número
        cout << "ID inválido. Intente de nuevo: ";
        limpiarBuffer();
    }

    // Buscar y eliminar paquete usando algoritmo STL
    auto it = remove_if(paquetes.begin(), paquetes.end(), 
                       [id](const PaqueteTuristico& p) { return p.id == id; });

    if (it != paquetes.end()) {        // Si se encontró el paquete
        paquetes.erase(it, paquetes.end());  // Eliminarlo del vector
        guardarPaquetes(paquetes);     // Guardar cambios
        cout << "Paquete eliminado correctamente.\n";
    } else {
        cout << "No se encontró el paquete con ID " << id << ".\n";
    }
}

// Función para mostrar el menú principal
void menu() {
    setlocale(LC_ALL, "es_ES.UTF-8");  // Configurar localización
    srand(time(0));                    // Inicializar semilla para números aleatorios

    int opcion;  // Variable para opción del menú
    do {
        // Mostrar opciones del menú
        cout << "\n--- GESTIÓN DE PAQUETES TURÍSTICOS ---\n";
        cout << "1. Crear paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout << "3. Modificar paquete\n";
        cout << "4. Eliminar paquete\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";

        // Validar entrada del menú (debe ser número entre 1 y 5)
        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cout << "Opción inválida. Intente con un número entre 1 y 5: ";
            limpiarBuffer();
        }

        limpiarBuffer();  // Limpiar buffer después de leer la opción

        // Ejecutar función según opción seleccionada
        switch (opcion) {
            case 1: crearPaquete(); break;     // Crear nuevo paquete
            case 2: mostrarPaquetes(); break;  // Mostrar todos los paquetes
            case 3: modificarPaquete(); break; // Modificar paquete existente
            case 4: eliminarPaquete(); break;  // Eliminar paquete
            case 5: cout << "Saliendo del programa...\n"; break;  // Salir
        }
    } while (opcion != 5);  // Repetir hasta que se seleccione salir
}

// Función principal
int main() {
    menu();  // Llamar al menú principal
    return 0;  // Indicar que el programa terminó correctamente
}