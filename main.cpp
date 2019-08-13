#include<iostream>
#include<fstream>
#include<sstream>
#include <windows.h>
#include <wininet.h>
#include<string>
#include <vector>

#include"aviTree.h"
#include"Sstring.h"
#include"stack.h"
#include"charStrLink.h"

#define MAXBLOCKSIZE 1024
#define URL_NUM 2000
#define MAXLENGTH 8

#pragma comment(lib, "wininet.lib")
#pragma warning(disable:4996)

using namespace std;
string extractFile="extract.txt";
string divideWFile="divideWords.txt";

struct log
{
	int index;
	int occur;
	int keyWords;
};

void GetWebSrcCode(const char *Url,ofstream& outputStream);
void extractInfo(ofstream &outputStream);//��ȡ��ҳ��Ϣ
int judgeTitle(CharString s);//�б��ǩ�µ������Ƿ�Ϊ����
CharString switchToMultiByte(CharString a);
CharString divideWords(CharString str,vector<CharString> wordHash);
aviTree CreateBiTree();
void searchWords(aviTree tree);


int main()
{
	ifstream inputStream("input/url.csv");
	string urlStr[URL_NUM];
	int a;
	char c;
	string s;
	
	ofstream outputStream;
	outputStream.open(extractFile, ios::out);
	
	CharString url[URL_NUM];
	getline(inputStream, s);
	for (int i = 0; i < URL_NUM; i++)
	{
		inputStream >> a >> c >> c;
		getline(inputStream, urlStr[i], '"');
		url[i]= CharString(const_cast<char*>(urlStr[i].c_str()), urlStr[i].length());
		
		GetWebSrcCode(urlStr[i].c_str(),outputStream);
		
	}
	cout<<"��ҳ�������"<<endl;

	aviTree tree=CreateBiTree();
	searchWords(tree);
	system("pause");
	return 0;
}

void searchWords(aviTree tree)
{
	ifstream dicFile("�ʵ�.txt"); // �򿪴ʵ�
	if (!dicFile.is_open()) // �򿪴ʵ�ʧ�����˳�
	{
	cout << "�ʵ��ʧ��!" << endl;
	return;
	}
	vector<CharString> wordhash;
	string strtmp;
	
	cout<<"��ʼ���شʿ�"<<endl;
	while (getline(dicFile, strtmp, '\n')) // ����ʵ��ÿһ�в�����������ϣ�� 
	{ 
		wordhash.push_back(CharString(
			const_cast<char*>(strtmp.c_str()),strtmp.length())
			); //���뵽��ϣ��
	} 
	ifstream queryFile("input/query.txt");
	if (!queryFile.is_open()) // �򿪲�ѯ�ļ�ʧ���򷵻�
	{
	cout << "��ѯ�ļ���ʧ��";
	return;
	}

	ofstream outputStream;
	outputStream.open("result.txt", ios::out);
	while (!queryFile.eof()) //�����ѯ�ļ���ÿһ�в������ƥ�䷨����
	{
	string line;
	getline(queryFile, line);
	if(line.length()<=0)
	{
		outputStream<<endl;
		continue;
	}
	CharString result= divideWords(CharString(const_cast<char*>(line.c_str()),line.length()),
								wordhash); // ���÷ִʺ������зִʴ���
	if(result.getLength()<=0)
	{
		outputStream<<endl;
		continue;
	}
	struct log * searchLog=new struct log[URL_NUM+1];//����ÿ���ĵ��еĳ��ִ��� 0λ����
	
	for(int j=0;j<URL_NUM+1;j++)
	{
		searchLog[j].occur=0;
		searchLog[j].keyWords=0;
		searchLog[j].index=j;
	}
	
	while(result.getLength()>2)
	{
		int pos=result.indexOfChar(0,',');
		CharString word=result.substring(0,pos);
		keyType data={word,0,1,1,NULL};
		aviNode* node=tree.Search(tree.root,data);//�����в���
		if(node)
		{
			dNode* p=node->m_key.dHead;
			while(p)
			{
				searchLog[p->docIndex].occur+=p->times;
				searchLog[p->docIndex].keyWords+=1;
				p=p->next;
			}
		}
		result=result.substring(pos+1,result.getLength()-pos-1);
	}
		int max=1;
		for(int j=1;j<URL_NUM;j++)
		{
			for(int k=URL_NUM;k>=j+1;k--)
			{
				if(searchLog[k].keyWords<searchLog[k+1].keyWords)
					swap(searchLog[k],searchLog[k+1]);
			}
		}
		cout<<"��ʼ�����ѯ���"<<endl;
		for(int j=1;j<URL_NUM+1;j++)
		{
			if(searchLog[j].occur!=0&&searchLog[j].index<=URL_NUM)
				outputStream<<'('<<searchLog[j].index<<','<<searchLog[j].occur<<')'<<' ';
		}
		outputStream<<endl;
	}

}

//��һ�����ӽ��зִ�
CharString divideWords(CharString str,vector<CharString> wordHash)
{
	CharString result=CharString("\0",0);
	CharString seprate=CharString(",",1);
	while(str.getLength()>2)
	{
		int length=str.getLength();
		if(length>MAXLENGTH)
		{
			length=MAXLENGTH;
		}
		
		int m=count(wordHash.begin(),wordHash.end(),str.substring(str.getLength()-length,length));
		
		while(length>2&&m<=0)
		{
			length-=1;
			m=count(wordHash.begin(),wordHash.end(),str.substring(str.getLength() - length, length));
		}
		
		if(m>0)
		{
		result=result.concat(str.substring(str.getLength() - length, length));
		result=result.concat(seprate);
		}
		str = str.substring(0, str.getLength() - length);
	}
	return result;
}

aviTree CreateBiTree()
{
	ifstream dicFile("�ʵ�.txt"); // �򿪴ʵ�
	if (!dicFile.is_open()) // �򿪴ʵ�ʧ�����˳�
	{
	cout << "�ʵ��ʧ��!" << endl;
	exit(0);
	}
	vector<CharString> wordhash;
	string strtmp;
	int i=0;
	//��ʼ���شʿ�
	while (getline(dicFile, strtmp, '\n')) // ����ʵ��ÿһ�в�����������ϣ�� 
	{ 
		wordhash.push_back(CharString(
			const_cast<char*>(strtmp.c_str()),strtmp.length())
			); //���뵽��ϣ��
		i++;
	} 

	string line; //���ڱ���ӽ����ļ��ж����ÿһ��

	ifstream exfile("extract.txt"); // ���ļ�
	if (!exfile.is_open()) // �򿪽�������ļ�ʧ�����˳�
	{
	cout << "�����ļ���ʧ��";
	exit(0);
	}

	cout<<"��ʼ�ִ�"<<endl;
	int k=0,j=0;
	aviTree tree;
	tree.root=NULL;
	ofstream output;
	output.open(divideWFile, ios::out);
	i=1;//�ĵ�����
	while (!exfile.eof()) //��������ļ���ÿһ�в������ƥ�䷨����
	{
	string line;
	getline(exfile, line);
	if(line.length()<=0)//��������Ϊ��
	{
		output<<endl;
		i++;
		continue;
	}
	CharString result= divideWords(CharString(const_cast<char*>(line.c_str()),line.length()),
								wordhash); // ���÷ִʺ������зִʴ���
	if(result.getLength()>0)
		result.outputChStr(output);
	output<<endl;

	while(result.getLength()>2)
	{
		int pos=result.indexOfChar(0,',');
		CharString word=result.substring(0,pos);
		keyType data={word,k,
					1,//�����ڶ���ƪ�ĵ���
					1,//�ܳ��ִ���
					new dNode((i+1)/2,1)};
		k++;
		result=result.substring(pos+1,result.getLength()-pos-1);
		tree.Insert(tree.root,data);//�ڲ���ڵ�Ĺ����е��ڶ�����ƽ��
	}
		i++;
	 // �÷ִʽ������ƽ�������
	}
	cout<<"�ִ����"<<endl;
	return tree;
	
}


//ץȡ��ҳԴ��
void GetWebSrcCode(const char *Url,ofstream &outputStream)
{
    HINTERNET hSession = InternetOpen("zwt", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hSession != NULL)
    {
        HINTERNET hURL = InternetOpenUrl(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
        if (hURL != NULL)
        {
            char Temp[MAXBLOCKSIZE] = {0};
            ULONG Number = 1;
            FILE *stream;
            if( (stream = fopen( "text.txt", "wb" )) != NULL )
            {
                while (Number > 0)
                {
                    InternetReadFile(hURL, Temp, MAXBLOCKSIZE - 1, &Number);
                    fwrite(Temp, sizeof (char), Number , stream);
                }
                fclose( stream );
            }
            InternetCloseHandle(hURL);
            hURL = NULL;

			extractInfo(outputStream);//������ҳ
        }
        InternetCloseHandle(hSession);
        hSession = NULL;

		
    }
	
}

int judgeTitle(CharString s)
{
	char a1[] = "<div class=\"z\">";
	CharString b1 = CharString(a1, 13);
	if (s.indexOf(0, b1) >= 0)
		return 1;//���� С�� ����

	char a4[] = "<div class=\"t_f";
	CharString b4 = CharString(a4, 14);
	if (s.indexOf(0, b4) >= 0)
		return 4;//����

	return 0;
}

CharString switchToMultiByte(CharString a)
{
	int i=0;
	CharString result=CharString("\0",0);
	while(i<a.getLength())
	{
	CharString temp=a.substring(a.indexOfChar(i,'#')+1,5);
	i=a.indexOfChar(i,'#')+5;
	if(i>a.getLength())
		break;
	wchar_t wstr= (temp.getString()[0]-'0') *10000
				+(temp.getString()[1]-'0') *1000
				+(temp.getString()[2]-'0')*100
				+(temp.getString()[3]-'0')*10
				+(temp.getString()[4]-'0');

	int needBytes = WideCharToMultiByte(CP_ACP, 0,&wstr, -1, NULL, 0, NULL, NULL);  

	char *pszBuf = NULL;
    if (needBytes > 0)  
    {  
        pszBuf = new char[needBytes+1];  
        ZeroMemory(pszBuf, (needBytes+1)*sizeof(char));  
        WideCharToMultiByte(CP_ACP, 0, &wstr, -1, pszBuf, needBytes, NULL, NULL);  
    }  
	result=result.concat(CharString(pszBuf,2));
	
	}
	return result;
}

void extractInfo(ofstream &outputStream)
{
	int i = 0;

	CharString title;
	CharString cont;
	
	int n,m,p,q,r;
	int flag[8] = { 0 };
	
	ifstream inputStream("text.txt");
	string readline;
	string read;
	while(!inputStream.eof())
	{
	getline(inputStream, readline);
	read=read+readline;
	}
	//��ʼ������ҳ
	CharString content=CharString(const_cast<char*>(read.c_str()),read.length());
	while(i<read.length())
	{
	n=content.indexOfChar(i, '<');
	if(n<0)
	{
		outputStream<<','<<',';
					return;
	}
	m = content.indexOfChar(n+1, '>');
	if(m<0)
	{
		outputStream<<','<<',';
					return;
	}
	int type=0;
	type=judgeTitle(content.substring(n, m - n + 1));

	if(flag[4])
		return;

	if (type > 0&&!flag[type])
	{
		switch (type)
		{
		case 1:
			{
				p=content.indexOf(m,CharString("<a href=\"forum",13));
				if(p<0)
				{
					outputStream<<','<<',';
					return;
				}
				q=content.indexOfChar(p+1,'>');
				r=content.indexOfChar(q+1,'<');

				
				flag[type]=1;


				p=content.indexOf(r+1,CharString("<a href=\"forum",13));
				q=content.indexOfChar(p+1,'>');
				r=content.indexOfChar(q+1,'<');

				
				flag[type+1]=1;

				p=content.indexOf(r+1,CharString("<a href",7));
				q=content.indexOfChar(p+1,'>');
				r=content.indexOfChar(q+1,'<');

				title=content.substring(q+1,r-q-1);
				title.outputChStr(outputStream);
				outputStream<<endl;
				flag[type+2]=1;

				i=q+1;
			}
			break;
		case 4:
			{
				p=content.indexOf(m,CharString("td class=\"t_f",13));
				q=content.indexOfChar(p+1,'>');
				//q=content.indexOfChar(q+1,'>');
				r=content.indexOfChar(q+1,'<');

				//cont=switchToMultiByte(content.substring(q+1,r-q-1));
				cont=content.substring(q+1,r-q-1);
				if(cont.getString()[79]==' '&&cont.getString()[78]==' '&&cont.getString()[77]==' ')
					cont=cont.substring(80,cont.getLength()-80);
				cont.outputChStr(outputStream);
				outputStream<<endl;
				flag[type]=1;

				i=q+1;
			}
			break;
			
		default:
			i=n+1;
			break;
		}
	}
	else
		i=n+1;
	}
}



