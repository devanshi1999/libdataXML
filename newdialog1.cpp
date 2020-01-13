#include "newdialog1.h"
#include "ui_newdialog1.h"
#include <QtDebug>
#include <QtCore>
#include <QtXml>

newDialog1::newDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDialog1)
{
    ui->setupUi(this);
}

newDialog1::~newDialog1()
{
    delete ui;
}

void newDialog1::AddBook(QString &input)
{
    qDebug() << input;
}

void newDialog1::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();
    AddBook(input);
}



