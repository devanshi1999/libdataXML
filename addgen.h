#ifndef ADDGEN_H
#define ADDGEN_H

#include <QDialog>
#include <QApplication>
#include <QtCore>
#include <QtXml>
#include <QtDebug>
#include <QtGui>

namespace Ui {
class addGen;
}

class addGen : public QDialog
{
    Q_OBJECT

public:
    explicit addGen(QWidget *parent = nullptr);

    ~addGen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addGen *ui;
    QString inputGenre ;
};

#endif // ADDGEN_H
