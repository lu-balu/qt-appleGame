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
        for(int j = 0; j < width; ++j){
            vec[i][j].reset(new Cell);
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
}
