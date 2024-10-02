#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pPrev;
		Element* pNext;

	public:
		Element(T Data, Element* pPrev=nullptr, Element* pNext = nullptr) : Data(Data), pPrev(pPrev), pNext(pNext) { cout << "EConstructor:\t" << this << endl; }
		~Element() { cout << "EDestructor:\t" << this << endl; }
		friend class List;
	} *Head,*Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) : Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator!=(const ConstBaseIterator& other) { return Temp != other.Temp; }
		bool operator==(const ConstBaseIterator& other) { return Temp == other.Temp; }
		T operator*()const { return Temp->Data; }

	};
public:
	 class ConstIterator: public ConstBaseIterator
	{
		
	public:
		ConstIterator(Element* Temp) : ConstBaseIterator(Temp) { cout << "CITConstructor: " << this << endl; }
		~ConstIterator() {}

		ConstIterator& operator++() 
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	 class ConstReverseIterator : public ConstBaseIterator
	 {

	 public:
		 ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp) { cout << "CRITConstructor: " << this << endl; }
		 ~ConstReverseIterator() {}

		 ConstReverseIterator& operator++()
		 {
			 Temp = Temp->pPrev;
			 return *this;
		 }
		 ConstReverseIterator operator++(int)
		 {
			 ConstReverseIterator old = *this;
			 Temp = Temp->pPrev;
			 return old;
		 }
		 ConstReverseIterator& operator--()
		 {
			 Temp = Temp->pNext;
			 return *this;
		 }
		 ConstReverseIterator operator--(int)
		 {
			 ConstReverseIterator old = *this;
			 Temp = Temp->pNext;
			 return old;
		 }
	 };
	 class Iterator:public ConstIterator
	 {
	 public:
		 Iterator(Element*Temp):ConstIterator(Temp){}
		 ~Iterator(){}
		 T& operator*() { return Temp->Data; }
	 };
	 class ReverseIterator :public ConstReverseIterator
	 {
	 public:
		 ReverseIterator(Element*Temp):ConstReverseIterator(Temp){}
		 ~ReverseIterator(){}
		 T& operator*() { return Temp->Data; }
	 };

	//						Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>l)
	{
		//for(int const* data = l.begin(); data != l.end(); ++data) push_back(*data);
		for (T data : l) push_back(data);
	}
	List(const List& other):List()
	{
		//for (int i : other) push_back(i);
		*this = other;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);
	}
	~List() { while (Head)pop_front(); cout << "LDestructor:\t" << this << endl; }

	//						Adding elements:
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Head = Head->pPrev = new Element(Data,nullptr,Head);
		}
		size++;

	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Tail = Tail->pNext = new Element(Data,Tail);
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
	void insert(T Data, int index)
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
		for (T i : other)push_back(i);
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "LMoveAssigment:\t" << this << endl;

	}
	//						Methods:
	ConstIterator begin()const { return Head; }
	ConstIterator end()const { return nullptr; }
	Iterator begin(){ return Head; }
	Iterator end(){ return nullptr; }
	ConstReverseIterator rbegin()const { return Tail; }
	ConstReverseIterator rend()const { return nullptr; }
	ReverseIterator rbegin(){ return Tail; }
	ReverseIterator rend(){return nullptr; }
	

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
		
	}
};
	
template <typename T>List<T>  operator + (const List<T>& left, const List<T>& right)
{
	List temp = left;
	for (T i : right)temp.push_back(i);
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
	List <int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list3)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // ITERATOR

	

	
	
	


}

