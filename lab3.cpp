
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

class Person {
    char ln[50], fn[50], mn[50], adr[50], gen[20], edu[20];
    int year;
public:
    Person() {}
    Person(const char* a, const char* b, const char* c, const char* d) {
        strcpy(ln, a);
        strcpy(fn, b);
        strcpy(mn, c);
        strcpy(adr, d);
        if (rand() % 2) strcpy(gen, "чоловіча");
        else strcpy(gen, "жіноча");
        if (rand() % 2) strcpy(edu, "вища");
        else strcpy(edu, "середня");
        year = 1960 + rand() % 50;
    }
    int age(int cur) const { return cur - year; }
    const char* gender() const { return gen; }
    const char* education() const { return edu; }
    void print() const {
        cout << ln << " " << fn << " " << mn << " (" << year 
             << "), адреса: " << adr 
             << ", стать: " << gen 
             << ", освіта: " << edu << endl;
    }
};

class People {
    Person* a;
    int n;
public:
    People(int N) {
        n = N;
        a = new Person[n];
    }
    ~People() {
        delete[] a;
    }
    void read() {
        cout << "Введіть ПІБ і адресу для кожної людини:" << endl;
        for (int i = 0; i < n; i++) {
            char ln[50], fn[50], mn[50], adr[50];
            cin >> ln >> fn >> mn >> adr;
            a[i] = Person(ln, fn, mn, adr);
        }
    }
    void older(int year, int limit) {
        cout << "Люди старші за " << limit << " років:" << endl;
        for (int i = 0; i < n; i++)
            if (a[i].age(year) > limit)
                a[i].print();
    }
    void withHigher() {
        cout << "Люди з вищою освітою:" << endl;
        for (int i = 0; i < n; i++)
            if (!strcmp(a[i].education(), "вища"))
                a[i].print();
    }
    void males() {
        cout << "Чоловіки:" << endl;
        for (int i = 0; i < n; i++)
            if (!strcmp(a[i].gender(), "чоловіча"))
                a[i].print();
    }
};

int main() {
    srand(time(0));

    cout << "Введіть поточний рік і кількість людей:" << endl;
    int year, n;
    cin >> year >> n;

    People p(n);
    p.read();

    cout << "Введіть граничний вік:" << endl;
    int limit;
    cin >> limit;

    p.older(year, limit);
    p.withHigher();
    p.males();
}

