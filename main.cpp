#include <iostream>
#include <algorithm>
#include <climits>
#include <cassert>
#include <chrono>
using namespace std;

class FenwickTreeMax {
private:
    int *tree;
    int n;

public:
    FenwickTreeMax(int size) : n(size) {
        tree = new int[n + 1];
        for (int i = 0; i <= n; i++)
            tree[i] = INT_MIN;
    }

    FenwickTreeMax(int input[], int size) : n(size) {
        tree = new int[n + 1];
        for (int i = 0; i <= n; i++)
            tree[i] = INT_MIN;
        for (int i = 0; i < n; i++) {
            update(i, input[i]);
        }
    }

    ~FenwickTreeMax() {
        delete[] tree;
    }

    void update(int idx, int val) {
        int i = idx + 1;
        while (i <= n) {
            tree[i] = max(tree[i], val);
            i += i & (-i);
        }
    }

    int query_prefix_max(int idx) {
        int res = INT_MIN;
        int i = idx + 1;
        while (i > 0) {
            res = max(res, tree[i]);
            i -= i & (-i);
        }
        return res;
    }
};

class FenwickTreeMin {
private:
    int *tree;
    int n;

public:
    FenwickTreeMin(int size) : n(size) {
        tree = new int[n + 1];
        for (int i = 0; i <= n; i++)
            tree[i] = INT_MAX;
    }

    FenwickTreeMin(int input[], int size) : n(size) {
        tree = new int[n + 1];
        for (int i = 0; i <= n; i++)
            tree[i] = INT_MAX;
        for (int i = 0; i < n; i++) {
            update(i, input[i]);
        }
    }

    ~FenwickTreeMin() {
        delete[] tree;
    }

    void update(int idx, int val) {
        int i = idx + 1;
        while (i <= n) {
            tree[i] = min(tree[i], val);
            i += i & (-i);
        }
    }

    int query_prefix_min(int idx) {
        int res = INT_MAX;
        int i = idx + 1;
        while (i > 0) {
            res = min(res, tree[i]);
            i -= i & (-i);
        }
        return res;
    }
};

class FenwickTreeSum {
private:
    int *tree;
    int n;

public:
    FenwickTreeSum(int size) : n(size) {
        tree = new int[n + 1];
        for (int i = 0; i <= n; i++)
            tree[i] = 0;
    }

    FenwickTreeSum(int input[], int size) : n(size) {
        tree = new int[n + 1];
        for (int i = 0; i <= n; i++)
            tree[i] = 0;
        for (int i = 0; i < n; i++) {
            update(i, input[i]);
        }
    }

    ~FenwickTreeSum() {
        delete[] tree;
    }

    void update(int idx, int delta) {
        int i = idx + 1;
        while (i <= n) {
            tree[i] += delta;
            i += i & (-i);
        }
    }

    int query(int idx) {
        int sum = 0;
        int i = idx + 1;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }
};

void test_range_max() {
    cout << "Running Prefix Max Tests...\n";
    FenwickTreeMax ft(10);

    ft.update(0, 5);
    ft.update(1, 10);
    ft.update(2, 3);
    ft.update(3, 20);
    ft.update(4, 8);

    assert(ft.query_prefix_max(0) == 5);
    assert(ft.query_prefix_max(1) == 10);
    assert(ft.query_prefix_max(2) == 10);
    assert(ft.query_prefix_max(3) == 20);
    assert(ft.query_prefix_max(9) == 20);

    ft.update(5, 50);
    assert(ft.query_prefix_max(9) == 50);

    cout << "Prefix Max Passed.\n";
}

void test_range_min() {
    cout << "Running Prefix Min Tests...\n";
    FenwickTreeMin ft(10);

    ft.update(0, 50);
    ft.update(1, 40);
    ft.update(2, 60);

    assert(ft.query_prefix_min(0) == 50);
    assert(ft.query_prefix_min(1) == 40);
    assert(ft.query_prefix_min(2) == 40);

    ft.update(3, 10);
    assert(ft.query_prefix_min(3) == 10);
    assert(ft.query_prefix_min(9) == 10);

    ft.update(4, 5);
    assert(ft.query_prefix_min(9) == 5);

    cout << "Prefix Min Passed.\n";
}

void TEST_02() {
    cout << "\nRunning Sum Test Case...\n";
    int data[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(data) / sizeof(data[0]);

    FenwickTreeSum ft(data, n);

    cout << "Initial Prefix Sums: ";
    for (int i = 0; i < n; i++) {
        cout << ft.query(i) << " ";
    }
    cout << "\n";

    int updateIdx = 5;
    int updateVal = 2;
    cout << "Updating index " << updateIdx << " by +" << updateVal << "...\n";
    ft.update(updateIdx, updateVal);

    cout << "Updated Prefix Sums: ";
    for (int i = 0; i < n; i++) {
        cout << ft.query(i) << " ";
    }
    cout << "\n";
}

void test_odd_size_mixed_values() {
    cout << "\nRunning Odd Size (13) with Mixed Values Case...\n";
    int data[] = {10, -5, 20, -10, 5, 5, -5, 10, 20, -20, 30, 5, -5};
    int n = sizeof(data) / sizeof(data[0]);

    FenwickTreeSum ft(data, n);

    cout << "Initial Prefix Sums: ";
    for (int i = 0; i < n; i++) {
        cout << ft.query(i) << " ";
    }
    cout << "\n";

    int updateIdx = 6;
    int updateVal = 15;
    cout << "Updating index " << updateIdx << " (value -5) by +15 (new value 10)...\n";
    ft.update(updateIdx, updateVal);

    cout << "Updated Prefix Sums: ";
    for (int i = 0; i < n; i++) {
        cout << ft.query(i) << " ";
    }
    cout << "\n";
}

void test_power_of_two_boundary() {
    cout << "\nRunning Power of 2 Boundary (16) Test Case...\n";
    int data[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int n = sizeof(data) / sizeof(data[0]);

    FenwickTreeSum ft(data, n);

    cout << "Initial Prefix Sums (should be 1 to 16): ";
    for (int i = 0; i < n; i++) {
        cout << ft.query(i) << " ";
    }
    cout << "\n";

    cout << "Updating index 0 (Start) by +10...\n";
    ft.update(0, 10);

    cout << "Updating index 15 (End) by +5...\n";
    ft.update(15, 5);

    cout << "Updated Prefix Sums: ";
    for (int i = 0; i < n; i++) {
        cout << ft.query(i) << " ";
    }
    cout << "\n";
}

void test_sparse_updates() {
    cout << "\nRunning Sparse Updates on Zero-initialized Array (Size 12)...\n";
    int n = 12;
    int data[12] = {0};
    FenwickTreeSum ft(data, n);

    cout << "Initial (All 0): ";
    for (int i = 0; i < n; i++)
        cout << ft.query(i) << " ";
    cout << "\n";

    cout << "Update indices 3, 7, 11 (prime-ish positions)...\n";
    ft.update(3, 100);
    ft.update(7, 50);
    ft.update(11, 25);

    cout << "Updated Prefix Sums: ";
    for (int i = 0; i < n; i++)
        cout << ft.query(i) << " ";
    cout << "\n";
}

void performance_comparison() {
    cout << "\nRunning Performance Comparison (O(N) vs O(log N))...\n";

    int size = 100000;
    int updates = 20000;
    int *normal_prefix = new int[size];
    for (int i = 0; i < size; i++)
        normal_prefix[i] = 0;

    FenwickTreeSum ft(size);

    auto start_normal = chrono::high_resolution_clock::now();
    for (int k = 0; k < updates; k++) {
        int idx = k % size;
        int val = 1;
        for (int j = idx; j < size; j++) {
            normal_prefix[j] += val;
        }
    }
    auto end_normal = chrono::high_resolution_clock::now();
    chrono::duration<double> diff_normal = end_normal - start_normal;

    auto start_bit = chrono::high_resolution_clock::now();
    for (int k = 0; k < updates; k++) {
        int idx = k % size;
        int val = 1;
        ft.update(idx, val);
    }
    auto end_bit = chrono::high_resolution_clock::now();
    chrono::duration<double> diff_bit = end_bit - start_bit;

    cout << "Normal Array Update Time (O(N)): " << diff_normal.count() << " s\n";
    cout << "Fenwick Tree Update Time (O(log N)): " << diff_bit.count() << " s\n";

    delete[] normal_prefix;
}

int main() {
    test_range_max();
    test_range_min();
    TEST_02();
    test_odd_size_mixed_values();
    test_power_of_two_boundary();
    test_sparse_updates();
    performance_comparison();
    return 0;
}
