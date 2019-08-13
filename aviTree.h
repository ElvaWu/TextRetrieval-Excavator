#ifndef AVITREE_H
#define AVITREE_H

//平衡二叉树类的声明
#include "Sstring.h"
#include "docLink.h"

struct keyType
{
	CharString term;
	int index;//单词ID
	int df;//出现文档个数
	int occur;//出现总次数
	dNode* dHead;//文档链表头节点
};//二叉树节点的键值

struct aviNode
{
	keyType m_key;
	int height;
	aviNode* left;
	aviNode* right;
	aviNode(keyType key) : m_key(key),height(0), left(NULL), right(NULL){}
};

class aviTree
{
public:
	 aviTree(){}
      ~aviTree(){}
      aviNode *root;

	  //插入结点
      void Insert(aviNode* &t,keyType  x);
      //删除结点
      //bool Delete(aviNode* &t,keyType  x);
      //查找是否存在给定值的结点
      aviNode* Search(aviNode* t,keyType  x) const;
	  //调整使其平衡
	  //单旋转 左
      aviNode* AdjustLL(aviNode *t);
      //单旋转 右
      aviNode* AdjustRR(aviNode *t);
      //双旋转 右左
      aviNode* AdjustLR(aviNode *t);
      //双旋转 左右
      aviNode* AdjustRL(aviNode *t);

	  int GetHeight(aviNode *t);

};  


#endif
