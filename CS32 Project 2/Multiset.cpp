#include "Multiset.h"

Multiset::Multiset()
{
	head = nullptr;
	tail = nullptr;
}

Multiset::Multiset(const Multiset &old)
{
	head = nullptr;
	tail = nullptr;

	Node* p = old.head;
	while (p != nullptr)
	{
		for (int x = 0; x < p->count; x++)
			insert(p->value);
		p = p->next;
	}
}

Multiset& Multiset::operator=(const Multiset& old) 
{
	if (this != &old)
	{
		Node* p = head;
		Node* m = head;
		while (p != nullptr) 
		{
			m = p;
			p = p->next;
			delete m; // deleting the contents of the Multiset
		}

		head = nullptr;
		tail = nullptr;

		Node* r = old.head;
		while (r != nullptr) 
		{
			for (int x = 0; x < r->count; x++)
				insert(r->value);
			r = r->next; // assigning values from the old Multiset to the current Multiset
		}
	}
	return *this;
}

Multiset::~Multiset()
{
	Node* p = head;
	Node* m = head;
	while (p != nullptr)
	{
		m = p;
		p = p->next;
		delete m;
	}
	head = nullptr;
	tail = nullptr;
}

bool Multiset::empty() const
{
	if (head == nullptr)
		return true;
	return false;
}

int Multiset::size() const
{
	int total = 0;
	Node* p = head;
	while (p != nullptr)
	{
		total += p->count;
		p = p->next;
	}
	return total;
}

int Multiset::uniqueSize() const
{
	int counter = 0;
	Node* p = head;
	while (p != nullptr)
	{
		counter++;
		p = p->next;
	}
	return counter;
}

bool Multiset::insert(const ItemType& value)  
{
	if (head == nullptr) // these statements are executed only if the Multiset is empty
	{
		Node* x = new Node;
		head = x;
		head->value = value;
		head->count = 1;
		head->next = nullptr;
		head->prev = nullptr;
		tail = head;
		return true;
	}

	Node* p = head;

	if (p->value == value)
	{
		p->count++;
		return true;
	}

	while (p->next != nullptr)
	{
		if (p->next->value == value) // this condition ensures that duplicate entries increment the count in an existing node (and are not allocated a seperate node)
		{
			p->next->count++;
			return true;
		}
		p = p->next;
	}

	// These statements can be accessed only if the Multiset is not empty and the value in the parameter is not a duplicate
	Node* y = new Node;
	p->next = y;
	y->value = value;
	y->count = 1;
	y->next = nullptr;
	y->prev = p;
	tail = y;
	return true;
}


int Multiset::erase(const ItemType& value) 
{
	if (empty()) // does nothing if Multiset is already empty
		return 0;

	if (head->value == value) // if a value from the first node needs be erased
	{
		if (head->count > 1)
			head->count -= 1;
		else
		{
			Node* q = head;
			head = head->next;
			if (head != nullptr)
				head->prev = nullptr;
			delete q;
		}
		return 1;
	}

	if (tail->value == value) // if a value from the last node needs be erased
	{
		if (tail->count > 1)
			tail->count -= 1;
		else
		{
			Node* t = tail;
			tail = tail->prev;
			if (tail != nullptr)
				tail->next = nullptr;
			delete t;
		}
		return 1;
	}

	// If a value from any other node needs to be erased

	Node* p = head;
	bool found = false;
	while (p->next != nullptr)
	{
		if (p->next->value == value)
		{
			found = true;
			break;
		}
		p = p->next;
	}

	if (found == false) // returns 0 if value passed as the parameter is not found in the list
		return 0;

	if (p->next->count > 1)
		p->next->count -= 1;
	else
	{
		Node* r = p->next->next;
		delete p->next;
		p->next = r;
		r->prev = p;
	}
	return 1;
}

int Multiset::eraseAll(const ItemType& value) 
{
	if (empty()) // does nothing if Multiset is already empty
		return 0;

	if (head->value == value) // if the first node needs be erased
	{
		int counter = head->count;
		Node* q = head;
		head = head->next;
		if (head != nullptr)
			head->prev = nullptr;
		delete q;

		return counter;
	}

	if (tail->value == value) // if the last node needs be erased
	{
		int counter = tail->count;
		Node* t = tail;
		tail = tail->prev;
		if (tail != nullptr)
			tail->next = nullptr;
		delete t;

		return counter;
	}

	// If any other node needs to be erased

	Node* p = head;
	bool found = false;
	while (p->next != nullptr)
	{
		if (p->next->value == value)
		{
			found = true;
			break;
		}
		p = p->next;
	}

	if (found == false) // returns 0 if value passed as the parameter is not found in the list
		return 0;

	int counter = p->next->count;
	Node* r = p->next->next;
	delete p->next;
	p->next = r;
	r->prev = p;
	return counter;
}

bool Multiset::contains(const ItemType& value) const
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->value == value)
			return true;
		p = p->next;
	}
	return false;
}

int Multiset::count(const ItemType& value) const
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->value == value)
			return p->count;
		p = p->next;
	}
	return 0;
}

int Multiset::get(int i, ItemType& value) const 
{
	int counter = 0;
	Node* p = head;
	while (p != nullptr)
	{
		if (i == counter)
		{
			value = p->value;
			return p->count;
		}
		p = p->next;
		counter++;
	}
	return 0;
}

void Multiset::swap(Multiset& other)
{
	Multiset temp(other);
	other = *this;
	*this = temp;
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result) 
{
	ItemType value;
	int count;

	Multiset temp; // the temp Multiset will collect values from ms1 and ms2 and pass it to the result Multiset

	for (int i = 0; ms1.get(i, value) != 0; i++)
	{
		count = ms1.get(i, value);
		for (int x = 0; x < count; x++)
			temp.insert(value);
	}

	for (int j = 0; ms2.get(j, value) != 0; j++)
	{
		count = ms2.get(j, value);
		for (int y = 0; y < count; y++)
			temp.insert(value);
	}

	result = temp; // result will have the same contents as temp even if result formerly had other data in it
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	ItemType value1, value2;
	int count1, count2, difference;
	bool occursInBoth = false;

	Multiset temp;

	for (int i = 0; ms1.get(i, value1) != 0; i++)
	{
		occursInBoth = false;
		count1 = ms1.get(i, value1);
		for (int j = 0; ms2.get(j, value2) != 0; j++)
		{
			count2 = ms2.get(j, value2);
			if (value1 == value2) // these statements are executed only if a match has been found in ms1 and ms2
			{
				occursInBoth = true;
				difference = count1 - count2;
				if (difference < 0) difference = 0;
				for (int a = 0; a < difference; a++)
					temp.insert(value1);
			}
		}
		if (!occursInBoth) // this condition is only satisfied if a value in ms1 was not found in ms2
		{
			for (int x = 0; x < count1; x++)
				temp.insert(value1);
		}
	}

	result = temp;
}


/*for (int j = 0; ms2.get(j, value2) != 0; j++)
{
occursInBoth = false;
count2 = ms2.get(j, value2);
for (int i = 0; ms1.get(i, value1) != 0; i++)
{
count1 = ms1.get(i, value1);
if (value2 == value1) occursInBoth = true;
}
if (!occursInBoth)
{
for (int y = 0; y < count2; y++)
temp.insert(value2);
}
}*/
