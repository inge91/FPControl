#ifndef CIRCULAR_ARRAY_H_INCLUDED
#define CIRCULAR_ARRAY_H_INCLUDED
#include <GL/glut.h>
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>

#include <cmath>
#include <fstream>

// TODO: declarate array in array, not before
template <class T>
class CircularArray{
	public:
	CircularArray(){

		// Create the array that will be used in a circular matter
		max = 5;
		iterator = 0;
	}

	void add_element(T element)
	{
		arr[iterator] = element;
		iterator += 1;
		iterator %= max;
	}

	T get_element(int i)
	{
		return arr[i];
	}
	T arr[5];

private:
	int iterator;
	int max;


};

#endif