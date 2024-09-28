#include"List.h"
void main()
{
	setlocale(LC_ALL, "");
	
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (auto i : list3)
	{
		cout << i << tab;
	}
	cout << endl;
}


