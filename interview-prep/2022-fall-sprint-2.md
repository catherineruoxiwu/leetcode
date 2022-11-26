# 2022 Fall Sprint II (Random Quesitons)

### 120. Triangle
- Find min element in a vector: `*min_element(s.begin(), s.end())`

### 189. Rotate Array
- Step 1 - **12345** 6789 ---> **54321** 6789
- Step 2 - 54321 **6789** ---> 54321 **9876**
- Step 3 - reverse: 543219876 ---> 678912345

### 223. Rectangle Area
- Calculate overlapse: 
```cpp
int calcOverlapse(int start1, int end1, int start2, int end2) {
    int len = min(end1, end2) - max(start1, start2);
    return len > 0 ? len : 0;
}
```

### 231. Poweer of Two
- `n & 1` tests whether the last bit is 1
- `n & (n - 1)` changes the rightest 1 into 0