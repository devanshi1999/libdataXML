#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include <QApplication>
#include <QtCore>
#include <QtXml>
#include <QtDebug>
#include <QtGui>

namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private slots:

    void on_pushButton_clicked();

private:
    Ui::addBook *ui;
    QString bookName, author, year;
};

#endif // ADDBOOK_H
