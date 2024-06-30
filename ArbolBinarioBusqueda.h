#ifndef ARBOLBINARIOBUSQUEDA_H_INCLUDED
#define ARBOLBINARIOBUSQUEDA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "Pilotos.h"
#include "NodoBinarioBusqueda.h"

class ArbolBB
{
private:
  NodoBB *raiz;
  ofstream archivo;
  string nodoDato;

public:
  int recorrido = 0;
  ArbolBB();
  bool estaVacio();

  void insertar(Piloto *dato);
  NodoBB *insertarNodo(Piloto *dato, NodoBB *nodoPtr);

  void eliminar(string numeroId);
  NodoBB *eliminarNodo(string numeroId, NodoBB *nodoPtr);

  string buscar(string numeroId);
  string buscarNodo(string numeroId, NodoBB *nodoPtr);
  NodoBB *buscarMin(NodoBB *nodoPtr);

  void RecorridoIn();
  void RecorridoIn(NodoBB *nodoPtr);
  void RecorridoPre();
  void RecorridoPre(NodoBB *nodoPtr);
  void RecorridoPost();
  void RecorridoPost(NodoBB *nodoPtr);

  void generarReporte();
  void imprimirNodo(NodoBB *nodoPtr);
  ~ArbolBB();
};

ArbolBB::ArbolBB()
{
  raiz = nullptr;
}

bool ArbolBB::estaVacio()
{
  return (raiz == nullptr);
}

void ArbolBB::insertar(Piloto *dato)
{
  raiz = insertarNodo(dato, raiz);
}

NodoBB *ArbolBB::insertarNodo(Piloto *dato, NodoBB *nodoPtr)
{
  if (nodoPtr == nullptr)
  {
    NodoBB *nuevo = new NodoBB(dato);
    nodoPtr = nuevo;
  }
  else if (dato->horasVuelo < nodoPtr->getHorasVuelo())
  {
    nodoPtr->setIzq(insertarNodo(dato, nodoPtr->getIzq()));
  }
  else if (dato->horasVuelo > nodoPtr->getHorasVuelo())
  {
    nodoPtr->setDer(insertarNodo(dato, nodoPtr->getDer()));
  }
  else
  {
    cout << "Nodo duplicado\n";
  }
  return nodoPtr;
}

void ArbolBB::eliminar(string numeroId)
{
  raiz = eliminarNodo(numeroId, raiz);
}

NodoBB *ArbolBB::eliminarNodo(string numeroId, NodoBB *nodoPtr)
{
  if (nodoPtr == nullptr)
    return nodoPtr;

  if (numeroId < nodoPtr->getNumeroId())
  {
    nodoPtr->setIzq(eliminarNodo(numeroId, nodoPtr->getIzq()));
  }
  else if (numeroId > nodoPtr->getNumeroId())
  {
    nodoPtr->setDer(eliminarNodo(numeroId, nodoPtr->getDer()));
  }
  else
  {
    if (nodoPtr->getIzq() == nullptr && nodoPtr->getDer() == nullptr)
    {
      delete nodoPtr;
      nodoPtr = nullptr;
    }
    else if (nodoPtr->getIzq() == nullptr)
    {
      NodoBB *temp = nodoPtr;
      nodoPtr = nodoPtr->getDer();
      delete temp;
    }
    else if (nodoPtr->getDer() == nullptr)
    {
      NodoBB *temp = nodoPtr;
      nodoPtr = nodoPtr->getIzq();
      delete temp;
    }
    else
    {
      NodoBB *temp = buscarMin(nodoPtr->getDer());
      nodoPtr->setNumeroId(temp->getNumeroId());
      nodoPtr->setDer(eliminarNodo(temp->getNumeroId(), nodoPtr->getDer()));
    }
  }
  return nodoPtr;
}

string ArbolBB::buscar(string numeroId)
{
  string vuelo = buscarNodo(numeroId, raiz);
  return vuelo;
}

string ArbolBB::buscarNodo(string numeroId, NodoBB *nodoPtr)
{
  if (nodoPtr == nullptr)
  {
    return "";
  }
  if (numeroId == nodoPtr->getNumeroId())
  {
    return nodoPtr->getVuelo();
  }
  else if (numeroId < nodoPtr->getNumeroId())
  {
    return buscarNodo(numeroId, nodoPtr->getIzq());
  }
  else
  {
    return buscarNodo(numeroId, nodoPtr->getDer());
  }
}

NodoBB *ArbolBB::buscarMin(NodoBB *nodoPtr)
{
  while (nodoPtr->getIzq() != nullptr)
  {
    nodoPtr = nodoPtr->getIzq();
  }
  return nodoPtr;
}

void ArbolBB::RecorridoIn()
{
  RecorridoIn(raiz);
  cout << endl;
}

void ArbolBB::RecorridoIn(NodoBB *nodoPtr)
{
  if (nodoPtr != nullptr)
  {
    RecorridoIn(nodoPtr->getIzq());
    cout << nodoPtr->getHorasVuelo() << " -> ";
    RecorridoIn(nodoPtr->getDer());
  }
}

void ArbolBB::RecorridoPre()
{
  RecorridoPre(raiz);
  cout << endl;
}

void ArbolBB::RecorridoPre(NodoBB *nodoPtr)
{
  if (nodoPtr != nullptr)
  {
    cout << nodoPtr->getHorasVuelo() << " -> ";
    RecorridoPre(nodoPtr->getIzq());
    RecorridoPre(nodoPtr->getDer());
  }
}

void ArbolBB::RecorridoPost()
{
  RecorridoPost(raiz);
  cout << endl;
}

void ArbolBB::RecorridoPost(NodoBB *nodoPtr)
{
  if (nodoPtr != nullptr)
  {
    RecorridoPost(nodoPtr->getIzq());
    RecorridoPost(nodoPtr->getDer());
    cout << nodoPtr->getHorasVuelo() << " -> ";
  }
}

void ArbolBB::generarReporte()
{
  if (!ArbolBB::estaVacio())
  {
    archivo.open("reporteArbolBinario.dot", ios::out);
    archivo << "digraph G {\n";

    imprimirNodo(raiz);

    archivo << "\n}";
    archivo.close();
    system("dot -Tpng reporteArbolBinario.dot -o reporteArbolBinario.png");
  }
}

void ArbolBB::imprimirNodo(NodoBB *nodoPtr)
{
  if (nodoPtr == nullptr)
  {
    return;
  }
  if (nodoPtr->getIzq() != nullptr)
  {
    nodoDato = nodoPtr->graficarDatosArbolBinario();
    archivo << nodoDato;
    archivo << " -> ";
    nodoDato = nodoPtr->getIzq()->graficarDatosArbolBinario();
    archivo << nodoDato;
    archivo << ";";
  }
  imprimirNodo(nodoPtr->getIzq());
  if (nodoPtr->getDer() != nullptr)
  {
    nodoDato = nodoPtr->graficarDatosArbolBinario();
    archivo << nodoDato;
    archivo << " -> ";
    nodoDato = nodoPtr->getDer()->graficarDatosArbolBinario();
    archivo << nodoDato;
    archivo << ";";
  }
  imprimirNodo(nodoPtr->getDer());
}

ArbolBB::~ArbolBB()
{
}

#endif // ARBOLBINARIOBUSQUEDA_H_INCLUDED
