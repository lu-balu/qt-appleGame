#include "inventory.h"
#include "ui_inventory.h"
#include <QGridLayout>

Inventory::Inventory(int height, int width, QWidget* parent):
  QWidget(parent),
  ui(new Ui::Inventory){
    ui->setupUi(this);
    vec.resize(height); //выделяю для внешнего вектора количество строк
    for(int i = 0; i < height; ++i){
        vec[i].resize(width); //выделяю для внутреннего вектора количество столбцов
    }

    QGridLayout* grid = new QGridLayout; // создаю сетку из ячеек с размерностью height*width
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            QWidget* obj = new Cell();
            grid->addWidget(obj, i, j);
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
}
