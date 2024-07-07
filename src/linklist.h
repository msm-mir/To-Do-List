#ifndef LINKLIST_H
#define LINKLIST_H

template <class T>
class Node {
private:
    T data;
    Node<T> *nextNode;
    Node<T> *previousNode;

public:
    Node(T data) {
        this->data = data;
        this->nextNode = nullptr;
        this->previousNode = nullptr;
    }
    void setData(T data) {
        this->data = data;
    }
    void setNextNode(Node<T> * nextNode) {
        this->nextNode = nextNode;
    }
    void setPreviousNode(Node<T> * previousNode) {
        this->previousNode = previousNode;
    }
    T getData() {
        return this->data;
    }
    Node<T>* getNextNode() {
        return this->nextNode;
    }
    Node<T>* getPreviousNode() {
        return this->previousNode;
    }
};

template <class T>
class LinkList {
private:
    Node<T> *headNode;
    Node<T> *tailNode;
    int size;

public:
    LinkList() {
        this->size = 0;
        this->headNode = nullptr;
        this->tailNode = nullptr;
    }
    Node<T>* getHeadNode() {
        return this->headNode;
    }
    Node<T>* getTailNode() {
        return this->tailNode;
    }
    void pushBack(T data) {
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
    int getSize() {
        return size;
    }
};

#endif // LINKLIST_H
