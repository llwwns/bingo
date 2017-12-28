#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

int check(const array<int, 100>& lst, int dx, int dy, int n, int x, int y) {
    if (n == 1) {
        return lst[x * 5 + y];
    } else {
        return max(lst[x * 5 + y], check(lst, dx, dy, n - 1, x + dx, y + dy));
    }
}

int bingoCount(const array<int, 100>& lst) {
    int m = min(check(lst, 1, 1, 5, 0, 0),
                check(lst, 1, -1, 5, 0, 4));
    for (int i = 0; i < 5; i++) {
        m = min({m, check(lst, 1, 0, 5, 0, i), check(lst, 0, 1, 5, i, 0)});
    }
    return m;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "usage: bingo COUNT" << endl;
        exit(1);
    }
    random_device rnd;
    std::mt19937 mt(rnd());
    array<int, 100> lst;
    map<int, int> total{};
    for (int i = 0; i < 100; i++) {
        lst[i] = i + 1;
    }
    stringstream ss;
    int n;
    ss << argv[1];
    ss >> n;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < 25; i++) {
            std::uniform_int_distribution<> dis(i, 99);
            swap(lst[i], lst[dis(mt)]);
        }
        int tmp = 0;
        swap(tmp, lst[12]);
        int r = bingoCount(lst);
        swap(tmp, lst[12]);
        auto p = total.find(r);
        if (p == total.end()) {
            total[r] = 1;
        } else {
            p->second++;
        }
    }
    for (auto p : total) {
        cout << p.first << "\t" << p.second / (double)n << endl;
    }
}
