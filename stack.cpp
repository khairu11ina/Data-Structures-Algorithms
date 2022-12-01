// Стек
#include <iostream>
using namespace std;

class Stack
{
private:
  int size; // размерность стэка
  int top;  // указатель на вершину стека
  int *arr; // указатель на массив стэка

public:
  // конструктор

  Stack(int length)
  {
    size = length;
    top = -1;              // идентификация пустого стека
    arr = new int[length]; // динамический массив размерностью length
  }

  // деструктор
  ~Stack()
  {
    delete[] arr;
  }

  // метод добавления нового элемента
  bool push(int value)
  {
    // проверяем, есть ли свободное место в стеке
    if (top == (size - 1))
    {
      return false;
    }
    else
    {
      top++;            // изменяем значение указателя на вершину стека
      arr[top] = value; // записываем значение по данному указателю

      return true;
    }
  }

  // метод извлечения элемента из стека
  int pop()
  {
    // проверяем, есть ли элементы для извлечения
    if (top < 0)
    {
      return -1;
    }
    else
    {
      return arr[top--]; // изменяем значение указателя на вершину стека
    }
  }
};

// Основная программа
int main()
{
  setlocale(LC_ALL, "Russian");

  int size; // размерность массива
  cout << "Vvedite razmer steka: ";
  cin >> size;

  Stack stack(size); // создание объекта
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

      bool result = stack.push(value);

      if (!result)
      {
        cout << "Stek zapolnen!" << endl;
      }
    }
    else
    {
      int result = stack.pop();

      if (result == -1)
      {
        cout << "Stek pust!" << endl;
      }
      else
      {
        cout << "Izvlechennoe znachenie: " << result << endl;
      }
    }
  } while (true);

  return 0;
}