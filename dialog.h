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

private slots:
    void on_BluetoothButton_clicked();

    void showMessage(const QString &sender, const QString &message);

    void on_ScanButton_clicked();

private:
    Ui::Dialog *ui;
    Bluetoothe bluetoothe ;
    int position;
    QFile *m_file;



};

#endif // DIALOG_H
