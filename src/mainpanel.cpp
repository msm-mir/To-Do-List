#include "mainpanel.h"
#include "ui_mainpanel.h"

MainPanel::MainPanel(std::map<QString,User> users, QString username, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainPanel) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;

    setProfile();

    connections();

    checkReminder();

    removeWidgets(listLayoutMap);
    removeWidgets(listTasksLayoutMap);
    removeWidgets(starTasksLayoutMap);
    removeWidgets(assignMeLayoutMap);
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

void MainPanel::checkReminder() {
    QString  reminder;
    for (auto &itr : users) {
        if (itr.first == username) {
            for (int i = 1; i <= itr.second.getListsSize(); i++) {
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++) {
                    if (itr.second.getLists(i).getTasks(j).getDate() == QDate::currentDate()) {
                        reminder += (itr.second.getLists(i).getTasks(j).getName() + "\n");
                    }
                }
            }
        }
    }
    QMessageBox::information(nullptr, "Reminder", reminder);
}

void MainPanel::onPushButtonTodayClicked() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->groupBoxPanel->setTitle("Today");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(todayLayoutMap);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                    if (itr.second.getLists(i).getTasks(j).getDate() == QDate::currentDate())
                        addTaskWidget(itr.second.getLists(i).getTasks(j), ui->todayFrame);
}

void MainPanel::onPushButtonListsClicked() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->groupBoxPanel->setTitle("Lists");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(listLayoutMap);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                addListWidget(itr.second.getLists(i));
}

void MainPanel::onPushButtonTasksClicked() {
    ui->stackedWidget->setCurrentIndex(2);
    ui->groupBoxPanel->setTitle("Tasks");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(tasksLayoutMap);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                    addTaskWidget(itr.second.getLists(i).getTasks(j), ui->tasksFrame);
}

void MainPanel::onPushButtonStarTasksClicked() {
    ui->stackedWidget->setCurrentIndex(3);
    ui->groupBoxPanel->setTitle("Star Tasks");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(starTasksLayoutMap);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                    if (itr.second.getLists(i).getTasks(j).getStar())
                        addTaskWidget(itr.second.getLists(i).getTasks(j), ui->starTasksFrame);
}

void MainPanel::onPushButtonCompletedClicked() {
    ui->stackedWidget->setCurrentIndex(4);
    ui->groupBoxPanel->setTitle("Completed Tasks");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(completeTasksLayoutMap);

    for (auto &itr : users)
        for (int i = 1; i <= itr.second.getListsSize(); i++)
            for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                if (itr.second.getLists(i).getTasks(j).getComplete())
                    addTaskWidget(itr.second.getLists(i).getTasks(j), ui->completeFrame);
}

void MainPanel::onPushButtonAssignedMeClicked() {
    ui->stackedWidget->setCurrentIndex(5);
    ui->groupBoxPanel->setTitle("Assigned To Me");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(assignMeLayoutMap);

    for (auto &itr : users)
        for (int i = 1; i <= itr.second.getListsSize(); i++)
            for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                if (itr.second.getLists(i).getTasks(j).getAssign() == username)
                    addTaskWidget(itr.second.getLists(i).getTasks(j), ui->assignMeFrame);
}

void MainPanel::onPushButtonAssignedOtherClicked() {
    ui->stackedWidget->setCurrentIndex(6);
    ui->groupBoxPanel->setTitle("Assigned To Other");

    this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");

    removeWidgets(assignOtherLayoutMap);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++)
                    if (itr.second.getLists(i).getTasks(j).getAssign() != "")
                        addTaskWidget(itr.second.getLists(i).getTasks(j), ui->assignOtherFrame);
}

void MainPanel::onPushButtonLogoutClicked() {
    Login *newPage = new Login(users);
    newPage->show();
    this->close();
}

void MainPanel::onListClicked() {
    ui->stackedWidget->setCurrentIndex(7);

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    List list = listTasksButtonMap[button];

    setListTheme(list.getId());
    ui->groupBoxPanel->setTitle(list.getName() + " List");

    removeWidgets(listTasksLayoutMap);

    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getLists(list.getId()).getTasksSize(); i++)
                addTaskWidget(itr.second.getLists(list.getId()).getTasks(i), ui->listTasksFrame);

    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(ui->pushButtonAddTask, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButtonAddTask, list.getId());
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(openAddTaskPage(int)));

    // connect(ui->pushButtonAddTask, SIGNAL(clicked()), this, SLOT(openAddTaskPage(list.getId())));
}

void MainPanel::setListTheme(int listId) {
    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 1; i <= itr.second.getListsSize(); i++)
                if (itr.second.getLists(i).getId() == listId) {
                    ui->groupBoxPanel->setTitle(itr.second.getLists(i).getName() + " List");

                    if (itr.second.getLists(i).getColor() == blue)
                        this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_blue_background.png);}");
                    if (itr.second.getLists(i).getColor() == green)
                        this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_green_background.png);}");
                    if (itr.second.getLists(i).getColor() == pink)
                        this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_pink_background.png);}");
                    if (itr.second.getLists(i).getColor() == purple)
                        this->setStyleSheet("QMainWindow {background-image: url(:/images/background/main_panel_purple_background.png);}");
                }
}

void MainPanel::getPdf() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    List list = listTasksButtonMap[button];

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Export PDF", QString(), "*.pdf");
    if (fileName.isEmpty()) { return; }
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fileName);

    QString title;
    QString text;

    for (auto &itr : users) {
        if (itr.first == username) {
            for (int i = 1; i <= itr.second.getListsSize(); i++) {
                for (int j = 1; j <= itr.second.getLists(i).getTasksSize(); j++) {
                    if (itr.second.getLists(i).getId() == list.getId()) {
                        title = itr.second.getLists(i).getName();
                        text += itr.second.getLists(i).getTasks(j).getName() + "<br>";
                    }
                }
            }
        }
    }
    QTextDocument doc;
    doc.setHtml("<h1>"+title+"</h1>\n<p>"+text+"</p>");
    doc.print(&printer);
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

void MainPanel::addListWidget(List list) {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->listFrame->layout());

    QHBoxLayout *newLayout = new QHBoxLayout(ui->listFrame);

    QString buttonText = tr(list.getName().toUtf8().constData());
    QString buttonTextPdf = tr("PDF");
    QString buttonTextDelete = tr("Delete");

    QPushButton *button = new QPushButton(buttonText, ui->listFrame);
    newLayout->addWidget(button);
    button->setFixedSize(350, 40);

    QPushButton *pdfButton = new QPushButton(buttonTextPdf, ui->listFrame);
    newLayout->addWidget(pdfButton);
    pdfButton->setFixedSize(65, 40);

    QPushButton *deleteButton = new QPushButton(buttonTextDelete, ui->listFrame);
    newLayout->addWidget(deleteButton);
    deleteButton->setFixedSize(80, 40);

    layout->insertLayout(0, newLayout);

    listLayoutMap.insert(button, newLayout);

    for (auto &itr : users) {
        if (itr.first == username) {
            for (int i = 1; i <= itr.second.getListsSize(); i++) {
                if (list.getId() == itr.second.getLists(i).getId()) {
                    listTasksButtonMap.insert(button, itr.second.getLists(i));
                    pdfButtonMap.insert(pdfButton, itr.second.getLists(i));
                }
            }
        }
    }

    connect(button, SIGNAL(clicked(bool)), this, SLOT(onListClicked()));
    connect(pdfButton, SIGNAL(clicked(bool)), this, SLOT(getPdf()));
}

void MainPanel::addTaskWidget(Task task, QFrame *frame) {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(frame->layout());

    QHBoxLayout *newLayout = new QHBoxLayout(frame);

    QString buttonText = tr(task.getName().toUtf8().constData());
    QString buttonTextDate = tr(task.getDate().toString().toUtf8().constData());
    QString buttonTextStar;
    QString buttonTextComplete;

    QPushButton *button = new QPushButton(buttonText, frame);
    newLayout->addWidget(button);
    button->setGeometry(15, 15, 300, 40);
    // button->setFixedHeight(40);

    QPushButton *dateButton = new QPushButton(buttonTextDate, frame);
    newLayout->addWidget(dateButton);
    dateButton->setGeometry(320, 15, 70, 40);
    // dateButton->setFixedHeight(40);

    QPushButton *starButton = new QPushButton(buttonTextStar, frame);
    newLayout->addWidget(starButton);
    starButton->setGeometry(395, 15, 25, 25);
    // starButton->setFixedHeight(25);
    starButton->setStyleSheet("background: transparent;"
                              "border: none;");
    QIcon iconStar;
    iconStar.addPixmap(QPixmap(":/images/icon/filled_star_icon.png"), QIcon::Normal, QIcon::On);
    iconStar.addPixmap(QPixmap(":/images/icon/star_icon.png"), QIcon::Normal, QIcon::Off);
    starButton->setIcon(iconStar);

    QPushButton *completeButton = new QPushButton(buttonTextComplete, frame);
    newLayout->addWidget(completeButton);
    completeButton->setGeometry(425, 15, 25, 25);
    // completeButton->setFixedHeight(25);
    completeButton->setStyleSheet("background: transparent;"
                              "border: none;");
    QIcon iconComplete;
    iconComplete.addPixmap(QPixmap(":/images/icon/on_icon.png"), QIcon::Normal, QIcon::On);
    iconComplete.addPixmap(QPixmap(":/images/icon/off_icon.png"), QIcon::Normal, QIcon::Off);
    completeButton->setIcon(iconComplete);

    layout->insertLayout(0, newLayout);

    if (frame == ui->todayFrame)
        todayLayoutMap.insert(button, newLayout);
    else if (frame == ui->listTasksFrame) {
        listTasksLayoutMap.insert(button, newLayout);

        completeButton->setCheckable(true);
        if (task.getComplete())
            completeButton->setChecked(true);
        starButton->setCheckable(true);
        if (task.getStar())
            starButton->setChecked(true);
    }
    else if (frame == ui->tasksFrame)
        tasksLayoutMap.insert(button, newLayout);
    else if (frame == ui->starTasksFrame) {
        starTasksLayoutMap.insert(button, newLayout);
        starButton->setCheckable(true);
        starButton->setChecked(true);
    }
    else if (frame == ui->completeFrame) {
        completeTasksLayoutMap.insert(button, newLayout);
        completeButton->setCheckable(true);
        completeButton->setChecked(true);
    }
    else if (frame == ui->assignMeFrame)
        assignMeLayoutMap.insert(button, newLayout);
    else if (frame == ui->assignOtherFrame)
        assignOtherLayoutMap.insert(button, newLayout);
}

void MainPanel::removeWidgets(QHash<QPushButton*,QHBoxLayout*> &layoutMap) {
    QHBoxLayout *tmpLayout;

    for (auto itr = layoutMap.begin(); itr != layoutMap.end(); ++itr) {
        tmpLayout = itr.value();
        while (tmpLayout->count() != 1) {
            QLayoutItem *item = tmpLayout->takeAt(1);
            delete item->widget();
            delete item;
        }
        delete itr.value();
        delete itr.key();
    }

    layoutMap.clear();
}
