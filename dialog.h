#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QApplication>
#include <QtCore>
#include <QtXml>
#include <QtDebug>
#include <QtGui>
#include <QMenu>
#include <QItemSelectionModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void removeItem();
    void addItem();
    void on_pushButton_2_clicked();
    void onCustomContextMenu(const QPoint &);

private:
    Ui::Dialog *ui;
    QStandardItemModel *model;
    QMenu* menu;
    QString Filename;
    QString temp;
    QModelIndex ind;
    QAction* removeAction;
    QItemSelectionModel* selectionmodel;
    void ReadFile();
    void WriteFile();
    void addGenre();


};

#endif // DIALOG_H
