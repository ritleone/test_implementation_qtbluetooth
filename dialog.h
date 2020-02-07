#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "bluetoothe.h"
#include "clientsocket.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();   
    void on_ScanButton_clicked();

private slots:
    void on_BluetoothButton_clicked();

    void showMessage(const QString &sender, const QString &message);

    int scanButtonEnable(QString &tab1);

private:
    Ui::Dialog *ui;
    Bluetoothe *bluetoothe = new Bluetoothe();
    int position;
    QFile *m_file;



};

#endif // DIALOG_H
