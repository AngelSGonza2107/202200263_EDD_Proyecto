#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "NodoMatriz.h"

class Matriz
{
private:
  NodoM *header;

  NodoM *encontrarFila(const string &vuelo)
  {
    NodoM *current = header->abajo;
    while (current && current->numeroVuelo != vuelo)
    {
      current = current->abajo;
    }
    return current;
  }

  NodoM *encontrarColumna(const string &destino)
  {
    NodoM *current = header->derecha;
    while (current && current->ciudadDestino != destino)
    {
      current = current->derecha;
    }
    return current;
  }

  NodoM *crearNodoCabeceraFila(const string &vuelo)
  {
    NodoM *nuevoNodo = new NodoM(vuelo, "", "");
    NodoM *current = header;

    while (current->abajo && current->abajo->numeroVuelo < vuelo)
    {
      current = current->abajo;
    }

    nuevoNodo->abajo = current->abajo;
    if (current->abajo)
    {
      current->abajo->arriba = nuevoNodo;
    }
    current->abajo = nuevoNodo;
    nuevoNodo->arriba = current;

    return nuevoNodo;
  }

  NodoM *crearNodoCabeceraColumna(const string &destino)
  {
    NodoM *nuevoNodo = new NodoM("", "", destino);
    NodoM *current = header;

    while (current->derecha && current->derecha->ciudadDestino < destino)
    {
      current = current->derecha;
    }

    nuevoNodo->derecha = current->derecha;
    if (current->derecha)
    {
      current->derecha->izquierda = nuevoNodo;
    }
    current->derecha = nuevoNodo;
    nuevoNodo->izquierda = current;

    return nuevoNodo;
  }

public:
  Matriz()
  {
    header = new NodoM("", "", "");
  }

  ~Matriz()
  {
    NodoM *currentFila = header;
    while (currentFila)
    {
      NodoM *currentColumna = currentFila;
      currentFila = currentFila->abajo;
      while (currentColumna)
      {
        NodoM *temp = currentColumna;
        currentColumna = currentColumna->derecha;
        delete temp;
      }
    }
  }

  void insertarPiloto(const string &vuelo, const string &piloto, const string &destino)
  {
    NodoM *fila = encontrarFila(vuelo);
    if (!fila)
    {
      fila = crearNodoCabeceraFila(vuelo);
    }

    NodoM *columna = encontrarColumna(destino);
    if (!columna)
    {
      columna = crearNodoCabeceraColumna(destino);
    }

    NodoM *nuevoNodo = new NodoM(vuelo, piloto, destino);

    NodoM *currentFila = fila;
    while (currentFila->derecha && currentFila->derecha->ciudadDestino < destino)
    {
      currentFila = currentFila->derecha;
    }
    nuevoNodo->derecha = currentFila->derecha;
    if (currentFila->derecha)
    {
      currentFila->derecha->izquierda = nuevoNodo;
    }
    currentFila->derecha = nuevoNodo;
    nuevoNodo->izquierda = currentFila;

    NodoM *currentColumna = columna;
    while (currentColumna->abajo && currentColumna->abajo->numeroVuelo < vuelo)
    {
      currentColumna = currentColumna->abajo;
    }
    nuevoNodo->abajo = currentColumna->abajo;
    if (currentColumna->abajo)
    {
      currentColumna->abajo->arriba = nuevoNodo;
    }
    currentColumna->abajo = nuevoNodo;
    nuevoNodo->arriba = currentColumna;
  }

  void eliminarPiloto(const string &vuelo, const string &destino)
  {
    NodoM *fila = encontrarFila(vuelo);
    NodoM *columna = encontrarColumna(destino);

    if (fila && columna)
    {
      NodoM *currentFila = fila;
      while (currentFila->derecha && currentFila->derecha->ciudadDestino != destino)
      {
        currentFila = currentFila->derecha;
      }
      if (currentFila->derecha && currentFila->derecha->ciudadDestino == destino)
      {
        NodoM *temp = currentFila->derecha;
        currentFila->derecha = temp->derecha;
        if (temp->derecha)
        {
          temp->derecha->izquierda = currentFila;
        }
        delete temp;
      }

      NodoM *currentColumna = columna;
      while (currentColumna->abajo && currentColumna->abajo->numeroVuelo != vuelo)
      {
        currentColumna = currentColumna->abajo;
      }
      if (currentColumna->abajo && currentColumna->abajo->numeroVuelo == vuelo)
      {
        NodoM *temp = currentColumna->abajo;
        currentColumna->abajo = temp->abajo;
        if (temp->abajo)
        {
          temp->abajo->arriba = currentColumna;
        }
        delete temp;
      }
    }
  }

  void crearFila(const string &vuelo)
  {
    if (!encontrarFila(vuelo))
    {
      crearNodoCabeceraFila(vuelo);
    }
  }

  void eliminarFila(const string &vuelo)
  {
    NodoM *fila = encontrarFila(vuelo);
    if (fila)
    {
      NodoM *current = fila->derecha;
      while (current)
      {
        NodoM *temp = current;
        current = current->derecha;
        eliminarPiloto(temp->numeroVuelo, temp->ciudadDestino);
      }

      if (fila->arriba)
      {
        fila->arriba->abajo = fila->abajo;
      }
      if (fila->abajo)
      {
        fila->abajo->arriba = fila->arriba;
      }
      delete fila;
    }
  }

  void crearColumna(const string &destino)
  {
    if (!encontrarColumna(destino))
    {
      crearNodoCabeceraColumna(destino);
    }
  }

  void eliminarColumna(const string &destino)
  {
    NodoM *columna = encontrarColumna(destino);
    if (columna)
    {
      NodoM *current = columna->abajo;
      while (current)
      {
        NodoM *temp = current;
        current = current->abajo;
        eliminarPiloto(temp->numeroVuelo, temp->ciudadDestino);
      }

      if (columna->izquierda)
      {
        columna->izquierda->derecha = columna->derecha;
      }
      if (columna->derecha)
      {
        columna->derecha->izquierda = columna->izquierda;
      }
      delete columna;
    }
  }

  void generarReporte()
  {
    ofstream archivoDOT;
    archivoDOT.open("reporteMatrizDispersa.dot", ios::out);
    if (!archivoDOT.is_open())
    {
      std::cerr << "No se pudo abrir el archivo para escribir el reporte." << std::endl;
      return;
    }

    archivoDOT << "digraph MatrizDispersa {\n";
    archivoDOT << "  node [shape=box];\n";

    // Crear nodos de la matriz
    NodoM *currentFila = header;
    int filaIndex = 0;
    while (currentFila)
    {
      NodoM *currentColumna = currentFila;
      int columnaIndex = 0;
      while (currentColumna)
      {
        if (currentColumna == header)
        {
          archivoDOT << "    \"" << currentColumna << "\" [label=\"Raiz\", group=0, fillcolor=lightgray, style=filled];\n";
        }
        else if (currentColumna->numeroVuelo.empty() && currentColumna->ciudadDestino.empty())
        {
          archivoDOT << "    \"" << currentColumna << "\" [label=\"Piloto: " << currentColumna->piloto << "\", group=" << columnaIndex << "];\n";
        }
        else if (currentColumna->numeroVuelo.empty())
        {
          archivoDOT << "    \"" << currentColumna << "\" [label=\"" << currentColumna->ciudadDestino << "\", group=" << columnaIndex << "];\n";
        }
        else if (currentColumna->ciudadDestino.empty())
        {
          archivoDOT << "    \"" << currentColumna << "\" [label=\"" << currentColumna->numeroVuelo << "\", group=0];\n";
        }
        else
        {
          archivoDOT << "    \"" << currentColumna << "\" [label=\"Piloto: " << currentColumna->piloto << "\", group=" << columnaIndex << "];\n";
        }
        currentColumna = currentColumna->derecha;
        columnaIndex++;
      }
      currentFila = currentFila->abajo;
      filaIndex++;
    }

    // Crear conexiones horizontales y verticales
    currentFila = header;
    while (currentFila)
    {
      NodoM *currentColumna = currentFila;
      while (currentColumna)
      {
        if (currentColumna->derecha)
        {
          archivoDOT << "    \"" << currentColumna << "\" -> \"" << currentColumna->derecha << "\";\n";
        }
        if (currentColumna->izquierda)
        {
          archivoDOT << "    \"" << currentColumna << "\" -> \"" << currentColumna->izquierda << "\";\n";
        }
        if (currentColumna->abajo)
        {
          archivoDOT << "    \"" << currentColumna << "\" -> \"" << currentColumna->abajo << "\";\n";
        }
        if (currentColumna->arriba)
        {
          archivoDOT << "    \"" << currentColumna << "\" -> \"" << currentColumna->arriba << "\";\n";
        }
        currentColumna = currentColumna->derecha;
      }
      currentFila = currentFila->abajo;
    }

    // Agrupar filas en el mismo rango horizontal
    currentFila = header;
    filaIndex = 0;
    while (currentFila)
    {
      archivoDOT << "    { rank=same; ";
      NodoM *currentColumna = currentFila;
      while (currentColumna)
      {
        archivoDOT << "\"" << currentColumna << "\"; ";
        currentColumna = currentColumna->derecha;
      }
      archivoDOT << "}\n";
      currentFila = currentFila->abajo;
      filaIndex++;
    }

    archivoDOT << "}\n";
    archivoDOT.close();

    system("dot -Tpng reporteMatrizDispersa.dot -o reporteMatrizDispersa.png");
  }
};
