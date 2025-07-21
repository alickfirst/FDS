#include "personclass.h"
#include "ui_personclass.h"

personclass::personclass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personclass)
{
    ui->setupUi(this);
}

personclass::~personclass()
{
    delete ui;
}
