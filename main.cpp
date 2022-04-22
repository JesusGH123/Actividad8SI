/*
Antonio Misael Delgado Salmerón
Jesús García Hernández

Referencia: https://www.geeksforgeeks.org/m-coloring-problem-backtracking-5/
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;
string colors[] = {"Blue", "Red", "Green"};

//Funcion utilizada para saber si un nodo es "seguro" para pintar de un color
//Entradas: Número del nodo, grafo, arreglo de colores de los nodos, un color
//Salida: Booleano que indica si es seguro colorear el nodo v con el color c
bool isSafe(int v, vector<vector<int>> & graph, int color[], int c)
{
    for(int i = 0; i < graph.size(); i++)
        if (graph[v][i] && c == color[i])
            return false;
             
    return true;
}

//Funcion: Función recursiva que prueba los colores para cada nodo
/*Entradas: Grafo, cantidad de colores, arreglo de colores para cada nodo, nodo actual, 
 ciudades, estructura para guardar la solucion final*/
//Salidas: Booleano de si existe solución o no
bool graphColoringUtil(vector<vector<int>> & graph, int m, int color[], int v, vector<string> &cities,deque<int> & solution)
{
    if(solution.size() == graph.size())
      return true;
    
    //Try different colors for vertex v
    for(int c = 1; c <= m; c++)
    {
      if (isSafe(v, graph, color, c))
      {
        cout << string(solution.size(),' ') << cities[v] << " (" << colors[c-1] << ")" << '\n';
        color[v] = c;
        solution.push_back(v);
        if(graphColoringUtil(graph, m, color, (v+1)%graph.size(), cities, solution))
            return true;
        color[v] = 0;
        solution.pop_back();
      }
    }
    return false;
}

//Funcion: Que una vez que termina la función recursiva, si el resultado es verdadero 
//imprime la solución, si no, imprime que no hay solución
//Entradas: Grafo, cantidad de colores, nodo inicial, ciudades
//Salidas: Booleano de si existe solución o no
bool graphColoring(vector<vector<int>> &graph, int m,int start, vector<string> &cities)
{
    int color[graph.size()];
    for(int i = 0; i < graph.size(); i++)
      color[i] = 0;
    deque<int> solution;
    if (graphColoringUtil(graph, m, color, start, cities,solution)){
      cout << "Solution exists, the assigned colors are: " << "\n";
      for(auto v: solution)
        cout << cities[v] << " (" << colors[color[v]-1] << ")" << '\n';
      cout << "\n";
    }
    else{
        cout << "Solution does not exist";
        return false;
    }

    return true;
}

//Funcion main
int main()
{
    int size, start;
    cout << "Insert the start node: ";
    cin >> start;

    ifstream f("graph.txt");
    f >> size;
    vector<vector<int>> graph(size);
    vector<string> cities(size);

    for(int i=0; i<size; i++) {
      graph[i].resize(size);
      for(int j=0; j<size; j++) {
        f >> graph[i][j];
      }
    }
  
    for(int i=0; i<size; i++)
      f >> cities[i];
  
    graphColoring(graph, 3,start, cities);
    return 0;
}