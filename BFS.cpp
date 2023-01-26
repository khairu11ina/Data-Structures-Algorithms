#include <iostream>
#include <windows.h>
#include <queue>
#include <fstream>
using namespace std;

ifstream inputFile("inputBFS.txt");
ofstream outputFile("outputBFS.txt");

class BFS
{
private:
  queue<int> q;
  int endBuf;
  int count;

  int size;  // размер графа (количество вершин)
  int start; // начальная точка
  int end;   // конечная точка

public:
  void BFSfunc(int size, int start, int end)
  {
    int **MATRIX = new int *[size]; // матрица связей. {*,*,*,*}
    for (int i = 0; i < size; i++)
    {
      MATRIX[i] = new int[size]; // {{},{},{},{}}
    }

    // инициализация матрицы связей
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        inputFile >> MATRIX[i][j];
      }
    }

    inputFile.close();

    int *WAYS = new int[size];      // массив нужен для того, чтобы запоминатоь путь из вершин
    bool *VISITED = new bool[size]; /* признак фиксации метки; массив содержит метки с двумя значениями:
  0 (вершина еще не рассмотрена) и 1 (вершина уже рассмотрена); */

    for (int i = 0; i < size; i++)
    {
      VISITED[i] = 0;
    }

    q.push(start);      // добавляем начальную вершину в очередь
    VISITED[start] = 1; // помечаем ее как пройденную
    WAYS[start] = -1;   // так как из одной вершины в ту же самую нельзя попасть

    while (!q.empty()) // если очередь не пустая
    {
      int unit = q.front();          // запоминаем вершину из очереди
      q.pop();                       // и извлекаем ее
      for (int i = 0; i < size; i++) // проходим по всем вершинам
      {
        if (!VISITED[i] && MATRIX[unit][i]) // если вершина не пройдена и имеет связь с вершиной, которую извлекли
        {
          q.push(i);      // добавляем вершину в очередь
          WAYS[i] = unit; // запоминаем из какой вершины пришли
          VISITED[i] = 1; // помечаем вершину как пройденную
        }
      }
    }

    endBuf = end;
    count = 0;
    do
    {
      count++;
      endBuf = WAYS[endBuf];
    } while (endBuf != WAYS[start]);
    int *rev = new int[count];
    int i = 0;
    rev[i] = end;
    i++;
    outputFile << "Кратчайший путь от " << start + 1 << " до " << end + 1 << ": ";

    do
    {
      rev[i] = WAYS[end];
      i++;
      end = WAYS[end];
    } while (end != start);
    i--;
    while (i > 0)
    {
      outputFile << rev[i] + 1 << R"(->)";
      i--;
    }
    outputFile << rev[0] + 1;
    outputFile.close();
  }
};

int main()
{
  BFS bfs;
  int size;  // размер графа (количество точек)
  int start; // начальная точка
  int end;   // конечная точка

  cout << "Vvedite kolichestvo tochek: ";
  cin >> size;
  cout << "Vvedite nachalnuy tochky: ";
  cin >> start;
  start--;
  cout << "Vvedite konechnuy tochky: ";
  cin >> end;
  end--;

  bfs.BFSfunc(size, start, end);
}