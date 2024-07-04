#include "signup.h"
#include "login.h"
#include "mainpanel.h"
#include "addlist.h"
#include "addtask.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication z(argc, argv);

    // Signup a;
    // a.show();

    // Login b;
    // b.show();

    MainPanel c;
    c.show();

    // AddList d;
    // d.show();

    // AddTask e;
    // e.show();

    return z.exec();
}
