#ifndef CELL_H
#define CELL_H
#include <QWidget>
#include "item.h"
#include <QScopedPointer>

namespace Ui {
class Cell;
}

class Cell: public QWidget
{
    Q_OBJECT

public:
    Cell(QWidget* parent = nullptr);
    QScopedPointer<Item> item;
    void dragEnterEvent (QDragEnterEvent* event);
    void dropEvent (QDropEvent* event);
    void clearCell();
    virtual ~Cell() { delete ui; }

private:
    Ui::Cell *ui;
};

#endif // CELL_H
