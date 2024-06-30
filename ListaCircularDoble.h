#ifndef LISTACIRCULARDOBLE_H_INCLUDED
#define LISTACIRCULARDOBLE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "Aviones.h"
#include "NodoListaCircularDoble.h"
#include "ArbolB.h"

class ListaCircularDoble
{
private:
  NodoLC *primero;
  NodoLC *ultimo;
  int tamano;

public:
  ListaCircularDoble();
  bool estaVacia();
  void insertarFinal(Avion *nuevoAvion);
  NodoLC *buscarAvion(string numeroRegistro);
  NodoLC *eliminarAvion(NodoLC *avion);
  // void moverAvion(ArbolB &otraLista, NodoLC *avion);
  string buscarAvion2(string numeroVuelo);
  void generarReporteMante();
  int obtenerTamano();
  ~ListaCircularDoble();
};

ListaCircularDoble::ListaCircularDoble()
{
  primero = nullptr;
  ultimo = nullptr;
  tamano = 0;
}

bool ListaCircularDoble::estaVacia()
{
  return (primero == nullptr) && (ultimo == nullptr);
}

void ListaCircularDoble::insertarFinal(Avion *newAvion)
{
  NodoLC *nuevoAvion = new NodoLC(newAvion);
  nuevoAvion->setAnterior(nullptr);
  nuevoAvion->setSiguiente(nullptr);
  if (ListaCircularDoble::estaVacia())
  {
    nuevoAvion->setAnterior(nuevoAvion);
    nuevoAvion->setSiguiente(nuevoAvion);
    primero = ultimo = nuevoAvion;
  }
  else
  {
    nuevoAvion->setSiguiente(primero);
    nuevoAvion->setAnterior(ultimo);
    ultimo->setSiguiente(nuevoAvion);
    primero->setAnterior(nuevoAvion);
    ultimo = nuevoAvion;
  }
  ++tamano;
}

NodoLC *ListaCircularDoble::buscarAvion(string numeroRegistro)
{
  if (primero == nullptr)
    return nullptr;
  NodoLC *actual = primero;
  do
  {
    if (actual->getNumeroRegistro() == numeroRegistro)
    {
      return actual;
    }
    actual = actual->getSiguiente();
  } while (actual != primero);
  return nullptr;
}

NodoLC *ListaCircularDoble::eliminarAvion(NodoLC *avion)
{
  if (primero == nullptr || avion == nullptr)
    return nullptr;
  if (avion->getSiguiente() == avion)
  {
    primero = ultimo = nullptr;
  }
  else
  {
    NodoLC *anterior = avion->getAnterior();
    NodoLC *siguiente = avion->getSiguiente();
    anterior->setSiguiente(siguiente);
    siguiente->setAnterior(anterior);
    if (avion == primero)
    {
      primero = siguiente;
    }
  }
  --tamano;
  return avion;
}

// void ListaCircularDoble::moverAvion(ArbolB &otraLista, NodoLC *avion)
// {
//   if (avion != nullptr)
//   {
//     Avion avion2(avion->getVuelo(), avion->getNumeroRegistro(), avion->getModelo(), avion->getCapacidad(), avion->getAerolinea(), avion->getCiudadDestino(), avion->getEstado());
//     eliminarAvion(avion);
//     otraLista.insertar(avion2);
//   }
// }

string ListaCircularDoble::buscarAvion2(string numeroVuelo)
{
  if (!primero)
  {
    return "";
  }

  NodoLC *actual = primero;
  do
  {
    if (actual->getVuelo() == numeroVuelo)
    {
      return actual->getCiudadDestino();
    }
    actual = actual->getSiguiente();
  } while (actual != primero);

  return "";
}

void ListaCircularDoble::generarReporteMante()
{
  if (!ListaCircularDoble::estaVacia())
  {
    ofstream archivo;
    archivo.open("reporteMantenimiento.dot", ios::out);
    archivo << "digraph G { \n rankdir = LR;\n";

    if (primero)
    {
      NodoLC *actual = primero;
      do
      {
        archivo << "nodo" << actual << " [label=\"" << actual->graficarDatos() << "\"];\n";
        actual = actual->getSiguiente();
      } while (actual != primero);

      actual = primero;
      do
      {
        archivo << "nodo" << actual << " -> nodo" << actual->getSiguiente() << ";\n";
        archivo << "nodo" << actual->getSiguiente() << " -> nodo" << actual << ";\n";
        actual = actual->getSiguiente();
      } while (actual != primero);
    }

    archivo << "}";
    archivo.close();

    system("dot -Tpng reporteMantenimiento.dot -o reporteMantenimiento.png");
  }
}

int ListaCircularDoble::obtenerTamano()
{
  return tamano;
}

ListaCircularDoble::~ListaCircularDoble()
{
}

#endif // LISTACIRCULARDOBLE_H_INCLUDED
