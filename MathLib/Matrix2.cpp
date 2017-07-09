#include "Matrix2.h"
#include <math.h>
///Constructors
template<class T>
Matrix2<T>::Matrix2() : m11(1), m12(0),                                      //Identity by default
m21(0), m22(1) {}

template<class T>
Matrix2<T>::Matrix2(Matrix2 &a_rhs) : m11(a_rhs.m11), m12(a_rhs.m12),
m21(a_rhs.m21), m22(a_rhs.m22) {}                   //Copy constructor, copy information from Matrix into the other

template<class T>
Matrix2<T>::Matrix2(T *a_ptr) : m11(a_ptr[0]), m12(a_ptr[1]),                          //Construct from list of type T
m21(a_ptr[2]), m22(a_ptr[3]) {}

template<class T>
Matrix2<T>::Matrix2(T a_m11, T a_m12, T a_m21, T a_m22) : m11(a_m11), m12(a_m12),
m21(a_m21), m22(a_m22) {}

#pragma region Base Operators
template<class T>
Matrix2<T> Matrix2<T>::operator * (const Matrix2 &a_rhs) const {
	/*
	[m11, m12]      *     [a_m11, a_m12]
	[m21, m22]            [a_m21, a_m22]
	*/
	return Matrix2<T>((m11 * a_rhs.m11 + m12 * a_rhs.m21), (m11 * a_rhs.m12 + m12 * a_rhs.m22),
		(m21 * a_rhs.m11 + m22 * a_rhs.m21), (m21 * a_rhs.m12 + m22 * a_rhs.m22));
}

template<class T>
Vector2<T> Matrix2<T>::operator * (const Vector2<T> &a_rhs) const {                      /*Because we're not in the Vector2 template class, we need to specify what type it is in all uses.
																			 DO NOT #define because it'll inherit everywhere*/
	/*
	[m11, m12]      *     [x,         =   [c_m11]
	[m21, m22]             y]             [c_m21]
	*/
	return Vector2<T>((m11 * a_rhs.x + m21 * a_rhs.y),                     //NOTE: When multiplying a matrice with a vector, it has to be treated cxr instead of rxc because the vector is
		(m12 * a_rhs.x + m22 * a_rhs.y));					   //technically a row vector, even though we're still getting the rows from the lhs and the columns from the rhs.
}

template<class T>
Matrix2<T> Matrix2<T>::operator = (const Matrix2 &a_rhs) {
	m11 = a_rhs.m11, m12 = a_rhs.m12;
	m21 = a_rhs.m21, m22 = a_rhs.m22;
	return *this;
}
#pragma endregion
//Operators that rely on base operators
#pragma region Advanced Operators
template<class T>
Matrix2<T>& Matrix2<T>::operator *=(const Matrix2 &a_rhs) {
	*this = *this * a_rhs;
	return *this;
}
#pragma endregion

#pragma region Functions
///Created out of the lhs
template<class T>
Matrix2<T> Matrix2<T>::createIdentity() {                                      //Return default matrix
	return Matrix2<T>(1, 0,
					  0, 1);
}

template<class T>
Matrix2<T> Matrix2<T>::createRotationZ(float a_rot) {                          //Return Matrix2 for rotating around Z axis
	return Matrix2<T>((T)cosf(a_rot), (T)sinf(a_rot),
					 -(T)sinf(a_rot), (T)cosf(a_rot));
}

template<class T>
Matrix2<T> Matrix2<T>::createScale(T a_xScale, T a_yScale) {           //Return Matrix2 for scaling
	return Matrix2<T>(a_xScale, 0,
					  0, a_yScale);
}
///Setters
template<class T>
void Matrix2<T>::set(T a_m11, T a_m12, T a_m21, T a_m22)   	// rebuild the matrix
{
	m11 = a_m11, m12 = a_m12;
	m21 = a_m21, m22 = a_m22;
}

template<class T>
void Matrix2<T>::set(T *a_ptr)                                        	// rebuild the matrix - expects pointer to array of 4 floats
{
	//Assign values with for loop for readability
	auto index = 0;
	for (auto r = 0; r < 2; r++) {
		for (auto c = 0; c < 2; c++) {
			mm[r][c] = a_ptr[index];
			index++;
		}
	}
}

template<class T>
void Matrix2<T>::setRotate(float a_rot)                                 // Rotate Matrix2 on the z axis circle
{
	m11 = (T)cosf(a_rot), m12 = (T)sinf(a_rot);
	m21 = -(T)sinf(a_rot), m22 = (T)cosf(a_rot);
}

template<class T>
void Matrix2<T>::setScale(T a_scaleX, T a_scaleY)                 // Scale matrix by given values
{
	mm[0][0] = a_scaleX; //Xx
	mm[1][1] = a_scaleY; //Yy
}
#pragma endregion
//Casts matrix to float pointer
template<class T>
Matrix2<T>::operator T* () { return m; }                   //Return start of matrix memory address

template<class T>
Vector2<T> & Matrix2<T>::operator [] (unsigned int index) { return v[index]; } //Return vector at specified index

 template class Matrix2<int>;
 template class Matrix2<short>;
 template class Matrix2<double>;
 template class Matrix2<float>;