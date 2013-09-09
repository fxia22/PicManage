#pragma once
#include <iostream>
#include <cstdlib>
#include "Node.h"
template <class T>
class LinkedList
{
private:
	Node<T> *front,*rear;
	Node<T> *prevPtr,*currPtr;
	int size;
	int position;

	Node<T> *GetNode(const T& item,Node<T> *ptrNext=NULL);
	void FreeNode(Node<T> *p);
	void CopyList(const LinkedList<T> &L);
public:
	LinkedList(void);
	LinkedList(const LinkedList<T> &L);
	~LinkedList(void);
	LinkedList<T> &operator= (const LinkedList<T> &L);
	int ListSize(void)const;
	void InitList();
	int ListEmpty(void)const;
	void Reset(int pos = 0);
	void Next(void);
	int EndOfList()const;
	int CurrentPosition(void)const;

	void InsertFront(const T& item);
	void InsertRear(const T& item);
	void InsertAt(const T& item);
	void InsertAfter(const T& item);
	void DeleteFront(void);
	void DeleteAt(void);
	T& Data(void);
	void ClearList(void);
	Node<T>* GetFront();
	Node<T>* GerRear();
	Node<T>* NodeAt(int pos)const;
};


template <class T>
Node<T>* LinkedList<T>::GetNode(const T &item, Node<T> *ptrNext)
{
	Node<T>* p=new Node<T>(item,ptrNext);
	if (p==NULL) 
	{
		cerr<<"Not Enough Memory"<<endl;
		exit(-1);
	}
	return p;
}

template <class T>
void LinkedList<T>::FreeNode(Node<T> *p)
{
	delete p;
}

template <class T>
void LinkedList<T>::CopyList(const LinkedList<T> &L)
{
	if (this->size!=0) 
	{
		cout<<"This may erase original data"<<endl;
		exit(-1);
	}
	Node<T>* p =L.GetFront();
	while (p!=NULL)
	{
		this->InsertRear(p->data);
		p=p->next;
	}
}

template <class T>
Node<T>* LinkedList<T>::GetFront()
{
	return front;
}

template <class T>
Node<T>* LinkedList<T>::GerRear()
{
	return rear;
}


template <class T>
LinkedList<T>::LinkedList(void)
{
	front = NULL;
	rear = NULL;
	prevPtr = NULL;
	currPtr = NULL;
	size = 0;
	position = 0;
}

template <class T>
void LinkedList<T>::InitList()
{
	front = NULL;
	rear = NULL;
	prevPtr = NULL;
	currPtr = NULL;
	size = 0;
	position = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &L)
{
	front = NULL;
	rear = NULL;
	prevPtr = NULL;
	currPtr = NULL;
	size = 0;
	CopyList(L);
}

template <class T>
LinkedList<T>::~LinkedList()
{
	this->ClearList();
}

template <class T>
void LinkedList<T>::ClearList()
{
	Node<T> *p= this->GetFront();
	Node<T> *q = p->NextNode();
	while (q!=NULL)
	{
		FreeNode(p);
		p=q;
		q=q->NextNode();
	}
	InitList();
}

template <class T>
LinkedList<T> & LinkedList<T>::operator =(const LinkedList<T> &L)
{
	if (size!=0)
	{
		cout<<"you will lose some data"<<endl;
		ClearList();
	}
	InitList();
	CopyList(L);
	return *this;
}

template<class T>
int LinkedList<T>::ListSize()const
{
	return size;
}

template<class T>
int LinkedList<T>::ListEmpty()const
{
	return (size==0);
}

template<class T>
void LinkedList<T>::Reset(int pos /* = 0 */)
{
	currPtr = front;
	prevPtr = NULL;
	position = 0;
	if ((pos<0)||(pos>size-1))
	{
		cout<<"Invalid position"<<endl;
		exit(-1);
	}
	if (size==0)
	{
		if (pos ==0) InitList();
		else {cerr<<"ListEmpty"<<endl;
		exit(-1);
		}
	}

	for (int i = 0;i<pos;i++)
	{
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}
}

template <class T>
void LinkedList<T>::Next(void)
{
	if (EndOfList())
	{
		cout<<"Rear of the List"<<endl;
		return;
	}
	else {
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}

};


template <class T>
int LinkedList<T>::EndOfList()const
{
	return (currPtr==NULL);
}

template <class T>
int LinkedList<T>::CurrentPosition()const
{
	if (currPtr==NULL)
	{
		cout<<"Position NULL exception"<<endl;
		return -1;
	}
	return position;
}


template<class T>
Node<T>*  LinkedList<T>::NodeAt(int pos)const
{
	if ((pos<0)||(pos>size-1))
	{
		cout<<"Invalid position"<<endl;
		exit(-1);
	}
	Node<T>* p= GetFront();
	for (int i=0;i<pos;i++)
	{
		p = p->NextNode();
	}
	return p;
}

template<class T>
void LinkedList<T>::InsertFront(const T& item)
{
	if (front ==NULL)
	{
		front = rear = GetNode(item,front);
		size++;
	}
	else 
	{
		front = GetNode(item,front);
		size++;
	}
}

template<class T>
void LinkedList<T>::InsertRear(const T& item)
{
	if (front==NULL)
	{
		front = rear= GetNode(item,rear);
		size++;
	}
	else
	{
		Node<T> *p=GetNode(item);
		 rear->InsertAfter(p);
		rear = p;
		size ++;
	}
}





template<class T>
void LinkedList<T>::InsertAt(const T& item)
{
	if (currPtr == front)
		InsertFront(item);
	else
	{
		prevPtr->next = GetNode(item,currPtr);
		size++;
	}
}

template<class T>
void LinkedList<T>::InsertAfter(const T& item)
{
	if (currPtr ==rear)
		InsertRear(item);
	else
	{
		currPtr->next = GetNode(item,currPtr->next);//next是私有成员，这里应该不能访问
		size++;
	}
}

template<class T>
void LinkedList<T>::DeleteFront()
{
	Node<T>*p=NULL;
	if (front==NULL)
	{
		cout<<"Front is Empty"<<endl;
		exit(-1);
	}
	p = front->NextNode();
	FreeNode(front);
	front = p;
	size--;
	return;
}

template<class T>
void LinkedList<T>::DeleteAt()
{
	if (currPtr==front) DeleteFront();
	if (currPtr==rear)
	{
		rear = prevPtr;
		rear->NextNode()=NULL;//注意这里
		FreeNode(currPtr);
		size--;
		return;
	}
	prevPtr->NextNode() = currPtr->NextNode();
	FreeNode(currPtr);
	currPtr = prevPtr;
	size--;

}


template<class T>
T& LinkedList<T>::Data()
{
	if (currPtr ==NULL)
	{
		cout<<"currentPtr=NULL"<<endl;
		exit(-1);
	}
	T& item=currPtr->data;
	return item;
}