#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream inputFile("inputDijkstra.txt");
ofstream outputFile("outputDijkstra.txt");

class Dijkstra
{
private:
  int min;                  // минимальный путь
  int min_index;            // индекс для минимального пути
  int temp;                 // текущий вес вершины
  int k;                    // индекс предыдущей вершины
  int weight;               // вес конечной вершины
  int MAX_INT = 2147483647; // константа

public:
  int start; // начальная точка
  int end;   // конечная точка
  int size;  // размер графа (количество точек)

  void dijkstraFunc(int start, int end, int size)
  {
    int **MATRIX = new int *[size]; // матрица связей. {*,*,*,*}
    for (int i = 0; i < size; i++)
    {
      MATRIX[i] = new int[size]; // {{},{},{},{}}
    }

    int *MIN_DISTANCE = new int[size]; // массив содержит расстояния - текущие кратчайшие расстояния от исходной до соответствующей вершины
    int *VERTEXES = new int[size];     /* массив содержит номера вершин - k-й элемент С[k] есть номер предпоследней
      вершины на текущем кратчайшем пути из Vi в Vk. (из исходной i-й в k-ю). Массив необходим для определения
      последовательности вершин входящих в кратчайший маршрут. */
    bool *VISITED = new bool[size];    /* признак фиксации метки; массив содержит метки с двумя значениями:
  0 (вершина еще не рассмотрена) и 1 (вершина уже рассмотрена); */

    // инициализация матрицы связей
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        inputFile >> MATRIX[i][j];
      }
    }

    inputFile.close();

    // инициализация вершин и расстояний
    for (int i = 0; i < size; i++)
    {
      MIN_DISTANCE[i] = MAX_INT;
      VISITED[i] = 0;
    }
    MIN_DISTANCE[start - 1] = 0;

    // шаг алгоритма
    do
    {
      min_index = MAX_INT;
      min = MAX_INT;

      for (int i = 0; i < size; i++)
      {
        // если вершину ещё не обошли и вес меньше min
        if (VISITED[i] == 0 && MIN_DISTANCE[i] < min)
        //  Переприсваиваем значения
        {
          min = MIN_DISTANCE[i];
          min_index = i;
        }
      }

      // Добавляем найденный минимальный вес к текущему весу вершины и сравниваем с текущим минимальным весом вершины
      if (min_index != MAX_INT)
      {
        for (int i = 0; i < size; i++)
        {
          if (MATRIX[min_index][i] > 0)
          {
            temp = min + MATRIX[min_index][i];
            if (temp < MIN_DISTANCE[i])
            {
              MIN_DISTANCE[i] = temp;
            }
          }
        }
        VISITED[min_index] = 1;
      }

    } while (min_index < MAX_INT);
    //  вывод кратчайших расстояний до вершин
    for (int i = start - 1; i < end; i++)
    {
      outputFile << "Nachalnaya tochka: " << start << " Konechnaya tochka: " << i + 1 << endl
                 << "Rasstoyanie: " << MIN_DISTANCE[i] << endl;
    }

    outputFile << "Put' ot " << start << " do " << end << ": ";

    VERTEXES[0] = end;              // начальный элемент равен конечной вершине
    k = 1;                          // индекс предыдущей вершины
    weight = MIN_DISTANCE[end - 1]; // вес конечной вершины

    // Восстановление пути
    while (end - 1 != start - 1) // пока не дошли до конечной вершины
    {
      for (int i = 0; i < size; i++) // просматриваем все вершины
      {
        if (MATRIX[i][end - 1] != 0) // если связь есть
        {
          temp = weight - MATRIX[i][end - 1]; // определяем вес пути из предыдущей вершины
          if (temp == MIN_DISTANCE[i])        // если вес совпал с рассчитанным значит из этой вершины и был переход
          {
            weight = temp;       // сохраняем новый вес
            end = i + 1;         // сохраняем предыдущую вершину
            VERTEXES[k] = i + 1; // и записываем ее в массив
            k++;
          }
        }
      }
    }

    if (start != 1)
    {
      for (int i = k - 1; i >= start - 1; i--)
      {
        outputFile << VERTEXES[i] << "->";
      }
      outputFile << VERTEXES[0];
    }
    else
    {
      for (int i = k - 1; i > start - 1; i--)
      {
        outputFile << VERTEXES[i] << "->";
      }
      outputFile << VERTEXES[0];
    }
    outputFile.close();
  }
};

int main()
{
  Dijkstra dijkstra;
  int start; // начальная точка
  int end;   // конечная точка
  int size;  // размер графа (количество точек)

  cout << "Vvedite kolichestvo tochek: ";
  cin >> size;
  cout << "Vvedite nachalnyu tochky: ";
  cin >> start;
  cout << "Vvedite konechnyu tochky: ";
  cin >> end;

  dijkstra.dijkstraFunc(start, end, size);
}
