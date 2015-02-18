//
//  SharedQueue.h
//  Lab12
//

#ifndef __Lab12__SharedQueue__
#define __Lab12__SharedQueue__

#include <mutex>
#include <iostream>

// Adapt LList code below to implement SharedQueue
// (then remove this comment)

template <typename T>
class SharedQueue {
public:
  SharedQueue();
  ~SharedQueue();
  bool IsEmpty() const;
  void Add(T value);
  bool Remove(T &item);
  void Print();
private:
  struct QueueItem {
    T item;
    QueueItem *next;
  };
  std::mutex lock;
  QueueItem *head, *tail;
};

template <typename T>
SharedQueue<T>::SharedQueue() {
	head = nullptr;
	tail = nullptr;
}

template <typename T>
SharedQueue<T>::~SharedQueue()
{
	while (!IsEmpty()) {
		T t;
		Remove(t);
		delete head;
	}
}

template <typename T>
inline bool SharedQueue<T>::IsEmpty() const
{
	return head == nullptr;
}

template <typename T>
void SharedQueue<T>::Add(T value)
{
	lock.lock();
	if (IsEmpty())
	{
		tail = new QueueItem;
		tail->item = value;
		head = tail;
	}
	else
	{
		tail->next = new QueueItem;
		tail->next->item = value;
		/*if (head == tail)
		{
			head = tail;
		}
		else
		{
			tail->next
		}*/
		tail = tail->next;
	}
	//else if (head == tail) // case were there is only 1 node
	//{
	//	tail->next = new QueueItem;
	//	tail->item = value;
	//	head = tail;
	//}
	//else
	//{
	//	tail->next = new QueueItem;
	//	tail->next->Item = value;
	//	tail = tail->next;
	//}
	tail->next = nullptr;
	lock.unlock();
}

template <typename T>
void SharedQueue<T>::Print()
{
	for (QueueItem *p = head; p != tail; p = p->next)
		std::cout << p->item << " ";
	std::cout << std::endl;
}

template <typename T>
bool SharedQueue<T>::Remove(T& item)
{
	lock.lock();
	if (IsEmpty())
	{
		lock.unlock();
		return false;
	}
	item = head->item;
	QueueItem *p = head->next;
	delete head;
	head = p;
	lock.unlock();
	return true;
}

#endif /* defined(__Lab12__SharedQueue__) */
