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

/***节点类***/
class AVLNode {
public:
	string userName;        //用户名
	string password;     //密码
	//short balanceFactor; //平衡因子
	int height;          //记录树高
	AVLNode* left;       //左儿子
	AVLNode* right;      //右儿子

	//AVLNode的构造函数
	//默认构造函数
	//平衡因子为0，两条链都为空
	AVLNode() :userName("0"), password("0"), height(0), left(0), right(0) {}

	//显式构造函数
	//平衡因子为0，两条链都为空
	AVLNode(string userName, string password) {
		this->userName = userName;
		this->password = password;
		//balanceFactor = 0;
		height = 0;
		left = 0;
		right = 0;
	}
};//类AVLNode声明结束
typedef AVLNode* AVLNodePointer;

class AVLTree {
public:
	/***AVLtree函数成员***/
	AVLTree();
	AVLTree(int num);
	~AVLTree();
	void inorder(ostream& out)const;//遍历AVLTree
	bool search(const string& item)const;//查找函数
	bool empty() const;//判空操作
	void insert(AVLNodePointer& ptr, const string& name, const string& pass);//插入操作
	void remove(AVLNodePointer& ptr, const string& item);//删除操作
	int getHeight(AVLNodePointer p);//获取树高
	AVLNodePointer& getRoot();//获取根节点
	void save();//保存功能
	void readTree();//读取功能:根据txt文件中存储的用户名以及密码来构造AVL树
	void graph(ostream& out)const;//图形化输出AVL树
	bool registerUser(string name,string pass);//注册新用户
	bool passChange(string name,string pass,string passEnd);//修改密码
	bool logIn(string name,string pass);//登录验证

private:
	/*数据成员*/
	AVLNodePointer root;

	/***辅助函数***/
	void inorderAux(ostream& out, AVLNodePointer subtreePtr)const;
	bool searchAux(AVLNodePointer subtreeRoot, const string& item) const;
	void saveAux(ofstream& ifile, AVLNodePointer ptr);
	void release(AVLNodePointer mySroot);
	void graphAux(ostream& out, int indent, AVLNodePointer subTree)const;
	void search2(const string& item, bool& found, AVLNodePointer& locptr)const;
	AVLNodePointer LL(AVLNodePointer ptr);//左单旋
	AVLNodePointer RR(AVLNodePointer ptr);//右单旋
	AVLNodePointer LR(AVLNodePointer ptr);//左-右旋
	AVLNodePointer RL(AVLNodePointer ptr);//右-左旋
};

