#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <algorithm>

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
    bool cleanBuffer = true;
    do {
        string input;
        double a, b, result;
        char operation;
        bool isValid = true;
        
        cout << "Введите выражение: ";
        if (cleanBuffer) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        getline(cin, input);
        
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        
        if (input.empty()) {
            cout << "Ошибка: Пустой ввод!\n";
            cleanBuffer = false;
            continue;
        }
        
        size_t operationPosition = input.find_first_of("+-*/");
        if (operationPosition == string::npos) {
            cout << "Ошибка: Не был введен оператор!\n";
            cleanBuffer = false;
            continue;
        }
        
        if (operationPosition == 0 || operationPosition == input.length() - 1) {
            cout << "Ошибка: Некорректная позиция оператора!\n";
            cleanBuffer = false;
            continue;
        }
        
        string firstNum = input.substr(0, operationPosition);
        for (char c : firstNum) {
            if (!isdigit(c) && c != '.' && c != '-') {
                cout << "Ошибка: Первый операнд не является числом!\n";
                cleanBuffer = false;
                isValid = false;
                break;
            }
        }
        if (!isValid) continue;
        
        string secondNum = input.substr(operationPosition + 1);
        for (char c : secondNum) {
            if (!isdigit(c) && c != '.' && c != '-') {
                cout << "Ошибка: Второй операнд не является числом!\n";
                cleanBuffer = false;
                isValid = false;
                break;
            }
        }
        if (!isValid) {
            continue;
        }

        try {
            a = stod(input.substr(0, operationPosition));
            operation = input[operationPosition];
            b = stod(input.substr(operationPosition + 1));
        }
        catch (const invalid_argument&) {
            cout << "Ошибка: Некорректный формат числа!" << endl;
            cleanBuffer = false;
            continue;
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
        cleanBuffer = true;
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
                        clearScreen();
                        return 0;
                    default:
                        clearScreen();
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