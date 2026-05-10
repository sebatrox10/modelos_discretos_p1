# Sistema de Diagnóstico Lógico - SoftLogic S.A.

## 📌 Descripción del Proyecto
Este proyecto es una herramienta de gestión de riesgos para proyectos de software desarrollada para la materia de **Modelos Discretos**. El objetivo es aplicar conceptos de **Lógica Proposicional**, **Lógica de Predicados de Primer Orden (LPPO)** y **Teoría de Conjuntos** utilizando estructuras de datos dinámicas en C++.

El sistema evalúa automáticamente el estado de los proyectos basándose en condiciones lógicas de retraso, errores y solicitudes del cliente, clasificándolos en conjuntos específicos para la toma de decisiones.

## 🏗️ Arquitectura Técnica
Para cumplir con los requerimientos de ingeniería, el sistema utiliza gestión de memoria dinámica (punteros) y sigue el siguiente flujo:

1.  **Cola de Recepción (Queue - FIFO):** Todos los proyectos nuevos ingresan a una cola. Esto garantiza que se procesen en el orden exacto en que llegan.
2.  **Motor de Inferencia:** Se extraen los proyectos de la cola para evaluar sus proposiciones lógicas ($P$, $Q$, $R$).
3.  **Gestor de Conjuntos (Linked Lists):** Una vez diagnosticados, los proyectos se almacenan en Listas Enlazadas que representan los conjuntos matemáticos:
    * **Conjunto A:** Proyectos Activos.
    * **Conjunto B:** Proyectos con Retraso ($> 10$ días).
    * **Conjunto C:** Proyectos Completados.

## 🧠 Modelo Lógico Implementado
### Proposiciones Simples
* **P:** El proyecto tiene más de 10 días de retraso.
* **Q:** Se han encontrado más de 3 errores críticos activos.
* **R:** El cliente ha solicitado una revisión urgente.

### Lógica de Predicados (LPPO)
El sistema está diseñado para realizar auditorías globales mediante cuantificadores:
* **Universal ($\\\\forall$):** Ejemplo: Verificar si *todos* los proyectos en el Conjunto C están libres de errores.
* **Existencial ($\\\\exists$):** Ejemplo: Verificar si *existe* al menos un proyecto en riesgo alto que necesite atención inmediata.

## 🚀 Estado del Primer Commit
En la versión inicial (`master`), se han implementado los cimientos del proyecto:
* [x] Definición del `struct Proyecto` con los atributos base.
* [x] Implementación dinámica de la **Cola de Recepción** (`encolar`/`desencolar`).
* [x] Funciones de evaluación para las proposiciones simples $P$, $Q$ y $R$.
* [x] Implementación de **Listas Enlazadas** para la clasificación en conjuntos.
* [x] Ciclo de procesamiento inicial que mueve datos de la Cola a las Listas según su lógica.

## 🛠️ Instrucciones para el Grupo
1.  **Compilación:** Utilizar `g++ main.cpp -o sistema`.
2.  **Continuación:** El siguiente paso es implementar la **Pila (Stack)** para evaluar expresiones compuestas y las funciones de operaciones entre conjuntos (Unión, Intersección, Diferencia).
3.  **Normas:** Mantener el uso de memoria dinámica y documentar cada nueva regla de inferencia agregada.
"""

file_path = "README.md"
with open(file_path, "w", encoding="utf-8") as f:
    f.write(readme_content)

print(f"Archivo {file_path} generado con éxito.")
