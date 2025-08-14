#include <iostream>
#include <limits>
using namespace std;

void showMenu() {
    cout << "\033[1m==================" << endl;
    cout << "       Меню       " << endl;
    cout << "==================\033[0m" << endl;
    cout << R"(Доступные действия:
1. Справка
2. Выполнить вычисление
3. Выход)" << endl;
    cout << "\nСделайте свой выбор: ";
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

void showHelp() {
    cout << "\033[1m==================" << endl;
    cout << "    Информация    " << endl;
    cout << "==================\033[0m" << endl;
    cout << R"(Данная программа предназначена для выполнения простых вычислений с целыми или имеющими дробную часть числами.

Возможности программы:
    "+" - сложение;
    "-" - вычитание;
    "*" - умножение;
    "/" - деление.

Примеры использования программы:
    "10 + 10";
    "15*2";
    "15 / 2.5".
    
Доступные действия:
1. Вернуться в главное меню
2. Выполнить вычисление
3. Выход)" << endl;
    cout << "\nСделайте свой выбор: ";
}

double calculate(double a, char operation, double b) {
    switch (operation) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                cout << "Ошибка: Деление на ноль!" << endl;
                return 0;
            }
            return a / b;
        default:
            cout << "Ошибка: Введено некорректное действие!" << endl;
            return 0;
    }
}

void calculationProcess() {
    bool calculateAgain;
    do {
        double a, b, result;
        char operation;
        bool inputValid = false;

        while (!inputValid) {
            cout << "Введите выражение: ";
            cin >> a;
            
            // Проверка первого числа
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: Некорректный ввод числа!" << endl;
                continue;
            }
            
            cin >> operation;
            
            // Проверка оператора
            if (operation != '+' && operation != '-' && 
                operation != '*' && operation != '/') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: Некорректная операция! Используйте +, -, *, /" << endl;
                continue;
            }
            
            cin >> b;
            
            // Проверка второго числа
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: Некорректный ввод числа!" << endl;
                continue;
            }
            
            inputValid = true;
        }

        result = calculate(a, operation, b);
        bool divisionByZero = (operation == '/' && b == 0);
        
        if (!divisionByZero) {
            cout << "Результат вычислений = " << result << endl;
        }
        
        cout << "Вычислить еще одно выражение? (y/n): ";
        char answer;
        cin >> answer;
        calculateAgain = (answer == 'y');
    } while (calculateAgain);
}

int main() {
    while (true) {
        showMenu();
        
        int choice = 0;
        cin >> choice;
        
        // Проверка ввода основного меню
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            cout << "Ошибка! Выбрано некорректное действие!" << endl;
            continue;
        }
        
        clearScreen();

        switch (choice) {
            case 1: {
                int helpChoice;
                showHelp();
                cin >> helpChoice;
                
                // Проверка ввода меню справки
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    clearScreen();
                    cout << "Ошибка! Выбрано некорректное действие!" << endl;
                    break;
                }
                
                switch (helpChoice) {
                    case 1:
                        clearScreen();
                        break;
                    case 2:
                        clearScreen();
                        calculationProcess();
                        clearScreen();
                        break;
                    case 3:
                        return 0;
                    default:
                        cout << "Ошибка! Выбрано некорректное действие!" << endl;
                }
                break;
            }

            case 2:
                calculationProcess();
                clearScreen();
                break;

            case 3:
                return 0;

            default:
                cout << "Ошибка! Выбрано некорректное действие!" << endl;
        }
    }
}