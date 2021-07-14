#pragma once

#include "Vector3.hpp"
#include "Vector4.hpp"

#include "../../Dependencies/include/glm/ext/matrix_transform.hpp"
#include "../../Dependencies/include/glm/glm.hpp"
#include "../../Dependencies/include/glm/ext.hpp"

#include <string>

namespace BF
{
#define XAxisX 0
#define XAxisY 4
#define XAxisZ 8
#define XAxisW 12

#define YAxisX 1
#define YAxisY 5
#define YAxisZ 9
#define YAxisW 13

#define ZAxisX 2
#define ZAxisY 6
#define ZAxisZ 10
#define ZAxisW 14

#define TransformX 3
#define TransformY 7 
#define TransformZ 11
#define TransformW 15

	template<class NumberType>	
	struct Matrix4x4
	{
		public:
		/*
		XA YA ZA Or
		 0  1  2  3
		 4  5  6  7
		 8  9 10 11
		12 13 14 15
		*/
		NumberType Data[16];


		Matrix4x4()
		{
			Data[0] = 1;
			Data[5] = 1;
			Data[10] = 1;
			Data[15] = 1;
		}

		Matrix4x4<NumberType> operator*(Matrix4x4<NumberType> matrixB)
		{
			Matrix4x4<NumberType> resultMatrix;

			NumberType& a = this->Data[0];
			NumberType& b = this->Data[1];
			NumberType& c = this->Data[2];
			NumberType& d = this->Data[3];
			NumberType& e = this->Data[4];
			NumberType& f = this->Data[5];
			NumberType& g = this->Data[6];
			NumberType& h = this->Data[7];
			NumberType& i = this->Data[8];
			NumberType& j = this->Data[9];
			NumberType& k = this->Data[10];
			NumberType& l = this->Data[11];
			NumberType& m = this->Data[12];
			NumberType& n = this->Data[13];
			NumberType& o = this->Data[14];
			NumberType& p = this->Data[15];

			NumberType& A = matrixB.Data[0];
			NumberType& B = matrixB.Data[1];
			NumberType& C = matrixB.Data[2];
			NumberType& D = matrixB.Data[3];
			NumberType& E = matrixB.Data[4];
			NumberType& F = matrixB.Data[5];
			NumberType& G = matrixB.Data[6];
			NumberType& H = matrixB.Data[7];
			NumberType& I = matrixB.Data[8];
			NumberType& J = matrixB.Data[9];
			NumberType& K = matrixB.Data[10];
			NumberType& L = matrixB.Data[11];
			NumberType& M = matrixB.Data[12];
			NumberType& N = matrixB.Data[13];
			NumberType& O = matrixB.Data[14];
			NumberType& P = matrixB.Data[15];

			NumberType& resultA = resultMatrix.Data[0];
			NumberType& resultB = resultMatrix.Data[1];
			NumberType& resultC = resultMatrix.Data[2];
			NumberType& resultD = resultMatrix.Data[3];
			NumberType& resultE = resultMatrix.Data[4];
			NumberType& resultF = resultMatrix.Data[5];
			NumberType& resultG = resultMatrix.Data[6];
			NumberType& resultH = resultMatrix.Data[7];
			NumberType& resultI = resultMatrix.Data[8];
			NumberType& resultJ = resultMatrix.Data[9];
			NumberType& resultK = resultMatrix.Data[10];
			NumberType& resultL = resultMatrix.Data[11];
			NumberType& resultM = resultMatrix.Data[12];
			NumberType& resultN = resultMatrix.Data[13];
			NumberType& resultO = resultMatrix.Data[14];
			NumberType& resultP = resultMatrix.Data[15];
		
			resultA = a * A + b * E + c * I + d * M;
			resultB = e * A + f * E + g * I + h * M;
			resultC = i * A + j * E + k * I + l * M;
			resultD = m * A + n * E + o * I + p * M;

			resultE = a * B + b * F + c * J + d * N;
			resultF = e * B + f * F + g * J + h * N;
			resultG = i * B + j * F + k * J + l * N;
			resultH = m * B + n * F + o * J + p * N;

			resultI = a * C + b * G + c * K + d * O;
			resultJ = e * C + f * G + g * K + h * O;
			resultK = i * C + j * G + k * K + l * O;
			resultL = m * C + n * G + o * K + p * O;

			resultM = a * D + b * H + c * L + d * P;
			resultN = e * D + f * H + g * L + h * P;
			resultO = i * D + j * H + k * L + l * P;
			resultP = m * D + n * H + o * L + p * P;

			return resultMatrix;
		}

		void operator=(Matrix4x4<NumberType> matrix4x4)
		{
			memcmp(this->Data, matrix4x4.Data, 16 * sizeof(NumberType));
		}

		void Move(NumberType x, NumberType y, NumberType z)
		{
			this->Data[12] += x;
			this->Data[13] += y;
			this->Data[14] += z;
		}
		void Move(Vector3<NumberType> vector3)
		{
			this->Data[12] += vector3.Data[0];
			this->Data[13] += vector3.Data[1];
			this->Data[14] += vector3.Data[2];
		}
		void MoveTo(NumberType x, NumberType y, NumberType z)
		{
			this->Data[12] = x;
			this->Data[13] = y;
			this->Data[14] = z;
		}
		void Rotate(NumberType x, NumberType y, NumberType z)
		{

		}
		void RotateTo(NumberType x, NumberType y, NumberType z)
		{

		}
		void Orbit(NumberType x, NumberType y, NumberType z)
		{

		}

		void LookAt(NumberType x, NumberType y, NumberType z)
		{

		}

		void LookAt(Vector3<NumberType> eye, Vector3<NumberType> center, Vector3<NumberType> up)
		{
			glm::vec3 eyeEE(eye.Data[0], eye.Data[1], eye.Data[2]);
			glm::vec3 centerEE(center.Data[0], center.Data[1], center.Data[2]);
			glm::vec3 upEE(up.Data[0], up.Data[1], up.Data[2]);

			 glm::mat4 view = glm::lookAt(eyeEE, centerEE, upEE);

			 Set(view);
		}

		// Flip matrix diagonally
		void Transpose()
		{
			//NumberType a = this->Data[0];
			NumberType b = this->Data[1];
			NumberType c = this->Data[2];
			NumberType d = this->Data[3];

			NumberType e = this->Data[4];
			//NumberType f = this->Data[5];
			NumberType g = this->Data[6];
			NumberType h = this->Data[7];

			NumberType i = this->Data[8];
			NumberType j = this->Data[9];
			//NumberType k = this->Data[10];
			NumberType l = this->Data[11];

			NumberType m = this->Data[12];
			NumberType n = this->Data[13];
			NumberType o = this->Data[14];
			//NumberType p = this->Data[15];

			//this->Data[0] = a;
			this->Data[1] = e;
			this->Data[2] = i;
			this->Data[3] = m;

			this->Data[4] = b;
			//this->Data[5] = f;
			this->Data[6] = j;
			this->Data[7] = n;

			this->Data[8] = c;
			this->Data[9] = g;
			//this->Data[10] = k;
			this->Data[11] = o;

			this->Data[12] = d;
			this->Data[13] = h;
			this->Data[14] = l;
			//this->Data[15] = p;
		}

		void Inverse()
		{
			glm::mat4 matrixA = glm::mat4();

			memcpy(&matrixA[0][0], this->Data, 16 * sizeof(NumberType));
		
			glm::mat4 matrixB = glm::inverse(matrixA);

			Set(matrixB);
		}

		void Set(NumberType value)
		{
			memset(this->Data, value, 16 * sizeof(NumberType));
		} 

		void Set(glm::mat4 matrix)
		{
			Set(0);

			memcpy(this->Data, &matrix[0][0], 16 * sizeof(NumberType));

			/*
			return;

			this->Data[0] = matrix[0][0];
			this->Data[1] = matrix[1][0];
			this->Data[2] = matrix[2][0];
			this->Data[3] = matrix[3][0];
			this->Data[4] = matrix[0][1];
			this->Data[5] = matrix[1][1];
			this->Data[6] = matrix[2][1];
			this->Data[7] = matrix[3][1];
			this->Data[8] = matrix[0][2];
			this->Data[9] = matrix[1][2];
			this->Data[10] = matrix[2][2];
			this->Data[11] = matrix[3][2];
			this->Data[12] = matrix[0][3];
			this->Data[13] = matrix[1][3];
			this->Data[14] = matrix[2][3];
			this->Data[15] = matrix[3][3];

			printf("\n\n\n%2.2c %2.2c %2.2c 2.2c\n", this->Data[0], this->Data[1], this->Data[2], this->Data[3]);
			printf("%2.2c %2.2c %2.2c 2.2c\n", this->Data[4], this->Data[5], this->Data[6], this->Data[7]);
			printf("%2.2c %2.2c %2.2c 2.2c\n", this->Data[8], this->Data[9], this->Data[10], this->Data[11]);
			printf("%2.2c %2.2c %2.2c 2.2c\n\n", this->Data[12], this->Data[13], this->Data[14], this->Data[15]);*/

			//this->Transpose();


		}

		void Orthographic(NumberType left, NumberType rigth, NumberType bottom, NumberType top, NumberType near, NumberType far)
		{
			glm::mat4 matrix = glm::ortho(left, rigth, bottom, top, near, far);

			Set(matrix);
		}

		void Perspective(NumberType fielfOfView, NumberType aspectRatio, NumberType near, NumberType far)
		{
			glm::mat4 matrix = glm::perspective(glm::radians(fielfOfView), aspectRatio, near, far);

			Set(matrix);
		}

		Vector4<NumberType> CurrentPosition()
		{
			return Vector4<NumberType>(Data[TransformX], Data[TransformY], Data[TransformZ], Data[TransformW]);
		}
		Vector4<NumberType> CurrentRotation()
		{
			return Vector4<NumberType>(Data[0], Data[5], Data[10]);
		}
		Vector4<NumberType> CurrentScaling()
		{
			return Vector4<NumberType>(Data[0], Data[5], Data[10]);
		}

		void Print()
		{
			printf("\n\n%2.2f %2.2f %2.2f %2.2f\n", this->Data[0], this->Data[1], this->Data[2], this->Data[3]);
			printf("%2.2f %2.2f %2.2f %2.2f\n", this->Data[4], this->Data[5], this->Data[6], this->Data[7]);
			printf("%2.2f %2.2f %2.2f %2.2f\n", this->Data[8], this->Data[9], this->Data[10], this->Data[11]);
			printf("%2.2f %2.2f %2.2f %2.2f\n\n", this->Data[12], this->Data[13], this->Data[14], this->Data[15]);
		}


		Vector4<NumberType> CurrentAxisX()
		{
			return Vector4<NumberType>(Data[XAxisX], Data[XAxisY], Data[XAxisZ], Data[XAxisW]);
		}
		Vector4<NumberType> CurrentAxisY()
		{
			return Vector4<NumberType>(Data[YAxisX], Data[YAxisY], Data[YAxisZ], Data[YAxisW]);
		}
		Vector4<NumberType> CurrentAxisZ()
		{
			return Vector4<NumberType>(Data[ZAxisX], Data[ZAxisY], Data[ZAxisZ], Data[ZAxisW]);
		}
	};
}