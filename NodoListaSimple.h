#ifndef NODOLISTASIMPLE_H_INCLUDED
#define NODOLISTASIMPLE_H_INCLUDED

#include <iostream>
using namespace std;

class NodoLS
{
private:
  string dato;
  NodoLS *siguiente;

public:
  NodoLS(string dato);
  NodoLS *getSiguiente();
  void setSiguiente(NodoLS *siguiente);
  string getDato();
  ~NodoLS();
};

NodoLS::NodoLS(string dato)
{
  this->dato = dato;
  this->siguiente = nullptr;
}

NodoLS *NodoLS::getSiguiente()
{
  return this->siguiente;
}

void NodoLS::setSiguiente(NodoLS *siguiente)
{
  this->siguiente = siguiente;
}

string NodoLS::getDato()
{
  return this->dato;
}

NodoLS::~NodoLS()
{
}

#endif // NODOLISTASIMPLE_H_INCLUDED
