// Очередь
#include <iostream>
using namespace std;

class Queue
{
private:
  int size;        // размерность массива
  int first, last; // указатель на начало и конец очереди
  int *arr;        // указатель на массив

public:
  // конструктор
  Queue(int length)
  {
    size = length;
    first = -1;
    last = -1;
    arr = new int[length]; // динамический массив размерностью length
  }

  // деструктор
  ~Queue()
  {
    delete[] arr;
  }

  // метод добавления нового элемента
  int add(int value)
  {
    // проверяем, есть ли свободное место в очереди
    if (first == 0 && (last + 1) == size)
    {
      return false;
    }
    if (first == last + 1)
    {
      return false;
    }
    if (first == -1)
      first = 0;
    last = (last + 1) % size;
    arr[last] = value;
    return true;
  }

  // метод извлечения элемента из очереди
  int extract()
  {
    int value;
    // проверяем, есть ли элементы для извлечения
    if (first == -1)
    {
      return -1;
    }
    else
    {
      value = arr[first];
      if (first == last)
      {
        first = -1;
        last = -1;
      }
      else
      {
        first = (first + 1) % size; // изменяем значение начала очереди
      }
      return value;
    }
  }
};

int main()
{
  setlocale(LC_ALL, "Russian");

  int size; // размерность массива
  cout << "Vvedite razmer ocheredi: ";
  cin >> size;

  Queue queue(size); // создание объекта
  bool operation;    // переменная для отличия добавления от извлечения
  int value;         // переменная, которая хранит значение, которое надо добавить в стек

  do
  {
    cout << "Dlya dobavleniya vvedite 1, dlya izvlecheniya vvedite 0: ";
    cin >> operation;

    if (operation)
    {
      cout << "Vvedite znachenie: ";
      cin >> value;
      bool result = queue.add(value);

      if (!result)
      {
        cout << "Ochered' zapolnena!" << endl;
      }
    }
    else
    {
      int result = queue.extract();

      if (result == -1)
      {
        cout << "Ochered' pusta!" << endl;
      }
      else
      {
        cout << "Izvlechennoe znachenie: " << result << endl;
      }
    }
  } while (true);

  return 0;
}