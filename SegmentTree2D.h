#pragma once
#include "Utils.h"

class SegmentTree2D {
    int n = 0;
    std::vector<Point> pts;                 // sorted by x (size n)
    std::vector<std::vector<Point>> tree;   // tree[node] = points in node's x-range sorted by y

    void buildNode(int node, int l, int r) {
        if (l == r) {
            tree[node] = { pts[l] };
            return;
        }
        int mid = (l + r) / 2;
        buildNode(node*2, l, mid);
        buildNode(node*2+1, mid+1, r);
        // merge children by y
        const auto &L = tree[node*2];
        const auto &R = tree[node*2+1];
        tree[node].resize(L.size() + R.size());
        std::merge(L.begin(), L.end(), R.begin(), R.end(), tree[node].begin(),
                   [](const Point& a, const Point& b){ return a.y < b.y; });
    }

    void queryNode(int node, int l, int r, int ql, int qr, int yLo, int yHi, std::vector<Point>& out) {
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            auto &vec = tree[node];
            auto lo = std::lower_bound(vec.begin(), vec.end(), yLo,
                [](const Point& p, int val){ return p.y < val; });
            auto hi = std::lower_bound(vec.begin(), vec.end(), yHi + 1,
                [](const Point& p, int val){ return p.y < val; });
            for (auto it = lo; it != hi; ++it) out.push_back(*it);
            return;
        }
        int mid = (l + r) / 2;
        queryNode(node*2, l, mid, ql, qr, yLo, yHi, out);
        queryNode(node*2+1, mid+1, r, ql, qr, yLo, yHi, out);
    }

public:
    SegmentTree2D(const std::vector<Point>& points) {
        if (points.empty()) { n = 0; return; }
        pts = points;
        std::sort(pts.begin(), pts.end(), [](const Point& a, const Point& b){
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });
        n = (int)pts.size();
        tree.assign(4*n + 5, {});
        buildNode(1, 0, n-1);
    }

    // Query by integer box [xLo..xHi] x [yLo..yHi]
    std::vector<Point> queryRect(int xLo, int xHi, int yLo, int yHi) {
        std::vector<Point> res;
        if (n == 0) return res;
        // map xLo..xHi to index range in pts
        std::vector<int> xs(n);
        for (int i=0;i<n;++i) xs[i] = pts[i].x;
        int L = int(std::lower_bound(xs.begin(), xs.end(), xLo) - xs.begin());
        int R = int(std::upper_bound(xs.begin(), xs.end(), xHi) - xs.begin()) - 1;
        if (L > R) return res;
        queryNode(1, 0, n-1, L, R, yLo, yHi, res);
        return res;
    }
};
