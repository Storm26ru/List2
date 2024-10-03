#include "List.h"

//											ConstBaseItertor:
		template<typename T>bool List<T> ::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const { return Temp != other.Temp; }
		template<typename T>bool List<T> ::ConstBaseIterator::operator==(const ConstBaseIterator& other)const { return Temp == other.Temp; }
		template<typename T> T List<T>::ConstBaseIterator:: operator*()const { return Temp->Data; }

//											ConstIterator:
		template<typename T> List<T>::ConstIterator:: ConstIterator(Element* Temp) : ConstBaseIterator(Temp) { cout << "CITConstructor: " << this << endl; }
		template<typename T> List<T>::ConstIterator::~ConstIterator() { cout << "CITDestructor: " << this << endl; }
		template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
//											ConstReverseIterator:
		template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator (Element* Temp) : ConstBaseIterator(Temp) { cout << "CRITConstructor: " << this << endl; }
		template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator() { cout << "CRITDestructor: " << this << endl; }
		template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
//											Iterator:
		template<typename T> T& List<T>::Iterator::operator*() { return ConstBaseIterator::Temp->Data; }
		template<typename T> T& List<T>::ReverseIterator::operator*() { return ConstBaseIterator::Temp->Data; }

	//						               Constructors:
	template<typename T> List<T>:: List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	template<typename T> List<T>::List(const std::initializer_list<T>& l)
	{
		//for(int const* data = l.begin(); data != l.end(); ++data) push_back(*data);
		for (T data : l) push_back(data);
	}
	template<typename T> List<T>::List(const List<T>& other) :List()
	{
		//for (int i : other) push_back(i);
		*this = other;
	}
	template<typename T>List<T>::List(List<T>&& other) :List()
	{
		*this = std::move(other);
	}
	template<typename T>List<T>:: ~List() { while (Head)pop_front(); cout << "LDestructor:\t" << this << endl; }

	//						Adding elements:
	template<typename T> void List<T>:: push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Head = Head->pPrev = new Element(Data, nullptr, Head);
		}
		size++;
	}
	template<typename T> void List<T>:: push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Tail = Tail->pNext = new Element(Data, Tail);
		}
		size++;
	}
	template<typename T> void List<T>::pop_front()
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
	template<typename T> void List<T>::pop_back()
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
	template<typename T> void List<T>::insert(T Data, int index)
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
	template<typename T> void List<T>::erase(int index)
	{
		Element* Temp;
		if (Head == nullptr && Tail == nullptr || index >= size) return;
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
	//								Operators:
	template<typename T> typename List<T>& List<T>::operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//for (Element* i = other.Head; i; i = i->pNext)push_back(i->Data);
		for (T i : other)push_back(i);
		return *this;
	}
	template<typename T> typename List<T>& List<T>::operator=(List<T>&& other)
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
	template<typename T> typename List<T>::ConstIterator List<T>::begin()const { return Head; }
	template<typename T> typename List<T>::ConstIterator List<T>::end()const { return nullptr; }
	template<typename T> typename List<T>::Iterator List<T>::begin() { return Head; }
	template<typename T> typename List<T>::Iterator List<T>::end() { return nullptr; }
	template<typename T> typename List<T>::ConstReverseIterator List<T>::rbegin()const { return Tail; }
	template<typename T> typename List<T>::ConstReverseIterator List<T>::rend()const { return nullptr; }
	template<typename T> typename List<T>::ReverseIterator List<T>::rbegin() { return Tail; }
	template<typename T> typename List<T>::ReverseIterator List<T>::rend() { return nullptr; }
	template<typename T> void List<T>::print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	template<typename T> void List<T>::reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;

	}

template <typename T>List<T>  operator + (const List<T>& left, const List<T>& right)
{
	List<T> temp = left;
	for (T i : right)temp.push_back(i);
	return temp;
}

