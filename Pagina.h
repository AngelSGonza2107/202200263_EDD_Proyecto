#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "Aviones.h"

class Pagina
{
public:
  bool esHoja;
  vector<Avion> aviones;
  vector<Pagina *> hijos;

  Pagina(bool hoja) : esHoja(hoja)
  {
    aviones.reserve(4); // Máximo 4 aviones por nodo (orden 5)
    hijos.reserve(5);   // Máximo 5 hijos por nodo (orden 5)
  }
};

#endif // PAGINA_H_INCLUDED
