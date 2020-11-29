#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include<QChar>
#include<QObject>
#include<map>

class node:public QObject
{
    Q_OBJECT

public:
    node()
    {
        parent=NULL;
        leftChild=NULL;
        rightChild=NULL;
        weight=0;
        ch=' ';
        len=0;
        code.clear();
    }
    node(node&obj)
    {
        parent=obj.parent;
        leftChild=obj.leftChild;
        rightChild=obj.rightChild;
        weight=obj.weight;
        ch=obj.ch;
        len=obj.len;
        code.clear();
    }
    node(node*&obj)
    {
        parent=obj->parent;
        leftChild=obj->leftChild;
        rightChild=obj->rightChild;
        weight=obj->weight;
        ch=obj->ch;
        len=obj->len;
        code.clear();
    }

private:
    QChar ch;
    double weight;
    node*parent;
    node*leftChild,*rightChild;
    int len;//当前节点路径长度
    QString code;//当前字符的哈夫曼编码
    double x=0;
    double y=0;//当前节点的坐标
    friend class huffman_tree;
    friend class func;
    friend class treeView;
};
class huffman_tree:public QObject
{
    Q_OBJECT

 public:

    void solve(QString str);//解码，输入01序列并输出原序列
    friend class mainWidget;
private:
    node*root=NULL;
    std::map<QChar,int>num;//保存字符与出现的数目
    double wpl=0;//带权路径长度
signals:
    void read(std::map<QChar,int>);
    void created(node*);
    void gotCode(node*,double);
private slots:
    void traverse(node*);//遍历
    void read_File_create(QString);//读入文件并统计字符数,然后建树
};

#endif // HUFFMAN_TREE_H
