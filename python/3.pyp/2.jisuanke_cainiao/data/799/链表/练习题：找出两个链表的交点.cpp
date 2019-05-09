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
ListNode* findIntersectionListNode(ListNode *head1, ListNode *head2) {
    if (head1 == NULL || head2 == NULL) return NULL;
    ListNode *tail1 = head1, *tail2 = head2;
    int len1 = 1,len2 = 1,ti;
    while (tail1->next != NULL) {
        tail1 = tail1->next;
        len1++;
    }
    while (tail2->next != NULL) {
        tail2 = tail2->next;
        len2++;
    }
    //printf("%d %d\n", len1,len2);
    if (tail1 != tail2) return NULL;
    if (len1 >= len2) {
        ti = len1 - len2;
        while (ti--) head1 = head1->next;
    } else {
        ti = len2 - len1;
        while (ti--) head2 = head2->next;
    }
    
    while (head1 != head2) {
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1;
}
int main() {
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    head->next = NULL;
    ListNode *temp = head;
    ListNode *ans = NULL;
    for (int i = 0; i < n; ++i) {
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = 0;
        temp->next->next = NULL;
        temp = temp->next;
        if (i == x) {
            ans = temp;
        }
    }
    temp = head;
    head = head->next;
    free(temp);
    ListNode *head2 = (ListNode*)malloc(sizeof(ListNode));
    head2->val = 0;
    head2->next = NULL;
    temp = head2;
    for (int i = 0; i < m; ++i) {
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = 0;
        temp->next->next = NULL;
        temp = temp->next;
    }
    temp->next = ans;
    temp = head2;
    head2 = head2->next;
    free(temp);
    temp = findIntersectionListNode(head, head2);
    if(temp == ans) {
        printf("Accept\n");
    } else {
        printf("Wrong answer\n");
    }
    return 0;
}