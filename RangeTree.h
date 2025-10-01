#pragma once
#include "Utils.h"
#include <memory>

class RangeTree {
    struct Node {
        int l, r;                       // indices in pts (sorted by x)
        std::vector<Point> byY;         // points in [l..r] sorted by y
        Node *left = nullptr, *right = nullptr;
        Node(int L, int R) : l(L), r(R) {}
    };

    std::vector<Point> pts; // sorted by x
    Node* root = nullptr;

    Node* build(int l, int r) {
        if (l > r) return nullptr;
        int mid = (l + r) / 2;
        Node* nd = new Node(l, r);
        nd->byY.reserve(r - l + 1);
        for (int i = l; i <= r; ++i) nd->byY.push_back(pts[i]);
        std::sort(nd->byY.begin(), nd->byY.end(), [](const Point& a, const Point& b){
            return a.y < b.y;
        });
        nd->left = build(l, mid - 1);
        nd->right = build(mid + 1, r);
        return nd;
    }

    void queryNode(Node* nd, int xLo, int xHi, int yLo, int yHi, std::vector<Point>& out) {
        if (!nd) return;
        // If node's x-range is outside query
        if (pts[nd->l].x > xHi || pts[nd->r].x < xLo) return;

        // if node's x-range fully inside query, binary-search its byY
        if (pts[nd->l].x >= xLo && pts[nd->r].x <= xHi) {
            // lower_bound for yLo
            auto lo = std::lower_bound(nd->byY.begin(), nd->byY.end(), yLo,
                [](const Point& p, int val){ return p.y < val; });
            // lower_bound for yHi+1 (i.e., first > yHi)
            auto hi = std::lower_bound(nd->byY.begin(), nd->byY.end(), yHi + 1,
                [](const Point& p, int val){ return p.y < val; });
            for (auto it = lo; it != hi; ++it) out.push_back(*it);
            return;
        }

        // partial overlap -> recurse
        queryNode(nd->left, xLo, xHi, yLo, yHi, out);
        queryNode(nd->right, xLo, xHi, yLo, yHi, out);
    }

public:
    RangeTree(const std::vector<Point>& points) {
        pts = points;
        std::sort(pts.begin(), pts.end(), [](const Point& a, const Point& b){
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });
        if (!pts.empty()) root = build(0, (int)pts.size() - 1);
    }

    // query for integer box [xLo..xHi] x [yLo..yHi], returns matching points
    std::vector<Point> queryRect(int xLo, int xHi, int yLo, int yHi) {
        std::vector<Point> res;
        queryNode(root, xLo, xHi, yLo, yHi, res);
        return res;
    }
};
