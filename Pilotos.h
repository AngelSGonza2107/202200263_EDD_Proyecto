#ifndef PILOTOS_H_INCLUDED
#define PILOTOS_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class Piloto
{
public:
  Piloto();
  Piloto(string nombre, string nacionalidad, string numeroId, string vuelo, int horasVuelo, string tipoLicencia);
  string nombre;
  string nacionalidad;
  string numeroId;
  string vuelo;
  int horasVuelo;
  string tipoLicencia;
  ~Piloto();
};

Piloto::Piloto()
{
}

Piloto::Piloto(string nombre, string nacionalidad, string numeroId, string vuelo, int horasVuelo, string tipoLicencia)
{
  this->nombre = nombre;
  this->nacionalidad = nacionalidad;
  this->numeroId = numeroId;
  this->vuelo = vuelo;
  this->horasVuelo = horasVuelo;
  this->tipoLicencia = tipoLicencia;
}

Piloto::~Piloto()
{
}

#endif // PILOTOS_H_INCLUDED
