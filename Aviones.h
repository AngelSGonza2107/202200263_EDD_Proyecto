#ifndef AVIONES_H_INCLUDED
#define AVIONES_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class Avion
{
public:
  Avion();
  Avion(string vuelo, string numeroRegistro, string modelo, int capacidad, string aerolinea, string ciudadDestino, string estado);
  string vuelo;
  string numeroRegistro;
  int getClave() const;
  string modelo;
  int capacidad;
  string aerolinea;
  string ciudadDestino;
  string estado;
  string getNumeroVuelo() const
  {
    return vuelo;
  }
  string getCiudadDestino() const
  {
    return ciudadDestino;
  }
  ~Avion();
};

Avion::Avion()
{
}

Avion::Avion(string vuelo, string numeroRegistro, string modelo, int capacidad, string aerolinea, string ciudadDestino, string estado)
{
  this->vuelo = vuelo;
  this->numeroRegistro = numeroRegistro;
  this->modelo = modelo;
  this->capacidad = capacidad;
  this->aerolinea = aerolinea;
  this->ciudadDestino = ciudadDestino;
  this->estado = estado;
}

int Avion::getClave() const
{
  string digitos = numeroRegistro.substr(1);
  return stoi(digitos);
}

Avion::~Avion()
{
}

#endif // AVIONES_H_INCLUDED
