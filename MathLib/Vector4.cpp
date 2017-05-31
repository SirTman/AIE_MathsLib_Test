#include <Vector4.h>
#include <math.h>

#pragma region Constructors
template<class T>
Vector4<T>::Vector4() : x(0), y(0), z(0), w(0) {}

template<class T>
Vector4<T>::Vector4(T a_x, T a_y, T a_z, T a_w) : x(a_x), y(a_y), z(a_z), w(a_w) {}

template<class T>
Vector4<T>::Vector4(const Vector4 & a_rhs) : x(a_rhs.x), y(a_rhs.y), z(a_rhs.z), w(a_rhs.w) {}   //Copy/reference constructor

#pragma endregion

#pragma region Base Operators
template<class T>
Vector4<T> Vector4<T>::operator+(const Vector4 & a_rhs) const                     // V2 = V2 + V2 
{
	return Vector4<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w);  //Constructing a template class, have to specify the data-type in <T>
}

template<class T>
Vector4<T> Vector4<T>::operator-(const Vector4 & a_rhs) const					// V2 = V2 - V2 
{
	return Vector4<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w);
}

template<class T>
Vector4<T> & Vector4<T>::operator=(const Vector4 & a_rhs)
{
	x = a_rhs.x, y = a_rhs.y, z = a_rhs.z, w = a_rhs.w;
	return *this;                                           //Return de-referenced Vector4 after operations
}

template<class T>
Vector4<T> Vector4<T>::operator*(T a_scalar) const
{
	return Vector4<T>(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);

}

template<class T>
Vector4<T> Vector4<T>::operator/(T a_scalar) const
{
	return Vector4<T>(x / a_scalar, y / a_scalar, z / a_scalar, w / a_scalar);

}

template<class T>
Vector4<T> Vector4<T>::operator -() const
{
	return Vector4<T>(-x, -y, -z, -w);                          // Return negative version of Vector4
}

template<class T>
//Casts vector to float pointer
Vector4<T>::operator T*()
{
	return &x;											// * Return start of memory address for Vector4
}

template<class T>
T & Vector4<T>::operator[](unsigned int index)
{
	return v[index];                                   // Return specified dimension of Vector
}
#pragma endregion

#pragma region Advanced Operators
template<class T>
Vector4<T> & Vector4<T>::operator+=(const Vector4 & a_rhs)
{
	*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
	return *this;
}

template<class T>
Vector4<T> & Vector4<T>::operator-=(const Vector4 & a_rhs)
{
	*this = *this - a_rhs;
	return *this;
}

template<class T>
Vector4<T> & Vector4<T>::operator*=(T a_scalar)
{
	*this = *this * a_scalar;
	return *this;
}

template<class T>
Vector4<T> & Vector4<T>::operator/=(T a_scalar)
{
	*this = *this / a_scalar;
	return *this;
}
#pragma endregion

#pragma region Conditions
template<class T>
bool Vector4<T>::operator==(const Vector4 & a_rhs) const
{
	if (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z && w == a_rhs.w) {              //Also compare translation points, Point != Vector
		return true;
	}
	return false;
}

template<class T>
bool Vector4<T>::operator!=(const Vector4 & a_rhs) const
{
	if (!(*this == a_rhs)) {
		return true;                                        //Yes, the vectors are not equal
	}
	return false;                                           //No, the vectors are equal
}
#pragma endregion

#pragma region Functions
template<class T>
T Vector4<T>::dot(const Vector4 & a_rhs)
{
	return ((x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z));
}

template<class T>
Vector4<T> Vector4<T>::cross(const Vector4& a_rhs) {
	/*
	x   a_x         x | y z x y | z
	y   a_y         x | y z x y | z
	z   a_z
	*/
	return Vector4<T>((y * a_rhs.z - z * a_rhs.y), (z * a_rhs.x - x * a_rhs.z), (x * a_rhs.y - y * a_rhs.x), w * a_rhs.w);
}

template<class T>
T Vector4<T>::magnitude()
{
	return T(sqrtf((x * x) + (y * y) + (z * z)));                       //Square root returns a double, typecast to float
}

template<class T>
void Vector4<T>::normalise()
{
	T m = magnitude();                                        //Compute magnitude only once for efficiency
	x /= m, y /= m, z /= m;
}

template<class T>
Vector4<T> Vector4<T>::getNormal()
{
	T m = magnitude();
	return Vector4<T>(x /= m, y /= m, z /= m, w);                       //Return normalized version of lhs
}
#pragma endregion

///Explicit instantiation required for template classes, allows definitions to be in .cpp

 template class Vector4<int>;
 template class Vector4<short>;
 template class Vector4<double>;
 template class Vector4<float>;
