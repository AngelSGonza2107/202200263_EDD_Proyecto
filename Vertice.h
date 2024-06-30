#include <iostream>
#include <sstream>
using namespace std;

class Vertice
{
private:
  string nombre;
  int numVertice;

public:
  Vertice();
  Vertice(string nombre, int n);
  string getNombre();
  void setNombre(string nombre);
  bool esIgual(string nombre);
  string graficarDatos();
  ~Vertice();
};

Vertice::Vertice()
{
}

Vertice::Vertice(string nombre, int n)
{
  this->nombre = nombre;
  this->numVertice = n;
}

string Vertice::getNombre()
{
  return this->nombre;
}

void Vertice::setNombre(string nombre)
{
  this->nombre = nombre;
}

bool Vertice::esIgual(string nombre)
{
  return (this->nombre == nombre);
}

string Vertice::graficarDatos()
{
  stringstream ss;
  ss << "\"" << this->nombre << "\"";
  return ss.str();
}

Vertice::~Vertice()
{
}