#include"Huffman_tree.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QChar>
#include<QDebug>
#include<queue>
#include<stack>
class func{//仿函数，用于优先队列进行排序
public:
    bool operator()(node*&a,node*&b)
    {
        return a->weight>b->weight;
    }
};

void huffman_tree::read_File_create(QString path)
{
    if(path.isEmpty()){
        return;
    }
    else
    {
        QFile fi(path);
        fi.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream st(&fi);
        QChar ch;
        while(!st.atEnd())
        {
            st>>ch;
            if(ch=='\xa')continue;//偶尔会读到\xa，不知道为什么，但为了以防万一，读到这个字符就跳过
            num[ch]++;
        }

    }

    emit read(num);

    qDebug()<<"creating"<<endl;
    int n=num.size();
    node*code=new node[n];
    int cnt=0;
    int sum=0;
    for(std::map<QChar,int>::iterator i=num.begin();i!=num.end();i++,cnt++)
    {
        sum+=i->second;
    }
    cnt=0;
    for(std::map<QChar,int>::iterator i=num.begin();i!=num.end();i++,cnt++)
    {
        double hz=i->second/(double)sum;
        code[cnt].ch=(*i).first;//字符
        code[cnt].weight=hz;//权值（频率）
    }//将num数组中的原始数据转化为一系列初始结点

    std::priority_queue<node,QVector<node*>,func> que;//优先队列,从小到大排序
    for(int i=0;i<n;i++)
    {
        que.push(&code[i]);

    }
    while(que.size()!=1)
    {
        node*s=new node();
        s=que.top();
        que.pop();

        node*t=new node();
        t=que.top();
        que.pop();

        node*r=new node();
        if(s->weight<t->weight){
            r->leftChild=s;
            r->rightChild=t;
        }
        else
        {
            r->leftChild=t;
            r->rightChild=s;
        }
        r->weight=s->weight+t->weight;
        s->parent=r;
        t->parent=r;

        que.push(r);

    }

    root=que.top();
    qDebug()<<"created"<<endl;
    emit created(root);
}
void huffman_tree::traverse(node*r)//前序遍历，同时求各字符编码与路径长度
{
    qDebug()<<"traverse has been runned"<<endl;


    std::stack<node*> s;
    node* i=root;
    while(!s.empty()||i!=NULL)
    {

        while(i!=NULL)
        {


            if(i->parent!=NULL)i->len=i->parent->len+1;//计算各节点路径长度

            if(i->parent!=NULL&&i->parent->leftChild!=NULL&&i->parent->leftChild==i) {
                i->code=i->parent->code+"0";

            }
            else if(i->parent!=NULL&&i->parent->rightChild!=NULL&&i->parent->rightChild==i) {
                i->code=i->parent->code+"1";
            }

            if(i->leftChild==NULL&&i->rightChild==NULL)//若为叶子节点，则将已有的编码逆序,并更新带权路径长度
            {
                for(int j=0;j<i->code.length()/2;j++){
                    QChar t=i->code[j];
                    i->code[j]=i->code[i->code.length()-j-1];
                    i->code[i->code.length()-j-1]=t;
                }
                wpl+=i->len*i->weight;
            }
            qDebug()<<'*'<<i->ch<<' '<<i->weight<<' '<<i->code<<' '<<i->len<<Qt::endl;
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
    qDebug()<<wpl;
    emit gotCode(root,wpl);

}


