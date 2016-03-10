#include "Multiset.h"
#include <string>

//const int DEFAULT_MAX_ITEMS = 200;

Multiset::Multiset()
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
		m_array[i].count = 0;
}

bool Multiset::empty() const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].count == 0)
			continue;
		else
			return false;
	}
	return true;
}

int Multiset::size() const
{
	int total = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		total = total + m_array[i].count;
	}
	return total;
}
// Return the number of items in the multiset.  For example, the size
// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.

int Multiset::uniqueSize() const
{
	int counter = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].count != 0)			
			counter++;
	}
	return counter;
}
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.

bool Multiset::insert(const ItemType& value)
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (value == m_array[i].value)
		{
			m_array[i].count++;
			return true;
		}
	}
	for (int j = 0; j < DEFAULT_MAX_ITEMS; j++)
	{
		if (m_array[j].count == 0)
		{
			m_array[j].value = value;
			m_array[j].count++;
			return true;
		}
	}
	return false;
}
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).

int Multiset::erase(const ItemType& value)
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (value == m_array[i].value && m_array[i].count != 0)
		{
			m_array[i].count--;
			return 1;
		}
	}
	return 0;
}
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.

int Multiset::eraseAll(const ItemType& value)
{
	int temp = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (value == m_array[i].value && m_array[i].count != 0)
		{
			temp = m_array[i].count;
			m_array[i].count = 0;
			return temp;
		}
	}
	return temp;
}
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.

bool Multiset::contains(const ItemType& value) const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (value == m_array[i].value && m_array[i].count != 0)
		{
			return true;
		}
	}
	return false;
}
// Return true if the value is in the multiset, otherwise false.

int Multiset::count(const ItemType& value) const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (value == m_array[i].value && m_array[i].count != 0)
		{
			return m_array[i].count;
		}
	}
	return 0;
}
// Return the number of instances of value in the multiset.

int Multiset::get(int i, ItemType& value) const
{
	if (i < 0 || i >= uniqueSize())
		return 0;

	int counter = 0;
	for (int x = 0; x < DEFAULT_MAX_ITEMS; x++)
	{
		if (m_array[x].count != 0)
			counter++;
		if (i == counter - 1)
		{
			value = m_array[x].value;
			return m_array[x].count;
		}
	}
	return 0;
}
// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)

void Multiset::swap(Multiset& other)
{
	MultiData temp;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		temp.value = this->m_array[i].value;
		temp.count = this->m_array[i].count;
		this->m_array[i].value = other.m_array[i].value;
		this->m_array[i].count = other.m_array[i].count;
		other.m_array[i].value = temp.value;
		other.m_array[i].count = temp.count;
	}
}
// Exchange the contents of this multiset with the other one. 