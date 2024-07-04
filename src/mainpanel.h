#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "login.h"

namespace Ui { class MainPanel; }

class MainPanel : public QMainWindow { Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = nullptr);
    ~MainPanel();

    void connections();

private slots:
    void onPushButtonTodayClicked();
    void onPushButtonListsClicked();
    void onPushButtonTasksClicked();
    void onPushButtonStarTasksClicked();
    void onPushButtonCompletedClicked();
    void onPushButtonAssignedMeClicked();
    void onPushButtonAssignedOtherClicked();
    void onPushButtonLogoutClicked();
    void onAddWidget();
    void onRemoveWidget();

private:
    Ui::MainPanel *ui;
};

#endif // MAINPANEL_H
