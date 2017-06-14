/*************************************************************
* Author:		Chelsea Christison
* Filename:		hashnode.h
* Date Created:	6.9.2017
*
**************************************************************/
#ifndef hashnode_H
#define hashnode_H

template<typename K, typename V>
class HashNode
{
public:
	HashNode(); 
	HashNode(K key, V value); 
	HashNode(const HashNode<K, V>& cpy); 
	HashNode& operator=(const HashNode<K, V>& rhs); 
	~HashNode(); 
	
	bool operator==(const HashNode<K, V>& rhs); 

	K getKey() const; 
	V getValue() const; 

private:
	K m_key; 
	V m_value; 
};

template <typename K, typename V>
HashNode<K, V>::HashNode()
{}

template <typename K, typename V>
HashNode<K, V>::HashNode(K key, V value) : m_key(key), m_value(value)
{}

template <typename K, typename V>
HashNode<K, V>::HashNode(const HashNode<K, V>& cpy) : m_key(cpy.m_key), m_value(cpy.m_value)
{}

template <typename K, typename V>
HashNode<K, V>& HashNode<K, V>::operator=(const HashNode<K, V>& rhs)
{
	if(this != &rhs)
	{
		m_key = rhs.m_key; 
		m_value = rhs.m_value; 
	}
	return *this; 
}

template <typename K, typename V>
HashNode<K, V>::~HashNode()
{}

template <typename K, typename V>
bool HashNode<K, V>::operator==(const HashNode<K, V>& rhs)
{
	return this->m_key == rhs.m_key; 
}

template <typename K, typename V>
K HashNode<K, V>::getKey() const
{
	return m_key; 
}

template <typename K, typename V>
V HashNode<K, V>::getValue() const
{
	return m_value; 
}
#endif
