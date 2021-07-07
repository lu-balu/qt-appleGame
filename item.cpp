#include "itemType.h"
#include "item.h"
#include "ui_item.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QDebug>

Item::Item(ItemType itemType, int count, QWidget *parent, bool infinity) :
  QWidget(parent),
  type(itemType),
  count(count),
  infinity(infinity),
  ui(new Ui::Item)
{
    player = new QMediaPlayer(this); // создаю плейлист со звуком откусывания яблока
    playlist = new QMediaPlaylist(player);

    player->setPlaylist(playlist);
    if(type == APPLE) {
        sound = "qrc:/sounds/apple.wav"; //указываю путь к звуку в зависимости от ItemType
    }
    else {
        sound = "qrc:/sounds/cherry.wav";
    }
    playlist->addMedia(QUrl(sound));

    ui->setupUi(this);
    if(infinity){ // устанавливаю для двух перетаскиваемых infinity Item невидимое поле count
        ui->label->setText("");
    }
    else{
        ui->label->setText(QString::number(count));// устанавливаю для остальных Item отображение счетчика count
    }
    if(type == APPLE) {
        path = ":/pictures/apple.png"; //указываю путь к картинке в зависимости от ItemType
    }
    else {
        path = ":/pictures/cherry.png";
    }

    QPixmap myPic(path); // создаю Pixmap в которую добавляю картинку в зависимости от ItemType и отображаю ее
    ui->label_2->setPixmap(myPic);
    ui->label_2->setScaledContents(true);
//    ui->label_2->show();
}

bool Item::isEmpty(){ // функция, проверяющая пустой ли Item
    if(count == 0){
        return true;
    }
    return false;
}

void Item::add(int number) { // функция, добавляющая число в счетчик Item
    if(number <= 0){ // если добавляется ноль - выход из функции
        return;
    }
    count += number;
    ui->label->setText(QString::number(count)); //вывожу в label текст, чему равен счетчик
}

void Item::remove(){ // функция, удаляющая 1 из Item
    --count;
    player->play(); // добавляю звук откусывания
    if(isEmpty()){ // если после вычитания 1 Item пустой - чищу Item
        clear();
        return;
    }
    ui->label->setText(QString::number(count)); //вывожу в label текст, чему равен счетчик
}

void Item::clear(){ // функция, очищающая Item
    count = 0;
    path = "";
    ui->label->setText("");
    ui->label_2->setText(" ");
}

void Item::startDrag(){ // перетаскивание Item
    QMimeData* pMimeData = new QMimeData;
    QPixmap myPic(path); // создаю Pixmap, где будет картинка, которая переносится
    myPic = myPic.scaled(141, 141); // указываю размер картинкаи, которая будет отображаться при перетаскивании
    pMimeData->setImageData(myPic.toImage()); // в объект класса qmimedata передается перетаскиваемая картинка Item
    pMimeData->setObjectName(QString::number(type)); // в объект класса qmimedata передается перетаскиваемый тип Item
    pMimeData->setText(QString::number(count)); // в pmimedata передается перетаскиваемый текст посредством setText()
    QDrag* pDrag = new QDrag(this);
    pDrag->setMimeData(pMimeData);
    pDrag->setPixmap(myPic); // устанавливаю картинку, которая будет отображаться при перетаскивании
    pDrag->setHotSpot(QPoint(myPic.width() / 2, myPic.height() / 2 )); // курсор будет посередине перетаскиваемой картинки

    Qt::DropAction result = pDrag->exec(Qt::MoveAction);
    if(result == Qt::MoveAction && !infinity){ // если Item перетащился в другую ячейку, и Item не равен infinity - он чистится
        clear();
    }
}

void Item::mouseReleaseEvent (QMouseEvent* event){
    if(isEmpty() || infinity){ // если Item пустой или два перетаскиваемых infinity Item - к нему нельзя добавляять или вычитать 1
        return;
    }
    if (event->button() == Qt::LeftButton){ // при нажатии левой кнопки мыши на Item происходит добавление 1
        add(1);
    }
    if(event->button() == Qt::RightButton){ // при нажатии правой кнопки мыши на Item происходит удаление 1
        remove();
    }
    QWidget::mousePressEvent(event);
}

void Item::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton){
        m_ptDragPos = event->pos(); // в m_ptDragPos сохранается положение курсора мыши в момент нажатия левой кнопки (только, если была нажата левая кнопка)
    }
}

void Item::mouseMoveEvent(QMouseEvent *event){// нужен для распознавания начала перетаскивания
    if(event->buttons() & Qt::LeftButton){
        int distance = (event->pos() - m_ptDragPos).manhattanLength();// величина, возвращаемая статическим методом startDragDistance (обычно 4 пиксела)
        if(distance > QApplication::startDragDistance()){// если больше 4 пикселей - перемещение указателя было не случайным
            startDrag();
        }
    }
    QWidget::mouseMoveEvent(event);
}






