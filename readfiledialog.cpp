#include "readfiledialog.h"
#include "ui_readfiledialog.h"

ReadFileDialog::ReadFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadFileDialog)
{
    ui->setupUi(this);

}

ReadFileDialog::~ReadFileDialog()
{
    delete ui;
}
void ReadFileDialog::on_readFileButton_clicked()
{
    QString path= QFileDialog::getOpenFileName(
                this,
                tr("open a txt file."),
                ".",
                tr("text files(*.txt)"));
    if(path.isEmpty())
        QMessageBox::warning(this,"warning","can not open the file");
    else
    {
        qDebug()<<path;
        emit display(1);
        emit file_Path(path);
    }
}
