#ifndef NEWDIALOG1_H
#define NEWDIALOG1_H

#include <QDialog>
#include <QApplication>
#include <QtCore>
#include <QtXml>
#include <QtDebug>
#include <QtGui>

namespace Ui {
class newDialog1;
}

class newDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit newDialog1(QWidget *parent = nullptr);
    ~newDialog1();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::newDialog1 *ui;

    void AddBook(QString &);
};

#endif // NEWDIALOG1_H
