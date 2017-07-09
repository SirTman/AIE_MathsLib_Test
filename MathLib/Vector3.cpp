#include <Vector3.h>
#include <math.h>
#pragma region Constructors
template<class T>
Vector3<T>::Vector3() : x(0), y(0), z(0) {}

template<class T>
Vector3<T>::Vector3(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z) {}

template<class T>
Vector3<T>::Vector3(const Vector3 & a_rhs) : x(a_rhs.x), y(a_rhs.y), z(a_rhs.z) {}   //Copy/reference constructor

#pragma endregion

#pragma region Base Operators
template<class T>
Vector3<T> Vector3<T>::operator+(const Vector3 & a_rhs) const                     // V2 = V2 + V2 
{
	return Vector3<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z);             //Constructing a template class, have to specify the data-type in <T>
}

template<class T>
Vector3<T> Vector3<T>::operator-(const Vector3 & a_rhs) const					// V2 = V2 - V2 
{
	return Vector3<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z);
}

template<class T>
Vector3<T> & Vector3<T>::operator=(const Vector3 & a_rhs)
{
	x = a_rhs.x, y = a_rhs.y, z = a_rhs.z;
	return *this;                                           //Return de-referenced Vector3 after operations
}

template<class T>
Vector3<T> Vector3<T>::operator*(T a_scalar) const
{
	return Vector3<T>(x * a_scalar, y * a_scalar, z * a_scalar);

}

template<class T>
Vector3<T> Vector3<T>::operator/(T a_scalar) const
{
	return Vector3<T>(x / a_scalar, y / a_scalar, z / a_scalar);

}

template<class T>
Vector3<T> Vector3<T>::operator -() const
{
	return Vector3<T>(-x, -y, -z);                          // Return negative version of vector3
}

template<class T>
//Casts vector to float pointer
Vector3<T>::operator T*()
{
	return &x;											// * Return start of memory address for Vector3
}

template<class T>
T & Vector3<T>::operator[](unsigned int index)
{
	return v[index];                                   // Return specified dimension of Vector
}
#pragma endregion

#pragma region Advanced Operators
template<class T>
Vector3<T> & Vector3<T>::operator+=(const Vector3 & a_rhs)
{
	*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
	return *this;
}

template<class T>
Vector3<T> & Vector3<T>::operator-=(const Vector3 & a_rhs)
{
	*this = *this - a_rhs;
	return *this;
}

template<class T>
Vector3<T> & Vector3<T>::operator*=(T a_scalar)
{
	*this = *this * a_scalar;
	return *this;
}

template<class T>
Vector3<T> & Vector3<T>::operator/=(T a_scalar)
{
	*this = *this / a_scalar;
	return *this;
}
#pragma endregion

#pragma region Conditions
template<class T>
bool Vector3<T>::operator==(const Vector3 & a_rhs) const
{
	if (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z) {              //Also compare translation points, Point != Vector
		return true;
	}
	return false;
}

template<class T>
bool Vector3<T>::operator!=(const Vector3 & a_rhs) const
{
	if (!(*this == a_rhs)) {
		return true;                                        //Yes, the vectors are not equal
	}
	return false;                                           //No, the vectors are equal
}
#pragma endregion

#pragma region Functions
template<class T>
T Vector3<T>::dot(const Vector3 & a_rhs)
{
	return ((x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z));
}

template<class T>
Vector3<T> Vector3<T>::cross(const Vector3& a_rhs) {
	/*
	x   a_x         x | y z x y | z
	y   a_y         x | y z x y | z
	z   a_z
	*/
	return Vector3<T>((y * a_rhs.z - z * a_rhs.y), (z * a_rhs.x - x * a_rhs.z), (x * a_rhs.y - y * a_rhs.x));
}

template<class T>
T Vector3<T>::magnitude()
{
	return T(sqrtf((x * x) + (y * y) + (z * z)));                       //Square root returns a double, typecast to float
}

template<class T>
void Vector3<T>::normalise()
{
	T m = magnitude();                                        //Compute magnitude only once for efficiency
	x /= m, y /= m, z /= m;
}

template<class T>
Vector3<T> Vector3<T>::getNormal()
{
	T m = magnitude();
	return Vector3<T>(x /= m, y /= m, z /= m);                       //Return normalized version of lhs
}
#pragma endregion

///Explicit instantiation required for template classes, allows definitions to be in .cpp

 template class Vector3<int>;
 template class Vector3<short>;
 template class Vector3<double>;
 template class Vector3<float>;
