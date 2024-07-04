#ifndef ADDLIST_H
#define ADDLIST_H

#include <QMainWindow>

namespace Ui { class AddList; }

class AddList : public QMainWindow { Q_OBJECT

public:
    explicit AddList(QWidget *parent = nullptr);
    ~AddList();

private:
    Ui::AddList *ui;
};

#endif // ADDLIST_H
