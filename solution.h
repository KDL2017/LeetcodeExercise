#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include <unordered_set>

using namespace std;

class Solution {
    struct ListNode{
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };

public:
    //2.两数相加 难度：中等 提示：双指针
    //我的解题思路：
    //  不进位直接加完存储在当前位置
    //  进位需要用到下一位指针：下一位加和÷10，当前位和余10
    //  需要判断是否已经到最后一位
    //  可以直接存储到其中一个数组，不用再分配新的空间(不好操作？)

    /*ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {//试试递归
        ListNode* left1 = l1;
        ListNode* right1 = l1->next;
        ListNode* left2 = l2;
        ListNode* right2 = l2->next;
        while (right1 != nullptr || right2 != nullptr)
        {
            if (right1 != nullptr && right2 != nullptr)
            {
                if (left1->val + left2->val < 10)
                    left1->val = left1->val + left2->val;
                else
                {
                    right1->val++;
                    left1->val = (left1->val + left2->val) % 10;
                }
                left1 = left1->next;
                right1 = right1->next;
                left2 = left2->next;
                right2 = right2->next;
            }
            if (right1 == nullptr)
            {

            }
            
        }
    }*/

    //成功通过，2024/8/27
    //思路：将两链表处理成等长再计算
    //运行时间和内存消耗表现不佳
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l1_head = l1;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val + l2->val < 10) //不进位
                l1->val = l1->val + l2->val;
            else if (l1->val + l2->val >= 10 && l1->next != nullptr) //普通进位
            {
                (l1->next->val)++;
                l1->val = (l1->val + l2->val) % 10;
            }
            else if (l1->val + l2->val >= 10 && l1->next == nullptr) //进位时下一位存储空间为nullptr
            {
                l1->next = new ListNode(1);
                l1->val = (l1->val + l2->val) % 10;
            }
            if (l2->next == nullptr && l1->next != nullptr) //补长，下同
                l2->next = new ListNode(0);
            else if (l2->next != nullptr && l1->next == nullptr)
                l1->next = new ListNode(0);
            l1 = l1->next;
            l2 = l2->next;
        }
        return l1_head;
    }

    //官方题解
    //作者：力扣官方题解
    //链接：（https ://leetcode.cn/problems/add-two-numbers/solutions/435246/liang-shu-xiang-jia-by-leetcode-solution/）
    //来源：力扣（LeetCode）
    //相较于我自己的方法，速度明显提升，消耗内存变大
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr, * tail = nullptr; //开辟新空间存储
        int carry = 0; //进位值
        while (l1 || l2) {
            int n1 = l1 ? l1->val : 0; //提取l1节点携带值，若l1为空指针则取0
            int n2 = l2 ? l2->val : 0; //同上
            int sum = n1 + n2 + carry;
            if (!head) { //初始链表头为空
                head = tail = new ListNode(sum % 10);
            }
            else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) { //最后一位有进位值，需要多出一位存储
            tail->next = new ListNode(carry);
        }
        return head;
    }

    

    //3.无重复字符的最长字串 难度：中等 提示：滑动窗口，哈希表，双指针
    //我的解题思路：
    //  首先掌握哈希表用法（参考链接：https://blog.csdn.net/m0_70091181/article/details/135610035），这里使用unordered_set
    //  从字符串s的第一个字符出发，找到以每一个字符为开头的最长字串
    //      以abcabcbb为例，首先是a：abc，再是b：bca，再是c：cab，以此类推，此处需要循环体
    //  记录每一次的字串长度，更新最大值
    //  参考官方题解：https://leetcode.cn/problems/longest-substring-without-repeating-characters/solutions/227999/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/
    
    //成功通过，2024/8/27
    int lengthOfLongestSubstring(string s) {
        int len = s.length(); //记录字符串s的长度
        unordered_set<char> uset; //初始化unordered_set
        int ans = 0, right = 0; //求解最大值ans,右指针right用于计算字串长度
        for (int i = 0; i < len; ++i)
        {
            if (i != 0)
                uset.erase(s[i - 1]); //左指针右移一位，移除哈希表中前一个字符
            while (right < len && !uset.count(s[right]))
            {
                uset.insert(s[right]);
                ++right; //右指针右移
            }
            ans = max(ans, right - i);
        }
        return ans;
    }

    //4.寻找两个正序数组的中位数 难度：困难 提示：二分查找，分治
    //困难点：时间复杂度要求为O(log(m+n))
    //我的解题思路：
    //  既然是找中位数，对于一个正序数列，即使去掉第一个和最后一个（即最小最大值），中位数不变
    //  那么将该正序数列不断删减，最后剩下一个数则为中位数，剩下两个则取平均值
    //  第一感觉是要同时遍历两个数组一遍，但这样时间复杂度超出要求

    // 第一次尝试，利用递归，成功通过 2024/8/27
    // 虽然不是最佳，但好歹是O(m+n)
    // 内心OS：佩服自己写出来的屎山
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() == 1 && nums2.size() == 0)
            return nums1.back();
        else if (nums1.size() == 0 && nums2.size() == 1)
            return nums2.back();
        else if (nums1.size() == 1 && nums2.size() == 1)
            return double((nums1.back() + nums2.back())) / 2;
        else if (nums1.size() == 0 && nums2.size() > 1)
        {
            int len2 = nums2.size();
            if (len2 % 2)
                return nums2[(len2 - 1) / 2];
            else
                return double((nums2[len2 / 2] + nums2[(len2 / 2) - 1])) / 2;
        }
        else if (nums1.size() > 1 && nums2.size() == 0)
        {
            int len1 = nums1.size();
            if (len1 % 2)
                return nums1[(len1 - 1) / 2];
            else
                return double((nums1[len1 / 2] + nums1[(len1 / 2) - 1])) / 2;
        }
        else
        {
            if (nums1.front() <= nums2.front())
                nums1.erase(nums1.begin());
            else
                nums2.erase(nums2.begin());
            if (nums1.size() == 0)
            {
                nums2.pop_back();
                return findMedianSortedArrays(nums1, nums2);
            }
            else if (nums2.size() == 0)
            {
                nums1.pop_back();
                return findMedianSortedArrays(nums1, nums2);
            }
            if (nums1.back() >= nums2.back())
                nums1.pop_back();
            else
                nums2.pop_back();
            return findMedianSortedArrays(nums1, nums2);
        }
    }

    //官方题解
    //每次去除的不是头尾的一个元素，而是一段元素
    //作者：力扣官方题解
    //链接：https ://leetcode.cn/problems/median-of-two-sorted-arrays/solutions/258842/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        /* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
         * 这里的 "/" 表示整除
         * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
         * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
         * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
         * 这样 pivot 本身最大也只能是第 k-1 小的元素
         * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
         * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
         * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
         */
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;

        while (true) {
            // 边界情况
            if (index1 == m) {
                return nums2[index2 + k - 1];
            }
            if (index2 == n) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[index1], nums2[index2]);
            }

            // 正常情况
            int newIndex1 = min(index1 + k / 2 - 1, m - 1);
            int newIndex2 = min(index2 + k / 2 - 1, n - 1);
            int pivot1 = nums1[newIndex1];
            int pivot2 = nums2[newIndex2];
            if (pivot1 <= pivot2) {
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            }
            else {
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1) {
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        }
        else {
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }

    


    //5.最长回文子串 难度：中等 提示：动态规划
    //我的解题思路：
    //  以babad为例，bab和aba都符合题意
    //  用一个二维数组flag表示两个位置之间的字串是否回文，如上例中flag[0][2]和flag[1][3]为True表示bab和aba回文
    //  二维数组flag使用vector<vector<bool>>
    //  判断得到flag二维数组，判断是否为回文串可以从子串长度2到字符串长度依次判断
    //  这样问题转为在flag[i][j]为true的前提下求j-i+1的最大值，再得到字串
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) // 字符串长度为1时直接返回
            return s;

        int maxLen = 1; // 记录回文字串最大长度
        int begin = 0; // 标记回文字串起始位置

        vector<vector<bool>> flag(n, vector<bool>(n));
        for (int i = 0; i < n; ++i) // 所有长度为1的字串flag初始化为true
            flag[i][i] = true;
        for (int L = 2; L <= n; ++L) // 从字串长度为2开始判断
        {
            for (int i = 0; i < n; ++i) // 左边界从头开始
            {
                int j = L + i - 1; // 由左边界和子串长度L得右边界j
                if (j >= n) break; // 右边界越界退出循环
                if (s[i] != s[j]) // 字串左右两侧字符不同，flag为false
                    flag[i][j] = false;
                else // 字串左右两侧字符相同，分情况讨论
                {
                    if (L < 4) flag[i][j] = true; // 字串长度小于等于3时，字串一定回文
                    else flag[i][j] = flag[i + 1][j - 1]; // 字串长度大于3时，flag和长度减2的字串相同，相当于头尾各去掉一个字符
                }

                if (flag[i][j] && j - i + 1 > maxLen)
                {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen); // substr()的用法，参考链接：https://blog.csdn.net/weixin_42557996/article/details/112245613
    }

    //6.Z字形变换 提示：
    string convert(string s, int numRows) {
        
    }

    //7.整数反转 要点：溢出判断与处理
    int reverse(int x) {

    }

    //8.字符串转换整数
    int myAtoi(string s) {
        int result = 0;
        int temp = 0;
        int i = 0;
        bool flag = true;
        while (s[i] == ' ')
        {
            s.erase(s.begin());
            i++;
        }
        if (s[0] == '-')
        {
            s.erase(s.begin());
            flag = false;
        }
           
        for (int i = 0; i < s.size(); i++)
        {
            if (isdigit(s[i]))
                temp = temp * 10 + int(s[i]);
            else
            {
                if (flag && temp <= INT_MAX)
                    return temp;
                else if (flag && temp > INT_MAX)
                    return INT_MAX;
                else if (!flag && result - temp > INT_MIN)
                    return result - temp;
                else if (!flag && result - temp < INT_MIN)
                    return INT_MIN;
            }
        }

    }

    //15.三数之和
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> re;
        vector<int> temp = {0, 0, 0};


        return re;
    }

    //70.爬楼梯 要点：动态规划
    int climbStairs(int n) {
        if (n == 1)
            return 1;
        else if (n == 2)
            return 2;
        else
            return climbStairs(n - 1) + climbStairs(n - 2);
    }
};





