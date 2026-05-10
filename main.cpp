#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. MODELO DE DATOS Y NODOS BASE
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
// 2. ESTRUCTURAS DE DATOS
// ==========================================
// --- COLA (FIFO) ---
struct Cola { Nodo* frente = nullptr; Nodo* final = nullptr; };

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

// --- LISTA (CONJUNTOS) ---
struct Lista { Nodo* cabeza = nullptr; };

void insertarEnLista(Lista& l, Proyecto p) {
    Nodo* nuevo = new Nodo{p, nullptr};
    if (l.cabeza == nullptr) l.cabeza = nuevo;
    else {
        Nodo* aux = l.cabeza;
        while (aux->siguiente != nullptr) aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
}

void imprimirLista(Lista l, string nombreConjunto) {
    cout << "\n--- CONJUNTO " << nombreConjunto << " ---\n";
    if (l.cabeza == nullptr) { cout << "  (Vacio)\n"; return; }
    Nodo* aux = l.cabeza;
    while (aux != nullptr) {
        cout << "  -> " << aux->dato.nombre << " | Estado: " << aux->dato.estado << "\n";
        aux = aux->siguiente;
    }
}

// --- PILA (LIFO) - MOTOR DE INFERENCIA ---
struct NodoPila {
    bool valorLogico;
    NodoPila* siguiente;
};

struct Pila { NodoPila* cima = nullptr; };

void apilar(Pila& p, bool v) {
    NodoPila* nuevo = new NodoPila{v, p.cima};
    p.cima = nuevo;
}

bool desapilar(Pila& p) {
    if (p.cima == nullptr) return false;
    NodoPila* aux = p.cima;
    bool v = aux->valorLogico;
    p.cima = p.cima->siguiente;
    delete aux;
    return v;
}

// ==========================================
// 3. LÓGICA PROPOSICIONAL
// ==========================================
bool evaluarP(Proyecto p) { return p.diasRetraso > 10; } 
bool evaluarQ(Proyecto p) { return p.erroresCriticos > 3; } 
bool evaluarR(Proyecto p) { return p.revisionUrgente; } 

// ==========================================
// PROGRAMA PRINCIPAL
// ==========================================
int main() {
    Cola colaRecepcion;
    Lista A; Lista B; Lista C;
    int opcion;

    do {
        cout << "\n========================================\n";
        cout << "  SISTEMA DE DIAGNOSTICO - SOFTLOGIC SA\n";
        cout << "========================================\n";
        cout << "1. Ingresar nuevo proyecto a la Cola\n";
        cout << "2. Procesar Cola (Motor de Inferencia con Pila)\n";
        cout << "3. Ver Conjunto A (Activos)\n";
        cout << "4. Ver Conjunto B (Retraso > 10)\n";
        cout << "5. Ver Conjunto C (Completados)\n";
        cout << "6. Salir\n";
        cout << "========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Proyecto p;
            cout << "Nombre del proyecto: "; cin >> p.nombre;
            cout << "Estado (Activo/Completado/Revision): "; cin >> p.estado;
            cout << "Dias de retraso: "; cin >> p.diasRetraso;
            cout << "Numero de errores criticos: "; cin >> p.erroresCriticos;
            int rev; cout << "Revision urgente? (1=Si, 0=No): "; cin >> rev;
            p.revisionUrgente = (rev == 1);
            encolar(colaRecepcion, p);
            cout << "[+] Proyecto encolado exitosamente.\n";

        } else if (opcion == 2) {
            if (colaRecepcion.frente == nullptr) {
                cout << "[-] La cola esta vacia.\n";
            } else {
                cout << "\n--- EJECUTANDO MOTOR DE INFERENCIA ---\n";
                while (colaRecepcion.frente != nullptr) {
                    Proyecto actual = desencolar(colaRecepcion);
                    cout << "\nEvaluando Proyecto: " << actual.nombre << "\n";
                    
                    bool valP = evaluarP(actual);
                    bool valQ = evaluarQ(actual);
                    bool valR = evaluarR(actual);

                    Pila pilaInferencia;

                    // INFERENCIA 1: Riesgo Alto -> Q AND P
                    apilar(pilaInferencia, valP);
                    apilar(pilaInferencia, valQ);
                    bool op1 = desapilar(pilaInferencia); // Saca valQ
                    bool op2 = desapilar(pilaInferencia); // Saca valP
                    bool riesgoAlto = (op1 && op2);
                    
                    // INFERENCIA 2: Estable -> NOT P AND NOT Q 
                    apilar(pilaInferencia, !valP);
                    apilar(pilaInferencia, !valQ);
                    bool op3 = desapilar(pilaInferencia); // Saca NOT valQ
                    bool op4 = desapilar(pilaInferencia); // Saca NOT valP
                    bool estable = (op3 && op4);

                    // Resultados de la inferencia
                    if (riesgoAlto) cout << "  [!] ALERTA CRITICA: Proyecto en riesgo alto (Q AND P).\n";
                    if (estable) cout << "  [*] ESTADO: Proyecto estable (~P AND ~Q).\n";
                    if (!riesgoAlto && !estable) cout << "  [-] ESTADO: Proyecto en seguimiento regular.\n";

                    // Clasificacion en Conjuntos
                    if (actual.estado == "Activo") insertarEnLista(A, actual);
                    if (actual.estado == "Completado") insertarEnLista(C, actual);
                    if (valP) insertarEnLista(B, actual);
                }
            }
        } else if (opcion == 3) imprimirLista(A, "A (Activos)");
        else if (opcion == 4) imprimirLista(B, "B (Con Retraso > 10 dias)");
        else if (opcion == 5) imprimirLista(C, "C (Completados)");

    } while (opcion != 6);

    return 0;
}
