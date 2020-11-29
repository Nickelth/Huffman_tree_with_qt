#include "mainwindow.h"

#include <QApplication>
#include<QWidget>
#include<QPaintDevice>
#include"mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget *main_widget=new mainWidget();
    main_widget->show();
    return a.exec();
}
