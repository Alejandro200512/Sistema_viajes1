#include <iostream>       // Para entrada/salida estándar
#include <vector>         // Para usar contenedores vector
#include <string>         // Para manejo de strings
#include <iomanip>        // Para formato de salida (setw, fixed)
#include <limits>         // Para límites de tipos (numeric_limits)
#include <algorithm>      // Para algoritmos como remove_if
#include <cctype>         // Para funciones de caracteres (toupper)
#include <fstream>        // Para manejo de archivos

using namespace std;      // Usar el espacio de nombres estándar

// Estructura que representa un destino turístico
struct Destino {
    string nombre;               // Nombre del destino
    double costo_dia_hotel;      // Costo por día de hotel
    double costo_persona_pasaje; // Costo de pasaje por persona
};

// Estructura que representa una reserva de viaje
struct Reserva {
    string destino;        // Nombre del destino reservado
    int dias;              // Días de estadía
    int adultos;           // Cantidad de adultos
    int ninos;             // Cantidad de niños
    int adultos_mayores;   // Cantidad de adultos mayores
    double total;          // Total a pagar
};

// Base de datos inicial de destinos disponibles
vector<Destino> destinos = {
    {"Galapagos", 80, 100},
    {"Quito", 100, 60},
    {"Cuenca", 80, 70},
    {"Ibarra", 50, 20}
};

// Vector para almacenar reservas en memoria
vector<Reserva> reservas;

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();  // Limpiar flags de error
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada hasta nueva línea
}

// Función para buscar un destino por nombre
Destino* buscarDestino(const string& nombre) {
    for(auto& destino : destinos) {  // Recorrer todos los destinos
        if(destino.nombre == nombre) {  // Si encuentra coincidencia
            return &destino;  // Devolver puntero al destino
        }
    }
    return NULL;  // Si no lo encuentra, devolver NULL
}

// Función para mostrar todos los destinos disponibles
void mostrarDestinos() {
    if(destinos.empty()) {  // Verificar si no hay destinos
        cout << "\nNo hay destinos registrados." << endl;
        return;
    }

    // Mostrar encabezado de la tabla
    cout << "\n=== LISTA DE DESTINOS ===" << endl;
    cout << left << setw(20) << "DESTINO" << setw(20) << "COSTO DIA HOTEL" << "COSTO PASAJE" << endl;
    cout << string(60, '-') << endl;

    // Mostrar cada destino con formato
    for(const auto& destino : destinos) {
        cout << left << setw(20) << destino.nombre 
             << setw(20) << fixed << setprecision(2) << destino.costo_dia_hotel 
             << fixed << setprecision(2) << destino.costo_persona_pasaje << endl;
    }
}

// Función para agregar un nuevo destino
void agregarDestino() {
    Destino nuevo;
    cout << "\n=== AGREGAR NUEVO DESTINO ===" << endl;
    
    // Solicitar nombre del destino
    cout << "Nombre del destino: ";
    getline(cin, nuevo.nombre);
    
    // Verificar si el destino ya existe
    if(buscarDestino(nuevo.nombre) != NULL) {
        cout << "Ya existe un destino con ese nombre." << endl;
        return;
    }

    // Solicitar costos
    cout << "Costo por dia de hotel: ";
    cin >> nuevo.costo_dia_hotel;
    limpiarBuffer();

    cout << "Costo por persona de pasaje: ";
    cin >> nuevo.costo_persona_pasaje;
    limpiarBuffer();

    // Agregar el nuevo destino al vector
    destinos.push_back(nuevo);
    cout << "Destino agregado exitosamente!" << endl;
}

// Función para editar un destino existente
void editarDestino() {
    string nombre;
    cout << "\n=== EDITAR DESTINO ===" << endl;
    cout << "Nombre del destino a editar: ";
    getline(cin, nombre);

    // Buscar el destino
    Destino* destino = buscarDestino(nombre);
    if(destino == NULL) {
        cout << "No se encontro el destino." << endl;
        return;
    }

    // Editar nombre (si se proporciona)
    cout << "Nuevo nombre (" << destino->nombre << "): ";
    string nuevoNombre;
    getline(cin, nuevoNombre);
    if(!nuevoNombre.empty()) {
        if(buscarDestino(nuevoNombre) == NULL) {
            destino->nombre = nuevoNombre;
        } else {
            cout << "Error: Ya existe un destino con ese nombre." << endl;
        }
    }

    // Editar costo de hotel (si se proporciona)
    cout << "Nuevo costo por dia de hotel (" << destino->costo_dia_hotel << "): ";
    string input;
    getline(cin, input);
    if(!input.empty()) {
        destino->costo_dia_hotel = stod(input);
    }

    // Editar costo de pasaje (si se proporciona)
    cout << "Nuevo costo por persona de pasaje (" << destino->costo_persona_pasaje << "): ";
    getline(cin, input);
    if(!input.empty()) {
        destino->costo_persona_pasaje = stod(input);
    }

    cout << "Destino actualizado exitosamente!" << endl;
}

// Función para eliminar un destino
void eliminarDestino() {
    string nombre;
    cout << "\n=== ELIMINAR DESTINO ===" << endl;
    cout << "Nombre del destino a eliminar: ";
    getline(cin, nombre);

    // Buscar y eliminar el destino
    auto it = remove_if(destinos.begin(), destinos.end(), 
        [&nombre](const Destino& d) { return d.nombre == nombre; });

    if(it != destinos.end()) {
        destinos.erase(it, destinos.end());
        cout << "Destino eliminado exitosamente" << endl;
    } else {
        cout << "Error: No se encontro el destino." << endl;
    }
}

// Función para guardar una reserva en archivo y memoria
void guardarReserva(const Reserva& reserva) {
    // Guardar en memoria
    reservas.push_back(reserva);
    
    // Guardar en archivo
    ofstream archivo("Reservas.txt", ios::app);  // Abrir en modo append
    if(archivo.is_open()) {
        // Escribir todos los datos de la reserva
        archivo << "Destino: " << reserva.destino << "\n"
                << "Dias: " << reserva.dias << "\n"
                << "Adultos: " << reserva.adultos << "\n"
                << "Niños: " << reserva.ninos << "\n"
                << "Adultos mayores: " << reserva.adultos_mayores << "\n"
                << "Total: $" << fixed << setprecision(2) << reserva.total << "\n"
                << "----------------------------------\n";
        archivo.close();
        cout << "Reserva guardada exitosamente en Reservas.txt" << endl;
    } else {
        cout << "Error al guardar la reserva en el archivo." << endl;
    }
}

// Función para mostrar todas las reservas agendadas
void verReservas() {
    if(reservas.empty()) {
        cout << "\nNo hay reservas agendadas." << endl;
        return;
    }

    cout << "\n=== RESERVAS AGENDADAS ===" << endl;
    // Mostrar cada reserva con formato
    for(const auto& reserva : reservas) {
        cout << "Destino: " << reserva.destino << "\n"
             << "Dias: " << reserva.dias << "\n"
             << "Adultos: " << reserva.adultos << "\n"
             << "Niños: " << reserva.ninos << "\n"
             << "Adultos mayores: " << reserva.adultos_mayores << "\n"
             << "Total: $" << fixed << setprecision(2) << reserva.total << "\n"
             << "----------------------------------\n";
    }
}

// Función para cargar reservas desde archivo al iniciar el programa
void cargarReservas() {
    ifstream archivo("Reservas.txt");
    if(archivo.is_open()) {
        reservas.clear();  // Limpiar reservas existentes
        string linea;
        Reserva temp;
        // Leer línea por línea y parsear los datos
        while(getline(archivo, linea)) {
            if(linea.find("Destino: ") != string::npos) {
                temp.destino = linea.substr(9);
            } else if(linea.find("Dias: ") != string::npos) {
                temp.dias = stoi(linea.substr(6));
            } else if(linea.find("Adultos: ") != string::npos) {
                temp.adultos = stoi(linea.substr(9));
            } else if(linea.find("Niños: ") != string::npos) {
                temp.ninos = stoi(linea.substr(7));
            } else if(linea.find("Adultos mayores: ") != string::npos) {
                temp.adultos_mayores = stoi(linea.substr(17));
            } else if(linea.find("Total: $") != string::npos) {
                temp.total = stod(linea.substr(8));
                reservas.push_back(temp);  // Agregar reserva completa al vector
            }
        }
        archivo.close();
    }
}

// Menú para gestionar destinos (CRUD)
void gestionarDestinos() {
    int opcion;
    do {
        cout << "\n=== GESTION DE DESTINOS ===" << endl;
        cout << "1. Mostrar destinos" << endl;
        cout << "2. Agregar destino" << endl;
        cout << "3. Editar destino" << endl;
        cout << "4. Eliminar destino" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        limpiarBuffer();

        switch(opcion) {
            case 1:
                mostrarDestinos();
                break;
            case 2:
                agregarDestino();
                break;
            case 3:
                editarDestino();
                break;
            case 4:
                eliminarDestino();
                break;
            case 5:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while(opcion != 5);
}

// Función para calcular el costo de un viaje y opcionalmente guardarlo como reserva
void calcularCostoViaje() {
    if(destinos.empty()) {
        cout << "\nNo hay destinos registrados para calcular." << endl;
        return;
    }

    mostrarDestinos();
    string nombreDestino;
    cout << "\n=== CALCULAR COSTO DE VIAJE ===" << endl;
    cout << "Ingrese el nombre del destino: ";
    getline(cin, nombreDestino);

    // Buscar el destino seleccionado
    Destino* destino = buscarDestino(nombreDestino);
    if(destino == NULL) {
        cout << "Error: No se encontro el destino." << endl;
        return;
    }

    int totalDias, adultos, ninos, adultos_mayores;
    
    // Validar días de hospedaje (1-31)
    do {
        cout << "Ingrese la cantidad de dias de hospedaje (1-31): ";
        cin >> totalDias;
        limpiarBuffer();
    } while(totalDias < 1 || totalDias > 31);

    // Validar cantidad de adultos (1-5)
    do {
        cout << "Ingrese cantidad de adultos (1-5): ";
        cin >> adultos;
        limpiarBuffer();
    } while(adultos < 1 || adultos > 5);

    // Validar cantidad de niños (0-4)
    do {
        cout << "Ingrese cantidad de niños (0-4): ";
        cin >> ninos;
        limpiarBuffer();
    } while(ninos < 0 || ninos > 4);

    // Validar cantidad de adultos mayores (0-5)
    do {
        cout << "Ingrese cantidad de adultos mayores (0-5): ";
        cin >> adultos_mayores;
        limpiarBuffer();
    } while(adultos_mayores < 0 || adultos_mayores > 5);

    // Verificar total de personas (1-5)
    int totalPersonas = adultos + ninos + adultos_mayores;
    if(totalPersonas < 1 || totalPersonas > 5) {
        cout << "Error: El total de personas debe estar entre 1 y 5." << endl;
        return;
    }

    // Calcular costos
    double costoHospedaje = destino->costo_dia_hotel * totalDias * totalPersonas;
    
    // Calcular costos de pasajes con descuentos
    double costoPasajeAdultos = adultos * destino->costo_persona_pasaje;
    double costoPasajeNinos = ninos * destino->costo_persona_pasaje * 0.5;  // 50% descuento
    double costoPasajeAdultosMayores = adultos_mayores * destino->costo_persona_pasaje * 0.9;  // 10% descuento
    double costoPasajeTotal = costoPasajeAdultos + costoPasajeNinos + costoPasajeAdultosMayores;

    // Calcular total a pagar
    double totalPagar = costoHospedaje + costoPasajeTotal;

    // Mostrar detalle de costos
    cout << "\n=== DETALLE DE COSTOS ===" << endl;
    cout << "Destino: " << destino->nombre << endl;
    cout << "Total personas: " << totalPersonas << " (Adultos: " << adultos 
         << ", Niños: " << ninos << ", Adultos mayores: " << adultos_mayores << ")" << endl;
    
    cout << fixed << setprecision(2);  // Formato de 2 decimales
    
    cout << "Costo de hospedaje (" << totalDias << " dias): $" << costoHospedaje << endl;
    
    // Mostrar desglose de pasajes
    cout << "Costo de pasajes:" << endl;
    cout << "  Adultos (" << adultos << "): $" << costoPasajeAdultos << endl;
    if(ninos > 0)
        cout << "  Niños (" << ninos << ") con 50% desc: $" << costoPasajeNinos << endl;
    if(adultos_mayores > 0)
        cout << "  Adultos mayores (" << adultos_mayores << ") con 10% desc: $" << costoPasajeAdultosMayores << endl;
    cout << "  TOTAL PASAJES: $" << costoPasajeTotal << endl;

    cout << "\nTOTAL A PAGAR: $" << totalPagar << endl;

    // Preguntar si desea guardar la reserva
    char opcion;
    cout << "\n¿Desea guardar esta reserva? (S/N): ";
    cin >> opcion;
    limpiarBuffer();

    if(toupper(opcion) == 'S') {
        // Crear y guardar reserva
        Reserva nuevaReserva = {
            destino->nombre,
            totalDias,
            adultos,
            ninos,
            adultos_mayores,
            totalPagar
        };

        guardarReserva(nuevaReserva);
    }
}

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    cout << "\n=== SISTEMA DE VIAJES ===" << endl;
    cout << "1. Gestionar destinos" << endl;
    cout << "2. Calcular costo de viaje" << endl;
    cout << "3. Ver reservas agendadas" << endl;
    cout << "4. Salir" << endl;
}

// Función principal
int main() {
    // Cargar reservas existentes al iniciar
    cargarReservas();

    int opcion;
    do {
        mostrarMenuPrincipal();
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        limpiarBuffer();

        switch(opcion) {
            case 1:
                gestionarDestinos();  // CRUD de destinos
                break;
            case 2:
                calcularCostoViaje();  // Cálculo y reservas
                break;
            case 3:
                verReservas();  // Mostrar reservas
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while(opcion != 4);

    return 0;
}