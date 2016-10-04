#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#define INF 1e5
using namespace std;
struct point
{
    float x_value;
    float y_value;
};
struct node
{
    point p;
    node *parent;
    char color;
    node *left;
    node *right;
};
class RBtree
{
    public :
        RBtree();
        void insert(char dim,point p);
        node* search(char dim,point p);
        int numofrange(char dim,float low,float up,vector<struct point>& pointArr);
        int numinrange(float low_x,float up_x,float low_y,float up_y, vector<struct point>& pointArr);
        point nearestnode(point p);
        int numofnode();
    private:
        void insert_x(point p, node *leaf);
        void insert_y(point p, node *leaf);
        node* search(char dim,point p, node *leaf);
        //void insertfix(node *leaf);
        float dis(point p1,point p2);
        point mindis(vector<struct point>& pointArr, point p ,float& D);
        point nearestnode(point p,float D);

        int nearsquare(point p,float D);
        int nearestsquare(point p,float D,vector<struct point>& pointArr);
        void leftrotate(node *leaf);
        void rightrotate(node *leaf);
        int numofnode(node *);
        int numofrange(char dim,float low,float up,node *leaf,vector<struct point>& pointArr);
        void node_ini(point p,node* leaf);
        node *root;
};
RBtree::RBtree()
{
    root=NULL;
}
void RBtree::node_ini(point p,node* leaf)
{
    leaf->p.x_value=p.x_value;
    leaf->p.y_value=p.y_value;
    leaf->left=NULL;
    leaf->right=NULL;
}
void RBtree::insert(char dim,point p)
{
    if(root!=NULL)
    {
        if(dim=='x')
            insert_x(p , root);
        if(dim=='y')
            insert_y(p , root);

    }

    else
    {
        root=new node;
        node_ini(p,root);
        root->parent=NULL;
        root->color='b';
    }
}

void RBtree::insert_x(point p, node *leaf)
{


    if(p.x_value<leaf->p.x_value)
    {
        if(leaf->left!=NULL)
            insert_x(p, leaf->left);
        else
        {
            leaf->left=new node;
            node_ini(p,leaf->left);
            leaf->left->parent=leaf;
           // insertfix(leaf->left);
        }
    }
    else if(p.x_value>=leaf->p.x_value)
    {
        if(leaf->right!=NULL)
            insert_x(p, leaf->right);
        else
        {
            leaf->right=new node;
            node_ini(p,leaf->right);
            leaf->right->parent=leaf;
         //   insertfix(leaf->right);
        }
    }

}
void RBtree::insert_y(point p, node *leaf)
{


    if(p.y_value<leaf->p.y_value)
    {
        if(leaf->left!=NULL)
            insert_y(p, leaf->left);
        else
        {
            leaf->left=new node;
            node_ini(p,leaf->left);
            leaf->left->parent=leaf;
          //  insertfix(leaf->left);
        }
    }
    else if(p.y_value>=leaf->p.y_value)
    {
        if(leaf->right!=NULL)
            insert_y(p, leaf->right);
        else
        {
            leaf->right=new node;
            node_ini(p,leaf->right);
            leaf->right->parent=leaf;
           // insertfix(leaf->right);
        }
    }

}
/*void RBtree::insertfix(node *t)
{
    node *u;
    while(t->parent!=NULL&&t->parent->color=='r')
    {
        node *g=t->parent->parent;
        if(g->left==t->parent)
        {
            if(g->right!=NULL)
            {
                u=g->right;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->right==t)
                {
                    t=t->parent;
                    leftrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                rightrotate(g);
            }
        }
        else
        {
            if(g->left!=NULL)
            {
                 u=g->left;
                 if(u->color=='r')
                 {
                      t->parent->color='b';
                      u->color='b';
                      g->color='r';
                      t=g;
                 }
            }
            else
            {
                if(t->parent->left==t)
                {
                       t=t->parent;
                       rightrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                leftrotate(g);
            }
        }
        root->color='b';
    }
}*/
void RBtree::leftrotate(node *p)
{
    if(p->right==NULL)
        return ;
    else
    {
        node *y=p->right;
        if(y->left!=NULL)
    {
        p->right=y->left;
        y->left->parent=p;
    }
    else
        p->right=NULL;
    if(p->parent!=NULL)
        y->parent=p->parent;
    if(p->parent==NULL)
        root=y;
    else
    {
        if(p==p->parent->left)
           p->parent->left=y;
        else
           p->parent->right=y;
    }
        y->left=p;
        p->parent=y;
    }
}
void RBtree::rightrotate(node *p)
{
    if(p->left==NULL)
        return ;
    else
    {
        node *y=p->left;
        if(y->right!=NULL)
        {
            p->left=y->right;
            y->right->parent=p;
        }
        else
            p->left=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
}
node *RBtree::search(char dim,point p)
{
    return search(dim, p, root);
}
node *RBtree::search(char dim,point p, node *leaf)
{
    float comp=0;
    if (dim=='x')
        comp=p.x_value;
    else if (dim=='y')
        comp=p.y_value;
    else
        return NULL;
    if(leaf!=NULL)
    {
        if(comp==leaf->p.x_value)
            return leaf;
        else if(comp<leaf->p.x_value)
            return search(dim,p, leaf->left);
        else
            return search(dim,p, leaf->right);
    }
    else
        return NULL;
}
 int RBtree::numofnode()
 {
     return numofnode(root);
 }
 int RBtree::numofnode(node *leaf)
 {
     int count=0;
     if (leaf != NULL) {
        count = 1 + numofnode(leaf->left) + numofnode(leaf->right);
    }
    return count;

 }
int RBtree::numofrange(char dim,float low,float up,vector<struct point>& pointArr)
{
   return numofrange(dim,low,up,root,pointArr);
}
int RBtree::numofrange(char dim,float low,float up,node *leaf,vector<struct point>& pointArr)
{

    int count=0;
    if (leaf!=NULL)
    {
        float comp=0;
        point temp;
        if (dim=='x')
            comp=leaf->p.x_value;
        else if (dim=='y')
            comp=leaf->p.y_value;
        else
            return 0;
        if(low>comp)
            count=numofrange(dim,low,up,leaf->right,pointArr);
        else if(up<comp)
            count=numofrange(dim,low,up,leaf->left,pointArr);
        else if(up>=comp>=low)
        {
            temp.x_value=leaf->p.x_value,
            temp.y_value=leaf->p.y_value,
            pointArr.push_back(temp);
            count=1+numofrange(dim,low,up,leaf->right,pointArr)+numofrange(dim,low,up,leaf->left,pointArr);
        }
    }
    return count;
}
int RBtree::numinrange(float low_x,float up_x,float low_y,float up_y, vector<struct point>& pointArr)
{
    numofrange('x',low_x,up_x,pointArr);
    class RBtree temptree;
    for(int i=0;i<pointArr.size();i++)
    {
        temptree.insert('y',pointArr[i]);
    }
    return temptree.numofrange('y',low_y,up_y,pointArr);
}
float RBtree::dis(point p1,point p2)
{
    return sqrt(pow(p1.x_value-p2.x_value,2)+pow(p1.y_value-p2.y_value,2));
}
point RBtree::mindis(vector<struct point>& pointArr, point p ,float& D)
{
    float min_d=INF;
    point temp;
    for(int i=0;i<pointArr.size();i++)
    {
        if(min_d>dis(p,pointArr[i]))
        {
            temp.x_value=pointArr[i].x_value;
            temp.y_value=pointArr[i].y_value;
            min_d=dis(p,pointArr[i]);
        }
    }
    pointArr.clear();
    return temp;
}
point RBtree::nearestnode(point p,float D)
{
    vector<struct point> tempArr;
    if(0<nearestsquare(p,D,tempArr)<10)
    {
        nearestsquare(p,D,tempArr);
        return mindis(tempArr,p,D);
    }
    if(nearestsquare(p,D,tempArr)>10&nearestsquare(p,D,tempArr)==0)
    {
        nearestsquare(p,D,tempArr);
        return mindis(tempArr,p,D);
    }
    if(nearestsquare(p,D,tempArr)>10&nearestsquare(p,D,tempArr)>0)
        return nearestnode(p,D/2);
    if(nearestsquare(p,D,tempArr)==0)
        return nearestnode(p,2*D);
}
point RBtree::nearestnode(point p)
{
    return nearestnode(p,1/sqrt(numofnode()));

}
int RBtree::nearestsquare(point p,float D,vector<struct point>& pointArr)
{
    return numinrange(p.x_value-D,p.x_value+D,p.y_value-D,p.y_value+D,pointArr);
}
