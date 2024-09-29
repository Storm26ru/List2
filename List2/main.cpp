#include <iostream>
#include<initializer_list>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pPrev;
		Element* pNext;

	public:
		Element(int Data, Element* pPrev=nullptr, Element* pNext = nullptr) : Data(Data), pPrev(pPrev), pNext(pNext) { cout << "EConstructor:\t" << this << endl; }
		~Element() { cout << "EDestructor:\t" << this << endl; }
		friend class List;
	} *Head,*Tail;

	 class Iterator
	{
		Element* ptr;
	public:
		Iterator(Element* ptr) : ptr(ptr) {}
		Iterator operator++()
		{
			ptr = ptr->pNext;
			return *this;
		}
		bool operator !=(const Iterator& other)const { return ptr != other.ptr; }
		const int& operator *()const { return ptr->Data; }
	};

	size_t size;

public:
	//						Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(initializer_list<int>l)
	{
		// (int const* data = l.begin(); data != l.end(); ++data) push_back(*data);
		for (int data : l) push_back(data);
	}
	List(const List& other):List()
	{
		//for (int i : other) push_back(i);
		*this = other;
	}
	~List() { while (Head)pop_front(); cout << "LDestructor:\t" << this << endl; }

	//						Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New; 
			Head = New;
		}
		size++;

	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head->pNext)
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		else { delete Head; Head = Tail = nullptr; }
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Tail->pPrev)
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}	
		else { delete Tail; Head = Tail = nullptr; }
		size--;
	}
	void insert(int Data, int index)
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (index == 0)push_front(Data);
		if (index == size)push_back(Data);
		else
		{
			Element* New = new Element(Data);
			Element* Temp;
			if (index < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < index; i++) Temp = Temp->pNext;
			}
			else
			{
				Temp = Tail;
				for (int i = size; i > index + 1; i--)Temp = Temp->pPrev;
			}
			New->pNext = Temp;
			New->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = New;
			Temp->pPrev = New;
		    size++;
		}
	}
	void erase(int index)
	{
		Element* Temp;
		if (Head == nullptr && Tail == nullptr||index>=size) return;
		if (index == size - 1) { pop_back(); return; }
		if (index == 0)pop_front();
		else
		{
			if (index < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < index; i++) Temp = Temp->pNext;
			}
			else
			{
				Temp = Tail;
				for (int i = size; i > index + 1; i--)Temp = Temp->pPrev;
			}
			Temp->pPrev->pNext = Temp->pNext;
			Temp->pNext->pPrev = Temp->pPrev;
			delete Temp;
			size--;
		}

	}
	//						Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//for (Element* i = other.Head; i; i = i->pNext)push_back(i->Data);
		for (int i : other)push_back(i);
		return *this;
	}
	//						Methods:
	Iterator begin()const { return Iterator(Head); }
	Iterator end()const { return Iterator(nullptr); }
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void revers_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
		
	}
};
	
List  operator + (const List& left, const List& right)
{
	List temp = left;
	for (int i : right)temp.push_back(i);
	return temp;
}

//#define BASE
#define ITERATOR
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE
	int n;
	int data;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	cout << "Введите индекс элемента для вставки: "; cin >> n;
	cout << "Введите значение элемента: "; cin >> data;
	list.insert(data, n);
	list.print();
	cout << "Введите индекс элемента для удаления: "; cin >> n;
	list.erase(n);
	list.print();
#endif // BASE

#ifdef ITERATOR
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list3)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // ITERATOR

	

	
	
	


}

