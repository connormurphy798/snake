## Coding standards

This document details the conventions used in this project.


### Naming conventions

Local variables and function parameters are named using underscore-separated lowercase words.

Class and struct names use upper camel case.

Fields of classes and structs are specified like local variables with an "f_" prefix.

Functions names are written in lower camel case.


### Example

Here is an example demonstrating the various conventions:

```
// MyClass.h
class MyClass {
public:
	MyClass(int num);

	void setNum(int new_num);

private:
	int		f_num;
};

// MyClass.cpp
void MyClass::setNum(int new_num) {
	int times_two = 2 * new_num;
	f_num = times_two;
}

```
