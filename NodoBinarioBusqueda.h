#ifndef NODOBINARIOBUSQUEDA_H_INCLUDED
#define NODOBINARIOBUSQUEDA_H_INCLUDED

#include <iostream>
#include <sstream>
using namespace std;

#include "Pilotos.h"

class NodoBB
{
private:
  Piloto *piloto;
  NodoBB *izq;
  NodoBB *der;

public:
  NodoBB(Piloto *piloto);
  void setDato(Piloto *piloto);
  void setIzq(NodoBB *izq);
  void setDer(NodoBB *der);
  NodoBB *getIzq();
  NodoBB *getDer();
  string getNombre();
  string getNumeroId();
  void setNumeroId(string numeroId);
  string getVuelo();
  int getHorasVuelo();
  string graficarDatosArbolBinario();
  ~NodoBB();
};

NodoBB::NodoBB(Piloto *piloto)
{
  this->piloto = piloto;
  this->izq = nullptr;
  this->der = nullptr;
}

void NodoBB::setDato(Piloto *piloto)
{
  this->piloto = piloto;
}

void NodoBB::setIzq(NodoBB *izq)
{
  this->izq = izq;
}

void NodoBB::setDer(NodoBB *der)
{
  this->der = der;
}

NodoBB *NodoBB::getIzq()
{
  return this->izq;
}

NodoBB *NodoBB::getDer()
{
  return this->der;
}

string NodoBB::getNombre()
{
  return this->piloto->nombre;
}

string NodoBB::getNumeroId()
{
  return this->piloto->numeroId;
}

void NodoBB::setNumeroId(string numeroId)
{
  this->piloto->numeroId = numeroId;
}

string NodoBB::getVuelo()
{
  return this->piloto->vuelo;
}

int NodoBB::getHorasVuelo()
{
  return this->piloto->horasVuelo;
}

string NodoBB::graficarDatosArbolBinario()
{
  stringstream ss;
  ss << "\"Piloto: " << this->getNombre() << "\n";
  ss << "Horas de vuelo: " << this->getHorasVuelo();
  ss << "\"";
  return ss.str();
}

NodoBB::~NodoBB()
{
}

#endif // NODOBINARIOBUSQUEDA_H_INCLUDED
