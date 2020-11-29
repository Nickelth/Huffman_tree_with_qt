#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDialog>
#include"Huffman_tree.h"
namespace Ui {
class treeView;
}

class treeView : public QDialog
{
    Q_OBJECT

public:
    explicit treeView(QWidget *parent = nullptr);
    ~treeView();
signals:
    void display(int);
private slots:
    void showData(node*,double);
    void drawTree(node*);
private:
    Ui::treeView *ui;
};

#endif // TREEVIEW_H
