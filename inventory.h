#ifndef INVENTORY_H
#define INVENTORY_H
#include <QWidget>
#include <QVector>
#include "cell.h"
#include <QSharedPointer>
#include <QtSql>

namespace Ui {
class Inventory;
}

class Inventory : public QWidget
{
    Q_OBJECT

public:
    Inventory(int height, int width, QWidget* parent = nullptr);
    QVector<QVector<QSharedPointer<Cell>>> vec;
    QSqlDatabase base;
    void clear();
    virtual ~Inventory() { delete ui; }

private:
    void _initTable(int height, int width);
    Ui::Inventory *ui;
};

#endif // INVENTORY_H
