#ifndef CELL_H
#define CELL_H
#include <QWidget>
#include "item.h"
#include <QScopedPointer>
#include <QtSql>

namespace Ui {
class Cell;
}

class Cell: public QWidget
{
    Q_OBJECT

public:
    Cell(QSqlDatabase* base, int line, int column, QWidget* parent = nullptr);
    Cell(int count, ItemType type, QSqlDatabase* base, int line, int column, QWidget* parent = nullptr);
    void dragEnterEvent (QDragEnterEvent* event);
    void dropEvent (QDropEvent* event);
    void clearCell();
    virtual ~Cell() { delete ui; }

private:
    QScopedPointer<Item> item;
    int line;
    int column;
    QSqlDatabase* base;
    Ui::Cell *ui;
};

#endif // CELL_H
