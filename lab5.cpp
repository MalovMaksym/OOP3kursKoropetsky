//1
//main.cpp
#include <iostream>
#include "video.h"
using namespace std;

int main() {
    int n;
    cout << "=== VIDEO COLLECTION ===\n\n";
    cout << "Скільки фільмів ви хочете ввести? ";
    cin >> n;
    
    VIDEO* collection = new VIDEO[n];
    
    cout << "\n=== ВВЕДЕННЯ ДАНИХ ===\n";
    for (int i = 0; i < n; i++) {
        cout << "\nФільм " << (i + 1) << ":\n";
        collection[i].input();
    }
    
    cout << "\n=== СПИСОК ВСІХ ФІЛЬМІВ ===\n";
    for (int i = 0; i < n; i++) {
        collection[i].display();
    }
    
    cin.ignore();
    string searchRezhiser;
    cout << "\n=== ПОШУК ЗА РЕЖИСЕРОМ ===\n";
    cout << "Введіть ім'я режисера: ";
    getline(cin, searchRezhiser);
    
    cout << "\nФільми режисера \"" << searchRezhiser << "\":\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (collection[i].getRezhiser() == searchRezhiser) {
            collection[i].display();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Фільми цього режисера не знайдено.\n";
    }
    
    delete[] collection;
    return 0;
}

//video.h 

#ifndef VIDEO_H
#define VIDEO_H

#include <string>
using namespace std;

class VIDEO {
private:
    string name;
    int year;
    string genre;
    string rezhiser;

public:
    VIDEO();
    VIDEO(string n, int y, string g, string r);
    
    void setName(string n);
    void setYear(int y);
    void setGenre(string g);
    void setRezhiser(string r);
    
    string getName() const;
    int getYear() const;
    string getGenre() const;
    string getRezhiser() const;
    
    void input();
    void display() const;
};

#endif

//video.cpp
#include "video.h"
#include <iostream>
using namespace std;

VIDEO::VIDEO() : name(""), year(0), genre(""), rezhiser("") {}

VIDEO::VIDEO(string n, int y, string g, string r) 
    : name(n), year(y), genre(g), rezhiser(r) {}

void VIDEO::setName(string n) { name = n; }
void VIDEO::setYear(int y) { year = y; }
void VIDEO::setGenre(string g) { genre = g; }
void VIDEO::setRezhiser(string r) { rezhiser = r; }

string VIDEO::getName() const { return name; }
int VIDEO::getYear() const { return year; }
string VIDEO::getGenre() const { return genre; }
string VIDEO::getRezhiser() const { return rezhiser; }

void VIDEO::input() {
    cin.ignore();
    cout << "Назва фільму: ";
    getline(cin, name);
    cout << "Рік випуску: ";
    cin >> year;
    cin.ignore();
    cout << "Жанр: ";
    getline(cin, genre);
    cout << "Режисер: ";
    getline(cin, rezhiser);
}

void VIDEO::display() const {
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "Назва: " << name << endl;
    cout << "Рік: " << year << endl;
    cout << "Жанр: " << genre << endl;
    cout << "Режисер: " << rezhiser << endl;
}

//2 
#include <iostream>
#include <string>
using namespace std;

class B1 {
protected:
    int dataB1;
public:
    B1(int val = 0) : dataB1(val) {
        cout << "Конструктор B1: " << dataB1 << endl;
    }
    
    void show() const {
        cout << "B1 data: " << dataB1 << endl;
    }
};

class D1 : public B1 {
protected:
    int dataD1;
public:
    D1(int valB1 = 0, int valD1 = 0) : B1(valB1), dataD1(valD1) {
        cout << "Конструктор D1: " << dataD1 << endl;
    }
    
    void show() const {
        cout << "--- Об'єкт D1 ---" << endl;
        B1::show();
        cout << "D1 data: " << dataD1 << endl;
    }
};

class D2 : private B1 {
protected:
    int dataD2;
public:
    D2(int valB1 = 0, int valD2 = 0) : B1(valB1), dataD2(valD2) {
        cout << "Конструктор D2: " << dataD2 << endl;
    }
    
    void show() const {
        cout << "--- Об'єкт D2 ---" << endl;
        B1::show();
        cout << "D2 data: " << dataD2 << endl;
    }
};

class B2 : public B1 {
protected:
    int dataB2;
public:
    B2(int valB1 = 0, int valB2 = 0) : B1(valB1), dataB2(valB2) {
        cout << "Конструктор B2: " << dataB2 << endl;
    }
    
    void show() const {
        cout << "--- Об'єкт B2 ---" << endl;
        B1::show();
        cout << "B2 data: " << dataB2 << endl;
    }
};


class D4 : public D1, public D2, public B2 {
private:
    int dataD4;
public:
    D4(int valB1_D1, int valD1, int valB1_D2, int valD2, 
       int valB1_B2, int valB2, int valD4) 
        : D1(valB1_D1, valD1), 
          D2(valB1_D2, valD2), 
          B2(valB1_B2, valB2), 
          dataD4(valD4) {
        cout << "Конструктор D4: " << dataD4 << endl;
    }
    
    void show() const {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║       Об'єкт D4 (повний)          ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        
        cout << "\nВід D1:" << endl;
        D1::show();
        
        cout << "\nВід D2:" << endl;
        D2::show();
        
        cout << "\nВід B2:" << endl;
        B2::show();
        
        cout << "\nВласні дані D4:" << endl;
        cout << "D4 data: " << dataD4 << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    }
};

int main() {
    cout << "╔═══════════════════════════════════════════╗" << endl;
    cout << "║  Демонстрація ієрархії успадкування (15) ║" << endl;
    cout << "╚═══════════════════════════════════════════╝" << endl;
    cout << "\nСхема: B1 -> D1, D2(private), B2 -> D4\n" << endl;
    
    cout << "\n=== Створення об'єкта D1 ===" << endl;
    D1 objD1(10, 20);
    objD1.show();
    
    cout << "\n\n=== Створення об'єкта D2 ===" << endl;
    D2 objD2(30, 40);
    objD2.show();
    
    cout << "\n\n=== Створення об'єкта B2 ===" << endl;
    B2 objB2(50, 60);
    objB2.show();
    
    cout << "\n\n=== Створення об'єкта D4 (множинне успадкування) ===" << endl;
    D4 objD4(100, 200, 300, 400, 500, 600, 700);
    objD4.show();
    
    return 0;
}
