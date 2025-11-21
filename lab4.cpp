//1
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
    
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
    
    int getDaysInMonth(int m, int y) const {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && isLeapYear(y)) return 29;
        return days[m - 1];
    }

public:
    Date() : year(2000), month(1), day(1) {}
    
    void input() {
        cout << "Введіть рік: ";
        cin >> year;
        cout << "Введіть місяць (1-12): ";
        cin >> month;
        cout << "Введіть день: ";
        cin >> day;
        
        if (month < 1 || month > 12) {
            cout << "Помилка: місяць має бути від 1 до 12\n";
            month = 1;
        }
        if (day < 1 || day > getDaysInMonth(month, year)) {
            cout << "Помилка: невірний день для цього місяця\n";
            day = 1;
        }
    }
    
    void display() const {
        cout << "Дата: " << day << "." 
             << (month < 10 ? "0" : "") << month << "." 
             << year << endl;
    }
    
    string getSeason() const {
        if (month == 12 || month <= 2) return "Зима";
        else if (month >= 3 && month <= 5) return "Весна";
        else if (month >= 6 && month <= 8) return "Літо";
        else return "Осінь";
    }
    
    void displaySeason() const {
        cout << "Пора року: " << getSeason() << endl;
    }
};

int main() {
    Date date;
    
    cout << "=== Демонстрація роботи класу Date ===\n\n";
    
    date.input();
    cout << "\n";
    date.display();
    date.displaySeason();
    
    return 0;
}


//2
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
    
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
    
    int getDaysInMonth(int m, int y) const {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && isLeapYear(y)) return 29;
        return days[m - 1];
    }
    
    void normalize() {
        while (month > 12) {
            month -= 12;
            year++;
        }
        while (month < 1) {
            month += 12;
            year--;
        }
        
        while (day > getDaysInMonth(month, year)) {
            day -= getDaysInMonth(month, year);
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        while (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day += getDaysInMonth(month, year);
        }
        
        if (year < 1) year = 1;
    }

public:
    Date() : year(2000), month(1), day(1) {}
    
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        normalize();
    }
    
    ~Date() {
    }
    
    void input() {
        cout << "Введіть рік: ";
        cin >> year;
        cout << "Введіть місяць (1-12): ";
        cin >> month;
        cout << "Введіть день: ";
        cin >> day;
        normalize();
    }
    
    void display() const {
        cout << day << "." 
             << (month < 10 ? "0" : "") << month << "." 
             << year;
    }
    
    string getSeason() const {
        if (month == 12 || month <= 2) return "Зима";
        else if (month >= 3 && month <= 5) return "Весна";
        else if (month >= 6 && month <= 8) return "Літо";
        else return "Осінь";
    }

    Date operator+(const Date& other) const {
        return Date(year + other.year, month + other.month, day + other.day);
    }
    
    Date operator-(const Date& other) const {
        return Date(year - other.year, month - other.month, day - other.day);
    }
    
    Date& operator++() {
        year++;
        return *this;
    }
    
    Date operator++(int) {
        Date temp = *this;
        month++;
        normalize();
        return temp;
    }

    Date& operator--() {
        if (year > 1) year--;
        return *this;
    }
    

    Date operator--(int) {
        Date temp = *this;
        month--;
        normalize();
        return temp;
    }
    
    Date& operator+=(int dummy) {
        day++;
        normalize();
        return *this;
    }
    
    Date& operator-=(int dummy) {
        day--;
        normalize();
        return *this;
    }
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
    
    bool operator>(const Date& other) const {
        return !(*this < other) && !(*this == other);
    }
};

int main() {
    cout << "=== Демонстрація роботи розширеного класу Date ===\n\n";
    
    Date d1(2024, 5, 15);
    Date d2(2, 3, 10);
    
    cout << "Дата 1: "; d1.display(); cout << " (Сезон: " << d1.getSeason() << ")\n";
    cout << "Дата 2: "; d2.display(); cout << endl << endl;
    
    Date d3 = d1 + d2;
    cout << "d1 + d2 = "; d3.display(); cout << endl;
    
    Date d4 = d1 - d2;
    cout << "d1 - d2 = "; d4.display(); cout << endl << endl;
    
    cout << "Префіксний ++d1 (рік+1): "; (++d1).display(); cout << endl;
    
    
    Date d5(2024, 5, 15);
    cout << "Постфіксний d5++ (місяць+1): " << endl;
    cout << "  До: "; d5.display(); cout << endl;
    d5++;
    cout << "  Після: "; d5.display(); cout << endl << endl;
    
    
    Date d6(2024, 5, 15);
    cout << "Префіксний --d6 (рік-1): "; (--d6).display(); cout << endl;
    
    
    Date d7(2024, 5, 15);
    cout << "Постфіксний d7-- (місяць-1): " << endl;
    cout << "  До: "; d7.display(); cout << endl;
    d7--;
    cout << "  Після: "; d7.display(); cout << endl << endl;
    

    Date d8(2024, 5, 15);
    cout << "d8 += 1 (день+1): " << endl;
    cout << "  До: "; d8.display(); cout << endl;
    d8 += 1;
    cout << "  Після: "; d8.display(); cout << endl;
    
    d8 -= 1;
    cout << "d8 -= 1 (день-1): "; d8.display(); cout << endl << endl;
    

    Date d9(2024, 5, 15);
    Date d10(2025, 6, 20);
    
    cout << "Порівняння дат:\n";
    cout << "d9: "; d9.display(); cout << endl;
    cout << "d10: "; d10.display(); cout << endl;
    cout << "d9 < d10: " << (d9 < d10 ? "true" : "false") << endl;
    cout << "d9 == d10: " << (d9 == d10 ? "true" : "false") << endl;
    cout << "d9 > d10: " << (d9 > d10 ? "true" : "false") << endl;
    
    return 0;
}