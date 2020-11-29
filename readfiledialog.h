#ifndef READFILEDIALOG_H
#define READFILEDIALOG_H

#include <QDialog>
#include<QString>
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>
namespace Ui {
class ReadFileDialog;
}

class ReadFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadFileDialog(QWidget *parent = nullptr);
    ~ReadFileDialog();

private:
    Ui::ReadFileDialog *ui;
signals:
    void display(int);
    void file_Path(QString);
private slots:
    void on_readFileButton_clicked();
};

#endif // READFILEDIALOG_H
