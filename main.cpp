#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. MODELADO DE DATOS
// ==========================================
struct Proyecto {
    string nombre;
    string estado;
    int erroresCriticos;
    int diasRetraso;
    string prioridad;

};

// ==========================================
// 2. NODO DINÁMICO
// ==========================================
struct Nodo {
    Proyecto dato;
    Nodo* siguiente; // Puntero al siguiente elemento en memoria
};

// ==========================================
// 3. ESTRUCTURA: COLA DE RECEPCIÓN (FIFO)
// ==========================================
struct Cola {
    Nodo* frente = nullptr;
    Nodo* final = nullptr;
};

// Función para ingresar un proyecto a la cola
void encolar(Cola& c, Proyecto p) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = p;
    nuevoNodo->siguiente = nullptr;

    if (c.frente == nullptr) {
        c.frente = nuevoNodo;
    } else {
        c.final->siguiente = nuevoNodo;
    }
    c.final = nuevoNodo;
    
    cout << "-> Proyecto '" << p.nombre << "' ingresado a la cola de diagnostico.\n";
}

// Función para sacar un proyecto de la cola para evaluar 
Proyecto desencolar(Cola& c) {
    if (c.frente == nullptr) {
        cout << "La cola de diagnostico esta vacia.\n";
        return {"", "", 0, 0, ""}; // Retorna un proyecto vacío
    }

    Nodo* aux = c.frente;
    Proyecto p = aux->dato;
    
    c.frente = c.frente->siguiente;
    if (c.frente == nullptr) {
        c.final = nullptr;
    }
    
    delete aux;
    return p;
}

// ==========================================
// PROGRAMA PRINCIPAL
// ==========================================
int main() {
    Cola colaDiagnostico;
    
    cout << "--- SISTEMA DE DIAGNOSTICO LOGICO - SOFTLOGIC S.A. ---\n\n";

    // 1. Simula el ingreso de datos (Luego hay que ponerlo en el Menú interactivo)
    Proyecto p1 = {"Migracion BD", "Activo", 4, 12, "Alta"};
    Proyecto p2 = {"Portal Pagos", "Activo", 1, 5, "Media"};
    Proyecto p3 = {"App Clientes", "Completado", 0, 0, "Baja"};

    // 2. Encola los proyectos en el orden que llegan
    encolar(colaDiagnostico, p1);
    encolar(colaDiagnostico, p2);
    encolar(colaDiagnostico, p3);
    
    cout << "\nIniciando proceso de extraccion...\n";
    
    // 3. Desencola el primero para prepararlo para evaluación lógica
    Proyecto aEvaluar = desencolar(colaDiagnostico);
    cout << "Proyecto extraido para analisis: " << aEvaluar.nombre << " (Errores: " << aEvaluar.erroresCriticos << ")\n";

    return 0;
}
