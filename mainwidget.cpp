#include "mainwidget.h"
#include "ui_mainwidget.h"
#include<QDebug>
mainWidget::mainWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    read_file_dialog=new ReadFileDialog();
    data_player=new dataPlayer();
    tree_view=new treeView();
    h_tree=new huffman_tree();
    layout=new QStackedLayout();
    layout->addWidget(read_file_dialog);
    layout->addWidget(data_player);
    layout->addWidget(tree_view);
    setLayout(layout);
    connect(read_file_dialog,SIGNAL(display(int)),layout,SLOT(setCurrentIndex(int)));
    connect(data_player,SIGNAL(display(int)),layout,SLOT(setCurrentIndex(int)));
    connect(read_file_dialog,SIGNAL(file_Path(QString)),h_tree,SLOT(read_File_create(QString)));
    connect(h_tree,SIGNAL(read(std::map<QChar,int>)),data_player,SLOT(showData(std::map<QChar,int>)));
    connect(h_tree,SIGNAL(created(node*)),h_tree,SLOT(traverse(node*)));
    connect(h_tree,SIGNAL(gotCode(node*,double)),tree_view,SLOT(showData(node*,double)));
    connect(h_tree,SIGNAL(created(node*)),tree_view,SLOT(drawTree(node*)));

}

mainWidget::~mainWidget()
{
    delete ui;
}

