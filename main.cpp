#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <algorithm>
using namespace std;

#include "ArbolB.h"
#include "ListaCircularDoble.h"
#include "ArbolBinarioBusqueda.h"
#include "TablaHash.h"
#include "Grafo.h"
#include "Matriz.h"
#include "ListaSimple.h"
#include "Aviones.h"
#include "Pilotos.h"

int opcion;

string linea;
string filename;

ListaCircularDoble listaMantenimiento;
ArbolB arbolBDisponible;
ArbolBB arbolBinarioPilotos;
TablaHash tablaPilotos;
Grafo grafoRutas(50);
Matriz matrizPilotoVuelo;

void cargarAviones(const string &filename, ArbolB &arbolBDisponible, ListaCircularDoble &listaMantenimiento)
{
  ifstream archivo(filename);
  if (archivo.is_open())
  {
    string linea;

    string vuelo;
    string numeroRegistro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudadDestino;
    string estado;

    while (getline(archivo, linea))
    {
      size_t pos = linea.find(":");
      if (pos != string::npos)
      {
        string key = linea.substr(0, pos);
        string value = linea.substr(pos + 1);

        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(remove(key.begin(), key.end(), '\t'), key.end());
        value.erase(0, 1);
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());

        if (key == "vuelo")
        {
          vuelo = value;
        }
        else if (key == "numero_de_registro")
        {
          numeroRegistro = value;
        }
        else if (key == "modelo")
        {
          modelo = value;
        }
        else if (key == "capacidad")
        {
          capacidad = stoi(value);
        }
        else if (key == "aerolinea")
        {
          aerolinea = value;
        }
        else if (key == "ciudad_destino")
        {
          ciudadDestino = value;
        }
        else if (key == "estado")
        {
          estado = value;
        }
      }
      else if (linea.find("}") != string::npos)
      {
        if (estado == "Disponible")
        {
          Avion nuevoAvionDisp(vuelo, numeroRegistro, modelo, capacidad, aerolinea, ciudadDestino, estado);
          arbolBDisponible.insertar(nuevoAvionDisp);
        }
        else if (estado == "Mantenimiento")
        {
          Avion *nuevoAvionMante = new Avion(vuelo, numeroRegistro, modelo, capacidad, aerolinea, ciudadDestino, estado);
          listaMantenimiento.insertarFinal(nuevoAvionMante);
        }
      }
    }
    cout << "Archivo de aviones cargado exitosamente." << endl;
    archivo.close();
  }
  else
  {
    cerr << "No se pudo abrir el archivo para leer." << endl;
  }
}

void cargarPilotos(const string &filename, ArbolBB &arbolBinarioPilotos, TablaHash &tablaPilotos)
{
  ifstream archivo(filename);
  if (archivo.is_open())
  {
    string linea;

    string nombre;
    string nacionalidad;
    string numeroId;
    string vuelo;
    int horasVuelo;
    string tipoLicencia;

    while (getline(archivo, linea))
    {
      size_t pos = linea.find(":");
      if (pos != string::npos)
      {
        string key = linea.substr(0, pos);
        string value = linea.substr(pos + 1);

        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(remove(key.begin(), key.end(), '\t'), key.end());
        value.erase(0, 1);
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());

        if (key == "nombre")
        {
          nombre = value;
        }
        else if (key == "nacionalidad")
        {
          nacionalidad = value;
        }
        else if (key == "numero_de_id")
        {
          numeroId = value;
        }
        else if (key == "vuelo")
        {
          vuelo = value;
        }
        else if (key == "horas_de_vuelo")
        {
          horasVuelo = stoi(value);
        }
        else if (key == "tipo_de_licencia")
        {
          tipoLicencia = value;
        }
      }
      else if (linea.find("}") != string::npos)
      {
        Piloto *nuevoPiloto = new Piloto(nombre, nacionalidad, numeroId, vuelo, horasVuelo, tipoLicencia);
        arbolBinarioPilotos.insertar(nuevoPiloto);
        tablaPilotos.insertar(numeroId);

        string ciudadDestino = "";
        ciudadDestino = arbolBDisponible.buscarAvion(vuelo);
        if (ciudadDestino == "")
        {
          ciudadDestino = listaMantenimiento.buscarAvion2(vuelo);
        }
        if (ciudadDestino != "")
        {
          matrizPilotoVuelo.insertarPiloto(vuelo, numeroId, ciudadDestino);
        }
      }
    }
    cout << "Archivo de pilotos cargado exitosamente." << endl;
    archivo.close();
  }
  else
  {
    cerr << "No se pudo abrir el archivo para leer." << endl;
  }
}

void cargarRutas(const string &filename, Grafo &grafoRutas)
{
  ifstream file(filename);
  if (file.is_open())
  {
    string linea;
    while (getline(file, linea))
    {
      stringstream ss(linea);
      string origen, destino, dist;

      getline(ss, origen, '/');
      getline(ss, destino, '/');
      getline(ss, dist, ';');
      int distancia = stoi(dist);

      grafoRutas.nuevoVertice(origen);
      grafoRutas.nuevoVertice(destino);
      grafoRutas.nuevoArco(origen, destino, distancia);
    }
    cout << "Rutas cargadas al sistema exitosamente." << endl;
    file.close();
  }
  else
  {
    cerr << "Error al abrir el archivo de movimientos. " << endl;
  }
}

void cargarMovimientos(const string &filename, ArbolBB &arbolBinarioPilotos, TablaHash &tablaPilotos)
{
  ifstream file(filename);
  if (file.is_open())
  {
    string linea;
    while (getline(file, linea))
    {
      stringstream ss(linea);
      string comando;

      getline(ss, comando, ',');

      if (comando == "MantenimientoAviones")
      {
        // string accion, numeroRegistro;
        // getline(ss, accion, ',');
        // getline(ss, numeroRegistro, ';');
        // if (accion == "Ingreso")
        // {
        //   if (arbolBDisponible.moverAvion(numeroRegistro, listaMantenimiento))
        //   {
        //     cout << "Avion " << numeroRegistro << " movido a Mantenimiento." << endl;
        //   }
        //   else
        //   {
        //     cout << "Avion no encontrado." << endl;
        //   }
        // }
        // else if (accion == "Salida")
        // {
        //   NodoLC *test = listaMantenimiento.buscarAvion(numeroRegistro);
        //   if (test != nullptr)
        //   {
        //     test->setEstado("Disponible");
        //     listaMantenimiento.moverAvion(arbolBDisponible, test);
        //     cout << "Avion " << numeroRegistro << " movido a Disponible." << endl;
        //   }
        //   else
        //   {
        //     cout << "No fue posible encontrar el avion " << numeroRegistro << " en la lista de aviones en mantenimiento." << endl;
        //   }
        // }
      }
      else if (comando.find("DarDeBaja") != string::npos)
      {
        string numeroId = comando.substr(10);
        numeroId.pop_back();
        numeroId.pop_back();
        if (!arbolBinarioPilotos.estaVacio())
        {
          string vuelo = "";
          string ciudadDestino = "";
          vuelo = arbolBinarioPilotos.buscar(numeroId);
          ciudadDestino = arbolBDisponible.buscarAvion(vuelo);
          if (ciudadDestino == "")
          {
            ciudadDestino = listaMantenimiento.buscarAvion2(vuelo);
          }
          matrizPilotoVuelo.eliminarPiloto(vuelo, ciudadDestino);
          arbolBinarioPilotos.eliminar(numeroId);
          tablaPilotos.eliminar(numeroId);
        }
      }
    }
    cout << "Movimientos cargados exitosamente al sistema." << endl;
    file.close();
  }
  else
  {
    cerr << "Error al abrir el archivo de movimientos. " << endl;
  }
}

void generarReportes(ArbolBB &arbolBinarioPilotos, TablaHash &tablaPilotos)
{
  if (arbolBinarioPilotos.estaVacio())
  {
    cout << "No se pueden generar reportes de los pilotos, no hay pilotos en la base de datos." << endl;
  }
  else
  {
    tablaPilotos.generarReporte();
    arbolBinarioPilotos.generarReporte();
  }
  arbolBDisponible.generarReporte();
  listaMantenimiento.generarReporteMante();
  grafoRutas.generarReporte();
  matrizPilotoVuelo.generarReporte();
}

void mostrarMenu()
{
  cout << endl;
  cout << "--------------- MENU ---------------" << endl;
  cout << "  1. Carga de aviones" << endl;
  cout << "  2. Carga de pilotos" << endl;
  cout << "  3. Carga de rutas" << endl;
  cout << "  4. Carga de movimientos" << endl;
  cout << "  5. Consulta de horas de vuelo (pilotos)" << endl;
  cout << "  6. Recomendar ruta" << endl;
  cout << "  7. Visualizar reportes" << endl;
  cout << "  8. Salir \n"
       << endl;
  cout << "Elija la opcion que desee realizar: ";
}

void mostrarMenuRecorridos()
{
  int opcionRecorrido;

  cout << endl;
  cout << "---- Seleccione el recorrido ----" << endl;
  cout << "  1. Preorden" << endl;
  cout << "  2. Inorden" << endl;
  cout << "  3. Postorden" << endl;
  cout << endl;
  cout << "Elija la opcion que desee realizar: ";
  cin >> opcionRecorrido;

  switch (opcionRecorrido)
  {
  case 1:
  {
    arbolBinarioPilotos.RecorridoPre();
  }
  break;
  case 2:
  {
    arbolBinarioPilotos.RecorridoIn();
  }
  break;
  case 3:
  {
    arbolBinarioPilotos.RecorridoPost();
  }
  break;
  default:
  {
    cout << " -- La opcion elegida no es valida. \n"
         << endl;
    Sleep(600);
  }
  break;
  }
}

int main()
{
  int opcion;
  do
  {
    mostrarMenu();
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
      cout << "Ingrese la ruta del archivo JSON para la carga de aviones: ";
      string rutaAviones;
      cin >> rutaAviones;
      cargarAviones(rutaAviones, arbolBDisponible, listaMantenimiento);
    }
    break;
    case 2:
    {
      cout << "Ingrese la ruta del archivo JSON para la carga de pilotos: ";
      string rutaPilotos;
      cin >> rutaPilotos;
      cargarPilotos(rutaPilotos, arbolBinarioPilotos, tablaPilotos);
    }
    break;
    case 3:
    {
      cout << "Ingrese la ruta del archivo para la carga de rutas: ";
      string rutaRutas;
      cin >> rutaRutas;
      cargarRutas(rutaRutas, grafoRutas);
    }
    break;
    case 4:
    {
      cout << "Ingrese la ruta del archivo para la carga de movimientos: ";
      string rutaMovimientos;
      cin >> rutaMovimientos;
      cargarMovimientos(rutaMovimientos, arbolBinarioPilotos, tablaPilotos);
    }
    break;
    case 5:
    {
      mostrarMenuRecorridos();
    }
    break;
    case 6:
    {
      string nodoInicio, nodoFin;
      cout << "Ingrese el nodo de inicio: ";
      cin >> nodoInicio;
      cout << "Ingrese el nodo final: ";
      cin >> nodoFin;

      grafoRutas.caminoMasCorto(nodoInicio, nodoFin);
    }
    break;
    case 7:
    {
      generarReportes(arbolBinarioPilotos, tablaPilotos);
    }
    break;
    case 8:
    {
      cout << "Saliendo..." << endl;
      exit(EXIT_SUCCESS);
    }
    break;
    default:
    {
      cout << " -- La opcion elegida no es valida. \n"
           << endl;
      Sleep(600);
    }
    break;
    }
    cin.clear();
  } while (opcion != 8);
  return 0;
}
