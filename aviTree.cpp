#include"aviTree.h"

int aviTree::GetHeight(aviNode *t)
{
	if (t == NULL)
          return -1;
    else
          return t->height;
}

aviNode* aviTree::Search(aviNode* t,keyType  x) const
{
	if (t == NULL)
         return NULL;
	if (x.term.compare(t->m_key.term)<0)
         return Search(t->left, x);
     else if (x.term.compare(t->m_key.term)>0)
         return Search(t->right, x);
     else
         return t;
}

void aviTree::Insert(aviNode* &t,keyType x)
{
	if (t == NULL)
     t = new aviNode(x);
		 
     else if (x.term.compare(t->m_key.term)<0)
	 {
         Insert(t->left, x);
         //判断平衡情况
         if (GetHeight(t->left) - GetHeight(t->right) > 1)
		 {
             //分两种情况 左左或左右
 
             if (x.term.compare(t->left->m_key.term)<0)//左左
                 t = AdjustLL(t);
             else  
				 //if(x.term.compare(t->left->m_key.term)>0)
                 t = AdjustLR(t);
			 //else
				// t->left->m_key.occur++;
         }
     }
     else if (x.term.compare(t->m_key.term)>0)
     {
         Insert(t->right, x);
         if (GetHeight(t->right) - GetHeight(t->left) > 1)
         {
             if (x.term.compare(t->right->m_key.term)>0)
                 t = AdjustRR(t);
             else 
				 //if(x.term.compare(t->right->m_key.term)<0)
                 t = AdjustRL(t);
			// else
				// t->right->m_key.occur++;
         }
	 }
     else if(!x.term.compare(t->m_key.term))//出现相同词
	 {
		 t->m_key.occur++;
		 dNode *p=t->m_key.dHead;
		 while(p->next)
			 p=p->next;
		 if(x.dHead->docIndex==p->docIndex)//若是在相同文档中出现，该词文档链表对应节点出现次数加一
			 p->times++;
		 else//若是在不同文档中出现，增加文档链表的节点
		 {
			 p->next=x.dHead;
			 t->m_key.df++;
		 }
	 }
     t->height = GetHeight(t->left)+1;
	 if(GetHeight(t->right)>GetHeight(t->left))
		 t->height=GetHeight(t->left)+1;//树的深度
 }

 aviNode* aviTree:: AdjustLL(aviNode *t)
 {
	  aviNode *q = t->left;
      t->left = q->right;
      q->right = t;
      t = q;

      t->height = GetHeight(t->left)+1;
	  if(GetHeight(t->right)>GetHeight(t->left))
		  t->height=GetHeight(t->right)+1;

      q->height = GetHeight(q->left)+1;
	  if(GetHeight(q->right)>GetHeight(q->left))
		q->height=GetHeight(q->right)+1;
      return q;
 }
      //单旋转 右
aviNode* aviTree:: AdjustRR(aviNode *t)
{
	 aviNode *q = t->right;
     t->right = q->left;
     q->left = t;
     t = q;

     t->height = GetHeight(t->left)+1;
	 if(GetHeight(t->right)>GetHeight(t->left))
		 t->height=GetHeight(t->right)+1;

     q->height = GetHeight(q->left)+1;
	 if(GetHeight(q->right)> GetHeight(q->left))
		 q->height=GetHeight(q->right)+1;
     return q;
}
      
aviNode * aviTree::AdjustLR(aviNode *t)
{
	AdjustRR(t->left);
    return AdjustLL(t);
}
      
aviNode * aviTree::AdjustRL(aviNode *t)
{
	AdjustLL(t->right);
    return AdjustRR(t);
}

