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
    //2.������� �Ѷȣ��е� ��ʾ��˫ָ��
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

    

    //3.���ظ��ַ�����ִ� �Ѷȣ��е� ��ʾ���������ڣ���ϣ��˫ָ��
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

    //4.Ѱ�����������������λ�� �Ѷȣ����� ��ʾ�����ֲ��ң�����
    //���ѵ㣺ʱ�临�Ӷ�Ҫ��ΪO(log(m+n))
    //�ҵĽ���˼·��
    //  ��Ȼ������λ��������һ���������У���ʹȥ����һ�������һ��������С���ֵ������λ������
    //  ��ô�����������в���ɾ�������ʣ��һ������Ϊ��λ����ʣ��������ȡƽ��ֵ
    //  ��һ�о���Ҫͬʱ������������һ�飬������ʱ�临�Ӷȳ���Ҫ��

    // ��һ�γ��ԣ����õݹ飬�ɹ�ͨ�� 2024/8/27
    // ��Ȼ������ѣ����ô���O(m+n)
    // ����OS������Լ�д������ʺɽ
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

    //�ٷ����
    //ÿ��ȥ���Ĳ���ͷβ��һ��Ԫ�أ�����һ��Ԫ��
    //���ߣ����۹ٷ����
    //���ӣ�https ://leetcode.cn/problems/median-of-two-sorted-arrays/solutions/258842/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        /* ��Ҫ˼·��Ҫ�ҵ��� k (k>1) С��Ԫ�أ���ô��ȡ pivot1 = nums1[k/2-1] �� pivot2 = nums2[k/2-1] ���бȽ�
         * ����� "/" ��ʾ����
         * nums1 ��С�ڵ��� pivot1 ��Ԫ���� nums1[0 .. k/2-2] ���� k/2-1 ��
         * nums2 ��С�ڵ��� pivot2 ��Ԫ���� nums2[0 .. k/2-2] ���� k/2-1 ��
         * ȡ pivot = min(pivot1, pivot2)������������С�ڵ��� pivot ��Ԫ�ع��Ʋ��ᳬ�� (k/2-1) + (k/2-1) <= k-2 ��
         * ���� pivot �������Ҳֻ���ǵ� k-1 С��Ԫ��
         * ��� pivot = pivot1����ô nums1[0 .. k/2-1] ���������ǵ� k С��Ԫ�ء�����ЩԪ��ȫ�� "ɾ��"��ʣ�µ���Ϊ�µ� nums1 ����
         * ��� pivot = pivot2����ô nums2[0 .. k/2-1] ���������ǵ� k С��Ԫ�ء�����ЩԪ��ȫ�� "ɾ��"��ʣ�µ���Ϊ�µ� nums2 ����
         * �������� "ɾ��" ��һЩԪ�أ���ЩԪ�ض��ȵ� k С��Ԫ��ҪС���������Ҫ�޸� k ��ֵ����ȥɾ�������ĸ���
         */
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;

        while (true) {
            // �߽����
            if (index1 == m) {
                return nums2[index2 + k - 1];
            }
            if (index2 == n) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[index1], nums2[index2]);
            }

            // �������
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

    


    //5.������Ӵ� �Ѷȣ��е� ��ʾ����̬�滮
    //�ҵĽ���˼·��
    //  ��babadΪ����bab��aba����������
    //  ��һ����ά����flag��ʾ����λ��֮����ִ��Ƿ���ģ���������flag[0][2]��flag[1][3]ΪTrue��ʾbab��aba����
    //  ��ά����flagʹ��vector<vector<bool>>
    //  �жϵõ�flag��ά���飬�ж��Ƿ�Ϊ���Ĵ����Դ��Ӵ�����2���ַ������������ж�
    //  ��������תΪ��flag[i][j]Ϊtrue��ǰ������j-i+1�����ֵ���ٵõ��ִ�
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) // �ַ�������Ϊ1ʱֱ�ӷ���
            return s;

        int maxLen = 1; // ��¼�����ִ���󳤶�
        int begin = 0; // ��ǻ����ִ���ʼλ��

        vector<vector<bool>> flag(n, vector<bool>(n));
        for (int i = 0; i < n; ++i) // ���г���Ϊ1���ִ�flag��ʼ��Ϊtrue
            flag[i][i] = true;
        for (int L = 2; L <= n; ++L) // ���ִ�����Ϊ2��ʼ�ж�
        {
            for (int i = 0; i < n; ++i) // ��߽��ͷ��ʼ
            {
                int j = L + i - 1; // ����߽���Ӵ�����L���ұ߽�j
                if (j >= n) break; // �ұ߽�Խ���˳�ѭ��
                if (s[i] != s[j]) // �ִ����������ַ���ͬ��flagΪfalse
                    flag[i][j] = false;
                else // �ִ����������ַ���ͬ�����������
                {
                    if (L < 4) flag[i][j] = true; // �ִ�����С�ڵ���3ʱ���ִ�һ������
                    else flag[i][j] = flag[i + 1][j - 1]; // �ִ����ȴ���3ʱ��flag�ͳ��ȼ�2���ִ���ͬ���൱��ͷβ��ȥ��һ���ַ�
                }

                if (flag[i][j] && j - i + 1 > maxLen)
                {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen); // substr()���÷����ο����ӣ�https://blog.csdn.net/weixin_42557996/article/details/112245613
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





