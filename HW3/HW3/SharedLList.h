//
//  SharedLList.h
//  Homework 3
//
//  Created by Nathan Sturtevant on 2/16/15.
//  Copyright (c) 2015 Nathan Sturtevant. All rights reserved.
//

#ifndef Homework_3_SharedLList_h
#define Homework_3_SharedLList_h

#include <iostream>
#include <thread>
#include <mutex>

template <typename T>
class SharedLList {
public:
	SharedLList();
	~SharedLList();
	bool IsEmpty();
	void AddBack(T item);
	T PeekFront();
	bool RemoveFront(T &item);
	void Print();
private:
	struct ListItem
	{
		T item;
		ListItem* next;
	};
	ListItem *GetFromCache();
	void Free(ListItem *l);
	ListItem *head, *tail;
	ListItem *cache;
	std::mutex lock;
};

template <typename T>
SharedLList<T>::SharedLList()
{
	head = tail = 0;
	cache = 0;
}

template <typename T>
SharedLList<T>::~SharedLList()
{
	while (head != 0)
	{
		ListItem *tmp = head->next;
		delete head;
		head = tmp;
	}
	while (cache != 0)
	{
		ListItem *tmp = cache->next;
		delete cache;
		cache = tmp;
	}
}


template <typename T>
bool SharedLList<T>::IsEmpty()
{
	return head == 0;
}


template <typename T>
void SharedLList<T>::AddBack(T item)
{
	lock.lock();

	ListItem *t = GetFromCache();
	t->item = item;
	t->next = 0;
	if (head == 0)
	{
		head = t;
		tail = t;
	}
	else {
		tail->next = t;
		tail = t;
	}
	lock.unlock();
}

template <typename T>
bool SharedLList<T>::RemoveFront(T &item)
{
	lock.lock();
	if (head == 0)
	{
		lock.unlock();
		return false;
	}
	item = head->item;
	ListItem *t = head;
	if (head == tail)
	{
		head = tail = 0;
	}
	else {
		head = head->next;
	}
	Free(t);
	lock.unlock();
	return true;
}

template <typename T>
typename SharedLList<T>::ListItem *SharedLList<T>::GetFromCache()
{
	if (cache == 0)
		return new ListItem;
	ListItem *tmp = cache;
	cache = cache->next;
	tmp->next = 0;
	return tmp;
}

template <typename T>
void SharedLList<T>::Free(ListItem *l)
{
	l->next = cache;
	cache = l;
}

template <typename T>
void SharedLList<T>::Print()
{
	lock.lock();
	for (ListItem *t = head; t; t = t->next)
	{
		std::cout << t->item << " ";
	}
	std::cout << "\n";
	lock.unlock();
}


#endif
