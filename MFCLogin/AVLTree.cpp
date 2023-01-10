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
		cout << "������12λ�û�����";
		while (cin >> name) {
			if (name.size() != 12) {
				cout << "�û������Ȳ�����Ҫ��" << endl;
				cout << "������12λ�û�����";
			}
			else break;
		}
		cout << "������8~20λ���룺";
		while (cin >> pass) {
			if (pass.size() < 8 || pass.size() > 18) {
				cout << "���볤�Ȳ�����Ҫ��" << endl;
				cout << "������8~18λ����: ";
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
	ofile.open("User��Ϣ.txt", ios::out);
	saveAux(ofile, root);
	ofile.close();
}

void AVLTree::readTree()
{
	ifstream ifile;
	ifile.open("User��Ϣ.txt", ios::in);
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
	cout << "��������ע���12λ�û�����";
	while (cin >> name) {
		if (name.size() != 12) {
			cout << "�û������Ȳ�����Ҫ��" << endl;
			cout << "������12λ�û�����";
		}
		else if (search(name)) {
			cout << "���û����ѱ�ע�ᣡ" << endl;
			cout << "������12λ�û�����";
		}
		else break;
	}
	cout << "������8~20λ���룺";
	while (cin >> pass) {
		if (pass.size() < 8 || pass.size() > 18) {
			cout << "���볤�Ȳ�����Ҫ��" << endl;
			cout << "������8~18λ����: ";
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
	cout << "�޸�����" << endl;
	cout << "�������û�����";
	cin >> name;*/
	search2(name, found, locptr);
	if (!found) {
		cout << "�û���������" << endl;
		return false;
	}
	else {
		/*cout << "������ԭ���룺";
		cin >> passStart;
		cout << "�����������룺";
		cin >> passEnd;*/
		if (pass != locptr->password) {
			//cout << "ԭ��������޸�ʧ��" << endl;
			return false;
		}
		else {
			locptr->password = passEnd;
			save();
			//cout << "�޸ĳɹ�" << endl;
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
			//cout << "������󣬵�¼ʧ��" << endl;
			return false;
		}
		else {
			//cout << "��¼�ɹ�" << endl;
			return true;
		}
	}
	else {
		cout << "�û���������" << endl;
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




//��������������λ�������ƽ������Ϊ-2�����Ƚڵ���Һ��ӵ���������ʱʹ��
AVLNodePointer AVLTree::LL(AVLNodePointer ptr)
{
	AVLNodePointer tmp = ptr->right;
	//���������Ľڵ���ҽڵ������ת����
	ptr->right = tmp->left;//��tmp���������ҵ�ptr����������
	tmp->left = ptr;//��ptr��Ϊtmp��������

	//��������
	ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
	tmp->height = getHeight(tmp->right) > ptr->height ? getHeight(tmp->right) + 1 : ptr->height + 1;
	return tmp;//����������ĸ��ڵ�
}

//�ҵ�������������λ�������ƽ������Ϊ+2�����Ƚڵ�����ӵ���������ʱʹ��
AVLNodePointer AVLTree::RR(AVLNodePointer ptr)
{
	AVLNodePointer tmp = ptr->left;
	//���������Ľڵ����ڵ������ת����
	ptr->left = tmp->right;//��tmp���������ҵ�ptr����������
	tmp->right = ptr;//��ptr��Ϊtmp��������

	//��������
	ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
	tmp->height = getHeight(tmp->left) > ptr->height ? getHeight(tmp->left) + 1 : ptr->height + 1;
	return tmp;//�����ҵ�����ĸ��ڵ�
}

//��-��������������λ�������ƽ������Ϊ+2�����Ƚڵ�����ӵ���������ʱʹ��
AVLNodePointer AVLTree::LR(AVLNodePointer ptr)
{
	ptr->left = LL(ptr->left);//�ȶ�ptr����ڵ��������
	return RR(ptr);//�ٶ�ptr��������������
}

//��-��������������λ�������ƽ������Ϊ-2�����Ƚڵ���Һ��ӵ���������ʱʹ��
AVLNodePointer AVLTree::RL(AVLNodePointer ptr)
{
	ptr->right = RR(ptr->right);//�ȶ�ptr���ҽڵ�����ҵ���
	return LL(ptr);//�ٶ�ptr��������������
}

void AVLTree::insert(AVLNodePointer& ptr, const string& name, const string& pass)
{
	if (ptr == 0) {
		ptr = new AVLNode(name, pass);
		ptr->height = 1;
	}
	else if (name < ptr->userName) {
		insert(ptr->left, name, pass);//�ݹ����������
		if (getHeight(ptr->left) - getHeight(ptr->right) == 2) {
			//��ƽ��ʱ�����������������н��в��룬��ֻ�������������������������
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
	//������������ƣ�����ɾ����ʱ����Ҫ���������������ڣ����߶������ڣ�����ֻ����һ��
	if (ptr == 0) {
		return;
	}
	else {
		if (item < ptr->userName) {
			remove(ptr->left, item);//�ڸ��ڵ���������еݹ�Ѱ��ɾ��Ŀ��
			//ɾ�������ʧ�������ת
			if (getHeight(ptr->right) - getHeight(ptr->left) > 1) {
				if (getHeight(ptr->right->left) > getHeight(ptr->right->right)) {
					ptr = RL(ptr);
				}
				else {
					ptr = LL(ptr);
				}
			}
			//ɾ������δ����ʧ��
			else {
				ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;

			}
		}
		else if (item > ptr->userName) {
			remove(ptr->right, item);//�ڸ��ڵ���������еݹ�Ѱ��ɾ��Ŀ��
			//ɾ�������ʧ�������ת
			if (getHeight(ptr->left) - getHeight(ptr->right) > 1) {
				if (getHeight(ptr->left->right) > getHeight(ptr->left->left)) {
					ptr = LR(ptr);
				}
				else {
					ptr = RR(ptr);
				}
			}
			//ɾ������δ����ʧ��
			else {
				ptr->height = getHeight(ptr->left) > getHeight(ptr->right) ? getHeight(ptr->left) + 1 : getHeight(ptr->right) + 1;
			}
		}
		//item=ptr->userName:�ҵ�ָ��ɾ���û����Ľڵ�
		else {
			//��ɾ���ڵ����������������
			if (ptr->left != 0 && ptr->right != 0) {
				if (getHeight(ptr->left) > getHeight(ptr->right)) {
					AVLNodePointer tmp = ptr->left;
					//Ѱ�Ҵ�ɾ���ڵ���������е����userName��
					while (tmp->right != 0) {
						tmp = tmp->right;
					}
					//����ptr�Ǵ�ɾ���ڵ㣬�ýڵ���Ϣɾ��������������������userName�����Ϣ�����޸�
					ptr->userName = tmp->userName;
					ptr->password = tmp->password;
					//AVL���в��ܴ���������ͬ�û������ѽ�tmp��Ϣ���Ƶ�ptrλ�ã�����ptr����������Ѱ���ظ��û�������ɾ��
					remove(ptr->left, ptr->userName);
				}
				else {
					AVLNodePointer tmp = ptr->right;
					//Ѱ�Ҵ�ɾ���ڵ���������е���СuserName��
					while (tmp->left != 0) {
						tmp = tmp->left;
					}
					//��tmp����Ϣ���Ƶ���ɾ���ڵ�ptrλ��
					ptr->userName = tmp->userName;
					ptr->password = tmp->password;
					remove(ptr->right, ptr->userName);
				}
			}
			//��ɾ���ڵ�ֻ�������������������������߶�������
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


