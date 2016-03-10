#ifndef MULTISET_H

#define MULTISET_H

#include <string>
typedef  std::string ItemType;

class Multiset
{
public:
	Multiset();
	Multiset(const Multiset &old);	
	Multiset& operator=(const Multiset& old);
	~Multiset();
	bool empty() const;
	int size() const;
	int uniqueSize() const;
	bool insert(const ItemType& value);
	int erase(const ItemType& value);
	int eraseAll(const ItemType& value);
	bool contains(const ItemType& value) const;
	int count(const ItemType& value) const;
	int get(int i, ItemType& value) const;
	void swap(Multiset& other);

private:
	struct Node
	{
		ItemType value;
		int count;
		Node* prev;
		Node* next;
	};
	Node* head;
	Node* tail;
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif
