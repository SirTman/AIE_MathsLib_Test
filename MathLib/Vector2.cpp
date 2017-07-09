#pragma once
#include <Vector2.h>
#include <math.h>
#pragma region Constructors
template<class T>
 Vector2<T>::Vector2() : x(0), y(0) {}

template<class T>
 Vector2<T>::Vector2(T a_x, T a_y) : x(a_x), y(a_y) {}

template<class T>
 Vector2<T>::Vector2(const Vector2 & a_rhs) : x(a_rhs.x), y(a_rhs.y) {}   //Copy/reference constructor

#pragma endregion

#pragma region Base Operators
template<class T>
 Vector2<T> Vector2<T>::operator+(const Vector2 & a_rhs) const                     // V2 = V2 + V2 
{
	return Vector2<T>(x + a_rhs.x, y + a_rhs.y);             //Constructing a template class, have to specify the data-type in <T>
}

template<class T>
 Vector2<T> Vector2<T>::operator-(const Vector2 & a_rhs) const					// V2 = V2 - V2 
{
	return Vector2<T>(x - a_rhs.x, y - a_rhs.y);
}

template<class T>
 Vector2<T> & Vector2<T>::operator=(const Vector2 & a_rhs)
{
	x = a_rhs.x, y = a_rhs.y;
	return *this;                                           //Return de-referenced Vector2 after operations
}

template<class T>
 Vector2<T> Vector2<T>::operator*(T a_scalar) const
{
	return Vector2<T>(x * a_scalar, y * a_scalar);

}

template<class T>
 Vector2<T> Vector2<T>::operator/(T a_scalar) const
{
	return Vector2<T>(x / a_scalar, y / a_scalar);

}

template<class T>
 Vector2<T> Vector2<T>::operator -() const
{
	return Vector2<T>(-x, -y);                          // Return negative version of Vector2
}

template<class T>
//Casts vector to float pointer
 Vector2<T>::operator T*()
{
	return &x;											// * Return start of memory address for Vector2
}

template<class T>
 T & Vector2<T>::operator[](unsigned int index)
{
	return v[index];                                   // Return specified dimension of Vector
}
#pragma endregion

#pragma region Advanced Operators
template<class T>
 Vector2<T> & Vector2<T>::operator+=(const Vector2 & a_rhs)
{
	*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
	return *this;
}

template<class T>
 Vector2<T> & Vector2<T>::operator-=(const Vector2 & a_rhs)
{
	*this = *this - a_rhs;
	return *this;
}

template<class T>
 Vector2<T> & Vector2<T>::operator*=(T a_scalar)
{
	*this = *this * a_scalar;
	return *this;
}

template<class T>
 Vector2<T> & Vector2<T>::operator/=(T a_scalar)
{
	*this = *this / a_scalar;
	return *this;
}
#pragma endregion

#pragma region Conditions
template<class T>
 bool Vector2<T>::operator==(const Vector2 & a_rhs) const
{
	if (x == a_rhs.x && y == a_rhs.y) {             
		return true;
	}
	return false;
}

template<class T>
 bool Vector2<T>::operator!=(const Vector2 & a_rhs) const
{
	if (!(*this == a_rhs)) {
		return true;                                        //Yes, the vectors are not equal
	}
	return false;                                           //No, the vectors are equal
}
#pragma endregion

#pragma region Functions
template<class T>
 T Vector2<T>::dot(const Vector2 & a_rhs)
{
	return ((x * a_rhs.x) + (y * a_rhs.y));
}

template<class T>
 T Vector2<T>::magnitude()
{
	return T(sqrtf((x * x) + (y * y)));                       //Square root returns a double, typecast to float
}

template<class T>
 void Vector2<T>::normalise()
{
	T m = magnitude();                                        //Compute magnitude only once for efficiency
	x /= m, y /= m;
}

template<class T>
 Vector2<T> Vector2<T>::getNormal()
{
	T m = magnitude();
	return Vector2<T>(x /= m, y /= m);                       //Return normalized version of lhs
}
#pragma endregion

///Explicit instantiation required for template classes, allows definitions to be in .cpp

 template class Vector2<int>;
 template class Vector2<short>;
 template class Vector2<double>;
 template class Vector2<float>;
