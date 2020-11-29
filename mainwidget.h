#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDialog>
#include<QStackedLayout>
#include"readfiledialog.h"
#include"dataplayer.h"
#include"treeview.h"
#include"Huffman_tree.h"
namespace Ui {
class mainWidget;
}

class mainWidget : public QDialog
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    Ui::mainWidget *ui;
    ReadFileDialog *read_file_dialog;
    dataPlayer *data_player;
    treeView *tree_view;
    huffman_tree *h_tree;
    QStackedLayout *layout;
private slots:
};

#endif // MAINWIDGET_H
