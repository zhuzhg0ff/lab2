#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <numeric>

using namespace std;

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();

void displayMenu() {
    cout << "Выберите задачу (1-8, 0 для выхода): ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            default: if (choice != 0) cout << "Неверный выбор. Попробуйте еще раз." << endl; break;
        }
    } while (choice != 0);

    return 0;
}

template <typename T>
void inputContainer(T& container, const string& prompt) {
    cout << "Введите элементы для " << prompt << " (закончите ввод любым нечисловым символом): ";
    typename T::value_type element;
    while (cin >> element) {
        container.push_back(element);
    }
    cin.clear();  // Очищаем состояние потока
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Игнорируем оставшиеся символы
}

void task1() {
    vector<int> V;
    deque<int> D;
    list<int> L;

    inputContainer(V, "vector");
    inputContainer(D, "deque");
    inputContainer(L, "list");

    if (V.size() < 3 || D.size() < 3 || L.size() < 3) {
        cout << "Недостаточно элементов (минимум 3)" << endl;
        return;
    }
    
    if (V.size() % 2 == 0|| D.size() % 2 == 0 || L.size() % 2 == 0) {
        cout << "Является чётным" << endl;
        return;
    }
    
    auto modify = [](auto &container) {
        int size = container.size();
        container.front() *= 2;
        auto middleIt = next(container.begin(), size / 2);
        *middleIt *= 2;
        container.back() *= 2;
    };

    modify(V);
    modify(D);
    modify(L);

    cout << "Измененный вектор: ";
    for (const auto &e : V) cout << e << " ";
    cout << "\nИзмененный дек: ";
    for (const auto &e : D) cout << e << " ";
    cout << "\nИзмененный список: ";
    for (const auto &e : L) cout << e << " ";
    cout << endl;
}

void task2() {
    list<int> L;
    inputContainer(L, "list");

    if (L.size() % 3 != 0) {
        cout << "Не делится на 3" << endl;
        return;
    }

    int thirdSize = L.size() / 3;
    auto it = L.begin();
    advance(it, thirdSize);
    list<int> firstThird(it, next(it, thirdSize));
    L.insert(L.end(), firstThird.rbegin(), firstThird.rend());

    cout << "Список после добавления первой трети в обратном порядке: ";
    for (const auto &e : L) cout << e << " ";
    cout << endl;
}

void task3() {
    deque<int> D;
    inputContainer(D, "deque");

    if (D.size() % 4 != 0) {
        cout << "Дек не кратен 4" << endl;
        return;
    }

    int halfSize = D.size() / 2;

    // Создаем копию оригинального дека
    deque<int> temp = D;

    // Удаляем элементы с четными порядковыми номерами
    for (int i = 0; i < halfSize; ++i) {
        if (temp[i] % 2 == 0) {
            temp.erase(temp.begin() + i);
            --i; // Смещаем индекс, так как удалили элемент
        }
    }

    // Присваиваем изменения обратно оригинальному деку
    D.clear();
    D.insert(D.end(), temp.begin(), temp.end());

    cout << "Дек после удаления: ";
    for (const auto &e : D) cout << e << " ";
    cout << endl;
}

void task4() {
    vector<int> numbers;
    string filename;
    cout << "Введите элементы для записи в файл: ";
    inputContainer(numbers, "vector");
    cout << "Введите имя файла для записи: ";
    cin >> filename;

    ofstream outFile(filename);

    // Заменяем все значения 0 на 10 и добавляем пробелы
    replace_copy_if(numbers.begin(), numbers.end(),
                     ostream_iterator<int>(outFile, " "),
                     [](int x) { return x == 0; },
                     10);

    outFile.close();

    cout << "Данные записаны в файл " << filename << endl;
}


void task5() {
    int K;
    vector<int> V;

    cout << "Введите количество подряд идущих нулей для удаления: ";
    cin >> K;
    inputContainer(V, "vector");

    auto it = search_n(V.rbegin(), V.rend(), K, 0);
    if (it != V.rend()) {
        V.erase((it + K).base(), it.base());
    }

    cout << "Вектор после удаления: ";
    for (const auto &e : V) cout << e << " ";
    cout << endl;
}

void task6() {
    list<int> L1, L2;
    inputContainer(L1, "L1 (list)");

    inputContainer(L2, "L2 (list)");

    if (L1.size() % 4 != 0 || L2.size() % 4 != 0) {
        cout << "Недостаточно элементов (каждый должен содержать минимум 4)" << endl;
        return;
    }

    auto mid1 = next(L1.begin(), L1.size() / 2);
    auto mid2 = next(L2.begin(), L2.size() / 2);

    reverse(L1.begin(), mid1);
    reverse(mid2, L2.end());

    cout << "Список L1 после инверсии первой половины: ";
    for (const auto &e : L1) cout << e << " ";
    cout << "\nСписок L2 после инверсии второй половины: ";
    for (const auto &e : L2) cout << e << " ";
    cout << endl;
}

void task7() {
    list<int> L;
    inputContainer(L, "list");

    auto is_even = [](int n) { return n % 2 == 0; };
    auto it = partition(L.begin(), L.end(), is_even);

    cout << "Четных: " << distance(L.begin(), it) << ", Нечетных: " << distance(it, L.end()) << endl;
}

void task8() {
    list<int> L;
    inputContainer(L, "list");
    vector<double> V;

    if (L.size() > 1) {
        adjacent_difference(L.begin(), L.end(), back_inserter(V), [](int a, int b) { return (a + b) / 2.0; });
        V.erase(V.begin()); // Удаляем первый элемент, он изначально равен нулю.
    }

    cout << "Вектор средних: ";
    for (const auto &e : V) cout << e << " ";
    cout << endl;
}
