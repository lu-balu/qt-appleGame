#ifndef ITEM_H
#define ITEM_H
#include "itemType.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtSql>

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    //конструктор для бесконечного Item
    Item(ItemType type,
         QWidget* parent = nullptr);
    //конструктор для Item в ячейке
    Item(ItemType type,
         int count,
         int line,
         int column,
         QSqlDatabase* base,
         QWidget* parent = nullptr);
    virtual ~Item() { delete ui; }

    bool isEmpty();
    void startDrag();
    void mouseReleaseEvent (QMouseEvent* event);
    void add(int number);
    void remove();
    void clear();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent (QMouseEvent* event);

    ItemType type;
    int count;
    bool infinity;
    int line;
    int column;
    QString path;
    QString sound;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;

private:
    QString typeToPath(ItemType type);

    QSqlDatabase* base;
    QPoint m_ptDragPos;
    Ui::Item *ui;
};

#endif // ITEM_H
