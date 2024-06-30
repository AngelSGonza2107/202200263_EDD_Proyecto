#include <iostream>
#include <string>
using namespace std;

class NodoM
{
public:
  string numeroVuelo;
  string piloto;
  string ciudadDestino;
  NodoM *arriba;
  NodoM *abajo;
  NodoM *izquierda;
  NodoM *derecha;

  NodoM(const std::string &vuelo, const std::string &piloto, const std::string &destino)
      : numeroVuelo(vuelo), piloto(piloto), ciudadDestino(destino), arriba(nullptr), abajo(nullptr), izquierda(nullptr), derecha(nullptr) {}

  ~NodoM() {}
};