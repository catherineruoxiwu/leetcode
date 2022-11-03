# Microsoft SDE Intern Final Round Prep

## Time Complexity
- T(n) = T(n/2) + Θ(1) ∈ Θ(log n)
- T(n) = 2T(n/2) + Θ(n) ∈ Θ(n log n)
- T(n) = 2T(n/2) + Θ(log n) ∈ Θ(n)
- T(n) = T(cn) + Θ(n) ∈ Θ(n)
- T(n) = 2T(n/4) + Θ(1) ∈ Θ(√n)
- T(n) = T(√n) + Θ(1) ∈ Θ(log log n)
### Master Theorem
T(n) = a * T(n/b) + n ^ c for constatns a > 0, b > 1, c >= 0
- if c > logb a, T(n) ∈ O(n^c)
- if c = logb a, T(n) ∈ O(n^c log n)
- if c < logb a, T(n) ∈ O(n^(logb a))

## Arrays & Strings

### 200. Number of Islands
```cpp
// Recursive DFS
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
// Iterative BFS, less space O(M * N) -> O(min(M, N))
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

## Tree

### Traversal Templates

#### Inorder
```cpp
// Recursive
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << endl;
    inorder(root->right);
}
// Iterative
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
// Morris O(1) space (manipulate the tree structure)
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
#### Preorder
```cpp
```
#### Postorder
```cpp
```

#### By Level
```cpp
// Iteractive BFS using queue
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
// Recursice DFS
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
                curLevel[lToR ? i : count - 1- i] = cur->val;
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

### todo: normal tree

### 437. Path Sum III
```cpp
// Best Case:
// T(n) = 2 * T(n/2) + O(n) ∈ O(n*log n)
// Worst Case:
// T(n) = T(n-1) + O(n) ∈ O(n^2)
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
// Hashtable
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

## Graph

### 

## C++ Syntax



## Resources
1. [Microsoft Problems](https://leetcode.com/company/microsoft/)
2. [Top Microsoft Questions](https://leetcode.com/problem-list/top-microsoft-questions)
3. [Top Questions from Microsoft](https://leetcode.com/explore/interview/card/microsoft/)

## My Timeline
