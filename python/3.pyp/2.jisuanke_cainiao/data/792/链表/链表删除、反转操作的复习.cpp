#include <iostream>
#include<iostream>
using namespace std;

template <typename Type> class Node {
public:
    Type data;
    Node<Type> *next;
    Node(const Type &_data) {
        data = _data;
        next = NULL;
    }
};
template <typename Type> class LinkedList {
private:
    Node<Type> *head;
public:
    LinkedList() {
        head = NULL;
    }
    ~LinkedList() {
        Node<Type> *current_node = head;
        while (current_node != NULL) {
            Node<Type> *delete_node = current_node;
            current_node = current_node->next;
            delete delete_node;
        }
    }
    bool insert(Node<Type> *node, int index) {
        if (head == NULL) {
            if (index != 0) {
                return false;
            }
            head = node;
            return true;
        }
        if (index == 0) {
            node->next = head;
            head = node;
            return true;
        }
        Node<Type> *current_node = head;
        int count = 0;
        while (current_node->next != NULL && count < index - 1) {
            current_node = current_node->next;
            count++;
        }
        if (count == index - 1) {
            node->next = current_node->next;
            current_node->next = node;
            return true;
        }
        return false;
    }
    void output() {
        if (head == NULL) {
            return;
        }
        Node<Type> *current_node = head;
        while (current_node != NULL) {
            cout << current_node->data << " ";
            current_node = current_node->next;
        }
        cout << endl;
    }
    int delete_node(int index) {
        if(head == NULL){
            return 0;
        }
        Node <Type> *current_node = head;
        int count = 0;
        if(index == 0){
            head = head->next;
            free(current_node);
            return 1;
        }
        while(current_node->next != NULL && count < index - 1){
            current_node = current_node->next;
            count++;
        }
        if (count == index - 1 && current_node->next != NULL) {
            Node <Type> * delete_node = current_node->next;
            current_node->next = delete_node->next;
            free(delete_node);
            return 1;
        }
        return 0;
    }
    void reverse() {
        if(head == NULL) {
            return ;
        }
        Node <Type> *next_node, *current_node;
        current_node = head->next;
        head->next = NULL;
        while(current_node!= NULL){
            next_node = current_node->next;
            current_node->next = head;
            head = current_node;
            current_node = next_node;
        }
        return ;
    }
};
int main() {
    LinkedList<int> linkedlist;
    int n,x,y,z;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if(x == 1){
            cin >> y >> z;
            Node<int> *node = (Node<int> *)malloc(sizeof(Node<int>));
            node->data = z;
            node->next = NULL;
            if(linkedlist.insert(node,y)){
                printf("success\n");
            }else{
                printf("failed\n");
            }
        }else if(x == 2) {
            linkedlist.output();
            
        }else if(x == 3){
            cin >> y;
            if(linkedlist.delete_node(y)){
                printf("success\n");
            }else {
                printf("failed\n");
            }
        }else{
            linkedlist.reverse();
        }
    }
    return 0;
}