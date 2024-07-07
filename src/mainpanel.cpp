#include "mainpanel.h"
#include "ui_mainpanel.h"

MainPanel::MainPanel(std::map<QString,User> users, QString username, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainPanel) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;

    setProfile();

    connections();

    removeWidgets(ui->listFrame);
    removeWidgets(ui->listTasksFrame);
    removeWidgets(ui->starTasksFrame);
}

MainPanel::~MainPanel() {
    delete ui;
}

void MainPanel::setProfile() {
    for (auto &itr : users)
        if (itr.first == username) {
            ui->labelName->setText(itr.second.getFirstName()+" "+itr.second.getLastName());
            ui->labelUsername->setText(username);
        }
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

    connect(ui->pushButtonAddList, SIGNAL(clicked()), this, SLOT(openAddListPage()));
}

void MainPanel::onPushButtonTodayClicked() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->groupBoxPanel->setTitle("Today");
}

void MainPanel::onPushButtonListsClicked() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->groupBoxPanel->setTitle("Lists");

    removeWidgets(ui->listFrame);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                addListsWidget(itr.second.getLists(i).getName(), i);
}

void MainPanel::onPushButtonTasksClicked() {
    ui->stackedWidget->setCurrentIndex(2);
    ui->groupBoxPanel->setTitle("Tasks");
}

void MainPanel::onPushButtonStarTasksClicked() {
    ui->stackedWidget->setCurrentIndex(3);
    ui->groupBoxPanel->setTitle("Star Tasks");

    removeWidgets(ui->starTasksFrame);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                    if (itr.second.getLists(i).getTasks(j).getStar())
                        addStarTasksWidget(itr.second.getLists(i).getTasks(j).getName());
}

void MainPanel::onPushButtonCompletedClicked() {
    ui->stackedWidget->setCurrentIndex(4);
    ui->groupBoxPanel->setTitle("Completed Tasks");
}

void MainPanel::onPushButtonAssignedMeClicked() {
    ui->stackedWidget->setCurrentIndex(5);
    ui->groupBoxPanel->setTitle("Assigned To Me");


}

void MainPanel::onPushButtonAssignedOtherClicked() {
    ui->stackedWidget->setCurrentIndex(6);
    ui->groupBoxPanel->setTitle("Assigned To Other");
}

void MainPanel::onPushButtonLogoutClicked() {
    Login *newPage = new Login(users);
    newPage->show();
    this->close();
}

void MainPanel::onListClicked(int listId) {
    ui->stackedWidget->setCurrentIndex(7);
    ui->groupBoxPanel->setTitle("List Tasks");

    removeWidgets(ui->listTasksFrame);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getLists(listId).getTasksSize(); i++)
                addListTasksWidget(itr.second.getLists(i).getTasks(listId).getName());

    connect(ui->pushButtonAddTask, SIGNAL(clicked()), this, SLOT(openAddTaskPage(listId)));
}

void MainPanel::openAddListPage() {
    AddList *newPage = new AddList(users, username);
    newPage->show();
    this->close();
}

void MainPanel::openAddTaskPage(int listId) {
    AddTask *newPage = new AddTask(users, username, listId);
    newPage->show();
    this->close();
}

void MainPanel::addListsWidget(QString qButton, int listId) {
    static int cnt = 0;

    if (cnt == 0)
        listLayout = qobject_cast<QVBoxLayout*>(ui->listFrame->layout());
    cnt++;

    QHBoxLayout *newListLayout = new QHBoxLayout(ui->listFrame);

    QString buttonText = tr(qButton.toUtf8().constData());
    QString buttonTextEdit = tr("Edit");
    QString buttonTextDelete = tr("Delete");

    QPushButton *listButton = new QPushButton(buttonText, ui->listFrame);
    newListLayout->addWidget(listButton);
    listButton->setFixedSize(350, 40);

    QPushButton *editButton = new QPushButton(buttonTextEdit, ui->listFrame);
    newListLayout->addWidget(editButton);
    editButton->setFixedSize(65, 40);

    QPushButton *deleteButton = new QPushButton(buttonTextDelete, ui->listFrame);
    newListLayout->addWidget(deleteButton);
    deleteButton->setFixedSize(80, 40);

    listLayout->insertLayout(0, newListLayout);

    connect(listButton, SIGNAL(clicked()), this, SLOT(onListClicked(listId)));
}

void MainPanel::addListTasksWidget(QString qButton) {
    static int cnt = 0;

    if (cnt == 0)
        listTasksLayout = qobject_cast<QVBoxLayout*>(ui->listTasksFrame->layout());
    cnt++;

    QHBoxLayout *newListTasksLayout = new QHBoxLayout(ui->listTasksFrame);

    QString buttonText = tr(qButton.toUtf8().constData());
    QString buttonTextEdit = tr("Edit");
    QString buttonTextDelete = tr("Delete");

    QPushButton *listTasksButton = new QPushButton(buttonText, ui->listTasksFrame);
    newListTasksLayout->addWidget(listTasksButton);
    listTasksButton->setFixedSize(350, 40);

    QPushButton *editButton = new QPushButton(buttonTextEdit, ui->listTasksFrame);
    newListTasksLayout->addWidget(editButton);
    editButton->setFixedSize(65, 40);

    QPushButton *deleteButton = new QPushButton(buttonTextDelete, ui->listTasksFrame);
    newListTasksLayout->addWidget(deleteButton);
    deleteButton->setFixedSize(80, 40);

    listTasksLayout->insertLayout(0, newListTasksLayout);
}

void MainPanel::addStarTasksWidget(QString qButton) {
    static int cnt = 0;

    if (cnt == 0)
        starTasksLayout = qobject_cast<QVBoxLayout*>(ui->starTasksFrame->layout());
    cnt++;

    QHBoxLayout *newStarTasksLayout = new QHBoxLayout(ui->starTasksFrame);

    QString buttonText = tr(qButton.toUtf8().constData());
    QString buttonTextEdit = tr("Edit");
    QString buttonTextDelete = tr("Delete");

    QPushButton *starTasksButton = new QPushButton(buttonText, ui->starTasksFrame);
    newStarTasksLayout->addWidget(starTasksButton);
    starTasksButton->setFixedSize(350, 40);

    QPushButton *editButton = new QPushButton(buttonTextEdit, ui->starTasksFrame);
    newStarTasksLayout->addWidget(editButton);
    editButton->setFixedSize(65, 40);

    QPushButton *deleteButton = new QPushButton(buttonTextDelete, ui->starTasksFrame);
    newStarTasksLayout->addWidget(deleteButton);
    deleteButton->setFixedSize(80, 40);

    starTasksLayout->insertLayout(0, newStarTasksLayout);
}

void MainPanel::removeWidgets(QFrame *frame) {
    QVBoxLayout *fLayout = qobject_cast<QVBoxLayout*>(frame->layout());

    while (fLayout->count() != 1) {
        QLayoutItem *item = fLayout->takeAt(0);
        delete item->widget();
        delete item;
    }
}
