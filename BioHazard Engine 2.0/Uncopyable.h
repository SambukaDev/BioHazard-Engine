#pragma once


class Uncopyable {


protected:


	Uncopyable(){}


	Uncopyable(const Uncopyable&); // prevent the user for coping an Object

	Uncopyable& operator = (const Uncopyable&); // prevent the user to assign an object to another.



};