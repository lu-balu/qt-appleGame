#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "item.h"
#include <QHBoxLayout>
#include "cell.h"
#include "inventory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralwidget->setDisabled(true);

    // Создаем объект класса QAction (действие) с названием пункта меню "Quit"
    QAction *quit = new QAction("&Выйти", this);
    // Создаем объект класса QAction (действие) с названием пункта меню "newGame"
    QAction *newGame = new QAction("&Новая игра", this);

    // Создаем объект класса QMenu (меню)
    QMenu *menu;
    menu = menuBar()->addMenu("&Меню");

    // Помещаем действие "Quit" (Выход) в меню с помощью метода addAction()
    menu->addAction(newGame);
    menu->addAction(quit);

    // Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает свое выполнение
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    // Когда мы выбираем в меню опцию "newGame", то mainWindow становится доступным для польователя

    connect(newGame, SIGNAL(triggered()), this, SLOT(setMainWindowEnabled()));

    QHBoxLayout* hLayout = new QHBoxLayout; //создаю горизонтальный layout

    QWidget* inventory = new Inventory(3,3, this); //создаю Инвентарь
    hLayout->addWidget(inventory); //добавляю в горизонтальный layout Инвентарь

    QVBoxLayout* vLayout = new QVBoxLayout; //создаю вертикальный layout
    QWidget* first = new Item(APPLE, 1, this, true); //создаю объект APPLE
    QWidget* second = new Item(PEACH, 1, this, true);  //создаю объект PEACH
    vLayout->addWidget(first); // добавляю в вертикальный layout APPLE
    vLayout->addWidget(second); // добавляю в вертикальный layout PEACH

    hLayout->addLayout(vLayout); //добавляю в горизонтальный layout вертикальный layout с объектом APPLE и объектом PEACH
    vLayout->setSpacing(100);
    vLayout->setMargin(100);

    ui->centralwidget->setLayout(hLayout);
}

void MainWindow::setMainWindowEnabled(){
    ui->centralwidget->setEnabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

