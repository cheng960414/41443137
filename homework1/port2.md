# Homework 1 - Ackermann Function

## 1. 解題說明

### 問題描述
本題目要求實現經典的**阿克曼函數（Ackermann's Function）** $A(m, n)$。其數學定義如下：
$$A(m, n) = \begin{cases} n + 1 & \text{if } m = 0 \\ A(m - 1, 1) & \text{if } n = 0 \\ A(m - 1, A(m, n - 1)) & \text{otherwise} \end{cases}$$

### 解題策略
1. **模擬系統 Call Stack**：利用自訂陣列 Stack 儲存 $m$ 的數值，將雙重遞迴轉換為迴圈。
2. **狀態轉化規則**：
   - $m == 0$：$n = n + 1$。
   - $n == 0$：壓入 $m - 1$，並將 $n$ 設為 1。
   - $m > 0$ 且 $n > 0$：依序壓入 $m - 1$ 與 $m$，將 $n$ 更新為 $n - 1$。
3. **動態記憶體管理**：實作 `push_stack` 與 `pop_stack`，空間不足時自動倍增，計算結束後 `delete[]` 釋放記憶體。

---

## 2. 程式實作

```cpp
#include <iostream>

using namespace std;

void push_stack(int*& s, int& top, int& capacity, int val) {
    if (top >= capacity - 1) {
        int new_capacity = capacity * 2;
        int* new_s = new int[new_capacity];
        for (int i = 0; i <= top; i++) {
            new_s[i] = s[i];
        }
        delete[] s;
        s = new_s;
        capacity = new_capacity;
    }
    s[++top] = val;
}

int pop_stack(int* s, int& top) {
    return s[top--];
}

int a(int m, int n) {
    int capacity = 16;
    int top = -1;
    int* s = new int[capacity];

    push_stack(s, top, capacity, m);

    while (top >= 0) {
        m = pop_stack(s, top);

        if (m == 0) {
            n++;
        }
        else if (n == 0) {
            push_stack(s, top, capacity, m - 1);
            n = 1;
        }
        else {
            n--;
            push_stack(s, top, capacity, m - 1);
            push_stack(s, top, capacity, m);
        }
    }

    delete[] s;
    return n;
}

int main() {
    int m, n;
    if (cin >> m >> n) {
        cout << a(m, n) << endl;
    }
    return 0;
}
