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
    //2.������� ��ʾ��˫ָ��
    //�ҵĽ���˼·��
    //  ����λֱ�Ӽ���洢�ڵ�ǰλ��
    //  ��λ��Ҫ�õ���һλָ�룺��һλ�Ӻ͡�10����ǰλ����10
    //  ��Ҫ�ж��Ƿ��Ѿ������һλ
    //  ����ֱ�Ӵ洢������һ�����飬�����ٷ����µĿռ�(���ò�����)

    /*ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {//���Եݹ�
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

    //�ɹ�ͨ����2024/8/27
    //˼·������������ɵȳ��ټ���
    //����ʱ����ڴ����ı��ֲ���
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l1_head = l1;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val + l2->val < 10) //����λ
                l1->val = l1->val + l2->val;
            else if (l1->val + l2->val >= 10 && l1->next != nullptr) //��ͨ��λ
            {
                (l1->next->val)++;
                l1->val = (l1->val + l2->val) % 10;
            }
            else if (l1->val + l2->val >= 10 && l1->next == nullptr) //��λʱ��һλ�洢�ռ�Ϊnullptr
            {
                l1->next = new ListNode(1);
                l1->val = (l1->val + l2->val) % 10;
            }
            if (l2->next == nullptr && l1->next != nullptr) //��������ͬ
                l2->next = new ListNode(0);
            else if (l2->next != nullptr && l1->next == nullptr)
                l1->next = new ListNode(0);
            l1 = l1->next;
            l2 = l2->next;
        }
        return l1_head;
    }

    //�ٷ����
    //���ߣ����۹ٷ����
    //���ӣ���https ://leetcode.cn/problems/add-two-numbers/solutions/435246/liang-shu-xiang-jia-by-leetcode-solution/��
    //��Դ�����ۣ�LeetCode��
    //��������Լ��ķ������ٶ����������������ڴ���
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr, * tail = nullptr; //�����¿ռ�洢
        int carry = 0; //��λֵ
        while (l1 || l2) {
            int n1 = l1 ? l1->val : 0; //��ȡl1�ڵ�Я��ֵ����l1Ϊ��ָ����ȡ0
            int n2 = l2 ? l2->val : 0; //ͬ��
            int sum = n1 + n2 + carry;
            if (!head) { //��ʼ����ͷΪ��
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
        if (carry > 0) { //���һλ�н�λֵ����Ҫ���һλ�洢
            tail->next = new ListNode(carry);
        }
        return head;
    }

    

    //3.���ظ��ַ�����ִ� ��ʾ���������ڣ���ϣ��˫ָ��
    //�ҵĽ���˼·��
    //  �������չ�ϣ���÷����ο����ӣ�https://blog.csdn.net/m0_70091181/article/details/135610035��������ʹ��unordered_set
    //  ���ַ���s�ĵ�һ���ַ��������ҵ���ÿһ���ַ�Ϊ��ͷ����ִ�
    //      ��abcabcbbΪ����������a��abc������b��bca������c��cab���Դ����ƣ��˴���Ҫѭ����
    //  ��¼ÿһ�ε��ִ����ȣ��������ֵ
    //  �ο��ٷ���⣺https://leetcode.cn/problems/longest-substring-without-repeating-characters/solutions/227999/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/
    
    //�ɹ�ͨ����2024/8/27
    int lengthOfLongestSubstring(string s) {
        int len = s.length(); //��¼�ַ���s�ĳ���
        unordered_set<char> uset; //��ʼ��unordered_set
        int ans = 0, right = 0; //������ֵans,��ָ��right���ڼ����ִ�����
        for (int i = 0; i < len; ++i)
        {
            if (i != 0)
                uset.erase(s[i - 1]); //��ָ������һλ���Ƴ���ϣ����ǰһ���ַ�
            while (right < len && !uset.count(s[right]))
            {
                uset.insert(s[right]);
                ++right; //��ָ������
            }
            ans = max(ans, right - i);
        }
        return ans;
    }

    //5.������Ӵ� ��ʾ����̬�滮
    string longestPalindrome(string s) {
        
    }

    //6.Z���α任 ��ʾ��
    string convert(string s, int numRows) {
        
    }

    //7.������ת Ҫ�㣺����ж��봦��
    int reverse(int x) {

    }

    //8.�ַ���ת������
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

    //15.����֮��
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> re;
        vector<int> temp = {0, 0, 0};


        return re;
    }

    //70.��¥�� Ҫ�㣺��̬�滮
    int climbStairs(int n) {
        if (n == 1)
            return 1;
        else if (n == 2)
            return 2;
        else
            return climbStairs(n - 1) + climbStairs(n - 2);
    }
};





