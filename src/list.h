#ifndef LIST_H
#define LIST_H

#include <QString>
#include "task.h"
#include "linklist.h"

enum Color {
    none, blue, green, pink, purple
};

class List {
private:
    int id;
    QString userId;
    QString name;
    Color color;
    LinkList<Task> tasks;

public:
    List();
    ~List();

    void setId(int);
    int getId();

    void setUserId(QString);
    QString getUserId();

    void setName(QString);
    QString getName();

    void setColor(Color);
    Color getColor();

    void addTasks(Task);
    Task getTasks(int);
    int getTasksSize();

    void operator << (Task);
};

#endif // LIST_H
