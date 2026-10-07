# Homework 1 - Ackermann Function（阿克曼函數非遞迴實作）

## 1. 解題說明

### 1.1 問題描述

本題要求實作阿克曼函數（Ackermann Function）$A(m,n)$，並且不能直接使用遞迴的方式完成。

阿克曼函數的定義如下：

$$
A(m,n)=
\begin{cases}
n+1 & \text{if } m=0 \\
A(m-1,1) & \text{if } m>0,\ n=0 \\
A(m-1,A(m,n-1)) & \text{if } m>0,\ n>0
\end{cases}
$$

阿克曼函數是一個成長速度非常快的函數，即使輸入的數值不大，也可能產生大量的函數呼叫。

本題的重點是將原本的遞迴運算改成**非遞迴（Non-recursive）**的方式，利用 Stack（堆疊）模擬原本函式呼叫的過程。

---

### 1.2 解題策略

本題使用自行建立的動態陣列 Stack 來模擬系統的 Call Stack。

程式的主要流程如下：

1. 建立一個動態陣列作為 Stack。
2. 將輸入的 `m` 放入 Stack。
3. 使用 `while` 迴圈持續處理 Stack 中的資料。
4. 每次從 Stack 取出一個 `m`。
5. 根據 Ackermann 函數的三種條件進行處理。
6. 必要時將新的 `m` 放回 Stack。
7. 當 Stack 清空時，代表所有運算完成，此時 `n` 就是答案。
8. 最後釋放動態配置的記憶體。

---

### 1.3 三種情況的處理

#### 情況一：`m == 0`

根據 Ackermann 函數：

$$
A(0,n)=n+1
$$

因此直接將 `n` 加 1。

```cpp
if (m == 0) {
    n++;
}
```

---

#### 情況二：`m > 0` 且 `n == 0`

根據：

$$
A(m,0)=A(m-1,1)
$$

所以將 `m - 1` 放入 Stack，並將 `n` 設為 1。

```cpp
else if (n == 0) {
    push_stack(s, top, capacity, m - 1);
    n = 1;
}
```

---

#### 情況三：`m > 0` 且 `n > 0`

根據：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

需要先處理內層的：

$$
A(m,n-1)
$$

再處理外層的：

$$
A(m-1,\text{結果})
$$

因此利用 Stack 的 **LIFO（Last In, First Out）** 特性，將兩個 `m` 依照適當的順序放入 Stack。

```cpp
else {
    n--;
    push_stack(s, top, capacity, m - 1);
    push_stack(s, top, capacity, m);
}
```

由於 Stack 後進先出，所以最後放入的 `m` 會優先被取出，可以模擬原本的遞迴流程。

---

## 2. 程式實作

以下為本次作業的完整程式碼：

```cpp
#include <iostream>

using namespace std;

// 將資料放入 Stack
// 當 Stack 空間不足時，自動將容量加倍
void push_stack(int*& s, int& top, int& capacity, int val) {

    if (top >= capacity - 1) {

        int new_capacity = capacity * 2;

        int* new_s = new int[new_capacity];

        // 複製原本 Stack 的資料
        for (int i = 0; i <= top; i++) {
            new_s[i] = s[i];
        }

        // 釋放原本的記憶體
        delete[] s;

        // 將 Stack 指向新的陣列
        s = new_s;

        capacity = new_capacity;
    }

    s[++top] = val;
}


// 從 Stack 取出資料
int pop_stack(int* s, int& top) {
    return s[top--];
}


// 非遞迴 Ackermann Function
int a(int m, int n) {

    int capacity = 16;
    int top = -1;

    // 建立動態 Stack
    int* s = new int[capacity];

    // 將初始的 m 放入 Stack
    push_stack(s, top, capacity, m);

    while (top >= 0) {

        // 取出目前要處理的 m
        m = pop_stack(s, top);

        // A(0,n) = n + 1
        if (m == 0) {
            n++;
        }

        // A(m,0) = A(m-1,1)
        else if (n == 0) {

            push_stack(s, top, capacity, m - 1);

            n = 1;
        }

        // A(m,n) = A(m-1,A(m,n-1))
        else {

            n--;

            // 放入外層的 m - 1
            push_stack(s, top, capacity, m - 1);

            // 放入內層的 m
            push_stack(s, top, capacity, m);
        }
    }

    // 釋放動態記憶體
    delete[] s;

    return n;
}


int main() {

    int m, n;

    cin >> m >> n;

    cout << a(m, n) << endl;

    return 0;
}
```

---

## 3. 效能分析

### 3.1 時間複雜度

本程式使用 `while` 迴圈處理 Stack 中的狀態，每次迴圈會執行一次 `pop_stack()`，並依照條件決定是否執行 `push_stack()`。

`push_stack()` 在 Stack 尚有空間時只需要：

```cpp
s[++top] = val;
```

因此單次 Push 的時間複雜度為：

$$
O(1)
$$

但是當 Stack 容量不足時，需要建立新的陣列並將原本的資料全部複製過去，此時單次擴充的成本為：

$$
O(k)
$$

其中 $k$ 為當時 Stack 中的資料數量。

由於 Stack 的容量每次加倍，因此動態擴充的總成本具有攤銷特性，平均每次 Push 的成本仍可視為：

$$
O(1)
$$

---

Ackermann 函數本身的運算量會隨著輸入值快速增加。

例如：

$$
A(0,n)=n+1
$$

$$
A(1,n)=n+2
$$

$$
A(2,n)=2n+3
$$

$$
A(3,n)=2^{n+3}-3
$$

因此隨著 $m$ 增加，實際需要處理的 Stack 狀態數量會快速增加。

若令 $T(m,n)$ 表示本程式處理 Ackermann 函數所需要的迴圈次數，則其主要受到 Ackermann 函數展開次數影響。

因此本程式的整體時間複雜度可表示為：

$$
O(T(m,n))
$$

其中 $T(m,n)$ 會隨 Ackermann 函數的輸入快速成長。

---

### 3.2 空間複雜度

本程式使用動態陣列建立 Stack。

假設運算過程中 Stack 的最大使用量為 $S$，則 Stack 所需要的空間為：

$$
O(S)
$$

此外，程式沒有使用遞迴，因此不會額外使用系統 Call Stack 儲存大量遞迴函式。

因此本程式的空間複雜度主要取決於：

$$
O(S)
$$

其中 $S$ 為 Ackermann 函數計算過程中的最大 Stack 深度。

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
$ g++ main.cpp --std=c++21 -o main.exe
$ .\main.exe
1 2
4
```

其中：

```text
1 2
```

為使用者輸入。

```text
4
```

為程式輸出。

根據 Ackermann 函數：

$$
A(1,2)=4
$$

因此結果正確。

---

### 4.3 測試二

輸入：

```shell
$ .\main.exe
2 2
7
```

根據 Ackermann 函數：

$$
A(2,2)=7
$$

因此結果正確。

---

### 4.4 測試三

輸入：

```shell
$ .\main.exe
3 2
29
```

根據 Ackermann 函數：

$$
A(3,2)=29
$$

因此結果正確。

---

### 4.5 測試結果

| 測試編號 | 輸入 `m n` | 預期輸出 | 實際輸出 | 結果 |
|---|---|---:|---:|---|
| 1 | `1 2` | `4` | `4` | Pass |
| 2 | `2 2` | `7` | `7` | Pass |
| 3 | `3 2` | `29` | `29` | Pass |

由測試結果可以確認程式可以正確計算不同輸入的 Ackermann 函數。

---

## 5. 申論及開發報告

### 5.1 為什麼使用 Stack？

Ackermann 函數是一個具有多層遞迴結構的函數。

一般使用遞迴方式實作時，每一次函式呼叫都會將相關資訊放到系統的 Call Stack 中。

本題要求不能使用遞迴，因此可以使用自己建立的 Stack 來模擬 Call Stack。

Stack 具有 **LIFO（Last In, First Out）** 的特性，而遞迴函式的呼叫與返回過程也具有類似的先進後出特性，因此非常適合用來模擬遞迴。

---

### 5.2 使用動態陣列的原因

本程式使用動態陣列建立 Stack，而不是使用固定大小的陣列。

初始容量設定為：

```cpp
int capacity = 16;
```

當 Stack 空間不足時，將容量增加為原本的兩倍：

```cpp
int new_capacity = capacity * 2;
```

再將原本的資料複製到新的陣列。

這樣可以讓 Stack 根據實際需求增加容量，而不需要一開始就設定非常大的陣列。

---

### 5.3 開發過程遇到的問題

在開發過程中，最主要遇到的問題是如何將原本的遞迴式轉換成 Stack 操作。

尤其是：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

這一部分需要先完成內層的 $A(m,n-1)$，再處理外層的 $A(m-1,\text{結果})$。

因此必須仔細確認 Stack 的 Push 順序。

另外，在處理：

$$
A(m,0)=A(m-1,1)
$$

時，也需要記得將 `n` 設定為 `1`。

如果沒有更新 `n`，可能會造成錯誤結果或無限迴圈。

---

### 5.4 動態記憶體管理

由於本程式使用：

```cpp
new int[capacity]
```

建立動態陣列，因此在程式結束後必須使用：

```cpp
delete[] s;
```

釋放記憶體。

在 Stack 擴充時，也需要先釋放舊的陣列，再讓指標指向新的陣列。

另外，`push_stack()` 使用：

```cpp
int*& s
```

讓函式可以直接修改外部的 Stack 指標。

當建立新的陣列後：

```cpp
s = new_s;
```

外部的 `s` 也會同步指向新的記憶體位置。

---

### 5.5 總結

透過這次作業，我了解到遞迴並不是唯一可以解決遞迴問題的方法。

雖然 Ackermann 函數原本是使用遞迴定義，但是可以利用 Stack 的 LIFO 特性模擬函式呼叫的過程，再配合 `while` 迴圈完成非遞迴版本。

這次實作也讓我更加熟悉 Stack、動態記憶體配置、指標與參考的使用方式。

在實作過程中，最大的困難是理解 Ackermann 函數的執行順序，以及如何將遞迴狀態轉換成 Stack 中的資料。經過測試不同的輸入後，確認程式可以得到正確結果。

因此，本次作業除了讓我了解 Ackermann 函數，也讓我更加理解**資料結構中的 Stack 如何實際應用在演算法設計中**。
