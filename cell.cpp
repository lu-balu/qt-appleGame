#include "cell.h"
#include "ui_cell.h"
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
//#include "item.h"
//#include <QtAlgorithms>

Cell::Cell(int count, ItemType type, QSqlDatabase* base, int line, int column, QWidget* parent) :
    QWidget(parent),
    item(nullptr),
    line(line),
    column(column),
    base(base),
    ui(new Ui::Cell)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    if(count != 0){
        item.reset(new Item(type, count, line, column, base, this));
        QVBoxLayout* vBox = new QVBoxLayout(this); //создаю layout, добавляю и отрисовываю в нем item
        vBox->addWidget(item.get());
        ui->widget->setLayout(vBox);
    }
}

Cell::Cell(QSqlDatabase* base, int line, int column, QWidget *parent) :
  QWidget(parent),
  item(nullptr),
  line(line),
  column(column),
  base(base),
  ui(new Ui::Cell) {
    setAcceptDrops(true);
    ui->setupUi(this);
}

void Cell::dragEnterEvent (QDragEnterEvent* event){
    int newType = event->mimeData()->objectName().toInt(); // в newType записываю тип из mimeData перетаскиваемого Item
    ItemType type = static_cast<ItemType>(newType);

    // проверка на совместимость типа данных перетаскиваемого объекта
    if(item.isNull() || item->type == type || item->isEmpty()){
        event->acceptProposedAction();//готовность виджета принять перетаскиваемый объект
    }
}

void Cell::dropEvent (QDropEvent* event){
    int count = event->mimeData()->text().toInt(); //в count записываю count из mimeData перетаскиваемого Item
    int newType = event->mimeData()->objectName().toInt(); // в newType записываю тип из mimeData перетаскиваемого Item
    ItemType type = static_cast<ItemType>(newType);

    //создаю запрос в БД
    QSqlQuery query;

    if(!item.isNull()){//если Item уже существует и если он пустой - чищу от него ячейку
        if(item->isEmpty()){
            item.reset();
        }
    }

    if(!item.isNull()){ //если Item существует и не пустой - сравниваю и прибавляю к нему добавляемый элемент
        if(item->type != type){
            return;
        }
        count += item->count;
    }
    item.reset(new Item(type, count, line, column, base, this)); //создаю новый Item, в который записываю данные из перетаскиваемого Item
    event->acceptProposedAction();
    qDebug() << "В ячейку записался count: " << count;
    qDebug() << "В ячейку записался type: " << newType;

    qDeleteAll(ui->widget->children()); //чищу widget от лежащего в нем layout

    QVBoxLayout* vBox = new QVBoxLayout(this); //создаю layout, добавляю и отрисовываю в нем item
    vBox->addWidget(item.get());
    ui->widget->setLayout(vBox);

    //заполняю запрос на изменение строки в БД

    QString str = "UPDATE apple SET count = %1, type = %2 WHERE line = %3 AND column = %4";
    str = str.arg(count)
             .arg(newType)
             .arg(line)
             .arg(column);
    bool b = query.exec(str);
    if(!b) {
        qDebug() << "не получается выполнить запрос на изменение строки в БД";
        qDebug() << base->lastError().text();
    }
    else{
        qDebug() << "изменена строка" << line << " столбец" << column;
    }
}

void Cell::clearCell(){
    if(item.isNull()){
        return;
    }
    item.reset();
}





