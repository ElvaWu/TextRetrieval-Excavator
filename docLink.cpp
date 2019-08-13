#include"docLink.h"

void add(dNode* &dLink,int index,int times)
{
	dNode* p=dLink;
	if(!p)
	{
	dLink=new dNode(index,times);	
	p->next=nullptr;
		return;
	}
	while(p->next)
	{
	p=p->next;
	}
	p->next=new dNode(index,times);
	p->next->next=nullptr;
}

dNode* search(dNode* dLink,int index)
{
	dNode* p=dLink;
	while(p)
	{
		p=p->next;
		if(p->docIndex==index)
		return p;
	}
	return nullptr;
}

void edit(dNode* &dLink,int preIndex,int index,int times)
{
	dNode* p=dLink;
	while(p)
	{
		p=p->next;
		if(p->docIndex==preIndex)
		{
			p->docIndex=index;
			p->times=times;
			return;
		}
	}
}

void remove(dNode* &dLink,int index)
{
	dNode* p=dLink;
	while(p)
	{
	p=p->next;
	if(p->docIndex==index)
	{
		p->docIndex=index;
		p->next=p->next->next;
		return;
	}
	}
}