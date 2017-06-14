/************************************************************************
* Class: baseiterator.h
*
* Purpose: This abstract base class defines a base iterator to be used
*		for deriving other iterators.
*
* Manager functions:
* 	AbstractIterator()
*		default cursor is nullptr
*	AbstractIterator(L * data)
*		sets cursor to beginning of data 
*	~AbstractIterator()
*
* Methods:
*	virtual void Reset() = 0
*		initialize cursor to first element in data
*	virtual void MoveNext() = 0
*		traverse to next element
*	virtual bool IsDone() = 0
*		true when past last element
*	virtual Node * GetCurrent() = 0
*		pointer to current node
*
*************************************************************************/
#ifndef abstractiterator_h
#define abstractiterator_h

template<typename T>
class AbstractIterator
{
public:
	AbstractIterator();					//no arg c'tor 
	virtual ~AbstractIterator();		//virtual d'tor

protected:
	virtual void Reset() = 0;			//initialize cursor to first element in CityList
	virtual void MoveNext() = 0;		//traverse to next element
	virtual bool IsDone() = 0;			//true when past last element
	virtual T * GetCurrent() = 0;		//ptr to current node 
};

template <typename T>
AbstractIterator<T>::AbstractIterator()
{}

template <typename T>
AbstractIterator<T>::~AbstractIterator()
{}
#endif 
