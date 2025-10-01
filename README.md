# Search Nearby Restaurant: 2D Range Trees and Algorithms

This project implements and compares advanced 2D data structures to efficiently solve the Orthogonal Range Searching Problem, a core challenge for spatial queries in applications like **finding nearby restaurants**.

The solution provides a strong theoretical guarantee on query time, making it superior to simpler methods for large, production-level datasets.

---

## Key Project Achievements (C++ Implementation)

| Achievement | Fulfillment Details |
|-------------|---------------------|
| Engineered 2D Segment Tree and Range Tree | Implemented both the 2D Range Tree and 2D Segment Tree from scratch in C++ (`RangeTree.h`, `SegmentTree2D.h`). |
| Processed Queries within Chebyshev Distance | Efficiently processes the \( l_\infty \) (Chebyshev) distance metric by transforming search into axis-aligned rectangular queries (`main.cpp`). |
| Achieved \( O(n \log n) \) Preprocessing | Recursive merge-sort approach in construction guarantees optimal preprocessing time complexity. |
| Achieved \( O(m + (\log n)^2) \) Query Time | Delivers the theoretical logarithmic bound required for fast searching over large datasets. |
| Optimized for Practical Runtime | Chosen specifically to provide reliable, guaranteed query performance for real-world scenarios where data is large and random (`Optimization.md`). |
| Demonstration and Test Case Results | `main.cpp` demonstrates correct functionality using exact points and queries from the assignment (`a3.pdf`). |

---

## Test Visualization

The search space is defined by the Chebyshev distance, where \( d \) defines the side length of the search square around the query point.

<img src="Comparison/test-case_visual_aid.png" alt="Test Case Visualization" width="550"/>

---

## Verification Output

The following output confirms both the Range Tree and the 2D Segment Tree correctly identify the exact set of nearby points for each query:

== Query 1: Location (5.0,5.0), Distance d=1.0 ==
Range Tree Output: []; 
2D Segment Tree Output: []

== Query 2: Location (4.0,8.0), Distance d=2.0 == 
Range Tree Output: [(3,7) (4,9)]; 
2D Segment Tree Output: [(3,7) (4,9)]

== Query 3: Location (10.0,2.0), Distance d=1.5 == 
Range Tree Output: [(9,2)]; 
2D Segment Tree Output: [(9,2)]

---

## Theoretical Justification

For a detailed analysis of the performance bounds and comparative superiority against alternatives like the K-d Tree, see [Optimization.md](Comparison/Optimization.md).
