#ifndef LINKLIST_H
#define LINKLIST_H

#include <task.h>

template<typename T>
class Node {
private:
    T data;
    Node<T> *nextNode;
    Node<T> *previousNode;
public:
    Node(T data);
    void setData(T data);
    void setNextNode(Node<T> *nextNode);
    void setPreviousNode(Node<T> *previousNode);
    T getData();
    Node<T>* getNextNode();
    Node<T>* getPreviousNode();
};

template<typename T>
class LinkList {
private:
    Node<T> *headNode;
    Node<T> *tailNode;
    int size;
public:
    LinkList();
    Node<T>* getHeadNode();
    Node<T>* getTailNode();
    void pushBack(T data);
    int getSize();
};

template<typename T>
Node<T>::Node(T data) {
    this->data = data;
    this->nextNode = nullptr;
    this->previousNode = nullptr;
}
template<typename T>
void Node<T>::setData(T data) {
    this->data = data;
}
template<typename T>
void Node<T>::setNextNode(Node<T> * nextNode) {
    this->nextNode = nextNode;
}
template<typename T>
void Node<T>::setPreviousNode(Node<T> * previousNode) {
    this->previousNode = previousNode;
}
template<typename T>
T Node<T>::getData() {
    return this->data;
}
template<typename T>
Node<T>* Node<T>::getNextNode() {
    return this->nextNode;
}
template<typename T>
Node<T>* Node<T>::getPreviousNode() {
    return this->previousNode;
}

template<typename T>
LinkList<T>::LinkList() {
    this->size = 0;
    this->headNode = nullptr;
    this->tailNode = nullptr;
}
template<typename T>
Node<T>* LinkList<T>::getHeadNode() {
    return this->headNode;
}
template<typename T>
Node<T>* LinkList<T>::getTailNode() {
    return this->tailNode;
}
template<typename T>
void LinkList<T>::pushBack(T data) {
    Node<T> *tmp = new Node<T>(data);
    tmp->setNextNode(nullptr);
    tmp->setPreviousNode(this->tailNode);

    if (headNode == nullptr) {
        headNode = tmp;
    }

    this->tailNode = tmp;
    this->size++;

    if (tmp->getPreviousNode() != nullptr) {
        (tmp->getPreviousNode())->setNextNode(this->tailNode);
    }
}
template<typename T>
int LinkList<T>::getSize() {
    return size;
}


#endif // LINKLIST_H
