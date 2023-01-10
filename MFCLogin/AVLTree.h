#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
#include<Windows.h>
#include<algorithm>
#include "pch.h"
#include "framework.h"
#include "MFCLogin.h"
#include "AVLTree.h"
#include "MFCLoginDlg.h"
#include "afxdialogex.h"
using namespace std;

/***�ڵ���***/
class AVLNode {
public:
	string userName;        //�û���
	string password;     //����
	//short balanceFactor; //ƽ������
	int height;          //��¼����
	AVLNode* left;       //�����
	AVLNode* right;      //�Ҷ���

	//AVLNode�Ĺ��캯��
	//Ĭ�Ϲ��캯��
	//ƽ������Ϊ0����������Ϊ��
	AVLNode() :userName("0"), password("0"), height(0), left(0), right(0) {}

	//��ʽ���캯��
	//ƽ������Ϊ0����������Ϊ��
	AVLNode(string userName, string password) {
		this->userName = userName;
		this->password = password;
		//balanceFactor = 0;
		height = 0;
		left = 0;
		right = 0;
	}
};//��AVLNode��������
typedef AVLNode* AVLNodePointer;

class AVLTree {
public:
	/***AVLtree������Ա***/
	AVLTree();
	AVLTree(int num);
	~AVLTree();
	void inorder(ostream& out)const;//����AVLTree
	bool search(const string& item)const;//���Һ���
	bool empty() const;//�пղ���
	void insert(AVLNodePointer& ptr, const string& name, const string& pass);//�������
	void remove(AVLNodePointer& ptr, const string& item);//ɾ������
	int getHeight(AVLNodePointer p);//��ȡ����
	AVLNodePointer& getRoot();//��ȡ���ڵ�
	void save();//���湦��
	void readTree();//��ȡ����:����txt�ļ��д洢���û����Լ�����������AVL��
	void graph(ostream& out)const;//ͼ�λ����AVL��
	bool registerUser(string name,string pass);//ע�����û�
	bool passChange(string name,string pass,string passEnd);//�޸�����
	bool logIn(string name,string pass);//��¼��֤

private:
	/*���ݳ�Ա*/
	AVLNodePointer root;

	/***��������***/
	void inorderAux(ostream& out, AVLNodePointer subtreePtr)const;
	bool searchAux(AVLNodePointer subtreeRoot, const string& item) const;
	void saveAux(ofstream& ifile, AVLNodePointer ptr);
	void release(AVLNodePointer mySroot);
	void graphAux(ostream& out, int indent, AVLNodePointer subTree)const;
	void search2(const string& item, bool& found, AVLNodePointer& locptr)const;
	AVLNodePointer LL(AVLNodePointer ptr);//����
	AVLNodePointer RR(AVLNodePointer ptr);//�ҵ���
	AVLNodePointer LR(AVLNodePointer ptr);//��-����
	AVLNodePointer RL(AVLNodePointer ptr);//��-����
};

