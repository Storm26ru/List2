#include <iostream>
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
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
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
	void insert(int index)
	{


	}


	//						Methods:
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

void main()
{
	setlocale(LC_ALL, "");
	int n;
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
	
	
	


}

