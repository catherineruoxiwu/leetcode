# [Blind 75](https://neetcode.io/practice)

## Arrays & Hashing

### 217. Contains Duplicate

### 242. Valid Anagram
统计每个字符串各字母数量

### 1. Two Sum

### 49. Group Anagrams
核心是 `unordered_map<string, vector<string>>`，其中 key 既可以是把单词按字母排序之后的字符串，也可以是用长度为 26 的 ASCII 字符组成用来表示各字母出现的次数的字符串

### 347. Top K Frequent Elements
首先用 `unordered_map<int, int>` 存 `{数字: 出现的次数}`，之后再通过 `vector<vector<int>> bucket(nums.size()+1)` 排序，从后往前读最大的 k 个元素

### 238. Product of Array Except Self

### 271. Encode and Decode Strings
加密策略：长度 + "#" + 字符串本身

### 128. Longest Consecutive Sequence
通过 `unordered_set<int>s(nums.begin(), nums.end())` 预处理，再查连续数（注意：只查以一个数为最大值的 sequence）

## Two Pointers

### 125. Valid Palindrome

### 15. 3Sum
注意：和不能重复，排序之后前两个指针需要跳过重复数据

### 11. Container With Most Water

## Stack

### 20. Valid Parentheses

## Heap / Priority Queue

### 295. Find Median from Data Stream
Priority Queue C++ 写法：
```cpp
// custom class
class ComparisonClass {
public:
    bool operator() (Node, Node) {
        //comparison code here
    }
};
priority_queue<Node, vector<Node>, ComparisonClass> q;
// minHeap (min element at the top)
priority_queue<int, vector<int>, greater<int>> minPQ;
// maxHeap (max element at the top)
priority_queue<int, vector<int>, less<int>> maxPQ;
priority_queue<int> maxPQ;
```

## Linked List

### 206. Reverse Linked List

### 21. Merge Two Sorted Lists

### 

## Backtracking

### 39. Combination Sum
`void backtracking(vector<vector<int>>& ans, vector<int>& candidates, vector<int>& curComb, int target, int curSum, int start);`

### 79. Word Search
通过改 `[i][j]` 位置上的字符记录是否经过，别忘了改回来

## Graphs

### 200. Number of Islands
主函数遍历 2D 数组，每到一个 `'1'` 的位置 DFS 修改所有周围的 `'1'`

### 133. Clone Graph

### 417. Pacific Atlantic Water Flow
从四周开始 DFS

## 1-D Dynamic Programming

### 70. Climbing Stairs

### 198. House Robber




## Greedy

### 53. Maximum Subarray
`curMax` 存以 index `i` 结束的 subarray 和的最大值，`res` 存 `curMax` 的最大值

### 55. Jump Game
从后往前考虑



## Math & Geometry

### 48. Rotate Image

### 54. Spiral Matrix

### 73. Set Matrix Zeroes
第一行、第一列用来记录是否需要把整行/整列变 0，再用两个单独的变量记录是否把第一行、第一列变 0，空间复杂度 O(1)

## Bit Manipulation

### 191. Number of 1 Bits

### 338. Counting Bits
DP，`1 + dp[i - offset]`

### 190. Reverse Bits
```cpp
if (n & mask) res += (1 << (32-i));
mask <<= 1;
```

### 268. Missing Number

### 371. Sum of Two Integers
```cpp
unsigned int carry = (unsigned int) (a & b) << 1;
a = a ^ b;
b = carry;
```

### 125. Valid Palindrome
