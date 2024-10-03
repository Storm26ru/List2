#include "List.cpp"


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
	List <std::string> list = { "3", "5", "8", "13", "21" };
	for (std::string i : list)
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

