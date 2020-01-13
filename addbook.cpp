#include "addbook.h"
#include "ui_addbook.h"

addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);


}

addBook::~addBook()
{
    delete ui;
}



void addBook::on_pushButton_clicked()
{
    bookName = ui->lineEdit->text();
    author = ui->lineEdit_2->text();
    year = ui->lineEdit_3->text();

    QFile file("/Users/devanshisingh/desktop/my-work/projects/LibraryDataXML/temp.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Couldnt open the file";
        return ;
    }
    QTextStream stream(&file);
    stream << bookName+"\n"+author+"\n"+year;
    file.close();
}
