#include "addgen.h"
#include "ui_addgen.h"
#include<QtCore>
#include<QtDebug>
#include<QtXml>

addGen::addGen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGen)
{
    ui->setupUi(this);
}

addGen::~addGen()
{
    delete ui;
}

void addGen::on_pushButton_clicked()
{
    inputGenre = ui->lineEdit->text();

    QFile file("/Users/devanshisingh/desktop/my-work/projects/LibraryDataXML/temp.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Couldnt open the file";
        return ;
    }
    QTextStream stream(&file);
    stream << inputGenre;
    file.close();



    qDebug()<<"Written";
}


