#ifndef DATAPLAYER_H
#define DATAPLAYER_H

#include <QDialog>
#include<QTableWidget>
#include<QTableWidgetItem>
namespace Ui {
class dataPlayer;
}

class dataPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit dataPlayer(QWidget *parent = nullptr);
    ~dataPlayer();

signals:
    void display(int);
private:
    Ui::dataPlayer *ui;
private slots:
    void on_createTreeButton_clicked();
    void showData(std::map<QChar,int>);//输出数据
};

#endif // DATAPLAYER_H
