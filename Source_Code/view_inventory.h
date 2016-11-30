#ifndef VIEW_INVENTORY_H
#define VIEW_INVENTORY_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QDebug>
#include <QtGui>
#include <mainwindow.h>

namespace Ui {
class View_inventory;
}

class View_inventory : public QDialog
{
    Q_OBJECT

public:
    explicit View_inventory(QWidget *parent = 0);
    ~View_inventory();

private:
    Ui::View_inventory *ui;
    QSqlTableModel *model;
};

#endif // VIEW_INVENTORY_H
