#ifndef DOCLINK_H
#define DOCLINK_H

//文档链表节点声明
struct dNode
{
	int docIndex;
	int times;
	dNode* next;
	dNode(int index,int t):docIndex(index),times(t),next(nullptr){}
};

void add(dNode* &dLink,int index,int times);

dNode* search(dNode* dLink,int index);

void edit(dNode* &dLink,int preIndex,int index,int times);

void remove(dNode* &dLink,int index);


#endif