#pragma once
#include "Uncopyable.h"


template <typename T>


class Singleton : Uncopyable {


public:

	static T* Instance(){ // static member function = is a func that can be called without an istance of a class


		static T t;
		return &t;


	}


};