# Homework 1 - Ackermann Function 遞迴與非遞迴

## 1. 解題說明

### 1.1 問題描述

本題要求實作經典的阿克曼函數（Ackermann Function）A(m,n)。

阿克曼函數的定義如下：

$$
A(m,n)=
\begin{cases}
n+1 & \text{if } m=0 \\
A(m-1,1) & \text{if } m>0,\ n=0 \\
A(m-1,A(m,n-1)) & \text{if } m>0,\ n>0
\end{cases}
$$

阿克曼函數是一個成長速度非常快的函數，當輸入數值增加時，所需要的運算次數也會快速增加。

本次作業分別實作：

1. **遞迴版本（Recursive）**
2. **非遞迴版本（Non-recursive）**

並讓兩種方法使用相同的輸入，最後比較兩者的計算結果是否相同。

---

### 1.2 解題策略

#### 遞迴版本

遞迴版本直接依照阿克曼函數的數學定義實作。

當 `m == 0` 時：

$$
A(0,n)=n+1
$$

當 `n == 0` 時：

$$
A(m,0)=A(m-1,1)
$$

其他情況：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

因此可以直接使用函式自己呼叫自己的方式完成。

---

#### 非遞迴版本

非遞迴版本不能直接使用函式遞迴，因此使用 Stack（堆疊）模擬遞迴過程。

主要步驟如下：

1. 建立動態陣列作為 Stack。
2. 將初始的 `m` 放入 Stack。
3. 使用 `while` 迴圈處理 Stack。
4. 每次從 Stack 取出一個 `m`。
5. 根據 Ackermann 函數的三種條件進行處理。
6. 必要時將新的 `m` 放回 Stack。
7. 當 Stack 清空時，代表計算完成。
8. 回傳最後的 `n`。

---

### 1.3 遞迴與非遞迴的關係

遞迴版本會由系統自動使用 Call Stack 保存每一次函式呼叫。

非遞迴版本則自行建立 Stack，將原本系統需要保存的資訊交給自己管理。

因此兩種方法雖然寫法不同，但目的都是完成相同的 Ackermann 函數。

---

## 2. 程式實作

本程式同時包含遞迴版本與非遞迴版本。

```cpp
#include <iostream>

using namespace std;
// 遞迴版本
int recursive(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return recursive(m - 1, 1);
    }
    else {
        return recursive(m - 1, recursive(m, n - 1));
    }
}
// Stack Push
void push(int*& stack, int& top, int& capacity, int value) {
    // Stack 空間不足時，容量加倍
    if (top >= capacity - 1) {
        int newCapacity = capacity * 2;
        int* newStack = new int[newCapacity];
        // 複製原本 Stack 的資料
        for (int i = 0; i <= top; i++) {
            newStack[i] = stack[i];
        }
        // 釋放舊記憶體
        delete[] stack;
        stack = newStack;
        capacity = newCapacity;
    }
    stack[++top] = value;
}
// Stack Pop
int pop(int* stack, int& top) {
    return stack[top--];
}
// 非遞迴版本
int nonRecursive(int m, int n) {
    int capacity = 16;
    int top = -1;
    // 建立 Stack
    int* stack = new int[capacity];
    // 將初始 m 放入 Stack
    push(stack, top, capacity, m);
    while (top >= 0) {
        m = pop(stack, top);
        // A(0,n) = n + 1
        if (m == 0) {
            n++;
        }
        // A(m,0) = A(m-1,1)
        else if (n == 0) {
            push(stack, top, capacity, m - 1);
            n = 1;
        }
        // A(m,n) = A(m-1,A(m,n-1))
        else {
            n--;
            // 外層
            push(stack, top, capacity, m - 1);
            // 內層
            push(stack, top, capacity, m);
        }
    }
    // 釋放記憶體
    delete[] stack;
    return n;
}
int main() {
    int m, n;
    cin >> m >> n;
    // 遞迴版本
    cout << "Recursive: "
         << recursive(m, n) << endl;
    // 非遞迴版本
    cout << "Non-recursive: "
         << nonRecursive(m, n) << endl;
    return 0;
}
```

---

## 3. 效能分析

### 3.1 遞迴版本時間複雜度

遞迴版本會按照 Ackermann 函數的定義進行大量函式呼叫。

例如：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

一個函式呼叫可能產生更多函式呼叫，因此隨著 $m$、$n$ 增加，運算量會快速增加。

因此遞迴版本的時間複雜度與 Ackermann 函數本身的展開次數有關，可以表示為：

$$
O(T(m,n))
$$

其中 $T(m,n)$ 表示遞迴展開所需要的函式呼叫數量。

---

### 3.2 非遞迴版本時間複雜度

非遞迴版本使用 `while` 迴圈及 Stack 模擬遞迴。

每次 `pop` 的時間複雜度為：

$$
O(1)
$$

一般情況下 `push` 的時間複雜度也是：

$$
O(1)
$$

當 Stack 空間不足時，需要重新配置陣列並複製資料，單次擴充為：

$$
O(k)
$$

其中 $k$ 為當時 Stack 中的資料數量。

由於 Stack 容量每次加倍，因此整體具有攤銷效果。

不過 Ackermann 函數本身的運算量仍然非常大，因此非遞迴版本的整體時間複雜度仍可表示為：

$$
O(T(m,n))
$$

也就是說，改成非遞迴並不會改變 Ackermann 函數本身的巨大運算量。

---

### 3.3 遞迴版本空間複雜度

遞迴版本會使用系統 Call Stack 保存函式呼叫。

假設最大的遞迴深度為 $D$，則空間複雜度為：

$$
O(D)
$$

當遞迴深度過深時，可能發生 Stack Overflow。

---

### 3.4 非遞迴版本空間複雜度

非遞迴版本使用自行建立的 Stack。

假設計算過程中 Stack 的最大深度為 $S$，則空間複雜度為：

$$
O(S)
$$

因此兩種版本在概念上都需要保存尚未完成的運算狀態，只是遞迴版本由系統管理 Call Stack，而非遞迴版本由程式自己管理 Stack。

---

### 3.5 效能比較

| 項目 | 遞迴版本 | 非遞迴版本 |
|---|---|---|
| 時間複雜度 | $O(T(m,n))$ | $O(T(m,n))$ |
| 空間複雜度 | $O(D)$ | $O(S)$ |
| 是否使用函式遞迴 | 是 | 否 |
| 是否使用 Stack | 系統 Call Stack | 自訂 Stack |
| 程式碼難度 | 較簡單 | 較複雜 |
| 記憶體管理 | 系統管理 | 自行管理 |

---

## 4. 測試與驗證

### 4.1 測試環境

- 作業系統：Windows
- 程式語言：C++
- 編譯器：g++
- C++ 標準：C++21

---

### 4.2 測試一

輸入：

```shell
1 2
```

預期結果：

$$
A(1,2)=4
$$

遞迴版本與非遞迴版本皆得到 `4`，結果相同。

---

### 4.3 測試二

輸入：

```shell
2 2
```

預期結果：

$$
A(2,2)=7
$$

兩種版本皆得到 `7`，結果相同。

---

### 4.4 測試三

輸入：

```shell
3 2
```

預期結果：

$$
A(3,2)=29
$$

兩種版本皆得到 `29`，結果相同。

---

### 4.5 測試結果整理

| 測試編號 | 輸入 | 遞迴結果 | 非遞迴結果 | 是否相同 |
|---|---|---:|---:|---|
| 1 | `1 2` | 4 | 4 | 是 |
| 2 | `2 2` | 7 | 7 | 是 |
| 3 | `3 2` | 29 | 29 | 是 |

從測試結果可以確認，遞迴版本與非遞迴版本在相同輸入下皆能得到相同的 Ackermann 函數結果。

---

## 5. 申論及開發報告

### 5.1 為什麼使用遞迴？

Ackermann 函數本身就是使用遞迴方式定義，因此直接按照數學公式實作非常直觀。

例如：

```cpp
return recursive(m - 1, recursive(m, n - 1));
```

可以直接對應到：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

優點是程式碼比較簡單，也容易與數學公式對照。

但是遞迴的缺點是會大量使用系統 Call Stack，當遞迴深度太深時可能發生 Stack Overflow。

---

### 5.2 為什麼使用 Stack？

非遞迴版本不能直接呼叫自己，因此需要使用其他方式保存還沒有完成的運算狀態。

Stack 具有 LIFO（Last In, First Out）的特性，與遞迴函式呼叫的先進後出特性相似，因此可以用來模擬遞迴。

原本由系統自動管理的 Call Stack，改成由程式自行建立 Stack 管理。

---

### 5.3 遞迴與非遞迴的比較

透過這次實作，可以發現兩種方法雖然程式寫法不同，但最後都可以得到相同的結果。

遞迴版本的優點是程式碼簡單，而且非常接近 Ackermann 函數的數學定義。

非遞迴版本雖然程式比較複雜，但是可以讓我們了解遞迴背後其實也是利用 Stack 保存函式執行狀態。

因此，非遞迴版本可以讓我更深入了解 Stack 在演算法中的實際用途。

---

### 5.4 開發過程遇到的問題

實作非遞迴版本時，最困難的部分是確認 Stack 中資料的順序。

在：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

這個情況中，必須先完成內層的 $A(m,n-1)$，再處理外層的 $A(m-1,\text{結果})$。

因為 Stack 是 LIFO，所以 Push 的順序必須特別注意。

另外，當：

$$
A(m,0)=A(m-1,1)
$$

時，除了將 `m - 1` 放入 Stack，也必須將 `n` 設為 `1`。

經過多次測試後，確認遞迴版本與非遞迴版本的結果相同。

---
