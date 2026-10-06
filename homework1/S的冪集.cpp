#include <iostream>
#include <vector>

using namespace std;
// 遞迴函式：計算 powerset
vector<vector<char>> powerset(vector<char> S) {
    // 1. Base Case：遞迴終止條件
    if (S.empty()) {
        return { {} }; // 傳回包含一個空集合的 vector
    }
    // 2. 拆解問題
    char x = S.front();                           // 取出頭元素 ('a')
    vector<char> rest(S.begin() + 1, S.end());    // 剩餘元素 (['b', 'c'])
    vector<vector<char>> subPowerset = powerset(rest); // 遞迴呼叫取得下層結果
    // 3. 組合答案
    vector<vector<char>> result;
    // 加上不含 x 的所有子集
    for (const auto& subset : subPowerset) {
        result.push_back(subset);
    }
    // 加上包含 x 的所有子集
    for (const auto& subset : subPowerset) {
        vector<char> newSubset = subset;
        newSubset.insert(newSubset.begin(), x);   // 將 x 加回每一個子集前
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
            cout << res[i][j] << (j + 1 < res[i].size() ? "," : "");
        }
        cout << ")" << (i + 1 < res.size() ? ", " : "");
    }
    cout << " }" << endl;

    return 0;
}