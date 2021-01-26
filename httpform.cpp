#include "httpform.h"
#include "ui_httpform.h"

httpform::httpform(QWidget *parent) :BaseForm(parent),ui(new Ui::httpform)
{

    ui->setupUi(this);
}

httpform::~httpform()
{
    delete ui;
}
