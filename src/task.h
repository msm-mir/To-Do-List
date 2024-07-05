#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task {
private:
    int id;
    int listId;
    QString name;
    QDate date;
    QString detail = "";
    QString assign = "";
    bool star = false;
    bool complete = false;

public:
    Task();
    ~Task();

    void setId(int);
    int getId();

    void setListId(int);
    int getListId();

    void setName(QString);
    QString getName();

    void setDate(QDate);
    QDate getDate();

    void setDetail(QString);
    QString getDetail();

    void setAssign(QString);
    QString getAssign();

    void setStar(bool);
    bool getStar();

    void setComplete(bool);
    bool getComplete();
};

#endif // TASK_H
