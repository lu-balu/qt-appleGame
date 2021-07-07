#ifndef ITEM_H
#define ITEM_H
#include "itemType.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    Item(ItemType type, int count, QWidget* parent = nullptr, bool infinity = false);
    ItemType type;
    QString path;
    QString sound;
    int count;
    bool isEmpty();
    void startDrag();
    void mouseReleaseEvent (QMouseEvent* event);
    void add(int number);
    void remove();
    void clear();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent (QMouseEvent* event);
    bool infinity;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    virtual ~Item() { delete ui; }

private:
    Ui::Item *ui;
    QPoint m_ptDragPos;
};

#endif // ITEM_H
