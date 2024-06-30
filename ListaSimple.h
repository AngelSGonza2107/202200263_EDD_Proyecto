#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <iostream>
using namespace std;
#include "NodoListaSimple.h"

class ListaSimple
{
private:
  NodoLS *primero;

public:
  ListaSimple();
  bool estaVacia();
  NodoLS *getPrimero();
  void insertarFinal(string dato);
  void eliminarNodo(string numeroId);
  void visualizarLista();
  ~ListaSimple();
};

ListaSimple::ListaSimple()
{
  primero = nullptr;
}

bool ListaSimple::estaVacia()
{
  return primero == nullptr;
}

NodoLS *ListaSimple::getPrimero()
{
  return this->primero;
}

void ListaSimple::insertarFinal(string dato)
{
  NodoLS *nuevo = new NodoLS(dato);
  if (ListaSimple::estaVacia())
  {
    primero = nuevo;
  }
  else
  {
    NodoLS *actual = primero;
    while (actual->getSiguiente())
    {
      actual = actual->getSiguiente();
    }
    actual->setSiguiente(nuevo);
  }
}

void ListaSimple::eliminarNodo(string numeroId)
{
  if (ListaSimple::estaVacia())
  {
    cout << "La lista está vacía\n"
         << endl;
    return;
  }
  if (primero->getDato() == numeroId)
  {
    NodoLS *temp = primero;
    primero = primero->getSiguiente();
    delete temp;
    cout << "Piloto con número de identificación " << numeroId << " eliminado." << endl;
    return;
  }
  NodoLS *actual = primero;
  NodoLS *anterior = nullptr;
  while (actual && actual->getDato() != numeroId)
  {
    anterior = actual;
    actual = actual->getSiguiente();
  }
  if (!actual)
  {
    cout << "No se encontró el piloto con el número de identificación: " << numeroId << "." << endl;
    return;
  }
  anterior->setSiguiente(actual->getSiguiente());
  delete actual;
  cout << "Piloto con número de identificación " << numeroId << " eliminado." << endl;
}

void ListaSimple::visualizarLista()
{
  if (ListaSimple::estaVacia())
  {
    cout << "La lista está vacía\n"
         << endl;
  }
  else
  {
    NodoLS *actual = primero;
    while (actual)
    {
      cout << actual->getDato() << " -> ";
      actual = actual->getSiguiente();
    }
    cout << "\n"
         << endl;
  }
}

ListaSimple::~ListaSimple()
{
}

#endif // LISTASIMPLE_H_INCLUDED
