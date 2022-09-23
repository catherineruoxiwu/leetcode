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