# Sistema de Diagnóstico Lógico - SoftLogic S.A.

## 📌 Descripción del Proyecto
Este proyecto es una herramienta de gestión de riesgos para proyectos de software desarrollada para la materia de **Modelos Discretos**. El objetivo es aplicar conceptos de **Lógica Proposicional**, **Lógica de Predicados de Primer Orden (LPPO)** y **Teoría de Conjuntos** utilizando estructuras de datos dinámicas en C++.

El sistema evalúa automáticamente el estado de los proyectos basándose en condiciones lógicas de retraso, errores y solicitudes del cliente, clasificándolos en conjuntos específicos para la toma de decisiones.

## 🏗️ Arquitectura Técnica Implementada (Memoria Dinámica)
El sistema gestiona la memoria en tiempo de ejecución mediante nodos y punteros, estructurando el flujo en tres fases:

1. **Cola de Recepción (Queue - FIFO):** Todos los proyectos nuevos ingresan a una cola, garantizando que el procesamiento siga el orden estricto de llegada.
2. **Motor de Inferencia (Stack - LIFO):** Se extraen los proyectos de la cola y sus proposiciones simples ($P$, $Q$, $R$) se evalúan matemáticamente utilizando una **Pila**. Esto permite resolver reglas lógicas compuestas apilando y desapilando los valores booleanos.
3. **Gestor de Conjuntos (Linked Lists):** Tras el diagnóstico, los proyectos se enrutan a Listas Enlazadas independientes:
   * **Conjunto A:** Proyectos Activos.
   * **Conjunto B:** Proyectos con Retraso ($> 10$ días).
   * **Conjunto C:** Proyectos Completados.

## 🧠 Modelo Lógico Base
### Proposiciones Simples
* **P:** El proyecto tiene más de 10 días de retraso.
* **Q:** Se han encontrado más de 3 errores críticos activos.
* **R:** El cliente ha solicitado una revisión urgente.

### Inferencias Lógicas Aplicadas
* **Alerta Crítica:** $Q \land P$
* **Proyecto Estable:** $\neg P \land \neg Q$

---

## 🚀 Estado del Proyecto (Fase 3 Completada)
Actualmente, la infraestructura principal del sistema está funcional en la rama `main`:
* [x] Definición de `struct Proyecto` y Nodos.
* [x] **Cola** de recepción programada y funcional.
* [x] **Listas enlazadas** programadas para la clasificación $A$, $B$ y $C$.
* [x] **Pila** de inferencia dinámica integrada en el flujo.
* [x] Menú interactivo por consola (Opciones 1 al 6).

## 🛠️ Tareas Pendientes (Para el resto del equipo)
Para finalizar el alcance del proyecto, es necesario implementar las siguientes funciones y agregarlas al menú principal:

1. **Operaciones de Conjuntos (Funciones entre Listas):**
   * Intersección ($A \cap B$): Proyectos activos con retraso.
   * Diferencia ($A - C$): Proyectos en desarrollo.
   * Unión ($B \cup C$): Proyectos en revisión o finalizados.
2. **Auditoría con LPPO (Lógica de Predicados):**
   * Implementar funciones que recorran las listas evaluando el Cuantificador Universal ($\forall$) y Existencial ($\exists$). Ej: Validar que $\forall x \in C, \neg Q(x)$.
3. **Reporte Final:**
   * Generar un resumen estadístico (total analizados, alertas, estables).
