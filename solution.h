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
    //2.两数相加 提示：双指针
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

    

    //3.无重复字符的最长字串 提示：滑动窗口，哈希表，双指针
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

    //5.最长回文子串 提示：动态规划
    string longestPalindrome(string s) {
        
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





