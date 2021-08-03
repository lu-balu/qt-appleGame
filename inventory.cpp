#include "inventory.h"
#include "ui_inventory.h"
#include <QGridLayout>
#include <QtSql>

Inventory::Inventory(int height, int width, QWidget* parent):
  QWidget(parent),
  ui(new Ui::Inventory){
    ui->setupUi(this);

    // создаю базу данных
    base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("apple.db");
    // проверяю открылась ли БД
    if(!base.open()){
        qDebug() << "База данных не открылась";
        qDebug() << base.lastError().text();
        return;
    }
    qDebug() << "открыта база данных";

    // проверка, есть ли в БД таблица apple
    QSqlQuery query;
    // запрос количество объектов в БД с типом table и именем apple (если таблица есть - 1, если нет - 0)
    QString str = "SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = 'apple'";
    bool b = query.exec(str);
    if(!b) {
        qDebug() << "не удалось выполнить запрос с проверкой на наличие таблицы";
        qDebug() << base.lastError().text();
        return;
    }
    // query переходит к следующей строке (первой)
    query.next();
    //query.value() возвращает значение, которое лежит в 0 столбце (0 или 1)
    QVariant result = query.value(0);
    // QVariant приводится к типу bool
    bool isTableExist = result.value<bool>();

    if(!isTableExist){
        str =
                "CREATE TABLE apple ("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "line INTEGER NOT NULL,"
                "column INTEGER NOT NULL,"
                "type INTEGER NOT NULL,"
                "count INTEGER NOT NULL)";
        b = query.exec(str);
        if(!b) {
            qDebug() << "не удалось создать таблицу в БД";
            qDebug() << base.lastError().text();
            return;
        }
        qDebug() << "создалась Новая таблца в БД";

        _initTable(height, width);
    }

    vec.resize(height); //выделяю для внешнего вектора количество строк
    for(int i = 0; i < height; ++i){
        vec[i].resize(width); //выделяю для внутреннего вектора количество столбцов
        for(int j = 0; j < width; ++j){
            vec[i][j].reset(new Cell(&base, i, j));
        }
    }

    QGridLayout* grid = new QGridLayout; // создаю сетку из ячеек с размерностью height*width
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            grid->addWidget(static_cast<QWidget*>(vec[i][j].get()), i, j);
        }
    }
    grid->setMargin(0);
    grid->setSpacing(0);
    ui->widget->setLayout(grid);
}

void Inventory::clear(){ // очищаю Инвентарь
    for(int i = 0; i < vec.size(); ++i){
        for(int j = 0; j < vec[i].size(); ++j){
            vec[i][j]->clearCell();
        }
    }
    //запрос на очищение строк в БД
    QSqlQuery query;
    QString str = "UPDATE apple SET count = 0, type = 0";
    bool b = query.exec(str);
    if(!b) {
        qDebug() << "не получается очистить количество и тип в строках в БД";
        qDebug() << base.lastError().text();
    }
    else{
        qDebug() << "очищено количество и тип во всех строках";
    }
}

void Inventory::_initTable(int height, int width){
    QSqlQuery query;
    for(int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++ j){
            QString str = "INSERT INTO apple (line, column, type, count) VALUES (%1, %2, 0, 0)";
            str = str.arg(i)
                     .arg(j);
            bool b = query.exec(str);
            if(!b) {
                qDebug() << "не получается выполнить запрос по созданию строки в таблице";
            }
            else{
                qDebug() << query.exec("SELECT * FROM apple");
                qDebug() << "создана строчка " << i << " " << j;
            }
        }
    }
}
