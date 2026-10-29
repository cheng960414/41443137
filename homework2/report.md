# 41443137
# Homework 2 -多像式加法&乘法運算 
## 1. 解題說明
做指數次方相加與相乘

## 解題思路

利用陣列來存取使用者輸入的係數(coef)和指數(exp),

加法:

將指數項進行比較,當指數項有讀取到相同數字時,將兩者的係數項進行相加,

相乘:

先將A的第一個數對B所有數字相乘,係數相乘,指數相加,
## 2. 實作程式
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Polynomial;//前置宣告

class Term {
    friend class Polynomial;
private:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
private:
    Term* termArray; //儲存非零項的動態陣列
    int capacity;    //陣列容量
    int terms;       //實際非零項數量
public:
    Polynomial Add(const Polynomial& b);
    Polynomial Mult(const Polynomial& b);
    void Readinput();
    void show();
    void clear() {
        delete[] termArray;
        capacity = 2;
        terms = 0;
        termArray = new Term[capacity];
    }
    Polynomial() :capacity(2), terms(0) {
        termArray = new Term[capacity];
    }
    void newTerm(const float theCoef, const int theExp) {
        if (theCoef == 0)return;
        if (terms == capacity) {
            capacity *= 2;
            Term* temp = new Term[capacity];
            copy(termArray, termArray + terms, temp);
            delete[]termArray;
            termArray = temp;
        }
        termArray[terms].coef = theCoef;
        termArray[terms++].exp = theExp;
    }

};
//數字相加
Polynomial Polynomial::Add(const Polynomial& b) {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms))
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    for (; aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}
//數字相乘
Polynomial Polynomial::Mult(const Polynomial& b) {
    Polynomial c;
    for (int i = 0; i < terms; i++) {
        Polynomial temp;
        for (int j = 0; j < b.terms; j++) {
            temp.newTerm(termArray[i].coef * b.termArray[j].coef,
                termArray[i].exp + b.termArray[j].exp);
        }
        c = c.Add(temp);
    }
    return c;
}
//輸入數字
void Polynomial::Readinput() {
    clear();
    int numtemp;
    cin >> numtemp;
    for (int i = 0; i < numtemp; i++) {
        float coef;
        int exp;
        cin >> coef >> exp;
        newTerm(coef, exp);
    }
}
void Polynomial::show() {
    if (terms == 0) {
        cout << "0\n";
        return;
    }
    for (int i = 0; i < terms; ++i) {
        if (i > 0 && termArray[i].coef > 0) cout << " + ";

        if (termArray[i].exp == 0) {
    cout << termArray[i].coef;
        }
        else if (termArray[i].exp == 1) {
           cout << termArray[i].coef << "x";
        }
        else {
            cout << termArray[i].coef << "x^" << termArray[i].exp;
        }
    }
    cout << "\n";
}

void showMenu() {
    cout << "\n Polynomial 選單 \n";
        cout << "1. 顯示 A、B\n";
        cout << "2. A + B\n"; 
        cout << "3. A * B\n";
        cout << "0.結束程式\n";
        cout << "選擇：";
}


int main() {
    Polynomial A, B;
    cout << "!要先輸入需要幾個係數項!\n";
    cout << "輸入A多項式 :";
    A.Readinput();
    cout << "輸入B多項式 :";
    B.Readinput();
    A.show();
    B.show();

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) break;

        cout << "\n";
        if (choice == 0) break;

        switch (choice) {
        case 1:
            cout << "A(x) = ";  A.show();
            cout << "B(x) = ";  A.show();
            break;
        case 2: {
            Polynomial C = A.Add(B);
            cout << "A(x) = ";  A.show();
            cout << "B(x) = ";  B.show();
            cout << "A + B = ";  C.show();
            break;
        }
        case 3: {
            Polynomial C = A.Mult(B);
            cout << "A * B = "; C.show();
            break;
          }
        }
    }
    return 0;
```
