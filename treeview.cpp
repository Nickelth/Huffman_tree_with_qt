#include "treeview.h"
#include "ui_treeview.h"
#include<stack>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>
treeView::treeView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::treeView)
{
    ui->setupUi(this);

}

treeView::~treeView()
{
    delete ui;
}
void treeView::showData(node*r,double wpl)
{
    QString w=QString::number(wpl,'d',5);
    ui->label_2->setText(w);

    QStringList str;
    str<<"字符"<<"编码"<<"路径长度"<<"权值";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(str);

    std::stack<node*> s;
    node* i=r;
    int row=0;
    while(!s.empty()||i!=NULL)//前序遍历
    {

        while(i!=NULL)
        {
            if(i->leftChild==NULL&&i->rightChild==NULL)
            {
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(i->ch));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(i->code));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(i->len)));
                ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(i->weight)));
                 row++;
            }
            s.push(i);
            i=i->leftChild;
        }
        if(!s.empty())
        {
            i=s.top();
            s.pop();
            i=i->rightChild;
        }
    }
}

void treeView::drawTree(node* r)
{


    std::stack<node*> s;
    node* i=r;


    QGraphicsScene*p=new QGraphicsScene();
    QGraphicsRectItem *z=new QGraphicsRectItem(0,0,50,30,0);
    z->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    QPen *pen1=new QPen();
    pen1->setWidth(5);
    pen1->setColor(QColor(0,0,255,127));
    z->setPen(*pen1);
    p->addItem(z);
    ui->graphicsView->setScene(p);


    while(!s.empty()||i!=NULL)//前序遍历
    {

        while(i!=NULL)
        {
            if(i->parent!=NULL&&i->parent->leftChild!=NULL&&i->parent->leftChild==i)//如果当前节点是左孩子
            {
                i->x=i->parent->x-100;
                i->y=i->parent->y+80;
                while(p->itemAt(i->x,i->y,QTransform())!=NULL){//若当前位置有item
                    i->x+=60;//向右偏移直到不重合
                }
                z=new QGraphicsRectItem(i->x,i->y,50,30,p->itemAt(i->parent->x,i->parent->y,QTransform()));
                //所有在scene中有parent的item会自动添加到scene中，不必再通过addItem进行添加
                //z->setPos(i->parent->x-100,i->parent->y+80);
                //不要用setPos，其作用是将item坐标映射到scene中坐标，所以将一个坐标为x1,y1的item调用setPos(x2,y2)的实际效果是使其坐标变为了x1+x2,y1+y2

                qDebug()<<"current rect's point is"<<z->x()<<' '<<z->y();
                qDebug()<<"and it should be"<<i->x<<' '<<i->y;
                 z->setPen(*pen1);
                if(i->leftChild==NULL&&i->rightChild==NULL)//若为叶子节点
                {
                    QGraphicsTextItem *t=new QGraphicsTextItem(z);
                    t->setPlainText(i->ch);
                    t->setPos(i->x,i->y);
                }

                QGraphicsLineItem *l=new QGraphicsLineItem(i->parent->x,i->parent->y+30,i->x+50,i->y,z->parentItem());
                QPen pen2;
                pen2.setWidth(5);
                pen2.setColor(QColor(30,27,127,127));
                l->setPen(pen2);
            }
            else if(i->parent!=NULL&&i->parent->rightChild!=NULL&&i->parent->rightChild==i)//如果当前节点是右孩子
            {
                i->x=i->parent->x+100;
                i->y=i->parent->y+80;
                while(p->itemAt(i->x,i->y,QTransform())!=NULL){//若当前位置有item
                    i->x-=60;//向左偏移直到不重合
                }
                z=new QGraphicsRectItem(i->x,i->y,50,30,p->itemAt(i->parent->x,i->parent->y,QTransform()));
               //z->setPos(i->parent->x+100,i->parent->y+80);
                i->x=i->parent->x+100;
                i->y=i->parent->y+80;
                qDebug()<<"current rect's point is"<<z->x()<<' '<<z->y();
                 z->setPen(*pen1);
                if(i->leftChild==NULL&&i->rightChild==NULL)
                {
                    QGraphicsTextItem *t=new QGraphicsTextItem(z);
                    t->setPlainText(i->ch);
                     t->setPos(i->x,i->y);
                }

                QGraphicsLineItem *l=new QGraphicsLineItem(i->parent->x+50,i->parent->y+30,i->x,i->y,z->parentItem());
                QPen pen2;
                pen2.setWidth(5);
                pen2.setColor(QColor(30,27,127,127));
                l->setPen(pen2);

            }

            s.push(i);
            i=i->leftChild;
        }
        if(!s.empty())
        {
            i=s.top();
            s.pop();
            i=i->rightChild;
        }
    }


}
