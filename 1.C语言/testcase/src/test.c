/*************************************************************************
	> File Name: test.c
	> Author: ldc
	> Mail:
	> Created Time: 2018年10月05日 星期五 15时16分21秒
 ************************************************************************/
#include <stdio.h>
#include "test.h"
//链表头部
static struct FuncData *FuncData_head = NULL;
//增加链表节点函数,头插法
void addFuncData(const char *a, const char *b, test_func_t func) {
    struct FuncData *p = (struct FuncData *)malloc(sizeof(struct FuncData));
    p->a_str = a;
    p->b_str = b;
    p->func = func;
    p->next = FuncData_head;
    FuncData_head = p;
    return ;
}

int RUN_ALL_TEST() {
    struct FuncData *current_node, *next_node;
    if (FuncData_head == NULL) return 0;
    current_node = FuncData_head->next;
    FuncData_head->next = NULL;
    //链表逆序
    while (current_node != NULL) {
        next_node = current_node->next;
        current_node->next = FuncData_head;
        FuncData_head = current_node;
        current_node = next_node;
    }
    //三种不同测试结果的输出样式
    char color[3][100] = {
        "[ \033[1;32m%.2lf%%\033[0m ] total : %d，expect : %d\n",
        "[ \033[0;31m%.2lf%%\033[0m ] total : %d，expect : %d\n",
        "[ \033[1;31m%.2lf%%\033[0m ] total : %d，expect : %d\n"};
    //遍历链表,并且处理每个节点信息
    for (struct FuncData *p = FuncData_head; p; p = p->next) {
        printf("[%s, %s]\n", p->a_str, p->b_str);
        struct TestFuncData data = {0, 0};
        p->func(&data);
        double rate = 1.0 * data.expect / data.total * 100;
        int index = 0;
        if (rate < 100) index = 1;
        if (rate < 50) index = 2;
        printf(color[index], rate, data.total, data.expect);
    }
    return 0;
}
