# Homework 1 - Ackermann Function (遞迴與非遞迴實作)

## 1. 解題說明

### 問題描述
本題目要求實現經典的**阿克曼函數（Ackermann's Function）** $A(m, n)$。其數學遞迴定義如下：
$$A(m, n) = \begin{cases} n + 1 & \text{if } m = 0 \\ A(m - 1, 1) & \text{if } n = 0 \\ A(m - 1, A(m, n - 1)) & \text{otherwise} \end{cases}$$

阿克曼函數以其極快的增長速度著稱，常用於測試電腦系統的遞迴處理能力與 Stack 限制。本作業的主要目標為撰寫**非遞迴（Non-recursive / Iterative）**演算法來計算此函數。

### 解題策略
1. **模擬系統 Call Stack**：傳統遞迴會在系統呼叫堆疊（Call Stack）中保存每一層的區域變數。本題利用自訂的陣列 Stack 儲存 $m$ 的數值，將雙重遞迴轉換為迴圈結構。
2. **狀態轉化規則**：
   - 當從 Stack 彈出（Pop）的 $m == 0$ 時：代表已到達基底條件，將 $n$ 遞增 1（$n = n + 1$）。
   - 當 $n == 0$ 時：對應 $A(m - 1, 1)$，將 $m - 1$ 壓入（Push）Stack，並將 $n$ 重置為 1。
   - 當 $m > 0$ 且 $n > 0$ 時：對應 $A(m - 1, A(m, n - 1))$。由於 Stack 為後進先出（LIFO），先壓入外層的 $m - 1$，再壓入內層的 $m$，同時將 $n$ 更新為 $n - 1$。
3. **動態記憶體管理**：實作自訂 `push_stack` 與 `pop_stack`，當 Stack 容量不足時自動倍增（Resize），並於計算結束後釋放動態記憶體（`delete[]`），防止 Memory Leak。

---

## 2. 程式實作

```cpp
#include <iostream>

using namespace std;

// 壓棧函式：若空間不足則動態擴充 capacity
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

// 彈棧函式
int pop_stack(int* s, int& top) {
    return s[top--];
}

// 非遞迴計算 Ackermann 函數
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

    delete[] s; // 釋放動態宣告之記憶體
    return n;
}

int main() {
    int m, n;
    if (cin >> m >> n) {
        cout << a(m, n) << endl;
    }
    return 0;
}
3. 效能分析時間複雜度：$O(A(m, n))$阿克曼函數的運算次數完全取決於函數本身的輸出數值 $A(m, n)$。當 $m = 1$ 時：$A(1, n) = n + 2$，時間複雜度為 $O(n)$。當 $m = 2$ 時：$A(2, n) = 2n + 3$，時間複雜度為 $O(n)$。當 $m = 3$ 時：$A(3, n) = 2^{(n+3)} - 3$，時間複雜度呈指數級成長 $O(2^n)$。當 $m = 4$ 時：$A(4, n)$ 的成長速度為超指數級（Tetration），複雜度呈現極劇烈的爆發性成長。整體時間複雜度可表示為 $O(A(m, n))$。空間複雜度：$O(A(m, n))$空間分析：本程式採用自訂動態陣列作為堆疊（Stack）。最壞情況下（如計算內層遞迴展開時），Stack 的最大深度會正比於遞迴呼叫的總次數。整體空間複雜度為 $O(A(m, n))$。透過動態擴充機制，最大使用空間僅受限於實體記憶體限制，不會像遞迴版本輕易引發 Call Stack Overflow。4. 測試與驗證測試環境與編譯指令作業系統：Windows / Linux編譯器：g++
