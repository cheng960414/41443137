# 41443137
# Homework 2 -多像式加法&乘法運算 
## 1. 解題說明
做指數次方相加與相乘

## 解題思路

利用陣列來存取使用者輸入的係數和指數

加法:
將指數項進行比較,當指數項有讀取到相同數字時,將兩者的係數項進行相加
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
    Term *termArray; //儲存非零項的動態陣列
    int capacity;    //陣列容量
    int terms;       //實際非零項數量
public:
    Polynomial Add (const Polynomial& b);
    Polynomial Mult(const Polynomial& b);
    void Readinput();
    void clear(){
        delete[] termArray;
        capacity=2;
        terms=0;
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
void Polynomial::Readinput(){
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
int main() {
    Polynomial A, B;
    cout << "輸入A多項式 :";
    A.Readinput();
    cout << "輸入B多項式 :";
    B.Readinput();

}
```
