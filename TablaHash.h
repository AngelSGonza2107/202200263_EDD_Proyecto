#ifndef TABLAHASH_H_INCLUDED
#define TABLAHASH_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "ListaSimple.h"
#include "NodoListaSimple.h"

class TablaHash
{
private:
  int tamTabla;
  int numElementos;
  ListaSimple *tabla;

public:
  TablaHash();
  int clave(string numeroId);
  void insertar(string numeroId);
  void eliminar(string numeroId);
  void generarReporte();
  void imprimirTabla();
  ~TablaHash();
};

TablaHash::TablaHash()
{
  tamTabla = 18;
  tabla = new ListaSimple[18];
  numElementos = 0;
}

int TablaHash::clave(string numeroId)
{
  if (!numeroId.empty())
  {
    int valorAscii = static_cast<int>(numeroId[0]);
    int sumaDigitos = 0;
    for (size_t i = 1; i < numeroId.length(); ++i)
    {
      if (isdigit(numeroId[i]))
      {
        sumaDigitos += numeroId[i] - '0';
      }
    }
    int resultado = valorAscii + sumaDigitos;
    int j = (int)(resultado % tamTabla);
    return j;
  }
  return -1;
}

void TablaHash::eliminar(string numeroId)
{
  int indice = clave(numeroId);
  if (indice >= 0)
  {
    tabla[indice].eliminarNodo(numeroId);
  }
}

void TablaHash::insertar(string numeroId)
{
  int indice = clave(numeroId);
  if (indice >= 0)
  {
    tabla[indice].insertarFinal(numeroId);
  }
}

void TablaHash::imprimirTabla()
{
  for (int i = 0; i < tamTabla; i++)
  {
    cout << "[" << i << "] -> ";
    tabla[i].visualizarLista();
  }
}

void TablaHash::generarReporte()
{
  ofstream archivo;
  archivo.open("reporteTablaHash.dot", ios::out);
  archivo << "digraph G {\n rankdir=LR;\n node [shape=record];\n";

  for (int i = 17; i >= 0; --i)
  {
    archivo << "  pos" << i << " [label=\"{" << i << "|";
    NodoLS *actual = tabla[i].getPrimero();
    stringstream ss;
    while (actual)
    {
      ss << actual->getDato();
      if (actual->getSiguiente())
      {
        ss << "|";
      }
      actual = actual->getSiguiente();
    }
    archivo << ss.str() << "}\"];\n";
  }

  archivo << "}";
  archivo.close();

  system("dot -Tpng reporteTablaHash.dot -o reporteTablaHash.png");
}

TablaHash::~TablaHash()
{
}

#endif // TABLAHASH_H_INCLUDED
