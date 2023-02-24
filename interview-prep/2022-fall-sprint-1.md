# 2022 Fall Sprint I

## Time Complexity
### Common Recurrence Relations
- T(n) = T(n/2) + Θ(1) ∈ Θ(log n)
- T(n) = 2T(n/2) + Θ(n) ∈ Θ(n log n)
- T(n) = 2T(n/2) + Θ(log n) ∈ Θ(n)
- T(n) = T(cn) + Θ(n) ∈ Θ(n)
- T(n) = 2T(n/4) + Θ(1) ∈ Θ(√n)
- T(n) = T(√n) + Θ(1) ∈ Θ(log log n)
### Master Theorem
T(n) = a * T(n/b) + n ^ c for constants a > 0, b > 1, c >= 0
- if c > logb a, T(n) ∈ O(n^c)
- if c = logb a, T(n) ∈ O(n^c log n)
- if c < logb a, T(n) ∈ O(n^(logb a))

## Arrays & Strings

### 200. Number of Islands
Recursive DFS
```cpp
class Solution {
    int m, n;
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') return;
        grid[i][j] = '0';
        dfs(grid, i-1, j);
        dfs(grid, i+1, j);
        dfs(grid, i, j-1);
        dfs(grid, i, j+1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        m = grid.size();
        n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    ++res;
                }
            }
        }
        return res;
    }
};
```
Iterative BFS, less space O(M * N) -> O(min(M, N))
```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    queue<pair<int, int>> neighbours;
                    neighbours.push({i ,j});
                    grid[i][j] = '0';
                    while (!neighbours.empty()) {
                        int _i = neighbours.front().first;
                        int _j = neighbours.front().second;
                        if (_i - 1 >= 0 && grid[_i - 1][_j] == '1') {
                            neighbours.push({_i - 1, _j});
                            grid[_i - 1][_j] = '0';
                        }
                        if (_i + 1 < m && grid[_i + 1][_j] == '1') {
                            neighbours.push({_i + 1, _j});
                            grid[_i + 1][_j] = '0';
                        }
                        if (_j - 1 >= 0 && grid[_i][_j - 1] == '1') {
                            neighbours.push({_i, _j - 1});
                            grid[_i][_j - 1] = '0';
                        }
                        if (_j + 1 < n && grid[_i][_j + 1] == '1') {
                            neighbours.push({_i, _j + 1});
                            grid[_i][_j + 1] = '0';
                        }
                        neighbours.pop();
                    }
                }
            }
        }
        return res;
    }
};
```

### 468. Validate IP Address
Special case: "2001:0db8:85a3:0:0:8A2E:0370:7334:"

### 125. Valid Palindrome
```cpp
class Solution {
    bool isAlpNum(char c) {
        c = tolower(c);
        if (c >= '0' && c <= '9') return true;
        if (c >= 'a' && c <= 'z') return true;
        return false;
    }
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while(i < j) {
            while (i < j && !isAlpNum(s[i])) ++i;
            while (i < j && !isAlpNum(s[j])) --j;
            if (tolower(s[i]) != tolower(s[j])) {
                return false;
            }
            ++i; --j;
        }
        return true;
    }
};
```

### 151. Reverse Words in a String
O(n) in-place solution
```cpp
class Solution {
    void reverseWord(string& s, int start, int end, int destStart, int destEnd) {
        end = end - 1;
        int midPoint = (destStart + end) / 2;
        while (destStart <= midPoint && destStart <= destEnd) {
            swap(s[destStart++], s[end--]);
        }
    }
public:
    string reverseWords(string s) {
        // reverse then in place
        reverse(s.begin(), s.end());
        s += ' ';
        int start = 0, end;
        int destStart = 0, destEnd;
        // hello-world---
        // ---dlrow-olleh
        // world-hello---
        while (true) {
            while(start < s.size() && s[start] == ' ') ++start;
            if (start == s.size()) break;
            int end = s.find(' ', start);
            int strLen = end - start;
            destEnd = destStart + strLen - 1;
            reverseWord(s, start, end, destStart, destEnd);
            s[++destEnd] = ' ';
            destStart = destEnd + 1;
            start = end + 1;
        }
        return s.substr(0, destEnd);
    }
};
```

### 186. Reverse Words in a String II
```cpp
class Solution {
    void reverseWord(vector<char>& s, int start, int end) {
        int midPoint = (end - start - 1) / 2;
        for (int i = 0; i <= midPoint; ++i) {
            swap(s[start++], s[end--]);
        }
    }
public:
    void reverseWords(vector<char>& s) {
        reverse(s.begin(), s.end());
        int start = 0, end;
        while(start < s.size()) {
            end = start;
            while (end < s.size() && s[end] != ' ') {
                ++end;
            }
            reverseWord(s, start, end-1);
            start = end + 1;
        }
    }
};
```

### 5. Longest Palindromic Substring
```cpp
class Solution {
    string ans = "";
    // an excellant template
    void expandPalindrome(string s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            --l; ++r;
        }
        int len = r - l - 1;
        if (len > ans.size()) {
            ans = s.substr(l + 1, len);
        }
    }
public:
    string longestPalindrome(string s) {
        for (int i = 0; i < s.size(); ++i) {
            expandPalindrome(s, i, i);
            expandPalindrome(s, i, i+1);
        }
        return ans;
    }
};
```

### 49. Group Anagrams
```cpp
class Solution {
    // sort -> O(nk log k)
    // genKey -> O(nk)
    string genKey(string& str) {
        string key;
        for (int i = 0; i < 26; ++i) {
            key += char(0);
        }
        for (char c :str) {
            ++key[c - 'a'];
        }
        return key;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hashmap;
        for (string str: strs) {
            string key = genKey(str);
            if (hashmap.find(key) == hashmap.end()) {
                hashmap.insert({key, {}});
            }
            hashmap[key].push_back(str);
        }
        vector<vector<string>> res;
        for (auto& it: hashmap) {
            res.push_back(it.second);
        }
        return res;
    }
};
```

### 42. Trapping Rain Water
Rain trapped in current index = min(maxRain(0, curIdx), maxRain(curIdx, end)) 
O(n) space, O(n) time
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> maxLeftArr (n, 0); // 1 ~ n - 1
        vector<int> maxRightArr (n, 0); // n - 2 ~ 0
        maxLeftArr[0] = height[0];
        maxRightArr[n-1] = height[n-1];
        for (int i = 1; i < n; ++i) {
            maxLeftArr[i] = max(maxLeftArr[i-1], height[i]);
            maxRightArr[n-1-i] = max(maxRightArr[n-i], height[n-1-i]);
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += (min(maxLeftArr[i], maxRightArr[i]) - height[i]);
        }
        return res;
    }
};
```
Two Pointers solution with O(1) space, O(n) time
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int maxLeft = height[l], maxRight = height[r];
        int res = 0;
        while (l < r) {
            if (maxLeft <= maxRight) {
                // maxLeft <= maxRight -> maxLeft
                // maxLeft = max(from 0 to l)
                // realMaxRight = max(from l to end) >= maxRight
                // min(maxLeft, realMaxRight)-> maxLeft <= maxRight <= realMaxRight
                ++l;
                maxLeft = max(maxLeft, height[l]);
                res += (maxLeft - height[l]);
            } else {
                --r;
                maxRight = max(maxRight, height[r]);
                res += (maxRight - height[r]);
            }
        }
        return res;
    }
};
```

### 560. Subarray Sum Equals K
```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0;
        unordered_map<int, int> record; // [prefix sum: # of appearances]
        int prefixSum = 0;
        record[prefixSum] = 1;
        for (int& num : nums) {
            prefixSum += num;
            ans += record[prefixSum - k];
            ++record[prefixSum];
        }
        return ans;
    }
};
```

### 73. Set Matrix Zeroes
O(1) space, record row & col of 0s in the first row & col
```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool firstColContainsZero = false;
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                firstColContainsZero = true;
                break;
            }
        }
        bool firstRowContainsZero = false;
        for (int i = 0; i < n; ++i) {
            if (matrix[0][i] == 0) {
                firstRowContainsZero = true;
                break;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstColContainsZero) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
        if (firstRowContainsZero) {
            for (int j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
        }
    }
};
```

## Trees

### Traversal Templates

#### Inorder
Recursive
```cpp
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << endl;
    inorder(root->right);
}
```
Iterative
```cpp
void inorder(TreeNode* root) {
    stack<TreeNode*> stack;
    TreeNode* cur = root;
    while (cur || !stack.empty()) {
        while (cur) {
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.top();
        stack.pop();
        cout << cur->val << endl;
        cur = cur->right;
    }
}
```
Morris O(1) space (manipulate the tree structure)
```cpp
void inorderTraversal(TreeNode* root) {
    TreeNode* cur = root;
    while (cur) {
        if (!cur->left) {
            cout << cur->val << endl;
            cur = cur->right;
        } else {
            TreeNode* prev = cur;
            TreeNode* next = cur->left;
            cur = cur->left;
            while(cur->right) {
                cur = cur->right;
            }
            prev->left = nullptr;
            cur->right = prev;
            cur = next;
        }
    }
}
```

#### By Level
Iteractive BFS using queue
```cpp
void levelOrder(TreeNode* root) {
    if (!root) return res;
    queue<TreeNode*> level;
    level.push(root);
    while (!level.empty()) {
        int count = level.size();
        for (int i = 0; i < count; ++i) {
            TreeNode* curNode = level.front();
            cout << curNode->val << " ";
            if (curNode->left) level.push(curNode->left);
            if (curNode->right) level.push(curNode->right);
            level.pop();
        }
        cout << endl;
    }
}
```
Recursice DFS
```cpp
vector<vector<int>> ans;
void helper(TreeNode* root, int level) {
    if (!root) return;
    if (level >= ans.size()) {
        ans.push_back({});
    }
    ans[level].push_back(root->val);
    helper(root->left, level + 1);
    helper(root->right, level+1);
}
vector<vector<int>> levelOrder(TreeNode* root) {
    helper(root, 0);
    return ans;
}
```

### 297. Serialize and Deserialize Binary Tree
Preorder traversal solution
```cpp
class Codec {
public:

    void preorder(string& ans, TreeNode* root) {
        if (!root) {
            ans += "null,";
            return;
        }
        ans += to_string(root->val) + ',';
        preorder(ans, root->left);
        preorder(ans, root->right);
    }
    
    vector<string> parse(string& str) {
        int i = 1;
        vector<string> ans;
        auto nextComma = str.find(',');
        while (nextComma != string::npos) {
            ans.push_back(str.substr(i, nextComma - i));
            i = nextComma + 1;
            nextComma = str.find(',', i);
        }
        ans.push_back(str.substr(i, str.size() - i - 1 ));
        return ans;
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans = "[";
        preorder(ans, root);
        ans.pop_back();
        ans += "]";
        cout << ans << endl;
        return ans;
    }
    
    TreeNode* helper(vector<string>& vals, int& start) {
        ++start;
        if (vals[start] == "null") {
            return nullptr;
        }
        TreeNode* root =new TreeNode{stoi(vals[start])};
        root->left = helper(vals, start);
        root->right = helper(vals, start);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> parsedTree = parse(data);
        int ans = -1;
        return helper(parsedTree, ans);
    }
};
```

### 98. Validate Binary Search Tree
Recursively check the upper and lower bounds of the value of a node
```cpp
class Solution {
    bool isValidSubTree(TreeNode* root, TreeNode* lower, TreeNode* upper) {
        if (!root) return true;
        // (lower, upper)
        if ((lower != nullptr && root->val <= lower->val)
            || (upper != nullptr && root->val >= upper->val)) return false;
        return isValidSubTree(root->left, lower, root) && isValidSubTree(root->right, root, upper);
    }
public:
    bool isValidBST(TreeNode* root) {
        return isValidSubTree(root->left, nullptr, root) && isValidSubTree(root->right, root, nullptr);
    }
};
```
Recursive inorder traversal
```cpp
class Solution {
    TreeNode* prevNode = nullptr;
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        bool isLeftTreeValidBST = isValidBST(root->left);
        if (!isLeftTreeValidBST || (prevNode && root->val <= prevNode->val)) {
            return false;
        }
        prevNode = root;
        return isValidBST(root->right);
    }
};
```

### 103. Binary Tree Zigzag Level Order Traversal
```cpp
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;
        queue<TreeNode*> level;
        level.push(root);
        bool lToR = true;
        while(!level.empty()) {
            int count = level.size();
            vector<int> curLevel (count);
            for (int i = 0; i < count; ++i) {
                TreeNode* cur = level.front();
                curLevel[lToR ? i : count - 1- i] = cur->val; // Nice!!!
                if (cur->left) level.push(cur->left);
                if (cur->right) level.push(cur->right);
                level.pop();
            }
            lToR = !lToR;
            ans.push_back(curLevel);
        }
        return ans;
    }
};
```

### 235. Lowest Common Ancestor of a Binary Search Tree
```cpp
// Recursive solution based on BST's feature
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else {
            return root;
        }
    }
};
```

### 437. Path Sum III
Best Case: 
T(n) = 2 * T(n/2) + O(n) ∈ O(n*log n) 
Worst Case: 
T(n) = T(n-1) + O(n) ∈ O(n^2) 
```cpp
class Solution {
    int pathSumStartWithRoot(TreeNode* root, long long targetSum) {
        if (!root) return 0;
        return pathSumStartWithRoot(root->left, targetSum - root->val)
            + pathSumStartWithRoot(root->right, targetSum - root->val)
            + (targetSum == root->val ? 1 : 0); // do not pass down for children to handle
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        return pathSum(root->left, targetSum)
            + pathSum(root->right, targetSum) 
            + pathSumStartWithRoot(root, targetSum);
    }
};
```
Hashtable prefix sum O(n) solution
```cpp
class Solution {
    int count = 0;
    unordered_map<long long, int> hashmap; // [prefix sum: # of appearance]
    void traverse(TreeNode* root, long long curSum, int targetSum) {
        if (!root) return;
        curSum += root->val; // add current value first
        if (curSum == targetSum)  { // to avoid pushing {0 : 1} into the hashmap
            ++count;
        }
        count += hashmap[curSum - targetSum];
        if (hashmap.find(curSum) == hashmap.end()) {
            hashmap.insert({curSum, 0});
        }
        ++hashmap[curSum];
        traverse(root->left, curSum, targetSum);
        traverse(root->right, curSum, targetSum);
        --hashmap[curSum];
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        traverse(root, 0, targetSum);
        return count;
    }
};
```

## Linked Lists

### 141. Linked List Cycle
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) return true;
        }
        return false;
    }
};
```

### 2. Add Two Numbers
```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        int carry = 0;
        ListNode* curNode = dummy;
        while (l1 || l2 || carry) {
            int sum = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
            ListNode* nextNode = new ListNode(sum % 10);
            curNode->next = nextNode;
            curNode = nextNode;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            carry = sum / 10;
        }
        return dummy->next;
    }
};
```

### 445. Add Two Numbers II
Reverse the lists, add the numbers, then reverse

### 21. Merge Two Sorted Lists
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curNode = dummy;
        while(list1 && list2) {
            if (list1->val < list2->val) {
                curNode->next = list1;
                list1 = list1->next;
            } else {
                curNode->next = list2;
                list2 = list2->next;
            }
            curNode = curNode->next;
        }
        if (list1) curNode->next = list1;
        if (list2) curNode->next = list2;
        return dummy->next;
    }
};
```

### 23. Merge k Sorted Lists
Time O(n log n), Space O(k) with priority queue
Time O(n log n), Space O(1) with divide & conquer
```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return nullptr;
        }
        int n = lists.size();
        while (n > 1) {
            for (int i = 0; i < n / 2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[n - i -1]);
            }
            n = (n + 1) / 2;
        }
        return lists[0];
    }
};
```

### 146. LRU Cache
HashMap + Doubly Linked List
```cpp
struct Node {
    Node* prev;
    Node* next;
    int key;
    int value;
    Node() {}
    Node(int key, int value) : key{key}, value{value} {}
};

class LRUCache {
    int capacity;
    int size;
    Node* head;
    Node* tail;
    unordered_map<int, Node*> hashmap;
    // helper functions
    void removeNode(Node* curNode) {
        Node* prevNode = curNode->prev;
        Node* nextNode = curNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }
    void insertToFront(Node* curNode) {
        Node* firstNode = head->next;
        head->next = curNode;
        curNode->prev = head;
        curNode->next = firstNode;
        firstNode->prev = curNode;
    }
public:
    LRUCache(int capacity) : capacity{capacity}
    , size{0}
    , head{new Node{}}
    , tail{new Node{}} {
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (hashmap.find(key) == hashmap.end()) {
            return -1;
        }
        Node* curNode = hashmap[key];
        removeNode(curNode);
        insertToFront(curNode);
        return hashmap[key]->value;
    }
    
    void put(int key, int value) {
        Node* curNode;
        if (hashmap.find(key) == hashmap.end()) {
            curNode = new Node{key, value};
            ++size;
            hashmap.insert({key, curNode}); // faster than hashmap[key] = curNode
        } else {
            curNode = hashmap[key];
            curNode->value = value;
            removeNode(curNode);
        }
        insertToFront(curNode);
        if (size > capacity) {
            Node* lastNode = tail->prev;
            hashmap.erase(lastNode->key); // Don't forget
            tail = tail->prev; // can be removeNode(tail->prev);
            --size;
        }
    }
};
```

## Binary Search

### 35. Search Insert Position
If the element exists >> the index itself
Does not exist >> index of first element that is bigger than the target
```cpp
// print out the element when 
if (nums[mid] == target) {
    return mid;
}
if (nums[mid] > target) {
    r = mid - 1;
} else {
    l = mid + 1;
}
return l; // r < l; nums[r] < target < nums[l]
```

### 278. First Bad Version
find lower bound
```cpp
if (isBadVersion(mid)) { // >= target
    r = mid - 1;
} else {
    l = mid + 1;
}
return r + 1;
```

## Graphs

### 785. Is Graph Bipartite?
```cpp
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, 0); // 0: not defined; 1: white; 2: black
        queue<int> curLevel;
        curLevel.push(0);
        int curColor = 1;
        for (int i = 0; i < n; ++i) {
            if (color[i] != 0) {
                continue;
            }
            // init a queue for BFS around the current node
            int curColor = 1;
            color[i] = curColor;
            queue<int> curLevel;
            curLevel.push(i);
            // BFS
            while (!curLevel.empty()) {
                int count = curLevel.size();
                for (int k = 0; k < count; ++k) {
                    int curVertex = curLevel.front();
                    for (int& j : graph[curVertex]) {
                        if (color[j] == curColor) {
                            return false;
                        } else if (color[j] == 0) {
                            color[j] = 3 - curColor;
                            curLevel.push(j);
                        }
                    }
                    curLevel.pop();  // Don't forget!!!!
                }
                curColor = 3 - curColor;
            }
        }
        return true;
    }
};
```

## Stacks, Priority Queues & Tries

### 20. Valid Parentheses
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> unpaired;
        map<char, char> dict{{')', '('}, {']', '['}, {'}', '{'}};
        for (char c : s) {
            if (dict.count(c)) {
                if (unpaired.empty() || unpaired.top() != dict[c]) {
                    return false;
                } else {
                    unpaired.pop();
                }
            } else {
                unpaired.push(c);
            }
        }
        return unpaired.empty();
    }
};
```

### 1019. Next Greater Node In Linked List
Monotonic stack
```cpp
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        stack<pair<int, int>> s; // [idx, value]
        vector<int> ans;
        int i = 0;
        while(head) {
            ans.push_back(0);
            while(!s.empty()) {
                if (s.top().second < head->val) {
                    int idx = s.top().first;
                    ans[idx] = head->val;
                    s.pop();
                } else {
                    break;
                }
            }
            s.push(make_pair(i++, head->val));
            head = head->next;
        }
        return ans;
    }
};
```

## Math & Bit Manipulations

### Tricks
- a ^ a = 0
- n = n & (n - 1), remove the last 1 in the number
- ...

## C++ Syntax

### Priority Queues
Min Heap
```cpp
priority_queue<int, vector<int>, greater<int>> pq; // elements when greater<int> is true is at the bottom
```
Overload with a Comp function
```cpp
auto Comp = [](vector<int>& a, vector<int>& b) { return a->val > b->val; }
priority_queue<vector<int>, vector<vector<int>>, decltype(Comp)> pq(Comp);
```
Overload with a struct
```cpp
struct Comp {
    bool operator()(ListNode* l1, ListNode* l2) {
        return l1->val > l2->val;
    }
};
priority_queue<ListNode*, vector<ListNode*>, Comp> pq;
```
### Sort
Overload with a lamda
```cpp
sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
    return a[0] < b[0];
});
``` 
Overload with a Comp function
```cpp
static bool Comp(vector<int>& a, vector<int>& b) {
    return a[0] < b[0];
}
sort(intervals.begin(), intervals.end(), Comp);
```

## Resources
1. [Microsoft Problems](https://leetcode.com/company/microsoft/)
2. [Top Microsoft Questions](https://leetcode.com/problem-list/top-microsoft-questions)
3. [Top Questions from Microsoft](https://leetcode.com/explore/interview/card/microsoft/)
