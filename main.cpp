#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. MODELO DE DATOS
// ==========================================
struct Proyecto {
    string nombre;
    string estado; 
    int erroresCriticos;
    int diasRetraso;
    bool revisionUrgente; 
};

struct Nodo {
    Proyecto dato;
    Nodo* siguiente;
};

// ==========================================
// 2. ESTRUCTURAS DE DATOS: COLA Y LISTA
// ==========================================
struct Cola {
    Nodo* frente = nullptr;
    Nodo* final = nullptr;
};

struct Lista {
    Nodo* cabeza = nullptr;
};

// --- Operaciones de la Cola ---
void encolar(Cola& c, Proyecto p) {
    Nodo* nuevo = new Nodo{p, nullptr};
    if (c.frente == nullptr) c.frente = nuevo;
    else c.final->siguiente = nuevo;
    c.final = nuevo;
}

Proyecto desencolar(Cola& c) {
    if (c.frente == nullptr) return {"", "", 0, 0, false};
    Nodo* aux = c.frente;
    Proyecto p = aux->dato;
    c.frente = c.frente->siguiente;
    if (c.frente == nullptr) c.final = nullptr;
    delete aux;
    return p;
}

// --- Operaciones de la Lista (Conjuntos) ---
void insertarEnLista(Lista& l, Proyecto p) {
    Nodo* nuevo = new Nodo{p, nullptr};
    if (l.cabeza == nullptr) {
        l.cabeza = nuevo;
    } else {
        Nodo* aux = l.cabeza;
        while (aux->siguiente != nullptr) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

void imprimirLista(Lista l, string nombreConjunto) {
    cout << "\n--- CONJUNTO " << nombreConjunto << " ---\n";
    if (l.cabeza == nullptr) {
        cout << "  (Vacio)\n";
        return;
    }
    Nodo* aux = l.cabeza;
    while (aux != nullptr) {
        cout << "  -> " << aux->dato.nombre 
             << " | Estado: " << aux->dato.estado 
             << " | Retraso: " << aux->dato.diasRetraso << " dias"
             << " | Errores: " << aux->dato.erroresCriticos << "\n";
        aux = aux->siguiente;
    }
}

// ==========================================
// 3. FUNCIONES DE LÓGICA PROPOSICIONAL
// ==========================================
bool evaluarP(Proyecto p) { return p.diasRetraso > 10; } // P: Mas de 10 dias de retraso
bool evaluarQ(Proyecto p) { return p.erroresCriticos > 3; } // Q: Mas de 3 errores
bool evaluarR(Proyecto p) { return p.revisionUrgente; } // R: Revision urgente

// ==========================================
// PROGRAMA PRINCIPAL (MENÚ INTERACTIVO)
// ==========================================
int main() {
    Cola colaRecepcion;
    Lista A; // Activos
    Lista B; // Con Retraso
    Lista C; // Completados

    int opcion;

    do {
        cout << "\n========================================\n";
        cout << "  SISTEMA DE DIAGNOSTICO - SOFTLOGIC SA\n";
        cout << "========================================\n";
        cout << "1. Ingresar nuevo proyecto a la Cola\n";
        cout << "2. Procesar Cola (Motor de Inferencia)\n";
        cout << "3. Ver Conjunto A (Proyectos Activos)\n";
        cout << "4. Ver Conjunto B (Proyectos con Retraso > 10)\n";
        cout << "5. Ver Conjunto C (Proyectos Completados)\n";
        cout << "6. Salir\n";
        cout << "========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Proyecto p;
            cout << "\nNombre del proyecto (sin espacios): ";
            cin >> p.nombre;
            cout << "Estado (Activo/Completado/Revision): ";
            cin >> p.estado;
            cout << "Dias de retraso: ";
            cin >> p.diasRetraso;
            cout << "Numero de errores criticos: ";
            cin >> p.erroresCriticos;
            int rev;
            cout << "Revision urgente? (1 = Si, 0 = No): ";
            cin >> rev;
            p.revisionUrgente = (rev == 1);

            encolar(colaRecepcion, p);
            cout << "\n[+] Proyecto encolado exitosamente.\n";

        } else if (opcion == 2) {
            if (colaRecepcion.frente == nullptr) {
                cout << "\n[-] La cola esta vacia. No hay proyectos por procesar.\n";
            } else {
                cout << "\nProcesando diagnosticos...\n";
                while (colaRecepcion.frente != nullptr) {
                    Proyecto actual = desencolar(colaRecepcion);
                    cout << "\nEvaluando: " << actual.nombre << "...\n";
                    
                    bool valP = evaluarP(actual);
                    
                    // Clasificacion en conjuntos segun logica
                    if (actual.estado == "Activo") {
                        insertarEnLista(A, actual);
                        cout << "  -> Pertenece a Conjunto A (Activos)\n";
                    } else if (actual.estado == "Completado") {
                        insertarEnLista(C, actual);
                        cout << "  -> Pertenece a Conjunto C (Completados)\n";
                    }

                    if (valP) {
                        insertarEnLista(B, actual);
                        cout << "  -> Pertenece a Conjunto B (Retrasados)\n";
                    }
                }
                cout << "\n[+] Procesamiento finalizado.\n";
            }

        } else if (opcion == 3) {
            imprimirLista(A, "A (Activos)");
        } else if (opcion == 4) {
            imprimirLista(B, "B (Con Retraso > 10 dias)");
        } else if (opcion == 5) {
            imprimirLista(C, "C (Completados)");
        }

    } while (opcion != 6);

    cout << "\nSaliendo del sistema...\n";
    return 0;
}
