/*************************************************************************
	> File Name: test.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月24日 星期六 22时42分37秒
 ************************************************************************/
/*************************************************************************
  > File Name: linklist.c
  > Author: ShangKe
  > Mail: 
  > Created Time: 2018年06月06日 星期三 18时09分16秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
}LinkNode, Node;


typedef struct LinkList {
    LinkNode *head;
    int length;
} LinkList;

void output(LinkList *list) {
    LinkNode *head = list->head;
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("null\n");
}


LinkList *init() {
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));
    p->length = 0;
    return p;
}

LinkNode *getNewNode(int data) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = data;
    p->next = NULL;
    return p;
}

int insert(LinkList *list, int data, int ind) {
    if (ind < 0 || ind > list->length) return 0;
    LinkNode ret, *p;
    ret.next = list->head;
    p = &ret;
    while (ind--) {
        p = p->next;
    }
    LinkNode *new_node = getNewNode(data);
    new_node->next = p->next;
    p->next = new_node;
    list->head = ret.next;
    list->length++;
    return 1;
}

void clear(LinkList *list) {
    LinkNode *head = list->head;
    while (head) {
        LinkNode *p = head->next;
        free(head);
        head = p;
    }
    free(list);
    return;
}

int judge(LinkList *l) {
    LinkNode *p = l->head;
    while (p && p->next) {
        if (p->data > p->next->data) return 0;
        p = p->next;
    }
    return 1;
}


void l_sort(LinkNode *head, LinkNode *tail) {
  if (head == NULL || head == tail || head->next == tail) return ;
  int data = head->data;
  LinkNode *tmp = head;
  LinkNode *p = head->next;
  while (p != tail) {
    if (p->data < data) {
      int temp = p->data;
      p->data = tmp->data;
      tmp->data = temp;
      tmp = tmp->next;
    }
    p = p->next;
  }
  if (head == tmp) {
    l_sort(tmp->next, tail);
      return ;
  }
  l_sort(head, tmp);
  l_sort(tmp, tail);
  return ;
}

//没有有虚拟头节点,最后一个节点不参与排序
Node* quick_sort(Node *head, Node *tail){
    if(head == NULL) return NULL;
    if(head->next == NULL) return head;
    Node temp;//虚拟节点
    temp.next = head;
    Node *x = head, *y = tail, *z = head;
    while(x != y && x->next != NULL){ 
        while(x != y && x->next != NULL && x->next->data >= z->data) x = x->next;
        
        printf("%d",x->data);
        Node *inse = x->next;
        x->next = inse->next;
        //inse->next = temp.next;
        //temp.next = inse->next;
    }

    //temp.next = quick_sort(temp.next, z);
    //z->next = quick_sort(z->next, NULL);
    return temp.next;
}
int main() {
    //while (1) { 
        LinkList *linklist = init();
        srand(time(0));
        for (int i = 0; i < 20; i++) {
            int data = rand() % 100, ind = rand() % (i + 1);
            printf("%d : insert(%d, %d) = \n", i, data, ind);
            insert(linklist, data, ind);
            printf("insert end\n");
            fflush(stdout);
            output(linklist);
            quick_sort(linklist->head, NULL);
            //l_sort(linklist->head, NULL);
            printf("sort end : ");
            output(linklist);
            if (!judge(linklist)) {
                getchar();
            }
            printf("\n");
        }
        free(linklist);
    //}
    return 0;
}
