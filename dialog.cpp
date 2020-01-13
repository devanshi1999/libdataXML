#include "dialog.h"
#include "addgen.h"
#include "addbook.h"
#include "ui_dialog.h"
#include <QtCore>
#include <QtXml>
#include <QtDebug>
#include <QtGui>
#include <QItemSelectionModel>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    Filename = "/Users/devanshisingh/desktop/my-work/projects/LibraryDataXML/data.xml";
    model = new QStandardItemModel(0,1,this);

    QString temp;

    ReadFile();

    ui->treeView->setModel(model);

    menu = new QMenu(ui->treeView);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    menu->addAction("Remove",this,SLOT(removeItem()));
    menu->addAction("Add new",this,SLOT(addItem()));
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::ReadFile()
{
    QStandardItem *root = new QStandardItem("Books");

    model->appendRow(root);

    QDomDocument document;

    QFile file(Filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        document.setContent(&file);
        file.close();
    }

    QDomElement xmlroot = document.firstChildElement();

    QDomNodeList genres = xmlroot.elementsByTagName("Genre");

    for(int i=0;i<genres.count();i++)
    {
        QDomNode node = genres.at(i);

        QDomElement genre = node.toElement();

        QStandardItem *genreitem;

        if(genre.attribute("BookCount") == "1")
            genreitem = new QStandardItem(genre.attribute("Name")+" - "+genre.attribute("BookCount")+" Book");
        else
            genreitem = new QStandardItem(genre.attribute("Name")+" - "+genre.attribute("BookCount")+" Books");

        QDomNodeList books = genre.elementsByTagName("Book");

        for (int j=0; j<books.count();j++) {

            QDomElement book = books.at(j).toElement();

            QStandardItem *bookitem = new QStandardItem(book.attribute("Name")+" - "+book.attribute("Author")+" - "+book.attribute("Year"));

            genreitem->appendRow(bookitem);
        }


         root->appendRow(genreitem);

    }
}
void Dialog::WriteFile()
{
        QDomDocument document;

        //make a root node
        QDomElement xmlroot = document.createElement("Books");
        document.appendChild(xmlroot);

        QStandardItem *root = model->item(0,0);

        for (int i=0;i<root->rowCount();i++) {

            QStandardItem *genre = root->child(i,0);

            QStringList list2 = genre->text().split(" - ");

            QDomElement xmlgenre = document.createElement("Genre");
            xmlgenre.setAttribute("Name",list2[0]);
            xmlgenre.setAttribute("BookCount",list2[1]);

            //writing books
            for(int j=0;j<genre->rowCount();j++)
            {
                QStandardItem *book = genre->child(j,0);

                QStringList list1 = book->text().split(" - ");

                QDomElement xmlbook = document.createElement("Book");
                xmlbook.setAttribute("Name",list1[0]);
                xmlbook.setAttribute("Author",list1[1]);
                xmlbook.setAttribute("Year",list1[2]);

                xmlgenre.appendChild(xmlbook);
            }

            xmlroot.appendChild(xmlgenre);
        }

        //save to disk or write to file

        QFile file(Filename);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Could'nt open the file";
            return;
        }

        QTextStream stream(&file);
        stream << document.toString();
        file.close();

        qDebug() << "Saved";
}

void Dialog::addGenre()
{
    QString input;

    QFile file("/Users/devanshisingh/desktop/my-work/projects/LibraryDataXML/temp.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Couldnt open the file";
        return ;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        input=in.readLine();
    }
    file.close();

    if(input=="")
        return;

    QDomDocument document;

    QFile file1(Filename);
        if(file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            document.setContent(&file1);
            file1.close();
        }

    QDomElement xmlroot = document.firstChildElement();

    QDomElement newGen = document.createElement("Genre");
    newGen.setAttribute("Name",input);
    newGen.setAttribute("BookCount",0);
    xmlroot.appendChild(newGen);

    if(!file1.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Couldnt open the file";
        return ;
    }

    QTextStream stream(&file1);
    stream << document.toString();
    file1.close();

    model->clear();

    ReadFile();
}

void Dialog::removeItem()
{
    if(temp=="Books")
        return;
    QStringList list = temp.split(" - ");

    if(list.size()==2)
    {
        QString name = temp.split(" - ")[1];
        QString count = name.split(" Book")[0];
        count = count.split(" Books")[0];


    }

    model->removeRow(ind.row(),ind.parent());
}


void Dialog::addItem()
{
    //opening another dialog
    addBook addbookdialog;
    addbookdialog.setModal(true);
    addbookdialog.exec();

    QString bookName,author,year;

    QFile file("/Users/devanshisingh/desktop/my-work/projects/LibraryDataXML/temp.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Couldnt open the file";
        return ;
    }

    QTextStream in(&file);

    bookName = in.readLine();
    author = in.readLine();
    year = in.readLine();
    file.close();

    if(bookName=="")
        return;

    //create a new book

    QStandardItem *parentItem = model->itemFromIndex(ind);

    QStandardItem *bookitem = new QStandardItem(bookName+" - "+author+" - "+year);

    parentItem->appendRow(bookitem);
}


void Dialog::on_pushButton_clicked()
{
      addGen addgendialog;
      addgendialog.setModal(true);
      addgendialog.exec();

      addGenre();
}

void Dialog::on_pushButton_2_clicked()
{
    WriteFile();
}

void Dialog::onCustomContextMenu(const QPoint &point)
{
    ind = ui->treeView->indexAt(point);

    if(!ind.isValid())
        return;

    QStandardItem *item = model->itemFromIndex(ind);

    temp = item->text();

    menu->exec(ui->treeView->viewport()->mapToGlobal(point));

}
