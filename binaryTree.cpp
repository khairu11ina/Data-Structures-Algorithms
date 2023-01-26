#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
using namespace std;

ifstream inputFile("inputBinaryTree.txt");
ofstream outputFile("outputBinaryTree.txt");

// вершина дерева
struct TreeNode
{
  int value;
  TreeNode *left;
  TreeNode *right;
};

// структура дерева
class BinaryTree
{
private:
  TreeNode *root; // указатель на корень дерева
  TreeNode *minValue(TreeNode *item);
  TreeNode *delPrivate(TreeNode *current, int item);
  vector<int> myArray;

public:
  BinaryTree()
  {
    root = nullptr;
  }

  int search(int item);
  bool add(int item);
  void *delPublic(TreeNode *current, int item);
  vector<int> traversePreOrder(TreeNode *current);
  void writeFile(TreeNode *current);
  void readOneElementFromFile();
  void readFile();
  TreeNode *getRoot();
};

int BinaryTree::search(int item)
{
  TreeNode *current = root;

  if (current == nullptr)
  {
    return 0; // искомая вершина отсутствует
  }

  while (true)
  {
    // если проверяемый равен текущему
    if (current->value == item)
    {
      return 1; // такая вершина уже есть
    }

    // добавляемая вершина меньше текущей
    else if (current->value > item)
    {
      if (current->left == nullptr)
      {
        return 0; // конец алгоритма со значением 0
      }
      else
      {
        //если указатель на текущую вершину = указателю на левую
        current = current->left;

        continue; // переход к следующей слева вершине
      }
    }
    else
    { //добавляемая вершина больше текущей
      if (current->right == nullptr)
      //если указатель на правую вершину = 0
      {
        return 0; // конец алгоритма со значением 0
      }
      else
      {
        current = current->right; //указатель на текущую вершину = указателю на правую

        continue; //переход к следующей справа вершине
      }
    }
  }
}

bool BinaryTree::add(int item)
{
  TreeNode *current = root;
  TreeNode *prev = nullptr;

  // если текущий пуст, значит записываем именно в него
  if (current == nullptr)
  {
    current = new TreeNode;
    current->left = nullptr;
    current->right = nullptr;
    current->value = item;
    root = current;

    return true;
  }

  while (true)
  {
    // если такой элемент уже существует, значит выход из цикла
    if (current->value == item)
    {
      return false;
    }

    prev = current;
    // если проверяемый меньше текущего
    if (current->value < item)
    {
      current = current->right;
      if (current == nullptr)
      {
        current = new TreeNode;
        current->left = nullptr;
        current->right = nullptr;
        current->value = item;
        prev->right = current;

        return true;
      }
      else
      {
        continue;
      }
    }

    if (current->value > item)
    {
      current = current->left;
      if (current == nullptr)
      {
        current = new TreeNode;
        current->left = nullptr;
        current->right = nullptr;
        current->value = item;
        prev->left = current;

        return true;
      }
      else
      {
        continue;
      }
    }
  }
}

TreeNode *BinaryTree::minValue(TreeNode *item)
{
  TreeNode *current = item;

  while (current && current->left != NULL)
  {
    current = current->left;
  }

  return current;
}

TreeNode *BinaryTree::delPrivate(TreeNode *current, int item)
{
  if (current == nullptr)
  {
    return current;
  }

  if (current->value > item)
  {
    current->left = delPrivate(current->left, item);
  }

  else if (current->value < item)
  {
    current->right = delPrivate(current->right, item);
  }

  else
  {
    // если у родителя нет дочерних элементов или есть только один
    if (current->left == nullptr)
    {
      TreeNode *temp = current->right;

      return temp;
    }
    else if (current->right == nullptr)
    {
      TreeNode *temp = current->left;

      return temp;
    }

    // если у родителя два дочерних эдемента
    TreeNode *temp = minValue(current->right);

    // дочерний узел помещаем в удаляемый
    current->value = temp->value;

    // удаляем этот узел
    current->right = delPrivate(current->right, temp->value);
  }

  return current;
}

void *BinaryTree::delPublic(TreeNode *current, int item)
{
  return delPrivate(current, item);
}

vector<int> BinaryTree::traversePreOrder(TreeNode *current)
{
  if (current != nullptr)
  {
    myArray.push_back(current->value);

    traversePreOrder(current->left);

    traversePreOrder(current->right);
  }
  return myArray;
}

void BinaryTree::writeFile(TreeNode *current)
{
  if (current != nullptr)
  {
    outputFile << current->value << " ";

    writeFile(current->left);

    writeFile(current->right);
  }
}

void BinaryTree::readOneElementFromFile()
{
  int num;
  inputFile >> num;
  add(num);
}

void BinaryTree::readFile()
{
  while (!inputFile.eof())
    readOneElementFromFile();
}

TreeNode *BinaryTree::getRoot()
{
  return root;
}

int main()
{
  BinaryTree binaryTree;
  int action, element;
  string outputFileName = "outputBinaryTree.txt";
  vector<int> elem(500);

  cout << "\nAvailable function:\n"
          "1. dobavlenie elementa\n"
          "2. udalenie elementa\n"
          "3. poisk elementa\n"
          "4. read file\n"
          "5. write file\n"
          "6. vivod dereva\n"
          "7. exit\n\n";
  while (1)
  {
    cout << "\nInput number of function: ";
    cin >> action;

    switch (action)
    {

    case 1:
    {
      // добавление элемента
      cout << "Enter element: ";
      cin >> element;
      binaryTree.add(element);
      cout << "Element " << element << " uspeshno dobavlen." << endl;
      break;
    }

    case 2:
    {
      // удаление элемента
      cout << "Enter element to delete: ";
      cin >> element;
      binaryTree.delPublic(binaryTree.getRoot(), element);
      cout << "Element " << element << " uspeshno udalen." << endl;
      break;
    }

    case 3:
    {
      // поиск элемента
      cout << "Enter element to search for: ";
      cin >> element;
      cout << "If element is found: 1; If element isn't found:0.\n";
      cout << "Answer: " << binaryTree.search(element) << "\n";
      break;
    }

    case 4:
    {
      // Чтение файла с содержимым дерева
      binaryTree.readFile();
      cout << "Soderjimoe starogo dereva uspeshno vosstanovleno." << endl;
      break;
    }

    case 5:
    {
      // Запись в файл содержимого дерева
      binaryTree.writeFile(binaryTree.getRoot());
      cout << "Soderjimoe dereva zapisano v fail '" << outputFileName << "'." << endl;
      break;
    }

    case 6:
    {
      // Вывод текущего дерева
      cout << "tekushee derevo: " << endl;
      vector<int> result = binaryTree.traversePreOrder(binaryTree.getRoot());
      copy(result.begin(), result.end(),
           ostream_iterator<int>(cout, " "));
      cout << endl;
      break;
    }

    // выход из программы
    case 7:
    {
      exit(0);
    }
    default:
      break;
    }
  }
}