#ifndef INVENTORY_COUNT_H
#define INVENTORY_COUNT_H

#include <QDialog>
#include <QtSql>
#include <QDebug>

namespace Ui {
class inventory_count;
}

class inventory_count : public QDialog
{
    Q_OBJECT

public:
    explicit inventory_count(QWidget *parent = 0);
    ~inventory_count();

private slots:
    void on_inventoryCount_clicked(const QModelIndex &index);

    void on_edit_invCount_clicked();

private:
    Ui::inventory_count *ui;
};

#endif // INVENTORY_COUNT_H
