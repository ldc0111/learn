#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
        int val;
        struct Node *next;

} ListNode;
/**
 *  * 已经定义的 ListNode 结点
 *   * typedef struct Node {
 *    *     int val;
 *     *     struct Node *next;
 *      * } ListNode;
 *       */
 ListNode* linkedListCycleLinkedNode(ListNode *head) {
         if(head == NULL) return NULL;
         ListNode *qu = head,*slow = head;
     while(qu && qu->next && slow) {
                 qu = qu->next->next;
                 slow = slow->next;
                 if(qu == slow) break;
             
     }
         if(qu || qu->next) return NULL;
         qu = head;
         while(qu != slow) qu = qu->next, slow = slow->next;
         return qu;

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
         int d;
             scanf("%d", &d);
         ListNode *Nth = head;
     while (d--) {
                 Nth = Nth->next;
             
     }
         temp->next = Nth;
             temp = head;
         head = head->next;
         free(temp);
         ListNode *node = linkedListCycleLinkedNode(head);
     if (!node) {
                 printf("No cycle\n");
             
     } else {
                 printf("%d\n", node->val);
             
     }
         return 0;

 }
