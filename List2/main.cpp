#include"List.h"
void main()
{
	setlocale(LC_ALL, "");
	/*int n;
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
	List <int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;*/
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (auto i : list3)
	{
		cout << i << tab;
	}
	cout << endl;
	

	
	
	


}
/*https://www.cyberforum.ru/cpp-beginners/thread2382930.html
#include <iostream>
 
using namespace std;
 
struct ListItem {
    ListItem *next;
    int val;
    ListItem() : next(nullptr), val(0) {}
    ListItem(int v) : next(nullptr), val(v) {}
};
 
class ListIterator {
    ListItem *ptr;
public:
    ListIterator(ListItem *pel) : ptr(pel) {}
    ListIterator operator ++() {
        ListItem *tmp = ptr;
        ptr = ptr->next;
        return ListIterator(tmp);
    }
    bool operator != (const ListIterator& li) const {
        return ptr != li.ptr;
    }
    ListItem operator *() const {
        return *ptr;
    }
};
 
class List {
    ListItem *head;
public:
    List() : head(nullptr) {}
    List(initializer_list<int> lst) : head(nullptr) {
        for (auto el = lst.begin(); el != lst.end(); ++el)
            add(*el);
    }
    void add(int el) {
        ListItem *li = new ListItem(el);
        li->next = head;
        head = li;
    }
    ListIterator begin() const {
        return ListIterator(head);
    }
    ListIterator end() const {
        return ListIterator(nullptr);
    }
};
 
int main() {
    int a[] = { 1, 2, 3, 4, 5 };
    for (auto el : a)
        cout << el << ' ';
    cout << endl;
 
    List b = { 1, 2, 3, 4, 5 };
    for (const auto &el : b)
        cout << el.val << ' ';
    cout << endl;
}*/

