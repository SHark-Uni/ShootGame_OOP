#pragma once

#include <initializer_list>
#include <cassert>

namespace ShootingGame
{
	template <typename T>
	class LinkedList
	{
	public:
		struct Node
		{
			T data;
			Node* next;
			Node* prev;
		};

		class iterator
		{
			friend class LinkedList;
		public:
			iterator(Node* node = nullptr)
				:mNode(node)
			{

			}
			iterator(const iterator& other)
				:mNode(other.mNode)
			{

			}

			iterator& operator=(const iterator& rhs)
			{
				if (this == &rhs)
				{
					return *this;
				}
				mNode = rhs.mNode;
				return *this;
			}

			inline iterator operator++(int)
			{
				iterator tmp(mNode);
				mNode = mNode->next;
				return tmp;
			}
			inline iterator& operator++()
			{
				mNode = mNode->next;
				return *this;
			}

			inline iterator operator --(int)
			{
				iterator tmp(mNode);
				mNode = mNode->prev;
				return tmp;
			}

			inline iterator& operator--()
			{
				mNode = mNode->prev;
				return *this;
			}

			T& operator*() const 
			{
				assert(mNode != nullptr);
				return mNode->data;
			}
			bool operator ==(const iterator& other)
			{
				return (mNode == other.mNode);
			}
			bool operator !=(const iterator& other)
			{
				return (mNode != other.mNode);
			}
		private:
			Node* mNode;
		};
	public:
		LinkedList();
		LinkedList(std::initializer_list<T> list);
	/*	LinkedList(std::initializer_list<T> list)
		{

		}*/
		~LinkedList();
		LinkedList(const LinkedList& other);
		LinkedList(LinkedList&& other) noexcept;


		LinkedList& operator=(const LinkedList& rhs);
		iterator begin()
		{
			return iterator(mHead.next);
		}
		iterator end()
		{
			return iterator(&mTail);
		}

		inline void push_front(const T& data);
		inline void push_back(const T& data);
		inline T peek_front();
		inline T peek_back();
		inline void pop_front();
		inline void pop_back();
		inline void clear();
		inline int size()  { return mSize; }
		inline bool empty() { return (mSize == 0); }
		
		inline iterator erase(iterator iter);
		inline void remove(T Data);


	private:
		int mSize;
		Node mHead;
		Node mTail;
	};

	//생성 시, 더미헤드 생성, 더미 테일 생성
	template <typename T>
	LinkedList<T>::LinkedList()
		:mSize(0)
	{
		mHead.next = &mTail;
		mHead.prev = nullptr;

		mTail.prev = &mHead;
		mTail.next = nullptr;
	}

	template <typename T>
	LinkedList<T>::~LinkedList()
	{
		Node* cursor = mHead.next;

		while (cursor != &mTail)
		{
			Node* tmp = cursor;
			cursor = cursor->next;
			delete tmp;
		}
	}

	template <typename T>
	LinkedList<T>::LinkedList(std::initializer_list<T> list)
		:mSize(0)
	{
		mHead.next = &mTail;
		mHead.prev = nullptr;

		mTail.prev = &mHead;
		mTail.next = nullptr;

		for (const T& data : list)
		{
			push_back(data);
		}
	}

	//deep Copy
	template <typename T>
	LinkedList<T>::LinkedList(const LinkedList<T>& other)
		:mSize(0)
	{
		mHead.next = &mTail;
		mHead.prev = nullptr;

		mTail.prev = &mHead;
		mTail.next = nullptr;
		Node* curNode = other.mHead.next;

		while (curNode != &other.mTail)
		{
			push_back(curNode->data);
			curNode = curNode->next;
		}
	}

	template <typename T>
	LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
		:mSize(other.mSize)
	{
		mHead = other.mHead;
		mTail = other.mTail;

		// other에서 연결된 첫번째와 마지막 노드의 prev와 next를 고쳐줘야함. 
		// 임시개체의 mHead와 mTail의 주소를 그대로 들고 있게됨.
		other.mHead->prev = &mHead;
		other.mTail->next = &mTail;
	}

	template <typename T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
	{
		if (&rhs == *this)
		{
			return *this;
		}
		//쓰던 LinkedList에 대입할 때, 메모리 누수일어날 수 있음.
		Node* curNode = mHead->next;
		while (curNode != &mTail)
		{
			Node* tmp = curNode;
			curNode = curNode->next;
			delete tmp;
		}
		//복사
		mSize = 0;
		curNode = rhs.mHead.next;
		while (curNode != &rhs.mTail)
		{
			push_back(curNode->data);
		}

		return *this;
	}
	
	template <typename T>
	void LinkedList<T>::push_front(const T& data)
	{
		Node* curNode = new Node;
		assert(curNode != nullptr);

		curNode->data = data;
		curNode->next = mHead.next;
		curNode->prev = &mHead;
		
		(mHead.next)->prev = curNode;
		mHead.next = curNode;

		++mSize;
	}

	template <typename T>
	void LinkedList<T>::push_back(const T& data)
	{
		Node* curNode = new Node;
		assert(curNode != nullptr);

		curNode->data = data;
		curNode->next = &mTail;
		curNode->prev = mTail.prev;

		(mTail.prev)->next = curNode;
		mTail.prev = curNode;

		++mSize;
	}
	//노드 삭제
	template <typename T>
	void LinkedList<T>::pop_front()
	{
		//삭제할 대상 mHead->next
		Node* deleteNode = mHead.next;
		Node* nextNode = deleteNode->next;

		mHead.next = nextNode;
		//아무런 원소가 없는데 pop_front를 하는건 뻑나는 행동.
		static_assert(nextNode != nullptr,"you try to delete,there are no elements.");
		nextNode->prev = &mHead;

		free(deleteNode);
		--mSize;
	}

	template <typename T>
	void LinkedList<T>::pop_back()
	{
		Node* deleteNode = mTail.prev;
		Node* prevNode = deleteNode->prev;

		mTail.prev = prevNode;
		static_assert(prevNode != nullptr,"you try to delete,there are no elements.");
		prevNode->next = &mTail;
		
		free(deleteNode);
		--mSize;
	}

	template <typename T>
	T LinkedList<T>::peek_front()
	{
		return (mHead.next)->data;
	}
	template <typename T>
	T LinkedList<T>::peek_back()
	{
		return ((mTail.prev)->data);
	}
	
	template <typename T>
	void LinkedList<T>::clear()
	{
		// 연결 리스트를 모두 해제 시킨다.

		Node* curNode = mHead.next;

		while (curNode != &mTail)
		{
			Node* tmp = curNode;
			curNode = curNode->next;
			delete tmp;
		}
	}

	template <typename T>
	typename LinkedList<T>::iterator LinkedList<T>::erase(iterator iter)
	{
		Node* curNode = iter.mNode;
		Node* prevNode = curNode->prev;
		Node* nextNode = curNode->next;

		nextNode->prev = prevNode;
		prevNode->next = nextNode;

		++iter;
		delete curNode;

		return iter;
	}

	template <typename T>
	void LinkedList<T>::remove(T Data)
	{
		Node* curNode = mHead.next;

		while (curNode != &mTail)
		{
			if (curNode->data == Data)
			{
				Node* prevNode = curNode->prev;
				Node* nextNode = curNode->next;

				nextNode->prev = prevNode;
				prevNode->next = nextNode;
				free(curNode);
				return;
			}
			curNode = curNode->next;
		}
	}
}