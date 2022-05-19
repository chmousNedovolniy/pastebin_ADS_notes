#include <iostream>
#include <string>
#include <vector>

void PrintLcs(const std::string& a, const std::string& b, const std::vector<std::vector<int>>& lcs) {
    int i = a.size(), j = b.size();
    std::string answer;
    while (i > 0 && j > 0) {
        if (lcs[i][j] == lcs[i - 1][j - 1] + 1) {
            answer = a[i - 1] + answer;
            --i;
            --j;
        } else if (lcs[i][j] == lcs[i - 1][j]) {
            --i;
        } else {
            --j;
        }
    }
    for (const auto& row : lcs) {
        for (auto elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Length of LCS is " << lcs[a.size()][b.size()] << '\n';
    std::cout << answer << '\n';
}

void FindLcs(const std::string& a, const std::string& b) {
    // vector of size len(a) + 1, len(b) + 1
    std::vector<std::vector<int>> lcs(a.size() + 1, std::vector<int>(b.size() + 1, 0));
    for (int i = 1; i < a.size() + 1; ++i) {
        for (int j = 1; j < b.size() + 1; ++j) {
            // can be done easily in one line, but I'd just copy from python code
            // lcs[i][j] = (a[i - 1] == b[j - 1]) ? lcs[i - 1][j - 1] + 1 : std::max(lcs[i - 1][j], lcs[i][j - 1]);
            if (a[i - 1] == b[j - 1]) {
                lcs[i][j]= lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }
    PrintLcs(a, b, lcs);
}

int main() {
    std::string a = "abcdefgh";
    std::string b = "abdfghi";
    FindLcs(a, b);
}