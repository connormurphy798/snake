## Coding standards

This document details the conventions used in this project.


### Naming conventions

Local variables are named using underscore-separated lowercase words.

Class and struct names use upper camel case.

Fields of classes and structs are specified like local variables with an "f_" prefix.

Functions names are written in lower camel case.

Parameters to functions are specified like local variables with a "p_" prefix.


### Example

Here is an example demonstrating the various conventions:

```
class MyClass {
public:
	MyClass(int p_num);

	void setNum(int p_new_num);

private:
	int		f_num;
};

void MyClass::setNum(int p_new_num) {
	int times_two = 2 * p_new_num;
	f_num = times_two;
}


```
