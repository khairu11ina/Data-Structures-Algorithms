#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

ifstream inputFile("inputDFSrecursion.txt");
ofstream outputFile("outputDFSrecursion.txt");

class DFS
{
private:
  int endBuf;
  int count;

  int size;  // размер графа (количество вершин)
  int start; // начальная точка
  int end;   // конечная точка

public:
  void DFSfunc(int size, int start, int end)
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

    int *WAYS = new int[size];      // массив нужен для того, чтобы запоминатоь путь из вершин
    bool *VISITED = new bool[size]; /* признак фиксации метки; массив содержит метки с двумя значениями:
  0 (вершина еще не рассмотрена) и 1 (вершина уже рассмотрена); */

    inputFile.close();

    for (int i = 0; i < size; i++)
    {
      VISITED[i] = 0;
    }

    VISITED[start] = 1; // помечаем ее как пройденную
    WAYS[start] = -1;   //

    func(start, size, VISITED, MATRIX, WAYS);

    for (int i = 0; i < size; i++)
    {
      cout << WAYS[i] << ", ";
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
    outputFile << "Путь от " << start + 1 << " до " << end + 1 << ": ";

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

  void func(int dot, int size, bool *VISITED, int **MATRIX, int *WAYS)
  {
    VISITED[dot] = 1;
    for (int i = 0; i < size; i++)
    {
      if (!VISITED[i] && MATRIX[dot][i] == 1)
      {
        WAYS[i] = dot;
        VISITED[i] = 1;

        func(i, size, VISITED, MATRIX, WAYS);
      }
    }
  }
};

int main()
{
  DFS dfs;
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

  dfs.DFSfunc(size, start, end);
}