# 冪集（Power Set）

## 1. 解題說明

### 1.1 問題描述

本題要實作「冪集（Power Set）」。

給定一個集合 \(S\)，其冪集 \(P(S)\) 是由集合 \(S\) 的**所有子集合**所組成的集合。

例如：

\[
S=\{a,b,c\}
\]

其冪集為：

\[
P(S)=
\{
\emptyset,
\{a\},
\{b\},
\{a,b\},
\{c\},
\{a,c\},
\{b,c\},
\{a,b,c\}
\}
\]

一個包含 \(n\) 個元素的集合，其冪集總共有：

\[
2^n
\]

個子集合。

因此本程式以 `{'a', 'b', 'c'}` 作為測試資料，最後應該產生：

\[
2^3=8
\]

個子集合。

---

### 1.2 解題策略

本題使用**遞迴（Recursion）**來產生冪集。

假設目前集合為：

```text
{a, b, c}
```

首先取出第一個元素 `a`，剩下：

```text
{b, c}
```

接著遞迴計算 `{b, c}` 的冪集。

當 `{b, c}` 的所有子集合產生後，再針對每一個子集合分成兩種情況：

1. 不加入 `a`
2. 加入 `a`

例如 `{b,c}` 的冪集為：

```text
{}
{b}
{c}
{b,c}
```

加入 `a` 後，就會產生：

```text
{}
{b}
{c}
{b,c}

{a}
{a,b}
{a,c}
{a,b,c}
```

最後就得到 `{a,b,c}` 的完整冪集。

---

### 1.3 遞迴終止條件

當集合為空集合時：

```cpp
if (S.empty()) {
    return { {} };
}
```

空集合的冪集只有一個元素，也就是空集合本身：

\[
P(\emptyset)=\{\emptyset\}
\]

因此可以將：

```text
{}
```

作為遞迴的 Base Case。

---

## 2. 程式實作

完整程式如下：

```cpp
#include <iostream>
#include <vector>

using namespace std;

// 遞迴函式：計算 powerset
vector<vector<char>> powerset(vector<char> S) {
    // 1. Base Case：遞迴終止條件
    if (S.empty()) {
        return { {} };
    }
    // 2. 拆解問題
    char x = S.front();
    vector<char> rest(S.begin() + 1, S.end());
    vector<vector<char>> subPowerset = powerset(rest);
    // 3. 組合答案
    vector<vector<char>> result;
    // 加上不含 x 的所有子集
    for (const auto& subset : subPowerset) {
        result.push_back(subset);
    }
    // 加上包含 x 的所有子集
    for (const auto& subset : subPowerset) {
        vector<char> newSubset = subset;
        newSubset.insert(newSubset.begin(), x);
        result.push_back(newSubset);
    }
    return result;
}
int main() {
    vector<char> S = { 'a', 'b', 'c' };
    vector<vector<char>> res = powerset(S);
    cout << "{ ";
    for (size_t i = 0; i < res.size(); ++i) {
        cout << "(";
        for (size_t j = 0; j < res[i].size(); ++j) {
            cout << res[i][j]
                 << (j + 1 < res[i].size() ? "," : "");
        }
        cout << ")"
             << (i + 1 < res.size() ? ", " : "");
    }
    cout << " }" << endl;
    return 0;
}
```

### 2.1 `powerset()` 函式

`powerset()` 是本程式的主要遞迴函式。

```cpp
vector<vector<char>> powerset(vector<char> S)
```

輸入一個字元集合 `S`，並回傳這個集合的所有子集合。

---

### 2.2 Base Case

```cpp
if (S.empty()) {
    return { {} };
}
```

當集合沒有任何元素時，冪集只有空集合。

因此：

```text
P({})
=
{
    {}
}
```

這是遞迴停止的條件。

---

### 2.3 拆解問題

```cpp
char x = S.front();

vector<char> rest(S.begin() + 1, S.end());
```

首先取出集合中的第一個元素 `x`，再將剩下的元素存放在 `rest`。

例如：

```text
S = {a,b,c}
```

會拆成：

```text
x = a
rest = {b,c}
```

接著：

```cpp
vector<vector<char>> subPowerset = powerset(rest);
```

遞迴計算 `{b,c}` 的冪集。

---

### 2.4 組合結果

得到 `subPowerset` 後，分成兩種情況。

第一種是不加入 `x`：

```cpp
for (const auto& subset : subPowerset) {
    result.push_back(subset);
}
```

第二種是加入 `x`：

```cpp
for (const auto& subset : subPowerset) {
    vector<char> newSubset = subset;
    newSubset.insert(newSubset.begin(), x);
    result.push_back(newSubset);
}
```

因此每一個原本的子集合，都會產生兩個版本：

```text
不包含 x
包含 x
```

這也是冪集可以產生所有子集合的主要原因。

---

## 3. 效能分析

假設原始集合共有 \(n\) 個元素。

### 3.1 時間複雜度

一個包含 \(n\) 個元素的集合，其冪集共有：

\[
2^n
\]

個子集合。

而每一個子集合最多包含 \(n\) 個元素，因此建立與複製所有子集合需要處理的元素數量約為：

\[
n \times 2^n
\]

因此本程式的時間複雜度可表示為：

\[
\boxed{O(n2^n)}
\]

隨著 \(n\) 增加，冪集的數量會快速增加，因此程式的執行時間也會快速增加。

例如：

| 原集合元素數 \(n\) | 子集合數量 \(2^n\) |
|---:|---:|
| 1 | 2 |
| 2 | 4 |
| 3 | 8 |
| 4 | 16 |
| 5 | 32 |
| 10 | 1024 |
| 20 | 1,048,576 |

可以看出冪集的數量呈現指數成長。

---

### 3.2 空間複雜度

程式需要將所有子集合儲存在：

```cpp
vector<vector<char>> result;
```

一共有 \(2^n\) 個子集合，而每個子集合最多包含 \(n\) 個元素。

因此儲存所有結果所需要的空間為：

\[
\boxed{O(n2^n)}
\]

此外，遞迴函式本身的呼叫深度最多為 \(n\)，因此遞迴呼叫堆疊為：

\[
O(n)
\]

不過由於最後需要儲存完整的冪集，因此主要的空間消耗仍然是：

\[
\boxed{O(n2^n)}
\]

---

## 4. 測試與驗證

### 4.1 測試資料

本次測試集合為：

```text
{a,b,c}
```

因為集合共有 3 個元素，所以冪集應該有：

\[
2^3=8
\]

個子集合。

---

### 4.2 編譯指令

使用 C++ 編譯：

```text
$ g++ main.cpp --std=c++21 -o main.exe
```

執行：

```text
$ .\main.exe
```

---

### 4.3 程式輸出

執行後結果為：

```text
{ (), (a), (b), (a,b), (c), (a,c), (b,c), (a,b,c) }
```

共產生：

```text
8
```

個子集合。

---

### 4.4 正確性驗證

實際產生的結果為：

```text
()
(a)
(b)
(a,b)
(c)
(a,c)
(b,c)
(a,b,c)
```

與理論上的冪集：

\[
P(\{a,b,c\})
=
\{
\emptyset,
\{a\},
\{b\},
\{a,b\},
\{c\},
\{a,c\},
\{b,c\},
\{a,b,c\}
\}
\]

相符。

因此可以確認程式能夠正確產生集合的所有子集合。

---

## 5. 申論及開發報告

### 5.1 為什麼使用遞迴

本題使用遞迴的原因是冪集本身具有很明顯的遞迴特性。

當我們要計算：

```text
{a,b,c}
```

的冪集時，可以先計算：

```text
{b,c}
```

的冪集。

取得 `{b,c}` 的所有子集合後，再針對每一個子集合分成：

```text
不加入 a
加入 a
```

兩種情況。

因此可以將大問題拆成較小的相同問題，非常適合使用遞迴來實作。

---

### 5.2 遞迴流程

以：

```text
{a,b,c}
```

為例，程式會依序拆解：

```text
{a,b,c}
    ↓
{b,c}
    ↓
{c}
    ↓
{}
```

到達空集合後開始返回結果。

```text
P({})
```

得到：

```text
{}
```

接著加入 `c`：

```text
{}
{c}
```

再加入 `b`：

```text
{}
{c}
{b}
{b,c}
```

最後加入 `a`：

```text
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```

因此完成整個冪集。

---

### 5.3 開發過程

在實作過程中，主要需要注意的是遞迴的終止條件以及結果的組合方式。

一開始必須先確認空集合的冪集為：

\[
P(\emptyset)=\{\emptyset\}
\]

如果沒有設定這個 Base Case，遞迴就無法正常停止。

接著每次取出一個元素，將剩餘元素交給下一層遞迴處理。當遞迴返回後，再建立兩份結果，一份保留原本的子集合，另一份則加入目前取出的元素。

透過這種方式，可以確保每個元素都有「加入」和「不加入」兩種可能，最後就能得到所有可能的子集合。

---

另外，我也了解到冪集的數量會以 \(2^n\) 的速度增加。當集合元素增加時，產生的子集合數量會快速增加，因此雖然遞迴方式的程式碼相對直觀，但當輸入規模變大時，時間與記憶體的需求也會大幅增加。

這次實作讓我更加理解遞迴、子問題拆解以及時間與空間複雜度之間的關係。
::
