#include "Matrix3.h"
#include <math.h>
///Constructors
template<class T>
Matrix3<T>::Matrix3() : m11(1), m12(0), m13(0),                                                         //Identity matrix by default
m21(0), m22(1), m23(0),
m31(0), m32(0), m33(1) {}

template<class T>
Matrix3<T>::Matrix3(Matrix3 &a_rhs) : m11(a_rhs.m11), m12(a_rhs.m12), m13(a_rhs.m13),                 //Copy constructor, copy information from Matrix into the other
m21(a_rhs.m21), m22(a_rhs.m22), m23(a_rhs.m23),
m31(a_rhs.m31), m32(a_rhs.m32), m33(a_rhs.m33) {}

template<class T>
Matrix3<T>::Matrix3(T *a_ptr) : m11(a_ptr[0]), m12(a_ptr[1]), m13(a_ptr[2]),                 //Construct from list of type T
m21(a_ptr[3]), m22(a_ptr[4]), m23(a_ptr[5]),
m31(a_ptr[6]), m32(a_ptr[7]), m33(a_ptr[8]) {}

template<class T>
Matrix3<T>::Matrix3(T a_m11, T a_m12, T a_m13,
	T a_m21, T a_m22, T a_m23,
	T a_m31, T a_m32, T a_m33) : m11(a_m11), m12(a_m12), m13(a_m13),
								 m21(a_m21), m22(a_m22), m23(a_m23),
								 m31(a_m31), m32(a_m32), m33(a_m33) {}

#pragma region Base Operators
template<class T>
Matrix3<T> Matrix3<T>::operator * (const Matrix3 &a_rhs) const {
	/*
	[m11, m12, m13]      *     [a_m11, a_m12, a_m13]
	[m21, m22, m23]            [a_m21, a_m22, a_m23]
	[m31, m32, m33]			   [a_m31, a_m32, a_m33]
	*/
	Matrix3<T> tmp;
	//Do the matrix multiplication process in a for-loop for readability
	for (auto r = 0; r < 3; r++) {
		for (auto c = 0; c < 3; c++) {
			tmp.mm[r][c] = (mm[0][c] * a_rhs.mm[r][0] +                    //For each position, find the value for the equivalent position and it to the new Matrix
				mm[1][c] * a_rhs.mm[r][1] +
				mm[2][c] * a_rhs.mm[r][2]);
		}
	}
	return tmp;
}

template<class T>
Vector3<T> Matrix3<T>::operator * (const Vector3<T> &a_rhs) const {                      //Because we're not in the Vector3 template class, we need to specify what type it is in all uses.
	/*
	[m11, m12, m13]      *     [x,         =   [c_m11]
	[m21, m22, m23]             y,             [c_m21]
	[m31, m32, m33]			    z]			   [c_m31]
	*/
	return Vector3<T>(
		(m11 * a_rhs.x + m21 * a_rhs.y + m31 * a_rhs.z),
		 (m12 * a_rhs.x + m22 * a_rhs.y + m32 * a_rhs.z), 
		 (m13 * a_rhs.x + m23 * a_rhs.y + m33 * a_rhs.z));
}

template<class T>
Matrix3<T> Matrix3<T>::operator = (const Matrix3 &a_rhs) {
	m11 = a_rhs.m11, m12 = a_rhs.m12, m13 = a_rhs.m13,
	m21 = a_rhs.m21, m22 = a_rhs.m22, m23 = a_rhs.m23,
	m31 = a_rhs.m31, m32 = a_rhs.m32, m33 = a_rhs.m33;
	return *this;
}
#pragma endregion
//Operators that rely on base operators
#pragma region Advanced Operators
template<class T>
Matrix3<T>& Matrix3<T>::operator *=(const Matrix3 &a_rhs) {
	*this = *this * a_rhs;
	return *this;
}
#pragma endregion

#pragma region Functions
///Created out of the lhs
template<class T>
Matrix3<T> Matrix3<T>::createIdentity() {                                      //Return default matrix
	return Matrix3<T>(1, 0, 0,
		0, 1, 0,
		0, 0, 1);
}

template<class T>
Matrix3<T> Matrix3<T>::createRotationX(float a_rot) {                          //Return rotated Matrix3
	Matrix3<T> tmp;
	//Express via indexes for readability, we only change the relevant default values (rows x columns) 
	//Do not touch axis or values for what we're rotating with. (X and x in this case)
	tmp.mm[1][1] = (T)cosf(a_rot);    //Yy
	tmp.mm[2][1] = -(T)sinf(a_rot);    //Yz
	tmp.mm[1][2] = (T)sinf(a_rot);   //Zy
	tmp.mm[2][2] = (T)cosf(a_rot);    //Zz
	return tmp;
}

template<class T>
Matrix3<T> Matrix3<T>::createRotationY(float a_rot) {                          //Return rotated Matrix3
	Matrix3<T> tmp;
	tmp.mm[0][0] = (T)cosf(a_rot);   //Xx
	tmp.mm[2][0] = (T)sinf(a_rot);   //Xz
	tmp.mm[0][2] = -(T)sinf(a_rot);  //Zx
	tmp.mm[2][2] = (T)cosf(a_rot);   //Zz
	return tmp;
}

template<class T>
Matrix3<T> Matrix3<T>::createRotationZ(float a_rot) {                          //Return rotated Matrix3
	Matrix3<T> tmp;
	tmp.mm[0][0] = (T)cosf(a_rot);   //Xx
	tmp.mm[1][0] = -(T)sinf(a_rot);  //Xy
	tmp.mm[0][1] = (T)sinf(a_rot);   //Yx
	tmp.mm[1][1] = (T)cosf(a_rot);   //Yy
	return tmp;
}

template<class T>
Matrix3<T> Matrix3<T>::createScale(T a_xScale, T a_yScale, T a_zScale) {           //Return scaled Matrix3
	Matrix3<T> tmp;
	tmp.mm[0][0] = a_xScale;          //Xx
	tmp.mm[1][1] = a_yScale;		  //Yy
	tmp.mm[2][2] = a_zScale;	      //Zz
	return tmp;
}
///Setters
template<class T>
void Matrix3<T>::set(T a_m11, T a_m12, T a_m13,          // Rebuild the matrix with parameters
	T a_m21, T a_m22, T a_m23,
	T a_m31, T a_m32, T a_m33) 							// rebuild the matrix
{
	m11 = a_m11, m12 = a_m12, m13 = a_m13;
	m21 = a_m21, m22 = a_m22, m23 = a_m23;
	m31 = a_m31, m32 = a_m32, m33 = a_m33;
}

template<class T>
void Matrix3<T>::set(T *a_ptr)                                        	// rebuild the matrix - expects pointer to array of 4 floats
{
	//Assign values with for loop for readability
	auto index = 0;
	for (auto r = 0; r < 3; r++) {
		for (auto c = 0; c < 3; c++) {
			mm[r][c] = a_ptr[index];
			index++;
		}
	}
}

template<class T>
void Matrix3<T>::setRotateX(float a_rot)                                 // Rotate Matrix3 on the z axis circle
{
	//Express via indexes for readability, we only change the relevant values. 
	//Do not touch axis or values for what we're rotating with. (X and x in this case)
	mm[1][1] = (T)cosf(a_rot);    //Yy
	mm[2][1] = -(T)sinf(a_rot);    //Yz
	mm[1][2] = (T)sinf(a_rot);   //Zy
	mm[2][2] = (T)cosf(a_rot);    //Zz
}

template<class T>
void Matrix3<T>::setRotateY(float a_rot)                                 // Rotate Matrix3 on the z axis circle
{
	mm[0][0] = (T)cosf(a_rot);   //Xx
	mm[2][0] = (T)sinf(a_rot);   //Xz
	mm[0][2] = -(T)sinf(a_rot);  //Zx
	mm[2][2] = (T)cosf(a_rot);   //Zz
}

template<class T>
void Matrix3<T>::setRotateZ(float a_rot)                                 // Rotate Matrix3 on the z axis circle
{
	mm[0][0] = (T)cosf(a_rot);   //Xx
	mm[1][0] = -(T)sinf(a_rot);  //Xy
	mm[0][1] = (T)sinf(a_rot);   //Yx
	mm[1][1] = (T)cosf(a_rot);   //Yy
}

template<class T>
void Matrix3<T>::setScale(T a_scaleX, T a_scaleY, T a_scaleZ)                 // Scale matrix by given values
{
	mm[0][0] = a_scaleX; //Xx
	mm[1][1] = a_scaleY; //Yy
	mm[2][2] = a_scaleZ; //Zz
}

template<class T>
Vector3<T> Matrix3<T>::getTranslation() {
	return Vector3<T>{mm[0][2], mm[1][2], mm[2][2]};         //Matrix3 can double as a 2D Matrix with translation capabilities, return translation axis
}

template<class T>
T Matrix3<T>::getRotation(char a_axis) {
	switch (a_axis)
	{
		// ONLY WORKS IF NOT SKEWED (FORMS A RIGHT ANGLED TRIANGLE)
	case 'Z':                                       //atan2 = takes 2 arguments
		return -(T)atan2((double)mm[1][1], (double)mm[0][1]);            //Get the angle between the Y global axis and the local Y axis tan(adj/opp = Yy/Yx). Negative = counter-clockwise
	}
	return -(T)atan2(double(mm[1][1]), double(mm[0][1]));
}
#pragma endregion
//Casts matrix to float pointer
template<class T>
Matrix3<T>::operator T* () { return m; }                   //Return start of matrix memory address

template<class T>
Vector3<T> & Matrix3<T>::operator [] (unsigned int index) { return v[index]; } //Return vector at specified index

 template class Matrix3<int>;
 template class Matrix3<short>;
 template class Matrix3<double>;
 template class Matrix3<float>;

