/*************************************************************
* Author:		Chelsea Christison
* Filename:		exception.h
* Date Created:	4.2.2017
* Modifications:
*	4.7 - Added to 2d Array project
* *****
* Class: Exception
*
* Purpose : This class is a medium used for throwing exceptions
*
* Manager functions :
*	Exception()
*	Exception(char * msg)
*	Exception(const Exception& copy) 
*	~Exception()
*
* Methods:
*	Exception& operator=(const Exception& copy)
*	char * getMessage() const
*		retrieves message
*	void setMessage(char * msg)
*		sets the message
*	friend ostream& operator<<(ostream& stream, const Exception& exept)
*		returns ostream for output
*	
*************************************************************************/
#ifndef exception_H
#define exception_H
#include<iostream>
using std::endl; 

#include<ostream>
using std::ostream; 

class Exception
{
public:
	Exception();
	Exception(char * msg); 
	Exception(const Exception& copy); 
	~Exception();
	Exception& operator=(const Exception& copy); 
	char * getMessage() const;
	void setMessage(char * msg); 
	friend ostream& operator<<(ostream& stream, const Exception& exept); 
private:
	char * m_msg; 
};
#endif
