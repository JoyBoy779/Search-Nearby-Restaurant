// main.cpp
#include "Utils.h"
#include "RangeTree.h"
#include "SegmentTree2D.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Helper to ensure output consistency
static inline void sort_and_unique_vec(vector<Point>& v) {
    sort(v.begin(), v.end(), [](const Point& a, const Point& b){
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    v.erase(unique(v.begin(), v.end(), [](const Point& a, const Point& b){
        return a.x == b.x && a.y == b.y;
    }), v.end());
}

static inline void print_points(const vector<Point>& v) {
    if (v.empty()) { cout << "[]"; return; }
    cout << "[";
    for (size_t i=0;i<v.size();++i) {
        cout << "(" << v[i].x << "," << v[i].y << ")";
        if (i+1 < v.size()) cout << " ";
    }
    cout << "]";
}

int main() {
    // --- Database Initialization (COL106 Assignment 3 Spec) ---
    vector<Point> points = {
        {1,6},{2,4},{3,7},{4,9},{5,1},
        {6,3},{7,8},{8,10},{9,2},{10,5}
    };
    
    // BUILD STRUCTURES
    // Note: Both structures are built with O(n log n) preprocessing time.
    RangeTree rt(points);
    SegmentTree2D seg(points);

    // Queries to run (based on assignment specification)
    struct Q { double qx, qy, d; };
    vector<Q> queries = {
        {5.0, 5.0, 1.0}, // Query 1: Expected []
        {4.0, 8.0, 2.0}, // Query 2: Expected [(3,7), (4,9)]
        {10.0, 2.0, 1.5} // Query 3: Expected [(9,2)]
    };

    cout << "--- 2D Range Query Demonstration (Chebyshev Distance) ---\n\n";

    for (size_t qi=0; qi<queries.size(); ++qi) {
        auto q = queries[qi];
        cout << "== Query " << (qi+1) << ": Location (" << q.qx << "," << q.qy << "), Distance d=" << q.d << " ==\n";
        
        // --- Calculate Integer Bounds for Axis-Aligned Query Box (l_inf Distance) ---
        // l_inf distance implies a search box: [qx-d, qx+d] x [qy-d, qy+d]
        int xLo = (int) std::ceil(q.qx - q.d);
        int xHi = (int) std::floor(q.qx + q.d);
        int yLo = (int) std::ceil(q.qy - q.d);
        int yHi = (int) std::floor(q.qy + q.d);

        // --- Range Tree Query (O(log^2 n + m)) ---
        vector<Point> r1 = rt.queryRect(xLo, xHi, yLo, yHi);
        sort_and_unique_vec(r1);
        cout << "Range Tree Output:    ";
        print_points(r1);
        cout << "\n";

        // --- 2D Segment Tree Query (O(log^2 n + m)) ---
        vector<Point> r3 = seg.queryRect(xLo, xHi, yLo, yHi);
        sort_and_unique_vec(r3);
        cout << "2D Segment Tree Output: ";
        print_points(r3);
        cout << "\n\n";
    }

    return 0;
}