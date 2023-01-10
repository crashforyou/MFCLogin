#include"AVLTree.h"
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include "pch.h"
#include "framework.h"
#include "MFCLogin.h"
#include "AVLTree.h"
#include "MFCLoginDlg.h"
#include "afxdialogex.h"
#include<Windows.h>
using namespace std;

AVLTree::AVLTree()
{
	root = new AVLNode();
	root = 0;
}

AVLTree::AVLTree(int num)
{
	string name;
	string pass;
	for (int i = 0; i < num; i++) {
		cout << "请输入12位用户名：";
		while (cin >> name) {
			if (name.size() != 12) {
				cout << "用户名长度不符合要求！" << endl;
				cout << "请输入12位用户名：";
			}
			else break;
		}
		cout << "请输入8~20位密码：";
		while (cin >> pass) {
			if (pass.size() < 8 || pass.size() > 18) {
				cout << "密码长度不符合要求！" << endl;
				cout << "请输入8~18位密码: ";
			}
			else break;
		}
		cout << endl;
		insert(root, name, pass);
	}
}

AVLTree::~AVLTree()
{
	if (root != 0) {
		release(root);
	}
}

bool AVLTree::empty() const
{
	return root == 0;
}

int AVLTree::getHeight(AVLNodePointer p)
{
	if (p == 0) {
		int a = 0;
		return a;
	}
	else {
		return p->height;
	}
}

AVLNodePointer& AVLTree::getRoot()
{
	return root;
}

void AVLTree::save()
{
	ofstream ofile;
	ofile.open("User信息.txt", ios::out);
	saveAux(ofile, root);
	ofile.close();
}

void AVLTree::readTree()
{
	ifstream ifile;
	ifile.open("User信息.txt", ios::in);
	string name, pass;
	release(root);

	while (!ifile.eof()) {
		getline(ifile, name);
		getline(ifile, pass);
		//cout << name << " " << pass << endl;
		insert(root, name, pass);
		if (ifile.peek() == '\n') break;
	}
	ifile.close();
}

void AVLTree::graph(ostream& out) const
{
	graphAux(cout, 0, root);
}

bool AVLTree::registerUser(string name,string pass)
{
	/*string name, pass;
	cout << "请输入新注册的12位用户名：";
	while (cin >> name) {
		if (name.size() != 12) {
			cout << "用户名长度不符合要求！" << endl;
			cout << "请输入12位用户名：";
		}
		else if (search(name)) {
			cout << "该用户名已被注册！" << endl;
			cout << "请输入12位用户名：";
		}
		else break;
	}
	cout << "请输入8~20位密码：";
	while (cin >> pass) {
		if (pass.size() < 8 || pass.size() > 18) {
			cout << "密码长度不符合要求！" << endl;
			cout << "请输入8~18位密码: ";
		}
		else break;
	}*/
	if (search(name)) {
		return true;
	}
	else {
		if (name != "") {
			insert(root, name, pass);
			save();
			return false;
		}
	}
}

bool AVLTree::passChange(string name, string pass, string passEnd)
{
	bool found;
	AVLNodePointer locptr;
	/*string name, passStart, passEnd;
	cout << "修改密码" << endl;
	cout << "请输入用户名：";
	cin >> name;*/
	search2(name, found, locptr);
	if (!found) {
		cout << "用户名不存在" << endl;
		return false;
	}
	else {
		/*cout << "请输入原密码：";
		cin >> passStart;
		cout << "请输入新密码：";
		cin >> passEnd;*/
		if (pass != locptr->password) {
			//cout << "原密码错误，修改失败" << endl;
			return false;
		}
		else {
			locptr->password = passEnd;
			save();
			//cout << "修改成功" << endl;
			return true;
		}
	}
}

bool AVLTree::logIn(string name,string pass)
{
	AVLNodePointer locptr;
	bool found;
	search2(name, found, locptr);
	if (search(name))
	{
		if (pass != locptr->password) {
			//cout << "密码错误，登录失败" << endl;
			return false;
		}
		else {
			//cout << "登录成功" << endl;
			return true;
		}
	}
	else {
		cout << "用户名不存在" << endl;
	}
}

void AVLTree::release(AVLNodePointer mySroot)
{
	if (mySroot) {
		release(mySroot->left);
		release(mySroot->right);
		delete mySroot;
		mySroot = 0;
	}
}

void AVLTree::graphAux(ostream& out, int indent, AVLNodePointer subTree) const
{
	if (subTree != 0) {
		graphAux(out, indent + 8, subTree->right);
		out << setw(indent) << " " << subTree->userName << endl;
		graphAux(out, indent + 8, subTree->left);
	}
}

void AVLTree::search2(const string& item, bool& found, AVLNodePointer& locptr) const
{
	locptr = root;
	found = false;
	while (!found && locptr != 0) {
		if (item < locptr->userName) {
			locptr = locptr->left;
		}
		else if (item > locptr->userName) {
			locptr = locptr->right;
		}
		else
			found = true;
	}
}

void AVLTree::saveAux(ofstream& ifile, AVLNodePointer ptr)
{
	if (ptr != 0) {
		saveAux(ifile, ptr->left);
		ifile << ptr->userName << endl << ptr->password << endl;
		saveAux(ifile, ptr->right);
	}
}



void AVLTree::inorder(ostream& out) const
{
	inorderAux(out, root);
}

void AVLTree::inorderAux(ostream& out, AVLNodePointer subtreePtr) const
{
	if (subtreePtr != 0) {
		inorderAux(out, subtreePtr->left);
		out << subtreePtr->userName << " " << subtreePtr->password << endl;
		inorderAux(out, subtreePtr->right);
	}
}

bool AVLTree::search(const string& item) const
{
	return searchAux(root, item);
}

bool AVLTree::searchAux(AVLNodePointer subtreeRoot, const string& item) const
{
	if (subtreeRoot == 0) {
		return false;
	}
	if (item < subtreeRoot->userName) {
		return searchAux(subtreeRoot->left, item);
	}
	else if (item > subtreeRoot->userName) {
		return searchAux(subtreeRoot->right, item);
	}
	else {
		return true;
	}
}




//左单旋：当插入项位于最近的平衡因子为-2的祖先节点的右孩子的右子树中时使用
AVLNodePointer AVLTree::LL(AVLNodePointer ptr)
{
	AVLNodePointer tmp = ptr->right;
	//将传进来的节点的右节点进行旋转操作
	ptr->right = tmp->left;//将tmp的左子树挂到ptr的右子树上
	tmp->left = ptr;//将ptr作为tmp的左子树

	//更新树高
	ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
	tmp->height = getHeight(tmp->right) > ptr->height ? getHeight(tmp->right) + 1 : ptr->height + 1;
	return tmp;//返回左单旋后的根节点
}

//右单旋：当插入项位于最近的平衡因子为+2的祖先节点的左孩子的左子树中时使用
AVLNodePointer AVLTree::RR(AVLNodePointer ptr)
{
	AVLNodePointer tmp = ptr->left;
	//将传进来的节点的左节点进行旋转操作
	ptr->left = tmp->right;//将tmp的右子树挂到ptr的左子树上
	tmp->right = ptr;//将ptr作为tmp的右子树

	//更新树高
	ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
	tmp->height = getHeight(tmp->left) > ptr->height ? getHeight(tmp->left) + 1 : ptr->height + 1;
	return tmp;//返回右单旋后的根节点
}

//左-右旋：当插入项位于最近的平衡因子为+2的祖先节点的左孩子的右子树中时使用
AVLNodePointer AVLTree::LR(AVLNodePointer ptr)
{
	ptr->left = LL(ptr->left);//先对ptr的左节点进行左单旋
	return RR(ptr);//再对ptr进行右旋并返回
}

//右-左旋：当插入项位于最近的平衡因子为-2的祖先节点的右孩子的左子树中时使用
AVLNodePointer AVLTree::RL(AVLNodePointer ptr)
{
	ptr->right = RR(ptr->right);//先对ptr的右节点进行右单旋
	return LL(ptr);//再对ptr进行左旋并返回
}

void AVLTree::insert(AVLNodePointer& ptr, const string& name, const string& pass)
{
	if (ptr == 0) {
		ptr = new AVLNode(name, pass);
		ptr->height = 1;
	}
	else if (name < ptr->userName) {
		insert(ptr->left, name, pass);//递归插入左子树
		if (getHeight(ptr->left) - getHeight(ptr->right) == 2) {
			//不平衡时，由于是在左子树中进行插入，故只存在左子树高于右子树的情况
			if (name < ptr->left->userName) {
				ptr = RR(ptr);
			}
			else {
				ptr = LR(ptr);
			}
		}
	}
	else if (name > ptr->userName) {
		insert(ptr->right, name, pass);
		if (getHeight(ptr->left) - getHeight(ptr->right) == -2) {
			if (name > ptr->right->userName) {
				ptr = LL(ptr);
			}
			else {
				ptr = RL(ptr);
			}
		}
	}
	else {
		cerr << "insert error:the userName already exists!" << endl;
		return;
	}
	ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
}

void AVLTree::remove(AVLNodePointer& ptr, const string& item)
{
	//操作与插入相似，但是删除的时候需要分左右子树都存在，或者都不存在，或者只存在一个
	if (ptr == 0) {
		return;
	}
	else {
		if (item < ptr->userName) {
			remove(ptr->left, item);//在根节点的左子树中递归寻找删除目标
			//删除后出现失衡进行旋转
			if (getHeight(ptr->right) - getHeight(ptr->left) > 1) {
				if (getHeight(ptr->right->left) > getHeight(ptr->right->right)) {
					ptr = RL(ptr);
				}
				else {
					ptr = LL(ptr);
				}
			}
			//删除后树未出现失衡
			else {
				ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;

			}
		}
		else if (item > ptr->userName) {
			remove(ptr->right, item);//在根节点的右子树中递归寻找删除目标
			//删除后出现失衡进行旋转
			if (getHeight(ptr->left) - getHeight(ptr->right) > 1) {
				if (getHeight(ptr->left->right) > getHeight(ptr->left->left)) {
					ptr = LR(ptr);
				}
				else {
					ptr = RR(ptr);
				}
			}
			//删除后树未出现失衡
			else {
				ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
			}
		}
		//item=ptr->userName:找到指定删除用户名的节点
		else {
			//待删除节点的左右子树都存在
			if (ptr->left != 0 && ptr->right != 0) {
				if (getHeight(ptr->left) > getHeight(ptr->right)) {
					AVLNodePointer tmp = ptr->left;
					//寻找待删除节点的左子树中的最大userName项
					while (tmp->right != 0) {
						tmp = tmp->right;
					}
					//由于ptr是待删除节点，该节点信息删除后，需用左子树中最大的userName项的信息进行修改
					ptr->userName = tmp->userName;
					ptr->password = tmp->password;
					//AVL树中不能存在两个相同用户名，已将tmp信息复制到ptr位置，故在ptr的左子树中寻找重复用户名进行删除
					remove(ptr->left, ptr->userName);
				}
				else {
					AVLNodePointer tmp = ptr->right;
					//寻找待删除节点的右子树中的最小userName项
					while (tmp->left != 0) {
						tmp = tmp->left;
					}
					//将tmp的信息复制到待删除节点ptr位置
					ptr->userName = tmp->userName;
					ptr->password = tmp->password;
					remove(ptr->right, ptr->userName);
				}
			}
			//待删除节点只存在左子树或者右子树，或者都不存在
			else {
				
				AVLNodePointer tmp = ptr;
				if (ptr->left != 0) {
					ptr = ptr->left;
				}
				else {
					ptr = ptr->right;
				}
				delete tmp;
				save();
			}
		}
	}
}


