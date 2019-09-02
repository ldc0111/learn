/*************************************************************************
	> File Name: deleteNode.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年05月29日 星期三 15时10分14秒
 ************************************************************************/

#include<iostream>
using namespace std;

typedef struct ListNode{
    int val;
    struct ListNode *next;
}ListNode;

void deleteNode(ListNode *head, ListNode *tobeDelete) {
    if (head == NULL || tobeDelete == NULL) {
        return ;
    }
    if (tobeDelete->next != NULL) {
        //要删除的节点不是尾节点
        ListNode *nextNode = tobeDelete->next;
        tobeDelete->val = nextNode->val;
        tobeDelete->next = nextNode->next;
    } else {
        if (head == tobeDelete) {
            //只有一个节点
            head = NULL;
        } else {
            ListNode *curNode = head;
            while (curNode->next != tobeDelete) curNode = curNode->next;
            curNode->next = NULL;
        }
    }
    return ;
}


int main() {


    return 0;
}
