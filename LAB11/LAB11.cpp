#include <iostream>
#include <string>
#include "ExpressionTree.h"
using namespace std;

void displayMenu()
{
    cout << "\n==== МЕНЮ ОПЕРАЦИЙ С ДЕРЕВОМ ====" << endl;
    cout << "1. Создать новое дерево выражения" << endl;
    cout << "2. Вывести информацию о дереве" << endl;
    cout << "3. Найти узел по значению" << endl;
    cout << "4. Показать количество узлов и высоту дерева" << endl;
    cout << "5. Вычислить результат выражения" << endl;
    cout << "6. Освобождение памяти" << endl;
    cout << "0. Выход из программы" << endl;
    cout << "Выберите операцию (0-6): ";
}

int main()
{
    setlocale(LC_ALL, "RU");
    ExpressionTree expr; 
    int choice = -1;

    while (choice != 0)
    {
        displayMenu();
        
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите число от 0 до 6." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            expr.createTree(); 
            break;
        case 2:
            expr.printTree();
            break;
        case 3:
            expr.searchNode(); 
            break;
        case 4:
            expr.treeInfo(); 
            break;
        case 5:
            expr.calculateResult(); 
            break;
        case 6:
            expr.freeMemory();
            cout << "Память успешно очищена!"<<endl;
            break;
        case 0:
            expr.~ExpressionTree();
            exit(0);
        default:
            cout << "Некорректный выбор. Пожалуйста, выберите опцию от 0 до 5." << endl;
        }
    }

    return 0;
}
