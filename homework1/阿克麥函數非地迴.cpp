#include <iostream>
using namespace std;
void push_stack(int*& s, int& top, int& capacity, int val) {
    // 當堆疊空間已滿時，進行動態倍增擴充
    if (top >= capacity - 1) {
        int new_capacity = capacity * 2;
        int* new_s = new int[new_capacity];
        // 將舊陣列資料複製到新陣列
        for (int i = 0; i <= top; i++) {
            new_s[i] = s[i];
        }
        delete[] s; // 釋放舊記憶體
        s = new_s; // 將指標指向新記憶體空間
        capacity = new_capacity; // 更新容量
    }
    s[++top] = val;// 將數值壓入堆疊頂端
}
int pop_stack(int* s, int& top) {
    return s[top--];
}
int a(int m, int n) {
    int capacity = 16;             // 初始 Stack 容量
    int top = -1;                  // 初始 Stack 頂端位置 (-1 表示空 Stack)
    int* s = new int[capacity];    // 動態宣告 Stack 陣列
    // 將初始的 m 推入堆疊
    push_stack(s, top, capacity, m);
    // 當堆疊不為空時持續進行計算
    while (top >= 0) {
        m = pop_stack(s, top); // 取出 Stack 頂端的 m 值
        // 條件 1: A(0, n) = n + 1[cite: 1]
        if (m == 0) {
            n++;
        }
        // 條件 2: A(m, 0) = A(m - 1, 1)[cite: 1]
        else if (n == 0) {
            push_stack(s, top, capacity, m - 1); // 推入 (m - 1)
            n = 1;                              // 將 n 重置為 1
        }
        // 條件 3: A(m, n) = A(m - 1, A(m, n - 1))[cite: 1]
        else {
            n--; // 先計算內層的 (n - 1)
            // 由於 Stack 為後進先出 (LIFO)，先推入 m - 1，再推入 m
            push_stack(s, top, capacity, m - 1); // 較後執行的外層呼叫
            push_stack(s, top, capacity, m);     // 先執行的內層呼叫
        }
    }
    delete[] s; // 釋放動態宣告的 Stack 記憶體，防止記憶體洩漏 (Memory Leak)
    return n;   // 回傳最終計算結果
}
int main() {
    int m, n;
    // 讀取輸入並執行阿克曼函數
    if (cin >> m >> n) {
        cout << a(m, n) << endl;
    }
    return 0;
}