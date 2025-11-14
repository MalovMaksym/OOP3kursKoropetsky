//1
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int a[10];

    cout << "Згенерований масив з 10 елементів:" << endl;
    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 41 - 20; 
        cout << a[i] << " ";
    }
    cout << endl;

    long long s = 0;
    int c = 0;
    for (int i = 0; i < 10; i++) {
        if (a[i] != 0) {
            s += a[i];
            c++;
        }
    }

    cout << "Кількість ненульових елементів: " << c << endl;

    if (c > 0)
        cout << "Середнє арифметичне ненульових елементів: " << (double)s / c << endl;
    else
        cout << "Немає ненульових елементів, середнє не обчислюється." << endl;

    return 0;
}

//2
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int n;
    cout << "Введіть розмір квадратної матриці n:" << endl;
    cin >> n;

    if (n <= 0) {
        cout << "Некоректний розмір." << endl;
        return 0;
    }

    int** m = new int*[n];
    for (int i = 0; i < n; i++) m[i] = new int[n];

    cout << "Згенерована матриця:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 50; 
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    int ref = 0;
    for (int j = 0; j < n; j++) ref += m[0][j];

    for (int i = 1; i < n; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) s += m[i][j];
        if (s != ref) {
            cout << "Матриця не є магічним квадратом." << endl;
            return 0;
        }
    }

    for (int j = 0; j < n; j++) {
        int s = 0;
        for (int i = 0; i < n; i++) s += m[i][j];
        if (s != ref) {
            cout << "Матриця не є магічним квадратом." << endl;
            return 0;
        }
    }

    int d1 = 0, d2 = 0;
    for (int i = 0; i < n; i++) {
        d1 += m[i][i];
        d2 += m[i][n - 1 - i];
    }

    if (d1 == ref && d2 == ref)
        cout << "Матриця є магічним квадратом." << endl;
    else
        cout << "Матриця не є магічним квадратом." << endl;

    return 0;
}



//3
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = 100 + rand() % 900;

    cout << "Гра 'Вгадай число'. Введіть тризначне число (0 - вихід)." << endl;

    while (true) {
        int g;
        cout << "Ваш варіант -> ";
        cin >> g;

        if (g == 0) {
            cout << "Гру завершено." << endl;
            break;
        }

        if (g < 100 || g > 999) {
            cout << "Потрібно тризначне число." << endl;
            continue;
        }

        int a[3], b[3];
        int s = secret, x = g;
        for (int i = 2; i >= 0; i--) {
            a[i] = s % 10;
            b[i] = x % 10;
            s /= 10;
            x /= 10;
        }

        int exact = 0;
        for (int i = 0; i < 3; i++) if (a[i] == b[i]) exact++;

        bool ua[3] = {}, ub[3] = {};
        for (int i = 0; i < 3; i++) if (a[i] == b[i]) ua[i] = ub[i] = true;

        int total = exact;
        for (int i = 0; i < 3; i++)
            if (!ub[i])
                for (int j = 0; j < 3; j++)
                    if (!ua[j] && b[i] == a[j]) {
                        ua[j] = ub[i] = true;
                        total++;
                        break;
                    }

        cout << "Збіглися за значенням: " << total << endl;
        cout << "Збіглися за значенням і місцем: " << exact << endl;

        if (exact == 3) {
            cout << "Ви вгадали число!" << endl;
            break;
        }
    }

    return 0;
}


//4
#include <iostream>
#include <cstring>
using namespace std;

struct MorsePair {
    char ch;
    const char* code;
};

int main() {
    MorsePair t[36] = {
        {'A',".-"},{'B',"-..."},{'C',"-.-."},{'D',"-.."},
        {'E',"."},{'F',"..-."},{'G',"--."},{'H',"...."},
        {'I',".."},{'J',".---"},{'K',"-.-"},{'L',".-.."},
        {'M',"--"},{'N',"-."},{'O',"---"},{'P',".--."},
        {'Q',"--.-"},{'R',".-."},{'S',"..."},{'T',"-"},
        {'U',"..-"},{'V',"...-"},{'W',".--"},{'X',"-..-"},
        {'Y',"-.--"},{'Z',"--.."},{'0',"-----"},{'1',".----"},
        {'2',"..---"},{'3',"...--"},{'4',"....-"},{'5',"....."},
        {'6',"-...."},{'7',"--..."},{'8',"---.."},{'9',"----."}
    };

    char s[256];
    cout << "Введіть повідомлення латиницею:" << endl;
    cin.ignore();
    cin.getline(s, 256);

    cout << "Код Морзе:" << endl;

    for (int i = 0; s[i]; i++) {
        char c = s[i];
        if (c == ' ') {
            cout << "/ ";
            continue;
        }
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';

        const char* code = 0;
        for (int j = 0; j < 36; j++)
            if (t[j].ch == c)
                code = t[j].code;

        if (code) cout << code << " ";
        else cout << "? ";
    }

    cout << endl;
    return 0;
}



//файл 2
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ship {
protected:
    char name[50];
    double l, d;
public:
    Ship(const char* n) {
        strcpy(name, n);
        l = 50 + rand() % 151;
        d = 1000 + rand() % 9001;
    }
    virtual void show() {
        cout << "Корабель '" << name << "': довжина = " << l 
             << ", водотоннажність = " << d << endl;
    }
};

class Steamship : public Ship {
    char engine[50];
    double power;
public:
    Steamship(const char* n, const char* e)
        : Ship(n) {
        strcpy(engine, e);
        power = 5000 + rand() % 15001;
    }
    void show() override {
        cout << "Пароплав '" << name << "': довжина = " << l 
             << ", водотоннажність = " << d 
             << ", двигун = " << engine 
             << ", потужність = " << power << endl;
    }
};

class SailingShip : public Ship {
    int masts;
    double sailArea;
public:
    SailingShip(const char* n)
        : Ship(n) {
        masts = 1 + rand() % 4;
        sailArea = 100 + rand() % 901;
    }
    void show() override {
        cout << "Парусник '" << name << "': довжина = " << l 
             << ", водотоннажність = " << d 
             << ", щогл = " << masts 
             << ", площа вітрил = " << sailArea << endl;
    }
};

class Corvette : public SailingShip {
    bool mil;
public:
    Corvette(const char* n)
        : SailingShip(n) {
        mil = rand() % 2;
    }
    void show() override {
        cout << "Корвет '" << name << "': довжина = " << l 
             << ", водотоннажність = " << d 
             << ", військовий = " << (mil ? "так" : "ні") << endl;
    }
};

int main() {
    srand(time(0));
    Ship a("Корабель");
    Steamship b("Пароплав", "дизель");
    SailingShip c("Парусник");
    Corvette d("Корвет");

    cout << "Характеристики кораблів:" << endl;
    Ship* arr[4] = { &a, &b, &c, &d };
    for (int i = 0; i < 4; i++) arr[i]->show();
}
