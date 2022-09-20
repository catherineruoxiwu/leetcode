[LeetCode 101](https://github.com/changgyhub/leetcode_101)

# Greedy

### 455. Assign Cookies
```cpp
// sort & compare
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end()); sort(s.begin(), s.end());
        int i = 0, j = 0;
        while (i < g.size() && j < s.size()) {
            if (s[j] >= g[i]) ++i;
            ++j;
        }
        return i;
    }
};
```

### 135. Candy
```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int len = ratings.size();
        // each child must have at least one candy
        vector<int> candies(len, 1);
        // children with a higher rating get more than their left neighbors
        for (int i = 1; i < len; ++i) {
            if (ratings[i] > ratings[i-1]) candies[i] = candies[i-1] + 1;
        }
        // children with a higher rating get more than their right neighbors
        for (int i = len - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i+1]) candies[i] = max(candies[i], candies[i+1] + 1);
        }
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
```

### 435. Non-overlapping Intervals
```cpp
class Solution {
    static bool sortByEnd(vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // sort by end
        // `sortByEnd` can be replaced by lamda:
        // [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; }
        sort(intervals.begin(), intervals.end(), sortByEnd);
        int ans = 0;
        int lastEnd = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (lastEnd > intervals[i][0]) {
                // interval[i] is removed
                ++ans;
            } else {
                // interval[i] is kept
                lastEnd = intervals[i][1];
            }
        }
        return ans;
    }
};
```

### 605. Can Place Flowers
```cpp
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size();
        for (int i = 0; i < len; ++i) {
            // note: flowerbed must be 0 in order to plant new flowers
            if (flowerbed[i] == 0 && (i == 0 || flowerbed[i-1] == 0) &&
                (i == len - 1 || flowerbed[i+1] == 0)) {
                flowerbed[i] = 1;
                --n;
            }
        }
        return n <= 0;
    }
};
```

### 452. Minimum Number of Arrows to Burst Balloons
```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        // sort by end
        sort(points.begin(), points.end(),
             [](vector<int>& a, vector<int>& b) {
                 return a[1] < b[1];
             });
        int lastBurst = points[0][1];
        int ans = 1;
        for (int i = 1; i < points.size(); ++i) {
            // burst end
            if (lastBurst < points[i][0]) {
                lastBurst = points[i][1];
                ++ans;
            }
        }
        return ans;
    }
};
```

### 763. Partition Labels
```cpp
// Solution 1: calculate intervals & merge
class Solution {
public:
    vector<int> partitionLabels(string s) {
        // preprocess
        vector<pair<int, int>> record(26, {-1, -1});
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (record[c-'a'].first == -1) {
                record[c-'a'].first = i;
            }
            record[c-'a'].second = i;
        }
        sort(record.begin(), record.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first;
        });
        // skip the letters that did not appear
        int i = 0;
        while (record[i].first == -1) {
            ++i;
        }
        // merge intervals
        int start = record[i].first, end = record[i].second;
        ++i;
        vector<int> res;
        while (i < 26) {
            if (record[i].first < end) {
                end = max(end, record[i].second);
            } else {
                res.push_back(end - start + 1);
                start = record[i].first;
                end = record[i].second;
            }
            ++i;
        }
        res.push_back(end - start + 1);
        return res;
    }
};

// Solution 2: only keep track of the last appearances
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> lastApperance(26, 0);
        vector<int> res;
        // track the last appearance of a certain character
        for (int i = 0; i < s.size(); ++i) {
            lastApperance[s[i]-'a'] = i;
        }
        int end = 0, lastEnd = -1;
        for (int i = 0; i < s.size(); ++i) {
            // essense of the solution
            end = max(end, lastApperance[s[i]-'a']);
            if (i == end) {
                res.push_back(end - lastEnd);
                lastEnd = i;
            }
        }
        return res;
    }
};
```