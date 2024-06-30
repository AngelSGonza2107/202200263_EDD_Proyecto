#ifndef NODOLISTACIRCULARDOBLE_H_INCLUDED
#define NODOLISTACIRCULARDOBLE_H_INCLUDED

#include <iostream>
#include <sstream>
using namespace std;

#include "Aviones.h"

class NodoLC
{
private:
  Avion *dato;
  NodoLC *anterior;
  NodoLC *siguiente;

public:
  NodoLC(Avion *dato);
  void setDato(Avion *dato);
  void setSiguiente(NodoLC *siguiente);
  void setAnterior(NodoLC *anterior);
  NodoLC *getSiguiente();
  NodoLC *getAnterior();
  string getVuelo();
  string getNumeroRegistro();
  string getModelo();
  int getCapacidad();
  string getAerolinea();
  string getCiudadDestino();
  string getEstado();
  void setEstado(string estado);
  Avion *getDato();
  string graficarDatos();
  ~NodoLC();
};

NodoLC::NodoLC(Avion *dato)
{
  this->dato = dato;
  this->anterior = nullptr;
  this->siguiente = nullptr;
}

void NodoLC::setDato(Avion *dato)
{
  this->dato = dato;
}

void NodoLC::setSiguiente(NodoLC *siguiente)
{
  this->siguiente = siguiente;
}

void NodoLC::setAnterior(NodoLC *anterior)
{
  this->anterior = anterior;
}

NodoLC *NodoLC::getSiguiente()
{
  return this->siguiente;
}

NodoLC *NodoLC::getAnterior()
{
  return this->anterior;
}

string NodoLC::getVuelo()
{
  return this->dato->vuelo;
}

string NodoLC::getNumeroRegistro()
{
  return this->dato->numeroRegistro;
}

string NodoLC::getModelo()
{
  return this->dato->modelo;
}

int NodoLC::getCapacidad()
{
  return this->dato->capacidad;
}

string NodoLC::getAerolinea()
{
  return this->dato->aerolinea;
}

string NodoLC::getCiudadDestino()
{
  return this->dato->ciudadDestino;
}

string NodoLC::getEstado()
{
  return this->dato->estado;
}

void NodoLC::setEstado(string estado)
{
  this->dato->estado = estado;
}

Avion *NodoLC::getDato()
{
  return this->dato;
}

string NodoLC::graficarDatos()
{
  stringstream ss;
  ss << "Vuelo: " << this->getVuelo() << "\n";
  ss << "Numero de registro: " << this->getNumeroRegistro() << "\n";
  ss << "Estado: " << this->getEstado();
  return ss.str();
}

NodoLC::~NodoLC()
{
}

#endif // NODOLISTACIRCULARDOBLE_H_INCLUDED
