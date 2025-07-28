#include <iostream>  // Biblioteca para entrada/salida est�ndar
#include <vector>    // Biblioteca para usar contenedores vector
#include <string>    // Biblioteca para manejo de strings
#include <iomanip>   // Biblioteca para formateo de salida (setprecision, setw)
#include <limits>    // Biblioteca para l�mites num�ricos (numeric_limits)
#include <algorithm> // Biblioteca para algoritmos (remove_if)
#include <cctype>    // Biblioteca para funciones de caracteres (toupper)
#include <fstream>   // Biblioteca para manejo de archivos
#include <locale.h>		  // Para caracteres especiales 

using namespace std; // Usar el espacio de nombres est�ndar

//	Login de acxeso al contenido del crud 
bool login() {
    string usuarioCorrecto = "admin";
    string claveCorrecta = "1234";
    string usuarioIngresado, claveIngresada;
    int intentos = 3;
    cout << "INICIO DE SESI�N\n";

    while (intentos > 0) {
        cout << "\nUsuario: ";
        getline(cin, usuarioIngresado);
        cout << "Contrase�a: ";
        getline(cin, claveIngresada);

        if (usuarioIngresado == usuarioCorrecto && claveIngresada == claveCorrecta) {
            cout << "\nBienvenido.....Acceso concedido\n";
            return true;
        } else {
        	intentos -= 1;
        	if (intentos >= 1){
            	cout << "\nCredenciales incorrectas. Intentos restantes: " << intentos << "\n";				
			}
        }
    }

    cout <<"\nHas excedido el n�mero de intentos, accseso bloqueado";
    cout<<"\nSaliendo del sistema....";
    return false;
}
// Estructura para almacenar informaci�n de un destino tur�stico
struct Destino {
    string nombre;               // Nombre del destino
    double costo_dia_hotel;      // Costo por d�a de hotel
    double costo_persona_pasaje; // Costo de pasaje por persona
};

// Estructura para almacenar informaci�n de una reserva
struct Reserva {
	int numero_reserva;     //N�mero de reserva
	string cedula;          //cedula del cliente
	string nombre_cliente;  // Nombre del cliente
    string destino;         // Nombre del destino reservado
    int dias;               // Cantidad de d�as de estad�a
    int adultos;            // N�mero de adultos
    int ninos;              // N�mero de ni�os
    int adultos_mayores;    // N�mero de adultos mayores
    double total;           // Total a pagar por la reserva
};


// Vector global que almacena los destinos disponibles
vector<Destino> destinos = {
    {"Galapagos", 45, 80}, // Ejemplo de destino con costos
    {"Manta", 60, 120},
    {"Cuenca", 55, 90},
    {"Ibarra", 50, 100}
};

// Vector global que almacena las reservas realizadas
vector<Reserva> reservas;

// Funci�n para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear(); // Limpiar flags de error
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar hasta salto de l�nea
}

// Funci�n para buscar un destino por nombre
Destino* buscarDestino(const string& nombre) {
    for(auto& destino : destinos) { // Iterar sobre todos los destinos
        if(destino.nombre == nombre) { // Si encuentra coincidencia
            return &destino; // Retornar puntero al destino
        }
    }
    return nullptr; // Retornar NULL si no lo encuentra
}

// Funci�n para mostrar la lista de destinos disponibles
void mostrarDestinos() {
    if(destinos.empty()) { // Verificar si no hay destinos
        cout << "\nNo hay destinos registrados." << endl;
        return;
    }
    
    // Mostrar encabezado de la tabla
    cout << "\n=== LISTA DE DESTINOS ===" << endl;
    cout << left << setw(20) << "DESTINO" << setw(20) << "COSTO DIA HOTEL" << "COSTO PASAJE" << endl;
    cout << string(60, '-') << endl; // L�nea separadora
    
    //Para que valores num�ricos se vean con 2 decimales
    cout << fixed << setprecision(2);
    // Mostrar cada destino con su informaci�n
    for(const auto& destino : destinos) {
        cout << left << setw(20) << destino.nombre 
             << setw(20) << destino.costo_dia_hotel 
             << destino.costo_persona_pasaje << endl;
    }
}

//Funcion para validar el nombre del destino y del cliente
bool validarNombre_ClienteDestino(const string& nombre) {
    // Si el nombre est� vac�o, no es v�lido
    if (nombre.empty()) {
        return false;
    }

    // Revisar letra por letra
    for (char letra : nombre) {
        // Si no es letra y no es espacio, no es v�lido
        if (!(isalpha(letra) || letra == ' ')) {
            return false;
        }
    }

    return true; // Todo est� bien
}

// Funci�n para validar el costo por dia del hotel y del pasaje
// Pide al usuario un n�mero decimal y valida que no sea negativo
double validarCostos(string mensaje, double minimo = 0.0) {
    double valor;

    while (true) {
        cout << mensaje;     // Mostrar el mensaje al usuario
        cin >> valor;        // Leer el n�mero

        // Verificar si se ingres� algo incorrecto (letras, s�mbolos o n�mero menor al m�nimo)
        if (cin.fail() || valor < minimo) {
            cout << "Entrada inv�lida. Solo se permiten n�meros positivos. Intente otra vez." << endl;
            limpiarBuffer(); // Limpiar errores de entrada
        } else {
            limpiarBuffer(); // Limpiar cualquier car�cter sobrante
            return valor;    // Devolver el n�mero v�lido
        }
    }
}

// Funci�n para agregar un nuevo destino
void agregarDestino() {
    Destino nuevo; // Crear nuevo objeto Destino
    cout << "\n=== AGREGAR NUEVO DESTINO ===" << endl;
    
    // Solicitar nombre del destino
    cout << "Nombre del destino: ";
    getline(cin, nuevo.nombre);
        
    // Verificar si el nombre de destino es valido
    if(!validarNombre_ClienteDestino(nuevo.nombre)) {
        cout << "Nombre invalido. Debe contener al menos una letra." << endl;
        return;
    }
    //Verificar si el nombre de destino ya existe
	if (buscarDestino(nuevo.nombre) != nullptr) {
	    cout << "Ya existe un destino con ese nombre." << endl;
	    return;
	}
	
	// Pedir costo por d�a de hotel, solo aceptar n�meros
	
    nuevo.costo_dia_hotel = validarCostos("Costo por dia de hotel: ");
	
	// Pedir costo por persona de pasaje, solo aceptar n�meros
	nuevo.costo_persona_pasaje = validarCostos("Costo por persona de pasaje: ");
	
    // Agregar el nuevo destino al vector
    destinos.push_back(nuevo);
    cout << "Destino agregado exitosamente." << endl;
}

// Funci�n para editar un destino existente
void editarDestino() {
    string nombre;
    cout << "\n=== EDITAR DESTINO ===" << endl;
    cout << "Nombre del destino a editar: ";
    getline(cin, nombre);
    // Buscar el destino a editar
    Destino* destino = buscarDestino(nombre);
    if(destino == nullptr) {
        cout << "No se encontro el destino." << endl;
        return;
    }
    string nuevoNombre;
	while (true) {
	    cout << "Nuevo nombre (" << destino->nombre << "): ";
	    getline(cin, nuevoNombre);
	    // Si el usuario no quiere cambiar el nombre (deja vacio), mantener el actual y salir
	    if (nuevoNombre.empty()) {
	        nuevoNombre = destino->nombre;
	        break;
	    }
	    // Validar el nombre
	    if (!validarNombre_ClienteDestino(nuevoNombre)) {
	        cout << "Nombre inv�lido. Debe contener solo letras y espacios." << endl;
	    }
	    else if (nuevoNombre == destino->nombre) {
	        cout << "Error: El nombre ingresado es igual al actual. Debe ingresar un nombre diferente." << endl;
	    }
	    else if (buscarDestino(nuevoNombre) != nullptr) {
	        cout << "Error: Ya existe un destino con ese nombre." << endl;
	    }
	    else {
	        break; // Nombre v�lido y diferente, salir del ciclo
	    }
	}
	
	destino->nombre = nuevoNombre; 	// Asignar el nombre validado (que puede ser el actual si no cambio)
    string entrada;
    // Pide costo del hotel 
    cout << "Costo de hospedaje por dia actual (" << destino->costo_dia_hotel << ").\n";
	cout << "Presione Enter para mantenerlo, o escriba un nuevo valor: ";
	
	getline(cin, entrada);
	
    if (!entrada.empty()) {
        try {
            double nuevoCosto = stod(entrada);
            if (nuevoCosto >= 0)
                destino->costo_dia_hotel = nuevoCosto;
            else
                cout << "El costo debe ser un valor positivo. Se mantuvo el valor anterior." << endl;
        } catch (...) {
            cout << "Entrada invalida. Se mantuvo el valor anterior." << endl;
        }
    }
    
	// Solicitar costo de pasaje
    cout << "Costo de pasaje por persona actual (" << destino->costo_persona_pasaje << ")\n";
	cout << "Presione Enter para mantenerlo o escriba el nuevo valor: "; 
    getline(cin, entrada);
    if (!entrada.empty()) {
        try {
            double nuevoPasaje = stod(entrada);
            if (nuevoPasaje >= 0)
                destino->costo_persona_pasaje = nuevoPasaje;
            else
                cout << "El costo debe ser un valor positivo. Se mantuvo el valor anterior." << endl;
        } catch (...) {
            cout << "Entrada invalida. Se mantuvo el valor anterior." << endl;
        }
    }
        
    cout << "Destino actualizado exitosamente!" << endl;
}

// Funci�n para eliminar un destino
void eliminarDestino() {
    string nombre;
    cout << "\n=== ELIMINAR DESTINO ===" << endl;
    cout << "Nombre del destino a eliminar: ";
    getline(cin, nombre);     
    // Buscar y eliminar el destino usando algoritmo remove_if
    auto it = find_if(destinos.begin(), destinos.end(), 
	[&nombre](const Destino& d) { return d.nombre == nombre; });

    if(it != destinos.end()) {
        destinos.erase(it); // Eliminar del vector
        cout << "Destino eliminado exitosamente" << endl;
    } else {
        cout << "Error: No se encontro el destino." << endl;
    }
}

int contador_reservas = 1; // Lleva el n�mero de reserva

// Funci�n para guardar una reserva en memoria y archivo
void guardarReserva(const Reserva& reserva) {
    // Guardar en memoria
    reservas.push_back(reserva);
    
    // Guardar en archivo
    ofstream archivo("Reservas.txt", ios::app); // Abrir en modo append
    if(archivo.is_open()) {
        // Escribir todos los datos de la reserva
        archivo <<"Reserva: #"<<reserva.numero_reserva<<"\n"
		        <<"Cedula: " << reserva.cedula << "\n"
                <<"Nombre del cliente: "<<reserva.nombre_cliente<<"\n"
		        <<"Destino: " << reserva.destino << "\n"
                << "Dias: " << reserva.dias << "\n"
                << "Adultos: " << reserva.adultos << "\n"
                << "Ninos: " << reserva.ninos << "\n"
                << "Adultos mayores: " << reserva.adultos_mayores << "\n"
                << "Total: $" << fixed << setprecision(2) << reserva.total << "\n"
                << "----------------------------------\n";
        archivo.close();
        cout << "Reserva guardada exitosamente en Reservas.txt" << endl;
    } else {
        cout << "Error al guardar la reserva en el archivo." << endl;
    }
}

// Funci�n para mostrar las reservas agendadas
void verReservas() {
    if(reservas.empty()) { // Verificar si no hay reservas
        cout << "\nNo hay reservas agendadas." << endl;
        return;
    }

    cout << "\n=== RESERVAS AGENDADAS ===\n" << endl;
    cout << fixed << setprecision(2); // Aplicar formato de decimales una sola vez
    // Mostrar cada reserva con su informaci�n
    for(const auto& reserva : reservas) {
    	cout << string(40, '=') << "\n"; // L�nea superior para separar reservas
        cout <<"Reserva: #"<<reserva.numero_reserva<<"\n"
		     <<"Cedula: " << reserva.cedula << "\n"
             <<"Nombre del cliente: "<<reserva.nombre_cliente<<"\n"
		     <<"Destino: " << reserva.destino << "\n"
             << "Dias: " << reserva.dias << "\n"
             << "Adultos: " << reserva.adultos << "\n"
             << "Ninos: " << reserva.ninos << "\n"
             << "Adultos mayores: " << reserva.adultos_mayores << "\n"
             << "Total: $" << fixed << setprecision(2) << reserva.total << "\n"
             << string(40, '-') << "\n";
    }
}

void cargarReservas() {
    ifstream archivo("Reservas.txt"); // Abrir archivo para lectura
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de reservas." << endl;
        return;
    }

    reservas.clear(); // Limpiar reservas existentes
    string linea;
    Reserva temp;
    bool leyendoReserva = false;

    while (getline(archivo, linea)) {
        if (linea.find("Reserva: #") == 0) {
        	// Guardar reserva anterior si era valida  
			if (leyendoReserva) {
				reservas.push_back(temp);
			}
			
            temp = Reserva(); // Reiniciar datos
            leyendoReserva = true;

            try {
                temp.numero_reserva = stoi(linea.substr(11));
                if (temp.numero_reserva >= contador_reservas)
                    contador_reservas = temp.numero_reserva + 1;
            } catch (...) {
                cout << "Numero de reserva invalido. Se ignorara.\n";
                leyendoReserva = false; // Ignorar esta reserva
            }
			 
        } else if (leyendoReserva) {
        	try{
				if (linea.find("Cedula: ") == 0)
                temp.cedula = linea.substr(8);
				else if (linea.find("Nombre del cliente: ") == 0) 
					temp.nombre_cliente = linea.substr(21);
				else if (linea.find("Destino: ") == 0) 
					temp.destino = linea.substr(9);
				else if (linea.find("Dias: ") == 0) 
					temp.dias = stoi(linea.substr(6));
				else if (linea.find("Adultos: ") == 0) 
					temp.adultos = stoi(linea.substr(9));
				else if (linea.find("Ni�os: ") == 0) 
					temp.ninos = stoi(linea.substr(7));
				else if (linea.find("Adultos mayores: ") == 0) 
					temp.adultos_mayores = stoi(linea.substr(17));
				else if (linea.find("Total: $") == 0) 
					temp.total = stod(linea.substr(8));
			}catch(...){
				cout << "Error al leer una linea. Se ignorara esta reserva.\n";
				leyendoReserva=false;
			}
		}
	}
	
    // Guardar �ltima reserva si era valida
    if (leyendoReserva && !temp.cedula.empty() && temp.total > 0){
		reservas.push_back(temp);
	}
	
    archivo.close();
}

// Men� para gestionar destinos (CRUD)
void gestionarDestinos() {
    int opcion;
    do {
        // Mostrar opciones del men�
        cout << "\n=== GESTION DE DESTINOS ===" << endl;
        cout << "1. Mostrar destinos" << endl;
        cout << "2. Agregar destino" << endl;
        cout << "3. Editar destino" << endl;
        cout << "4. Eliminar destino" << endl;
        cout << "5. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        limpiarBuffer();

        // Manejar opci�n seleccionada
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
    } while(opcion != 5); // Repetir hasta que elija volver
}

//Funcion para validar si la ya cedula esta registrada
bool cedulaYaRegistrada(string cedula) {
    for (const auto& reserva : reservas) {
        if (reserva.cedula == cedula) {
            return true;
        }
    }
    return false;
}

//Validar cedula del cliente 

bool cedulaValida(string cedula) { // Inicia la funci�n que recibe un string llamado 'cedula' y devuelve true o false
    // Validar longitud
    if (cedula.length() != 10) {   // Verifica si la c�dula no tiene exactamente 10 caracteres
        return false;              //Si no tiene 10 caracteres, devuelve falso (no es v�lida)
    }

    // Validar que sean solo n�meros
    
    for (int i = 0; i < 10; i++) {  //Recorre cada uno de los 10 caracteres de la c�dula (del 0 al 9)
        if (cedula[i] < '0' || cedula[i] > '9') {  //Verifica si el car�cter actual no es un n�mero del 0 al 9
            return false;                          // Si encuentra una letra o s�mbolo, devuelve falso (no es v�lida)
        }
    }

    // Validar provincia
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');  //Convierte el primer car�cter en n�mero y lo multiplica por 10

    if (!(( provincia >= 1 && provincia <= 24) || provincia == 30)) { // Verifica si el c�digo de provincia est� entre 1 y 24 (provincias del Ecuador)o si es 30 (que representa a extranjeros)
        return false;  //Si no es ninguno de esos valores, devuelve falso (no es v�lida)
    }

    return true; // Si pasa todas las validaciones, devuelve verdadero (la c�dula es v�lida)
}

// Funci�n para validar la cantidad de dias de hospedaje, personas(adultos,ni�os,adultos mayores)
int validarCantidades(string mensaje, int minimo, int maximo) {
    int numero;

    while (true) {
        cout << mensaje;
        cin >> numero;

        if (cin.fail()) { // Si el usuario escribe letras o s�mbolos
            cout << "Eso no es un numero. Intenta otra vez.\n";
            limpiarBuffer();
        }
        else if (numero < minimo || numero > maximo) {
            cout << "El numero debe estar entre " << minimo << " y " << maximo << ".\n";
        }
        else {
            limpiarBuffer();
            return numero; // N�mero v�lido
        }
    }
}
// Funci�n principal para calcular costos de viaje
void calcularCostoViaje() {
    if(destinos.empty()) { // Verificar si hay destinos disponibles
        cout << "\nNo hay destinos registrados para calcular." << endl;
        return;
    }
    
	mostrarDestinos(); // Mostrar destinos disponibles
	cout << "\n=== CALCULAR COSTO DE VIAJE ===" << endl;
    string cedula;
    while (true) {
        cout << "Ingrese la cedula del cliente: ";
        getline(cin, cedula);

        if (!cedulaValida(cedula)) {
        	cout << "Cedula invalida. Debe tener 10 digitos validos." << endl;
        } else if (cedulaYaRegistrada(cedula)){
            cout << "Esta cedula ya tiene una reserva registrada" << endl;
        }else{
			break; // C�dula v�lida y no repetida
		}
    }
    
    string nombre_cliente;
    while(true){
    	cout<<"Ingrese el nombre del cliente: ";
    	getline(cin,nombre_cliente);
    	if(validarNombre_ClienteDestino(nombre_cliente)){
			break;
		}else{
			cout<<"Nombre invalido. Solo se permiten letras y espacios"<<endl;
		}
	}
    
    string nombreDestino;
	Destino* destino = nullptr;
	
	while (true) {
		cout << "Ingrese el nombre del destino: ";
		getline(cin, nombreDestino);
	    destino = buscarDestino(nombreDestino);
		if (destino == nullptr) {
			cout << "Error: No se encontro el destino. Revise la ortografia o consulte la lista mostrada arriba.\n";
		} else {
			break;}
	}
	 
    // Solicitar cantidad de d�as con la funcion validarCantidades()
    int totalDias = validarCantidades("Ingrese la cantidad de dias de estadia (1-31): ", 1, 31);
    
	//Declaracion de variables
	int adultos, ninos, adultos_mayores,totalPersonas=0;
	// Solicitar las cantidades de personas con la funcion validarCantidades()
	do {
		adultos = validarCantidades("Ingrese cantidad de adultos (0-5): ", 0, 5);
		ninos = validarCantidades("Ingrese cantidad de ni�os (0-5): ", 0, 5);
		adultos_mayores = validarCantidades("Ingrese cantidad de adultos mayores (0-5): ", 0, 5);
		
		totalPersonas = adultos + ninos + adultos_mayores;
	    if (totalPersonas < 1 || totalPersonas > 15) {
	        cout << "Error: El total de personas debe estar entre 1 y 15. Intente de nuevo.\n";
	    }
	} while (totalPersonas < 1 || totalPersonas > 15);
	
    // Calcular costos
    double costoHospedaje = destino->costo_dia_hotel * totalDias * totalPersonas;
    
    // C�lculos con descuentos:
    double costoPasajeAdultos = adultos * destino->costo_persona_pasaje;
    double costoPasajeNinos = ninos * destino->costo_persona_pasaje * 0.5; // 50% descuento
    double costoPasajeAdultosMayores = adultos_mayores * destino->costo_persona_pasaje * 0.9; // 10% descuento
    double costoPasajeTotal = costoPasajeAdultos + costoPasajeNinos + costoPasajeAdultosMayores;

    double totalPagar = costoHospedaje + costoPasajeTotal;

    // Mostrar detalle de costos
    cout << "\n=== DETALLE DE COSTOS ===" << endl;
    cout<< "Cedula del cliente: "<<cedula<<endl;
    cout << "Destino: " << destino->nombre << endl;
    cout << "Total personas: " << totalPersonas << " (Adultos: " << adultos 
         << ", Ni�os: " << ninos << ", Adultos mayores: " << adultos_mayores << ")" << endl;
    
    cout << fixed << setprecision(2); // Formatear decimales
    
    cout << "Costo de hospedaje (" << totalDias << " dias): $" << costoHospedaje << endl;
    
    // Mostrar desglose de pasajes
    cout << "Costo de pasajes:" << endl;
    cout << "  Adultos (" << adultos << "): $" << costoPasajeAdultos << endl;
    if(ninos > 0)
        cout << "  Ni�os (" << ninos << ") con 50% desc: $" << costoPasajeNinos << endl;
    if(adultos_mayores > 0)
        cout << "  Adultos mayores (" << adultos_mayores << ") con 10% desc: $" << costoPasajeAdultosMayores << endl;
    cout << "  TOTAL PASAJES: $" << costoPasajeTotal << endl;

    cout << "\nTOTAL A PAGAR: $" << totalPagar << endl;

    // Preguntar si desea guardar la reserva
    char opcion;
    cout << "\n�Desea guardar esta reserva? (S/N): ";
    cin >> opcion;
    limpiarBuffer();

    if(toupper(opcion) == 'S') {
        // Crear y guardar reserva
        Reserva nuevaReserva = {
        	contador_reservas++,
        	cedula,
        	nombre_cliente,
            destino->nombre,
            totalDias,
            adultos,
            ninos,
            adultos_mayores,
            totalPagar
        };

        guardarReserva(nuevaReserva);
        // Muestra el nmero de reserva confirmado
        cout << "\nReserva guardada exitosamente. Numero de reserva: #" << nuevaReserva.numero_reserva << endl;
		
    }
}

// Funci�n para mostrar el men� principal
void mostrarMenuPrincipal() {
    cout << "\n=== SISTEMA DE VIAJES ===" << endl;
    cout << "1. Gestionar destinos" << endl;
    cout << "2. Agendar reservas" << endl;
    cout << "3. Ver reservas agendadas" << endl;
    cout << "4. Salir" << endl;
}

void Sistema (){

    // Cargar reservas existentes al iniciar
    cargarReservas();

    int opcion;
    do {
        mostrarMenuPrincipal(); // Mostrar men�
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        limpiarBuffer();

        // Manejar opci�n seleccionada
        switch(opcion) {
            case 1:
                gestionarDestinos();
                break;
            case 2:
                calcularCostoViaje();
                break;
            case 3:
                verReservas();
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while(opcion != 4); // Repetir hasta que elija salir	
}

// Funci�n principal del programa
int main() {
    setlocale(LC_ALL, "Spanish");  // Soporte para caracteres en espa�ol

    if (login()) {
        Sistema();  // Solo entra al men� si el login fue exitoso
    }
    
}
