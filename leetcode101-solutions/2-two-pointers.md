# Two Pointers

### 167. Two Sum II - Input Array Is Sorted
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while (i < j) {
            int sum = numbers[i] + numbers[j];
            if (sum == target) {
                return vector<int>{i + 1, j + 1};
            } else if (sum < target) {
                ++i;
            } else {
                --j;
            }
        }
        return vector<int>{-1, -1};
    }
};
```

### 88. Merge Sorted Array
```cpp

```

