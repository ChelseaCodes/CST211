/*************************************************************
* Author:		Chelsea Christison
* Filename:		hashtable.h
* Date Created:	6.9.2017
*
**************************************************************/
#ifndef hashtable_H
#define hashtable_H
#include<list>
using std::list; 
#include <vector>
using std::vector;

#include "hashnode.h"


template <typename K, typename  V>
class HashTable
{
public:
	typedef int(*Hash)(K);
	HashTable();
	HashTable(Hash hashfunction, int size); 
	HashTable(const HashTable<K, V> & cpy);
	HashTable<K, V>& operator=(const HashTable<K, V>& rhs);
	~HashTable();

	void Insert(K key, V value);
	void setHash(Hash hashfunction); //store fctn ptr in data mem
	V operator[](K key);
	void Delete(K key);
	void Traverse(void(*visit)(V));

private:
	Hash m_hash;
	vector<list<HashNode<K, V>>> m_hash_table;
};

template <typename K, typename V>
HashTable<K, V>::HashTable(): m_hash(nullptr), m_hash_table(1)
{}

template <typename K, typename V>
HashTable<K, V>::HashTable(Hash hashfunction, int size): m_hash(hashfunction), m_hash_table(size)
{}

template <typename K, typename V>
HashTable<K, V>::HashTable(const HashTable<K, V>& cpy):  m_hash(cpy.m_hash), m_hash_table(cpy.m_hash_table)
{}

template <typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& rhs)
{
	if(this != &rhs)
	{
		m_hash_table = rhs.m_hash_table; 
		m_hash = rhs.m_hash; 
	}
	return *this; 
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{}

/************************************************************************
* Purpose:
*	This function inserts a node into the hash table using the key and 
*	value passed
* Pre-Conditions:
*	key - key used to be hashed
*	value - value to store into the node 
*************************************************************************/
template <typename K, typename V>
void HashTable<K, V>::Insert(K key, V value)
{
	HashNode<K, V> nn(key, value); 

	int hash = m_hash(key); 

	m_hash_table[hash].push_front(nn); 
}

/************************************************************************
* Purpose:
*	This function sets the hash function to the hash function passed
* Pre-Conditions:
*	hashfunction - pointer to the hash function
*************************************************************************/
template <typename K, typename V>
void HashTable<K, V>::setHash(Hash hashfunction)
{
	vector<list<HashNode<K, V>>> newTable(m_hash_table.size()); 

	for (list<HashNode<K, V>> L : m_hash_table)
	{
		for (HashNode<K, V> N : L)
		{
			HashNode<K, V> nn = N; 

			int hash = hashfunction(N.getKey()); 

			newTable[hash].push_front(nn);
		}
	}
	m_hash_table = newTable; 
	m_hash = hashfunction;
}

/************************************************************************
* Purpose:
*	This function overrides the bracket operator given the key passed, 
*	and returns the data
* Pre-Conditions:
*	key - key to find in the hash table to return 
* Mods: 
*	Changed to use the hash function to find obj. to delete. 
*************************************************************************/
template <typename K, typename V>
V HashTable<K, V>::operator[](K key)
{
	V value; 

	for(HashNode<K,V> N : m_hash_table[m_hash(key)])
	{
		if (N.getKey() == key)
		{
			value = N.getValue();
			break;
		}				
	}

	return value; 
}

/************************************************************************
* Purpose:
*	This function deletes a node from the table if its found.
* Pre-Conditions:
*	key - key used to delete from the table
*	
* Mods: 
*	Changed to use the hash function to find obj. to delete. 
*************************************************************************/
template <typename K, typename V>
void HashTable<K, V>::Delete(K key)
{
	int i = m_hash(key); 
	
	for (HashNode<K, V> N : m_hash_table[i])
	{
		if (N.getKey() == key)
		{
			m_hash_table[i].remove(N); 
			break; 
		}
	}
}

/************************************************************************
* Purpose:
*	This function traverses the entire hash table 
* Pre-Conditions:
*	visit -	function ptr to the output function 
*************************************************************************/
template <typename K, typename V>
void HashTable<K, V>::Traverse(void(* visit)(V))
{
	for (list<HashNode<K, V>> L : m_hash_table)
	{
		for (HashNode<K, V> N : L)
		{
			visit(N.getValue());
		}
	}
}
#endif
