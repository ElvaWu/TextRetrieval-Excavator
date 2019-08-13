#ifndef AVITREE_H
#define AVITREE_H

//ƽ��������������
#include "Sstring.h"
#include "docLink.h"

struct keyType
{
	CharString term;
	int index;//����ID
	int df;//�����ĵ�����
	int occur;//�����ܴ���
	dNode* dHead;//�ĵ�����ͷ�ڵ�
};//�������ڵ�ļ�ֵ

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

	  //������
      void Insert(aviNode* &t,keyType  x);
      //ɾ�����
      //bool Delete(aviNode* &t,keyType  x);
      //�����Ƿ���ڸ���ֵ�Ľ��
      aviNode* Search(aviNode* t,keyType  x) const;
	  //����ʹ��ƽ��
	  //����ת ��
      aviNode* AdjustLL(aviNode *t);
      //����ת ��
      aviNode* AdjustRR(aviNode *t);
      //˫��ת ����
      aviNode* AdjustLR(aviNode *t);
      //˫��ת ����
      aviNode* AdjustRL(aviNode *t);

	  int GetHeight(aviNode *t);

};  


#endif
