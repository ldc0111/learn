#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} ListNode;
/**
 * 已经定义的 ListNode 结点
 * typedef struct Node {
 *     int val;
 *     struct Node *next;
 * } ListNode;
 */
//思路找到选择一个基准值，遍历区间的链表吧小于基准值的都插到基准值前面
#define swap(a,b) ({a ^= b; b ^= a; a ^= b;})
ListNode *quick_sort(ListNode *head, ListNode *end) {
    if (head == end) return head;//head和end是同一个节点，或者为末尾的时候
    int val = head->val;
    ListNode * p = head, *q = head->next;
    while (q != end) {
        if (q->val < val) {
            swap(p->val,q->val);
            p = p->next;
        }
        q = q->next;
    }
    if (head == p) {
        quick_sort(p->next,end);
        return ;
    }
    quick_sort(head,p);
    quick_sort(p,end);
    return ;
}

ListNode* linkedListSort(ListNode *head) {
    quick_sort(head,NULL);
    return head;
}
int main() {
    int n;
    scanf("%d", &n);
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    head->next = NULL;
    ListNode *temp = head;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = x;
        temp->next->next = NULL;
        temp = temp->next;
    }
    temp = head;
    head = head->next;
    free(temp);
    head = linkedListSort(head);
    temp = head;
    while (head) {
        printf("%d ", head->val);
        head = head->next;
        free(temp);
        temp = head;
    }
    printf("\n");
    return 0;
}