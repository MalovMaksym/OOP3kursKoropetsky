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




//2
#include <iostream>
#include <ctime>
using namespace std;

class BoolMatrix {
    int n, m;
    bool** a;

public:

    BoolMatrix() {
        n = m = 0;
        a = 0;
    }

    BoolMatrix(int N, int M) {
        n = N;
        m = M;
        a = new bool*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new bool[m];
            for (int j = 0; j < m; j++)
                a[i][j] = rand() % 2;
        }
    }

    BoolMatrix(const BoolMatrix& b) {
        n = b.n;
        m = b.m;
        a = new bool*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new bool[m];
            for (int j = 0; j < m; j++)
                a[i][j] = b.a[i][j];
        }
    }

    ~BoolMatrix() {
        clear();
    }

    void clear() {
        if (a) {
            for (int i = 0; i < n; i++)
                delete[] a[i];
            delete[] a;
        }
        a = 0;
        n = m = 0;
    }

    BoolMatrix& operator=(const BoolMatrix& b) {
        if (this == &b) return *this;

        clear();
        n = b.n;
        m = b.m;

        a = new bool*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new bool[m];
            for (int j = 0; j < m; j++)
                a[i][j] = b.a[i][j];
        }

        return *this;
    }

    BoolMatrix operator||(const BoolMatrix& b) {
        BoolMatrix r(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                r.a[i][j] = a[i][j] || b.a[i][j];
        return r;
    }

    BoolMatrix operator&&(const BoolMatrix& b) {
        BoolMatrix r(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                r.a[i][j] = a[i][j] && b.a[i][j];
        return r;
    }

    BoolMatrix operator!() {
        BoolMatrix r(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                r.a[i][j] = !a[i][j];
        return r;
    }

    int countOnes() const {
        int c = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i][j]) c++;
        return c;
    }

    void sortRowsLexicographically() {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int k = 0;
                while (k < m && a[i][k] == a[j][k]) k++;

                if (k < m && a[j][k] < a[i][k]) {
                    bool* tmp = a[i];
                    a[i] = a[j];
                    a[j] = tmp;
                }
            }
        }
    }

    void show(const char* msg) const {
        cout << msg << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << a[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
};

void transform(BoolMatrix& A, const BoolMatrix& B) {
    A = A || B;
}

int main() {
    srand(time(0));

    BoolMatrix A(3, 4);
    BoolMatrix B(3, 4);

    A.show("Матриця A:");
    B.show("Матриця B:");

    BoolMatrix C = A || B;
    C.show("A OR B:");

    BoolMatrix D = A && B;
    D.show("A AND B:");

    BoolMatrix E = !A;
    E.show("NOT A:");

    cout << "Кількість одиниць у A: " << A.countOnes() << endl << endl;

    cout << "A після лексикографічного сортування:" << endl;
    A.sortRowsLexicographically();
    A.show("A:");

    transform(A, B);
    A.show("A = A OR B після трансформації:");

    return 0;
}
