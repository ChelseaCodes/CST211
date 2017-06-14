/*************************************************************
* Author:		Chelsea Christison
* Filename:		exception.cpp
* Date Created:	4.2.2017
* Modifications:
*	4.4 - Comments
*	4.4 - m_msg now is newed to handle cstrings
* ***********************************************************/
#include "exception.h"

#include <cstring>

//default constructor
Exception::Exception(): m_msg(nullptr) 
{}

//one arg constructor
Exception::Exception(char* msg)
{
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg); 
}

//copy constructor
Exception::Exception(const Exception& copy)
{
	m_msg = new char[strlen(copy.m_msg) + 1];
	strcpy(m_msg, copy.m_msg); 
}

//destructor
Exception::~Exception()
{
	delete[] m_msg; 
	m_msg = nullptr; 
}

//operator ='s
Exception& Exception::operator=(const Exception& copy)
{
	if(this != &copy)
	{
		delete[] m_msg;
		if(copy.m_msg != nullptr)
		{
			m_msg = new char[strlen(copy.m_msg) + 1];
			strcpy(m_msg, copy.m_msg);
		}
		else
			m_msg = nullptr; 
	}
	return *this; 
}

//get message
char* Exception::getMessage() const
{
	return m_msg;
}

//set message
void Exception::setMessage(char* msg)
{
	delete[] m_msg;
	if (msg)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else
		m_msg = nullptr; 	
}

//overloaded operator<< to output Exception message
ostream& operator<<(ostream& stream, const Exception& exept)
{
	return stream << exept.getMessage() << endl;
}
