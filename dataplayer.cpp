#include "dataplayer.h"
#include "ui_dataplayer.h"
#include<QStringList>
#include<QDebug>
dataPlayer::dataPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataPlayer)
{
    ui->setupUi(this);
}

dataPlayer::~dataPlayer()
{
    delete ui;
}
void dataPlayer::on_createTreeButton_clicked()
{
    emit display(2);
}
void dataPlayer::showData(std::map<QChar,int> data)
{
    QStringList str;
    str<<"字符"<<"个数"<<"频率";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(str);
    int row=0;
    int sum=0;
    qDebug()<<"showdata has been runned"<<endl;

    for(std::map<QChar,int>::iterator i=data.begin();i!=data.end();i++)
    {
        sum+=i->second;
    }
    for(std::map<QChar,int>::iterator i=data.begin();i!=data.end();i++,row++)
    {
        double hz=(double)i->second/sum;
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(i->first));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::number(i->second)));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(hz)));
    }
}
