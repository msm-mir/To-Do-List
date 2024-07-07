#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(std::map<QString,User> users, QString username, int listId, QWidget *parent) : QMainWindow(parent) , ui(new Ui::AddTask) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;
    this->listId = listId;

    connections();

    hideError();
}

AddTask::~AddTask() {
    delete ui;
}

void AddTask::connections() {
    //click to add task
    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(onPushButtonAddTaskClicked()));

    //click cancel
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(openMainPanelPage()));

    //click enter on line edits to add task
    connect(ui->lineEditTaskName, SIGNAL(returnPressed()), ui->pushButtonAdd, SLOT(click()));
    connect(ui->textEditDetails, SIGNAL(returnPressed()), ui->pushButtonAdd, SLOT(click()));
    connect(ui->lineEditAssign, SIGNAL(returnPressed()), ui->pushButtonAdd, SLOT(click()));

    //set cursor
    ui->lineEditTaskName->setFocus();
}

void AddTask::hideError() {
    ui->labelError->hide();
}

void AddTask::onPushButtonAddTaskClicked() {
    if (checkAddTask()) {
        addTask();
        openMainPanelPage();
    }
}

bool AddTask::checkAddTask() {
    hideError();

    //check line edits
    if (checkTaskNameField())
        return false;
    if (checkDateField())
        return false;
    if (checkDetailsField())
        return false;
    if (checkAssignField())
        return false;

    return true;
}

bool AddTask::checkTaskNameField() {
    if (ui->lineEditTaskName->text() == "") {
        ui->labelError->setText("Task Name field is empty");
        ui->labelError->show();
        return true;
    }
    if (checkName(ui->lineEditTaskName->text())) {
        ui->labelError->setText("Task Name field is invalid");
        ui->labelError->show();
        return true;
    }
    if (checkDuplicateName(ui->lineEditTaskName->text())) {
        ui->labelError->setText("Task Name already exists");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool AddTask::checkDateField() {
    if (ui->calendarWidget->selectedDate().toString(Qt::ISODate) == "") {
        ui->labelError->setText("Date isn't selected");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool AddTask::checkDetailsField() {
    if (checkString(ui->textEditDetails->toPlainText())) {
        ui->labelError->setText("Details field is invalid");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool AddTask::checkAssignField() {
    if (checkString(ui->lineEditAssign->text())) {
        ui->labelError->setText("Assign field is invalid");
        ui->labelError->show();
        return true;
    }
    if (findUsername(ui->lineEditAssign->text())) {
        ui->labelError->setText("Assign username doesn't exist");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool AddTask::checkName(QString text) {
    for (int i = 0; i < text.size(); i++) {
        if (((text[i] < 'A') || (text[i] > 'z')) || ((text[i] < 'a') && (text[i] > 'Z'))) {
            if ((text[i] >= '0') && (text[i] <='9'))
                continue;
            else
                return true;
        }
    }
    return false;
}

bool AddTask::checkString(QString text) {
    for (int i = 0; i < text.size(); i++) {
        if (((text[i] < 'A') || (text[i] > 'z')) || ((text[i] < 'a') && (text[i] > 'Z'))) {
            if ((text[i] == '.') || (text[i] == '_') || (text[i] == '-') || (text[i] == '/') || (text[i] == '(') || (text[i] == ')')
                || ((text[i] >= '0') && (text[i] <='9')))
                continue;
            else
                return true;
        }
    }
    return false;
}

bool AddTask::checkDuplicateName(QString name) {
    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 0; i < itr.second.getListsSize(); i++)
                if (itr.second.getLists(listId).getTasks(i).getName() == name)
                    return true;
    return false;
}

bool AddTask::findUsername(QString username) {
    if (users.find(username) != users.end())
        return false;
    return true;
}

void AddTask::openMainPanelPage() {
    MainPanel *newPage = new MainPanel(users, username);
    newPage->show();
    this->close();
}

void AddTask::addTask() {
    QString taskName = ui->lineEditTaskName->text();
    QDate date = ui->calendarWidget->selectedDate();
    QString details = ui->textEditDetails->toPlainText();
    QString assign = ui->lineEditAssign->text();

    bool star;
    if (ui->pushButtonStar->isChecked())
        star = true;
    else
        star = false;

    Task task;
    task.setName(taskName);
    task.setDate(date);
    task.setDetail(details);
    task.setAssign(assign);
    task.setStar(star);
    task.setComplete(false);

    for (auto &itr : users)
        if (itr.first == username) {
            // itr.second.getLists(listId).addTasks(task);
            task.setId(itr.second.getLists(listId).getTasksSize() + 1);
            itr.second.getLists(listId) << task;
        }

    addTaskToDatabase(task);
}

void AddTask::addTaskToDatabase(Task task) {
    QSqlDatabase mydb;

    if (!openDatabase(mydb))
        return;

    QSqlQuery query;
    query.prepare("INSERT INTO tasks (ListId, TaskId, Name, Date, Details, Assign, Star, Complete) VALUES "
                  "(:listId, :taskId, :name, :date, :details, :assign, :star, :complete)");
    query.bindValue(":listId", task.getListId());
    query.bindValue(":taskId", task.getId());
    query.bindValue(":name", task.getName());
    query.bindValue(":date", task.getDate().toString(Qt::ISODate));
    query.bindValue(":details", task.getDetail());
    query.bindValue(":assign", task.getAssign());
    query.bindValue(":star", task.getStar());
    query.bindValue(":complete", task.getComplete());
    query.exec();

    closeDatabase(mydb);
}

bool AddTask::openDatabase(QSqlDatabase &mydb) {
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/Code/4022/To Do List/uiap-final-project-msm-mir/src/ToDoList.db");

    if (!mydb.open())
        return false;
    else
        return true;
}

void AddTask::closeDatabase(QSqlDatabase &mydb) {
    mydb.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
