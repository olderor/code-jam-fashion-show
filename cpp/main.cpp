//
//  main.cpp
//  cpp
//
//  Created by olderor on 11.06.17.
//  Copyright © 2017 Bohdan Yevchenko. All rights reserved.
//

#include <fstream>
#include <vector>

using namespace std;

vector<int> is_busy_row;
vector<int> is_busy_column;
vector<int> is_busy_diagonal1;
vector<int> is_busy_diagonal2;
vector<vector<int>> matrixX;
vector<vector<int>> matrixP;
int result;

void clear(const int size) {
    result = 0;
    is_busy_row.clear();
    is_busy_row.resize(size);
    is_busy_column.clear();
    is_busy_column.resize(size);
    is_busy_diagonal1.clear();
    is_busy_diagonal1.resize(size * size);
    is_busy_diagonal2.clear();
    is_busy_diagonal2.resize(size * size);
    matrixX.clear();
    matrixP.clear();
    matrixX.resize(size);
    matrixP.resize(size);
    for (int i = 0; i < size; ++i) {
        matrixX[i].resize(size);
        matrixP[i].resize(size);
    }
}

void fillX(const int x, const int y) {
    matrixX[x][y] = 1;
    is_busy_row[x] = 1;
    is_busy_column[y] = 1;
}

void fillP(const int x,
           const int y,
           const int n) {
    
    matrixP[x][y] = 1;
    is_busy_diagonal1[x + y] = 1;
    is_busy_diagonal2[x - y + n - 1] = 1;
}

void fillAllX(const int n) {
    for (int i = 0; i < n; ++i) {
        ++result;
        if (is_busy_row[i]) {
            continue;
        }
        for (int j = 0; j < n; ++j) {
            if (is_busy_column[j]) {
                continue;
            }
            matrixX[i][j] = 2;
            is_busy_column[j] = 1;
            is_busy_row[i] = 1;
            break;
        }
    }
}

void processDiagonal(const int d, const int n) {
    if (is_busy_diagonal1[d]) {
        ++result;
        return;
    }
    int x, y;
    if (d < n) {
        x = d;
        y = 0;
    } else {
        x = n - 1;
        y = d - x;
    }
    
    while (0 <= x && y < n) {
        if (!is_busy_diagonal2[x - y + n - 1]) {
            is_busy_diagonal2[x - y + n - 1] = 1;
            matrixP[x][y] = 2;
            ++result;
            break;
        }
        --x, ++y;
    }
}

void fillAllP(const int n) {
    for (int i = 0; i < n; ++i) {
        processDiagonal(i, n);
        if (i != n - 1) {
            processDiagonal(n + n - i - 2, n);
        }
    }
}

int main() {
    int tests;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fin >> tests;
    for (int test = 0; test < tests; ++test) {
        int n, m;
        fin >> n >> m;
        clear(n);
        char c;
        int x, y;
        for (int i = 0; i < m; ++i) {
            fin >> c >> x >> y;
            --x, --y;
            switch (c) {
                case 'x':
                    fillX(x, y);
                    break;
                case '+':
                    fillP(x, y, n);
                    break;
                case 'o':
                    fillX(x, y);
                    fillP(x, y, n);
                    break;
            }
        }
        
        fillAllX(n);
        fillAllP(n);
        
        int parts = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrixX[i][j] == 2 || matrixP[i][j] == 2) {
                    ++parts;
                }
            }
        }
        fout << "Case #" << test + 1 << ": " << result << " " << parts << "\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrixX[i][j] == 2 || matrixP[i][j] == 2) {
                    char c = '+';
                    if (matrixX[i][j] && matrixP[i][j]) {
                        c = 'o';
                    } else if (matrixX[i][j]) {
                        c = 'x';
                    }
                    fout << c << " " << i + 1 << " " << j + 1 << "\n";
                }
            }
        }
    }
    
    fin.close();
    fout.close();
    
    return 0;
}















