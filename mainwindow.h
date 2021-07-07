#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inventory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QScopedPointer<Inventory> inventory;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void setMainWindowEnabled();
};
#endif // MAINWINDOW_H
