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
         //�ж�ƽ�����
         if (GetHeight(t->left) - GetHeight(t->right) > 1)
		 {
             //��������� ���������
 
             if (x.term.compare(t->left->m_key.term)<0)//����
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
     else if(!x.term.compare(t->m_key.term))//������ͬ��
	 {
		 t->m_key.occur++;
		 dNode *p=t->m_key.dHead;
		 while(p->next)
			 p=p->next;
		 if(x.dHead->docIndex==p->docIndex)//��������ͬ�ĵ��г��֣��ô��ĵ������Ӧ�ڵ���ִ�����һ
			 p->times++;
		 else//�����ڲ�ͬ�ĵ��г��֣������ĵ�����Ľڵ�
		 {
			 p->next=x.dHead;
			 t->m_key.df++;
		 }
	 }
     t->height = GetHeight(t->left)+1;
	 if(GetHeight(t->right)>GetHeight(t->left))
		 t->height=GetHeight(t->left)+1;//�������
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
      //����ת ��
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

