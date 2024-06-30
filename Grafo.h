#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Vertice.h"

class Grafo
{
private:
  int numVertices;
  int maxVertices;
  Vertice *vertices;
  int **matrizAdy;
  string arco;
  ofstream archivo;

public:
  Grafo();
  Grafo(int max);
  int getNumVertices();
  void setNumVertices(int n);
  void nuevoVertice(string nombre);
  int existeVertice(string nombre);
  void nuevoArco(string nombre1, string nombre2, int distancia);
  void imprimirMatriz();
  void generarReporte();
  void caminoMasCorto(string nombreInicio, string nombreFin);
  ~Grafo();
};

Grafo::Grafo()
{
}

Grafo::Grafo(int max)
{
  numVertices = 0;
  maxVertices = max;
  vertices = new Vertice[max];
  matrizAdy = new int *[max];
  for (int i = 0; i < max; i++)
  {
    matrizAdy[i] = new int[max];
  }
  for (int i = 0; i < maxVertices; i++)
  {
    for (int j = 0; j < maxVertices; j++)
    {
      matrizAdy[i][j] = 0;
    }
  }
}

int Grafo::getNumVertices()
{
  return this->numVertices;
}

void Grafo::setNumVertices(int n)
{
  this->numVertices = n;
}

void Grafo::nuevoVertice(string nombre)
{
  bool existe = (existeVertice(nombre) >= 0);
  if (!existe)
  {
    Vertice nuevo = Vertice(nombre, numVertices);
    vertices[numVertices] = nuevo;
    numVertices++;
  }
}

int Grafo::existeVertice(string nombre)
{
  int i = 0;
  bool encontrado = false;
  while (i < numVertices && !encontrado)
  {
    encontrado = vertices[i].esIgual(nombre);
    if (!encontrado)
    {
      i++;
    }
  }
  return (i < numVertices) ? i : -1;
}

void Grafo::nuevoArco(string nombre1, string nombre2, int distancia)
{
  int vertice1, vertice2;
  vertice1 = existeVertice(nombre1);
  vertice2 = existeVertice(nombre2);
  if (vertice1 >= 0 && vertice2 >= 0)
  {
    matrizAdy[vertice1][vertice2] = distancia;
  }
  else
  {
    cout << "Error, uno de los vértices no existen\n";
  }
}

void Grafo::imprimirMatriz()
{
  for (int i = 0; i < maxVertices; i++)
  {
    for (int j = 0; j < maxVertices; j++)
    {
      cout << " " << matrizAdy[i][j] << " ";
    }
    cout << endl;
  }
}

void Grafo::generarReporte()
{
  if (getNumVertices() == 0)
  {
  }
  else
  {
    archivo.open("reporteGrafo.dot", ios::out);
    archivo << "digraph G {\n"
            << endl;

    for (int i = 0; i < maxVertices; i++)
    {
      for (int j = 0; j < maxVertices; j++)
      {
        if (matrizAdy[i][j] > 0)
        {
          stringstream ss;
          ss << matrizAdy[i][j];
          string distancia = ss.str();
          arco = vertices[i].getNombre() + " -> " + vertices[j].getNombre() + " [label=\"" + distancia + "\"]" + ";\n";
          archivo << arco;
          arco.clear();
        }
      }
    }

    archivo << "\n}";
    archivo.close();
    system("dot -Tpng reporteGrafo.dot -o reporteGrafo.png");
  }
}

void Grafo::caminoMasCorto(string nombreInicio, string nombreFin)
{
  int verticeInicio = existeVertice(nombreInicio);
  int verticeFin = existeVertice(nombreFin);

  if (verticeInicio < 0 || verticeFin < 0)
  {
    cout << "Error, uno de los vértices no existe\n";
    return;
  }

  const int INF = 1e9;

  int dist[maxVertices];
  bool visitado[maxVertices];
  int prev[maxVertices];

  for (int i = 0; i < maxVertices; ++i)
  {
    dist[i] = INF;
    visitado[i] = false;
    prev[i] = -1;
  }

  dist[verticeInicio] = 0;

  for (int i = 0; i < maxVertices; ++i)
  {
    int u = -1;
    for (int j = 0; j < maxVertices; ++j)
    {
      if (!visitado[j] && (u == -1 || dist[j] < dist[u]))
      {
        u = j;
      }
    }

    if (dist[u] == INF)
      break;

    visitado[u] = true;

    for (int v = 0; v < maxVertices; ++v)
    {
      if (matrizAdy[u][v] && dist[u] + matrizAdy[u][v] < dist[v])
      {
        dist[v] = dist[u] + matrizAdy[u][v];
        prev[v] = u;
      }
    }
  }

  if (dist[verticeFin] == INF)
  {
    cout << "No existe un camino desde " << nombreInicio << " hasta " << nombreFin << "\n";
    return;
  }

  cout << "El camino más corto desde " << nombreInicio << " hasta " << nombreFin << " es de distancia " << dist[verticeFin] << " km.\n";

  int camino[maxVertices];
  int index = 0;
  for (int at = verticeFin; at != -1; at = prev[at])
  {
    camino[index++] = at;
  }

  cout << "Camino: ";
  for (int i = index - 1; i >= 0; --i)
  {
    cout << vertices[camino[i]].getNombre();
    if (i != 0)
    {
      cout << " -> ";
    }
  }
  cout << endl;
}

Grafo::~Grafo()
{
}