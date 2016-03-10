#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>

template <typename KeyType>
unsigned int computeHash(KeyType); // prototype function for computeHash

//unsigned int computeHash(const unsigned short& someKey); 
//unsigned int computeHash(const std::string& someKey);

template <typename KeyType, typename ValueType>
class HashTable
{
public:
	HashTable(unsigned int numBuckets, unsigned int capacity);
	~HashTable();
	bool isFull()	const;
	bool set(const KeyType&	key, const ValueType& value, bool permanent = false);
	bool get(const KeyType& key, ValueType& value)	const;
	bool touch(const KeyType& key);
	bool discard(KeyType& key, ValueType& value);

private:
	struct Node
	{
		Node(KeyType keyData, ValueType valueData, bool permanent, Node* lessRecent = nullptr, Node* moreRecent = nullptr, Node* nextInBucket = nullptr)
			: n_keyData(keyData), n_valueData(valueData), n_permanent(permanent), n_lessRecent(lessRecent), n_moreRecent(moreRecent), n_nextInBucket(nextInBucket) {}
		KeyType n_keyData;
		ValueType n_valueData;
		bool n_permanent;
		Node* n_lessRecent;
		Node* n_moreRecent;
		Node* n_nextInBucket;
	};

	Node** m_array;
	Node* m_mostRecent;
	Node* m_leastRecent;
	int m_numBuckets;
	int m_maxCapacity;
	int m_count;

	unsigned int getBucketNumber(const KeyType& someKey) const
	{
		unsigned int computeHash(KeyType);
		return computeHash(someKey) % m_numBuckets;
	}

	HashTable(const HashTable&);
	HashTable& operator=(const HashTable&);
};

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int numBuckets, unsigned int capacity)
{
	m_numBuckets = numBuckets;
	m_maxCapacity = capacity;
	m_count = 0;
	m_mostRecent = nullptr;
	m_leastRecent = nullptr;
	m_array = new Node*[numBuckets];

	for (int i = 0; i < m_numBuckets; i++) // initializes each pointer in every bucket as a null pointer
		m_array[i] = nullptr;	
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
	for (int i = 0; i < m_numBuckets; i++)
	{
		while (m_array[i] != nullptr) // deletes every node in a bucket if there are any
		{
			Node* temp = m_array[i];
			m_array[i] = m_array[i]->n_nextInBucket;
			delete temp;
		}
	}
	delete[] m_array; 
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::isFull() const
{
	if (m_count < m_maxCapacity)
		return false;
	else
		return true;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::set(const KeyType&	key, const ValueType& value, bool permanent = false)
{
	if (isFull())
		return false;

	unsigned int bucketNumber = getBucketNumber(key);
	Node* currentNode = m_array[bucketNumber];

	ValueType someValue;
	if (get(key, someValue) == true)
	{
		while (currentNode->n_keyData != key)
		{
			currentNode = currentNode->n_nextInBucket;
		}
		currentNode->n_valueData = value;
		touch(currentNode->n_keyData);
	}
	else
	{
		if (currentNode == nullptr)
		{
			if (!permanent)
			{
				m_array[bucketNumber] = new Node(key, value, false, m_mostRecent);

				if (m_mostRecent == nullptr)
					m_mostRecent = m_array[bucketNumber];
				else
				{
					m_mostRecent->n_moreRecent = m_array[bucketNumber];
					m_mostRecent = m_array[bucketNumber];
				}

				if (m_leastRecent == nullptr)
					m_leastRecent = m_array[bucketNumber];
			}
			else
			{
				m_array[bucketNumber] = new Node(key, value, true);
			}
			return true;
		}
		else
		{
			while (currentNode->n_nextInBucket != nullptr)
			{
				currentNode = currentNode->n_nextInBucket;
			}
			if (!permanent)
			{
				currentNode->n_nextInBucket = new Node(key, value, false, m_mostRecent);				

				if (m_mostRecent == nullptr)
					m_mostRecent = currentNode->n_nextInBucket;
				else
				{
					m_mostRecent->n_moreRecent = currentNode->n_nextInBucket;
					m_mostRecent = currentNode->n_nextInBucket;
				}
				
				if (m_leastRecent == nullptr)
					m_leastRecent = currentNode->n_nextInBucket;
			}
			else
			{
				currentNode->n_nextInBucket = new Node(key, value, true);
			}
		}
	}
	return true;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::get(const KeyType& key, ValueType& value)	const
{
	unsigned int bucketNumber = getBucketNumber(key);
	Node* currentNode = m_array[bucketNumber];
	
	if (currentNode == nullptr)
		return false;

	while (currentNode->n_keyData != key)
	{
		currentNode = currentNode->n_nextInBucket;
		if (currentNode == nullptr)
			return false;
	}
	
	value = currentNode->n_valueData;
	return true;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::touch(const KeyType& key)
{
	unsigned int bucketNumber = getBucketNumber(key);
	Node* currentNode = m_array[bucketNumber];

	if (currentNode == nullptr)
		return false;

	while (currentNode->n_keyData != key)
	{
		currentNode = currentNode->n_nextInBucket;
		if (currentNode == nullptr)
			return false;
	}

	if (currentNode->n_permanent)
		return false;
	else
	{
		if (currentNode->n_lessRecent != nullptr)  //|| currentNode->n_moreRecent != nullptr)
			currentNode->n_lessRecent->n_moreRecent = currentNode->n_moreRecent;
		if (currentNode->n_moreRecent != nullptr)  //|| currentNode->n_lessRecent != nullptr)
			currentNode->n_moreRecent->n_lessRecent = currentNode->n_lessRecent;

		if (currentNode == m_leastRecent)
			m_leastRecent = currentNode->n_moreRecent;

		currentNode->n_lessRecent = m_mostRecent;

		m_mostRecent->n_moreRecent = currentNode;
		currentNode->n_moreRecent = nullptr;
		m_mostRecent = currentNode;
		return true;
	}
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::discard(KeyType& key, ValueType& value)
{
	if (m_leastRecent == nullptr)
		return false;

	key = m_leastRecent->n_keyData;
	value = m_leastRecent->n_valueData;

	Node* temp = m_leastRecent;
	m_leastRecent = m_leastRecent->n_moreRecent;
	if (m_leastRecent != nullptr)
		m_leastRecent->n_lessRecent = nullptr;

	unsigned int bucketNumber = getBucketNumber(key);
	Node* currentNode = m_array[bucketNumber];

	if (currentNode->n_keyData == key)
	{
		m_array[bucketNumber] = currentNode->n_nextInBucket;
	}
	else
	{
		while (currentNode->n_nextInBucket->n_keyData != key)
		{
			currentNode = currentNode->n_nextInBucket;
		}
		currentNode->n_nextInBucket = currentNode->n_nextInBucket->n_nextInBucket;
	}

	delete temp;
	return true;
}

#endif