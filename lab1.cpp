//1
#include <iostream>
#include <cstdarg>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

class IntArray {
    int* a;
    int n;
public:
    IntArray(int N) {
        n = N;
        a = new int[n];
        srand(time(0));
        for (int i = 0; i < n; i++)
            a[i] = rand() % 41 - 20;
    }
    ~IntArray() {
        delete[] a;
    }
    void print() {
        cout << "Згенерований масив: ";
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << endl;
    }
    double average() {
        long long s = 0;
        for (int i = 0; i < n; i++) s += a[i];
        return (double)s / n;
    }
};

class Text {
    char s[256];
public:
    void read() {
        cout << "Введіть рядок: " << endl;
        cin.ignore();
        cin.getline(s, 256);
    }
    int letters() {
        int c = 0;
        for (int i = 0; s[i]; i++)
            if (isalpha((unsigned char)s[i])) c++;
        return c;
    }
};

class VarSum {
public:
    static int calc(int first, ...) {
        va_list args;
        va_start(args, first);
        int s = 0, x = first;
        while (x != 0) {
            s += x;
            x = va_arg(args, int);
        }
        va_end(args);
        return s;
    }
};

int main() {
    cout << "Введіть n:" << endl;
    int n;
    cin >> n;

    IntArray arr(n);
    arr.print();
    cout << "Середнє арифметичне масиву: " << arr.average() << endl;

    Text t;
    t.read();
    cout << "Кількість букв у введеному рядку: " << t.letters() << endl;

    cout << "Сума аргументів (1,2,0): " 
         << VarSum::calc(1, 2, 0) << endl;

    cout << "Сума аргументів (3,4,0,10,20): " 
         << VarSum::calc(3, 4, 0, 10, 20) << endl;

    cout << "Сума аргументів (5,6,7,0,1,2,3,4): " 
         << VarSum::calc(5, 6, 7, 0, 1, 2, 3, 4) << endl;
}

//2 

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

class RealArray {
    double* a;
    int n;
public:
    RealArray(int N) {
        n = N;
        a = new double[n];
        srand(time(0));
        for (int i = 0; i < n; i++)
            a[i] = (rand() % 2001 - 1000) / 10.0;
    }
    ~RealArray() {
        delete[] a;
    }
    void print() {
        cout << "Масив: ";
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << endl;
    }
    int countNegative() {
        int c = 0;
        for (int i = 0; i < n; i++) if (a[i] < 0) c++;
        return c;
    }
    double sumAfterMinAbs() {
        int p = 0;
        double mn = fabs(a[0]);
        for (int i = 1; i < n; i++)
            if (fabs(a[i]) < mn) mn = fabs(a[i]), p = i;
        double s = 0;
        for (int i = p + 1; i < n; i++) s += fabs(a[i]);
        return s;
    }
    void transformAndSort() {
        for (int i = 0; i < n; i++)
            if (a[i] < 0) a[i] = a[i] * a[i];
        sort(a, a + n);
    }
};

int main() {
    cout << "Введіть n:" << endl;
    int n;
    cin >> n;

    RealArray a(n);
    a.print();

    cout << "Кількість від’ємних елементів: " << a.countNegative() << endl;
    cout << "Сума модулів елементів після мінімального за модулем: " 
         << a.sumAfterMinAbs() << endl;

    a.transformAndSort();
    cout << "Масив після заміни від’ємних на квадрати і сортування: ";
    a.print();
}

