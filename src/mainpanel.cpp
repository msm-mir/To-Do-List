#include "mainpanel.h"
#include "ui_mainpanel.h"

MainPanel::MainPanel(std::map<QString,User> users, QString username, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainPanel) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;

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

    connect(ui->pushButtonAddList, SIGNAL(clicked()), this, SLOT(addListsWidget()));
    connect(ui->pushButtonAddTask, SIGNAL(clicked()), this, SLOT(addListTasksWidget()));
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
    ui->stackedWidget->setCurrentIndex(4);
}

void MainPanel::onPushButtonAssignedMeClicked() {
    ui->stackedWidget->setCurrentIndex(5);
}

void MainPanel::onPushButtonAssignedOtherClicked() {
    ui->stackedWidget->setCurrentIndex(6);
}

void MainPanel::onPushButtonLogoutClicked() {
    Login *newPage = new Login(users);
    newPage->show();
    this->close();
}

void MainPanel::onListClicked() {
    ui->stackedWidget->setCurrentIndex(7);
}

void MainPanel::addListsWidget() {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->frame->layout());

    QHBoxLayout *newLayout = new QHBoxLayout(ui->frame);

    QString buttonText = tr("List");
    QString buttonTextEdit = tr("Edit");
    QString buttonTextDelete = tr("Delete");

    QPushButton *listButton = new QPushButton(buttonText, ui->frame);
    newLayout->addWidget(listButton);
    listButton->setFixedSize(350, 40);

    QPushButton *editButton = new QPushButton(buttonTextEdit, ui->frame);
    newLayout->addWidget(editButton);
    editButton->setFixedSize(65, 40);

    QPushButton *deleteButton = new QPushButton(buttonTextDelete, ui->frame);
    newLayout->addWidget(deleteButton);
    deleteButton->setFixedSize(80, 40);

    layout->insertLayout(0, newLayout);
    mButtonToLayoutMap.insert(deleteButton, newLayout);

    connect(listButton, SIGNAL(clicked()), this, SLOT(onListClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(removeWidgets()));
}

void MainPanel::addListTasksWidget() {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->frame_2->layout());

    QHBoxLayout *newLayout = new QHBoxLayout(ui->frame_2);

    QString buttonText = tr("Task");
    QString buttonTextEdit = tr("Edit");
    QString buttonTextDelete = tr("Delete");

    QPushButton *TaskButton = new QPushButton(buttonText, ui->frame_2);
    newLayout->addWidget(TaskButton);
    TaskButton->setFixedSize(350, 40);

    QPushButton *editButton = new QPushButton(buttonTextEdit, ui->frame_2);
    newLayout->addWidget(editButton);
    editButton->setFixedSize(65, 40);

    QPushButton *deleteButton = new QPushButton(buttonTextDelete, ui->frame_2);
    newLayout->addWidget(deleteButton);
    deleteButton->setFixedSize(80, 40);

    layout->insertLayout(0, newLayout);

    mButtonToLayoutMap.insert(deleteButton, newLayout);

    connect(deleteButton, SIGNAL(clicked()), this, SLOT(removeWidgets()));
}

void MainPanel::removeWidgets() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QHBoxLayout *layout = mButtonToLayoutMap.take(button);

    while (layout->count() != 0) {
        QLayoutItem *item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }

    delete layout ;
}
