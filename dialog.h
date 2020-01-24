#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "bluetoothe.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();   

private slots:

    void on_ScanButton_clicked();

    void on_BluetoothButton_clicked();

private:
    Ui::Dialog *ui;
    Bluetoothe bluetoothe;
    int position;
};

#endif // DIALOG_H
