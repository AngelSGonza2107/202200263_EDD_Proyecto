#ifndef ARBOLB_H_INCLUDED
#define ARBOLB_H_INCLUDED

#include <iostream>
#include <fstream>
using namespace std;

#include "Pagina.h"
#include "ListaCircularDoble.h"

class ArbolB
{
private:
  Pagina *raiz;

  void insertarNoLleno(Pagina *nodo, const Avion &avion)
  {
    int i = nodo->aviones.size() - 1;

    if (nodo->esHoja)
    {
      nodo->aviones.push_back(avion);
      while (i >= 0 && nodo->aviones[i].getClave() > avion.getClave())
      {
        nodo->aviones[i + 1] = nodo->aviones[i];
        i--;
      }
      nodo->aviones[i + 1] = avion;
    }
    else
    {
      while (i >= 0 && nodo->aviones[i].getClave() > avion.getClave())
      {
        i--;
      }
      i++;
      if (nodo->hijos[i]->aviones.size() == 4)
      {
        dividirHijo(nodo, i);
        if (nodo->aviones[i].getClave() < avion.getClave())
        {
          i++;
        }
      }
      insertarNoLleno(nodo->hijos[i], avion);
    }
  }

  void dividirHijo(Pagina *nodo, int i)
  {
    Pagina *y = nodo->hijos[i];
    Pagina *z = new Pagina(y->esHoja);

    nodo->hijos.insert(nodo->hijos.begin() + i + 1, z);
    nodo->aviones.insert(nodo->aviones.begin() + i, y->aviones[2]);

    z->aviones.push_back(y->aviones[3]);
    y->aviones.resize(2);

    if (!y->esHoja)
    {
      for (int j = 0; j < 3; j++)
      {
        z->hijos.push_back(y->hijos[j + 2]);
      }
      y->hijos.resize(2);
    }
  }

  void generarDot(Pagina *nodo, ofstream &archivo, int &contador)
  {
    int nodoID = contador++;
    archivo << "Nodo" << nodoID << " [label=\"";
    for (const auto &avion : nodo->aviones)
    {
      archivo << " Avion: " << avion.numeroRegistro << " - ";
      archivo << avion.vuelo << " - ";
      archivo << avion.estado << " |";
    }
    archivo << "\"];\n";

    if (!nodo->esHoja)
    {
      for (size_t i = 0; i < nodo->hijos.size(); ++i)
      {
        int hijoID = contador;
        generarDot(nodo->hijos[i], archivo, contador);
        archivo << "Nodo" << nodoID << " -> Nodo" << hijoID << ";\n";
      }
    }
  }

  string buscar(Pagina *pagina, const string &numeroVuelo)
  {
    int i = 0;
    while (i < static_cast<int>(pagina->aviones.size()))
    {
      if (i < static_cast<int>(pagina->aviones.size()) && numeroVuelo == pagina->aviones[i].getNumeroVuelo())
      {
        return pagina->aviones[i].getCiudadDestino();
      }
      i++;
    }

    if (!pagina->esHoja)
    {
      for (Pagina *hijo : pagina->hijos)
      {
        string resultado = buscar(hijo, numeroVuelo);
        if (!resultado.empty())
        {
          return resultado;
        }
      }
    }
    return "";
  }

public:
  ArbolB() : raiz(nullptr) {}

  void insertar(Avion &avion)
  {
    if (!raiz)
    {
      raiz = new Pagina(true);
      raiz->aviones.push_back(avion);
    }
    else
    {
      if (raiz->aviones.size() == 4)
      {
        Pagina *s = new Pagina(false);
        s->hijos.push_back(raiz);
        dividirHijo(s, 0);
        insertarNoLleno(s, avion);
        raiz = s;
      }
      else
      {
        insertarNoLleno(raiz, avion);
      }
    }
  }

  string buscarAvion(const string &numeroVuelo)
  {
    string ciudad = "";
    if (raiz == nullptr)
    {
      return "";
    }
    ciudad = buscar(raiz, numeroVuelo);
    return ciudad;
  }

  void generarReporte()
  {
    ofstream archivo;
    archivo.open("reporteDisponibles.dot", ios::out);
    if (archivo.is_open())
    {
      archivo << "digraph G {\n";
      archivo << "node [shape=record];\n";
      int contador = 0;
      if (raiz != nullptr)
      {
        generarDot(raiz, archivo, contador);
      }
      archivo << "}\n";
      archivo.close();
      system("dot -Tpng reporteDisponibles.dot -o reporteDisponibles.png");
    }
    else
    {
      cerr << "No se pudo abrir el archivo para escribir\n";
    }
  }
};

#endif // ARBOLB_H_INCLUDED
