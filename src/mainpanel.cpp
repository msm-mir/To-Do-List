#include "mainpanel.h"
#include "ui_mainpanel.h"

MainPanel::MainPanel(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainPanel) {
    ui->setupUi(this);

    connections();
}

MainPanel::~MainPanel() {
    delete ui;
}

void MainPanel::connections() {
    //menu push buttons
    connect(ui->pushButtonToday, SIGNAL(clicked()), this, SLOT(onPushButtonTodayClicked()));
    connect(ui->pushButtonLists, SIGNAL(clicked()), this, SLOT(onPushButtonListsClicked()));
    connect(ui->pushButtonTasks, SIGNAL(clicked()), this, SLOT(onPushButtonTasksClicked()));
    connect(ui->pushButtonStarTasks, SIGNAL(clicked()), this, SLOT(onPushButtonStarTasksClicked()));
    connect(ui->pushButtonCompleted, SIGNAL(clicked()), this, SLOT(onPushButtonCompletedClicked()));
    connect(ui->pushButtonAssignedMe, SIGNAL(clicked()), this, SLOT(onPushButtonAssignedMeClicked()));
    connect(ui->pushButtonAssignedOther, SIGNAL(clicked()), this, SLOT(onPushButtonAssignedOtherClicked()));
    connect(ui->pushButtonLogout, SIGNAL(clicked()), this, SLOT(onPushButtonLogoutClicked()));

    connect(ui->pushButtonAddList, SIGNAL(clicked()), this, SLOT(onAddWidget()));
}

void MainPanel::onPushButtonTodayClicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainPanel::onPushButtonListsClicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainPanel::onPushButtonTasksClicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainPanel::onPushButtonStarTasksClicked() {
    ui->stackedWidget->setCurrentIndex(3);
}

void MainPanel::onPushButtonCompletedClicked() {
    ui->stackedWidget->setCurrentIndex(6);
}

void MainPanel::onPushButtonAssignedMeClicked() {
    ui->stackedWidget->setCurrentIndex(4);
}

void MainPanel::onPushButtonAssignedOtherClicked() {
    ui->stackedWidget->setCurrentIndex(5);
}

void MainPanel::onPushButtonLogoutClicked() {
    Login *newPage = new Login;
    newPage->show();
    this->close();
}

void MainPanel::onAddWidget() {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->frame->layout());

    QString buttonText = tr("Button: %1").arg(layout->count());
    QPushButton *button = new QPushButton(buttonText, ui->frame);
    layout->insertWidget(0, button);

    connect(button, SIGNAL(clicked()), this, SLOT(onRemoveWidget()));
}

void MainPanel::onRemoveWidget() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    delete button;
}
