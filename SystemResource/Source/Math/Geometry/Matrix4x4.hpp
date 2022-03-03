#pragma once

#include "Vector3.hpp"
#include "Vector4.hpp"

#include "AngleRadians.hpp"

#include <cstring>

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

#define WAxisX 3
#define WAxisY 7
#define WAxisZ 11
#define WAxisW 15

#define ScaleX 0
#define ScaleY 5
#define ScaleZ 10
#define ScaleW 15

#define TransformX 12
#define TransformY 13 
#define TransformZ 14
#define TransformW 15

namespace BF
{
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
		NumberType MatrixData[16];


		Matrix4x4()
		{
			Reset();
		}

		void Reset()
		{
			MatrixData[XAxisX] = 1;
			MatrixData[YAxisX] = 0;
			MatrixData[ZAxisX] = 0;
			MatrixData[WAxisX] = 0;

			MatrixData[XAxisY] = 0;
			MatrixData[YAxisY] = 1;
			MatrixData[ZAxisY] = 0;
			MatrixData[WAxisY] = 0;

			MatrixData[XAxisZ] = 0;
			MatrixData[YAxisZ] = 0;
			MatrixData[ZAxisZ] = 1;
			MatrixData[WAxisZ] = 0;

			MatrixData[XAxisW] = 0;
			MatrixData[YAxisW] = 0;
			MatrixData[ZAxisW] = 0;
			MatrixData[WAxisW] = 1;
		}

		void Multiply(const Matrix4x4<NumberType>& matrixB)
		{
			NumberType a = this->MatrixData[0];
			NumberType b = this->MatrixData[1];
			NumberType c = this->MatrixData[2];
			NumberType d = this->MatrixData[3];
			NumberType e = this->MatrixData[4];
			NumberType f = this->MatrixData[5];
			NumberType g = this->MatrixData[6];
			NumberType h = this->MatrixData[7];
			NumberType i = this->MatrixData[8];
			NumberType j = this->MatrixData[9];
			NumberType k = this->MatrixData[10];
			NumberType l = this->MatrixData[11];
			NumberType m = this->MatrixData[12];
			NumberType n = this->MatrixData[13];
			NumberType o = this->MatrixData[14];
			NumberType p = this->MatrixData[15];

			NumberType A = matrixB.MatrixData[0];
			NumberType B = matrixB.MatrixData[1];
			NumberType C = matrixB.MatrixData[2];
			NumberType D = matrixB.MatrixData[3];
			NumberType E = matrixB.MatrixData[4];
			NumberType F = matrixB.MatrixData[5];
			NumberType G = matrixB.MatrixData[6];
			NumberType H = matrixB.MatrixData[7];
			NumberType I = matrixB.MatrixData[8];
			NumberType J = matrixB.MatrixData[9];
			NumberType K = matrixB.MatrixData[10];
			NumberType L = matrixB.MatrixData[11];
			NumberType M = matrixB.MatrixData[12];
			NumberType N = matrixB.MatrixData[13];
			NumberType O = matrixB.MatrixData[14];
			NumberType P = matrixB.MatrixData[15];

			NumberType& resultA = MatrixData[0];
			NumberType& resultB = MatrixData[1];
			NumberType& resultC = MatrixData[2];
			NumberType& resultD = MatrixData[3];
			NumberType& resultE = MatrixData[4];
			NumberType& resultF = MatrixData[5];
			NumberType& resultG = MatrixData[6];
			NumberType& resultH = MatrixData[7];
			NumberType& resultI = MatrixData[8];
			NumberType& resultJ = MatrixData[9];
			NumberType& resultK = MatrixData[10];
			NumberType& resultL = MatrixData[11];
			NumberType& resultM = MatrixData[12];
			NumberType& resultN = MatrixData[13];
			NumberType& resultO = MatrixData[14];
			NumberType& resultP = MatrixData[15];

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
		}
		
		void ResetForthAxis()
		{
			// ---0
			// ---0
			// ---0
			// 0001

			this->MatrixData[3] = 0;
			this->MatrixData[7] = 0;
			this->MatrixData[11] = 0;
			this->MatrixData[12] = 0;
			this->MatrixData[13] = 0;
			this->MatrixData[14] = 0;
			this->MatrixData[15] = 1;
		}

		void Add(const Matrix4x4<NumberType>& matrixB)
		{
			NumberType a = this->MatrixData[0];
			NumberType b = this->MatrixData[1];
			NumberType c = this->MatrixData[2];
			NumberType d = this->MatrixData[3];
			NumberType e = this->MatrixData[4];
			NumberType f = this->MatrixData[5];
			NumberType g = this->MatrixData[6];
			NumberType h = this->MatrixData[7];
			NumberType i = this->MatrixData[8];
			NumberType j = this->MatrixData[9];
			NumberType k = this->MatrixData[10];
			NumberType l = this->MatrixData[11];
			NumberType m = this->MatrixData[12];
			NumberType n = this->MatrixData[13];
			NumberType o = this->MatrixData[14];
			NumberType p = this->MatrixData[15];

			NumberType A = matrixB.MatrixData[0];
			NumberType B = matrixB.MatrixData[1];
			NumberType C = matrixB.MatrixData[2];
			NumberType D = matrixB.MatrixData[3];
			NumberType E = matrixB.MatrixData[4];
			NumberType F = matrixB.MatrixData[5];
			NumberType G = matrixB.MatrixData[6];
			NumberType H = matrixB.MatrixData[7];
			NumberType I = matrixB.MatrixData[8];
			NumberType J = matrixB.MatrixData[9];
			NumberType K = matrixB.MatrixData[10];
			NumberType L = matrixB.MatrixData[11];
			NumberType M = matrixB.MatrixData[12];
			NumberType N = matrixB.MatrixData[13];
			NumberType O = matrixB.MatrixData[14];
			NumberType P = matrixB.MatrixData[15];

			NumberType& resultA = MatrixData[0];
			NumberType& resultB = MatrixData[1];
			NumberType& resultC = MatrixData[2];
			NumberType& resultD = MatrixData[3];
			NumberType& resultE = MatrixData[4];
			NumberType& resultF = MatrixData[5];
			NumberType& resultG = MatrixData[6];
			NumberType& resultH = MatrixData[7];
			NumberType& resultI = MatrixData[8];
			NumberType& resultJ = MatrixData[9];
			NumberType& resultK = MatrixData[10];
			NumberType& resultL = MatrixData[11];
			NumberType& resultM = MatrixData[12];
			NumberType& resultN = MatrixData[13];
			NumberType& resultO = MatrixData[14];
			NumberType& resultP = MatrixData[15];

			resultA = a + A;
			resultB = b + B;
			resultC = c + C;
			resultD = d + D;

			resultE = e + E;
			resultF = f + F;
			resultG = g + G;
			resultH = h + H;

			resultI = i + I;
			resultJ = j + J;
			resultK = k + K;
			resultL = l + L;

			resultM = m + M;
			resultN = n + N;
			resultO = o + O;
			resultP = p + P;
		}

		Matrix4x4<NumberType> operator*(const Matrix4x4<NumberType> matrixB)
		{
			Matrix4x4<NumberType> matrix;

			matrix.Multiply(matrixB);

			return matrix;
		}	

		void operator=(Matrix4x4<NumberType> matrix4x4)
		{
			memcmp(this->MatrixData, matrix4x4.MatrixData, 16 * sizeof(NumberType));
		}

		Matrix4x4<NumberType> operator*=(Matrix4x4<NumberType> matrixB)
		{
			return (*this) * matrixB;
		}

		void Move(const NumberType x, const NumberType y, const NumberType z)
		{
			MatrixData[TransformX] += x;
			MatrixData[TransformY] += y;
			MatrixData[TransformZ] += z;
		}
		void Move(const Vector3<NumberType> vector3)
		{
			MatrixData[TransformX] += vector3.X;
			MatrixData[TransformY] += vector3.Y;
			MatrixData[TransformZ] += vector3.Z;
		}
		void MoveTo(const Vector3<NumberType> vector)
		{
			MatrixData[TransformX] = vector.X;
			MatrixData[TransformY] = vector.Y;
			MatrixData[TransformZ] = vector.Z;
		}
		void MoveTo(const NumberType x, const NumberType y, const NumberType z)
		{
			MatrixData[TransformX] = x;
			MatrixData[TransformY] = y;
			MatrixData[TransformZ] = z;
		}

		void Rotate(const Vector3<NumberType> vector)
		{
			Rotate(vector.X, vector.Y, vector.Z);
		}

		void Rotate(NumberType x, NumberType y, NumberType z)
		{

			Matrix4x4<NumberType> result;


			Matrix4x4<NumberType> xRotation;
			Matrix4x4<NumberType> yRotation;
			Matrix4x4<NumberType> zRotation;
	

			//-----<X ROT>-----
			{
		
				float cosResult = Math::Cosinus(x);
				float sinResult = Math::Sinus(x);

				xRotation.MatrixData[5] = cosResult;
				xRotation.MatrixData[6] = sinResult;
				xRotation.MatrixData[9] = -sinResult;
				xRotation.MatrixData[10] = cosResult;
			
			}

			//-----<X ROT>-----
			{
			
				float cosResult = Math::Cosinus(y);
				float sinResult = Math::Sinus(y);

				yRotation.MatrixData[0] = cosResult;
				yRotation.MatrixData[2] = -sinResult;
				yRotation.MatrixData[8] = sinResult;
				yRotation.MatrixData[10] = cosResult;	
			}

			//-----<X ROT>-----
			{
			
				float cosResult = Math::Cosinus(z);
				float sinResult = Math::Sinus(z);

				zRotation.MatrixData[0] = cosResult;
				zRotation.MatrixData[1] = -sinResult;
				zRotation.MatrixData[4] = sinResult;
				zRotation.MatrixData[5] = cosResult;	
			}

			result = xRotation * yRotation * zRotation;

			Multiply(xRotation);
		}
		void RotateTo(const NumberType x, const NumberType y, const  NumberType z)
		{

		}
		void Orbit(const NumberType x, const NumberType y, const NumberType z)
		{

		}
		void Scale(const NumberType scalar)
		{
			MatrixData[ScaleX] *= scalar;
			MatrixData[ScaleY] *= scalar;
			MatrixData[ScaleZ] *= scalar;
		}
		void Scale(const NumberType x, const NumberType y, const NumberType z)
		{
			MatrixData[ScaleX] *= x;
			MatrixData[ScaleY] *= y;
			MatrixData[ScaleZ] *= z;
		}
		void ScaleSet(const NumberType x, const NumberType y, const NumberType z)
		{
			MatrixData[ScaleX] = x;
			MatrixData[ScaleY] = y;
			MatrixData[ScaleZ] = z;
		}
		void ScaleSet(const Vector3<NumberType> vector)
		{
			MatrixData[ScaleX] = vector.X;
			MatrixData[ScaleY] = vector.Y;
			MatrixData[ScaleZ] = vector.Z;
		}
		void Scale(const Vector3<NumberType> vector)
		{
			MatrixData[ScaleX] *= vector.X;
			MatrixData[ScaleY] *= vector.Y;
			MatrixData[ScaleZ] *= vector.Z;
		}

		void LookAt(NumberType x, NumberType y, NumberType z)
		{

		}

		void LookAt(Vector3<NumberType> eye, Vector3<NumberType> center, Vector3<NumberType> up)
		{		
			Vector3<NumberType> centereye = center - eye;
			Vector3<NumberType> f = Vector3<NumberType>::Normalize(centereye);
			Vector3<NumberType> frontUpCross;

			Vector3<NumberType>::CrossProduct(f, up, frontUpCross);

			Vector3<NumberType> s = Vector3<NumberType>::Normalize(frontUpCross);
			Vector3<NumberType> u;

			Vector3<NumberType>::CrossProduct(s, f, u);

			MatrixData[XAxisX] = s.X;
			MatrixData[XAxisY] = s.Y;
			MatrixData[XAxisZ] = s.Z;

			MatrixData[YAxisX] = u.X;
			MatrixData[YAxisY] = u.Y;
			MatrixData[YAxisZ] = u.Z;

			MatrixData[ZAxisX] = -f.X;
			MatrixData[ZAxisY] = -f.Y;
			MatrixData[ZAxisZ] = -f.Z;

			MatrixData[TransformX] = -Vector3<NumberType>::DotProduct(s, eye);
			MatrixData[TransformY] = -Vector3<NumberType>::DotProduct(u, eye);
			MatrixData[TransformZ] = Vector3<NumberType>::DotProduct(f, eye);
		}

		// Flip matrix diagonally
		void Transpose()
		{
			//NumberType a = this->MatrixData[0];
			NumberType b = this->MatrixData[1];
			NumberType c = this->MatrixData[2];
			NumberType d = this->MatrixData[3];

			NumberType e = this->MatrixData[4];
			//NumberType f = this->MatrixData[5];
			NumberType g = this->MatrixData[6];
			NumberType h = this->MatrixData[7];

			NumberType i = this->MatrixData[8];
			NumberType j = this->MatrixData[9];
			//NumberType k = this->MatrixData[10];
			NumberType l = this->MatrixData[11];

			NumberType m = this->MatrixData[12];
			NumberType n = this->MatrixData[13];
			NumberType o = this->MatrixData[14];
			//NumberType p = this->MatrixData[15];

			//this->MatrixData[0] = a;
			this->MatrixData[1] = e;
			this->MatrixData[2] = i;
			this->MatrixData[3] = m;

			this->MatrixData[4] = b;
			//this->MatrixData[5] = f;
			this->MatrixData[6] = j;
			this->MatrixData[7] = n;

			this->MatrixData[8] = c;
			this->MatrixData[9] = g;
			//this->MatrixData[10] = k;
			this->MatrixData[11] = o;

			this->MatrixData[12] = d;
			this->MatrixData[13] = h;
			this->MatrixData[14] = l;
			//this->MatrixData[15] = p;
		}

		// returns sucessful
		bool Inverse()
		{
			Matrix4x4<NumberType> result;
			double det = 0;

			result[0] = MatrixData[5] * MatrixData[10] * MatrixData[15] - MatrixData[5] * MatrixData[11] * MatrixData[14] - MatrixData[9] * MatrixData[6] * MatrixData[15] + MatrixData[9] * MatrixData[7] * MatrixData[14] + MatrixData[13] * MatrixData[6] * MatrixData[11] - MatrixData[13] * MatrixData[7] * MatrixData[10];
			result[4] = -MatrixData[4] * MatrixData[10] * MatrixData[15] + MatrixData[4] * MatrixData[11] * MatrixData[14] + MatrixData[8] * MatrixData[6] * MatrixData[15] - MatrixData[8] * MatrixData[7] * MatrixData[14] - MatrixData[12] * MatrixData[6] * MatrixData[11] + MatrixData[12] * MatrixData[7] * MatrixData[10];
			result[8] = MatrixData[4] * MatrixData[9] * MatrixData[15] - MatrixData[4] * MatrixData[11] * MatrixData[13] - MatrixData[8] * MatrixData[5] * MatrixData[15] + MatrixData[8] * MatrixData[7] * MatrixData[13] + MatrixData[12] * MatrixData[5] * MatrixData[11] - MatrixData[12] * MatrixData[7] * MatrixData[9];
			result[12] = -MatrixData[4] * MatrixData[9] * MatrixData[14] + MatrixData[4] * MatrixData[10] * MatrixData[13] + MatrixData[8] * MatrixData[5] * MatrixData[14] - MatrixData[8] * MatrixData[6] * MatrixData[13] - MatrixData[12] * MatrixData[5] * MatrixData[10] + MatrixData[12] * MatrixData[6] * MatrixData[9];
			result[1] = -MatrixData[1] * MatrixData[10] * MatrixData[15] + MatrixData[1] * MatrixData[11] * MatrixData[14] + MatrixData[9] * MatrixData[2] * MatrixData[15] - MatrixData[9] * MatrixData[3] * MatrixData[14] - MatrixData[13] * MatrixData[2] * MatrixData[11] + MatrixData[13] * MatrixData[3] * MatrixData[10];
			result[5] = MatrixData[0] * MatrixData[10] * MatrixData[15] - MatrixData[0] * MatrixData[11] * MatrixData[14] - MatrixData[8] * MatrixData[2] * MatrixData[15] + MatrixData[8] * MatrixData[3] * MatrixData[14] + MatrixData[12] * MatrixData[2] * MatrixData[11] - MatrixData[12] * MatrixData[3] * MatrixData[10];
			result[9] = -MatrixData[0] * MatrixData[9] * MatrixData[15] + MatrixData[0] * MatrixData[11] * MatrixData[13] + MatrixData[8] * MatrixData[1] * MatrixData[15] - MatrixData[8] * MatrixData[3] * MatrixData[13] - MatrixData[12] * MatrixData[1] * MatrixData[11] + MatrixData[12] * MatrixData[3] * MatrixData[9];
			result[13] = MatrixData[0] * MatrixData[9] * MatrixData[14] - MatrixData[0] * MatrixData[10] * MatrixData[13] - MatrixData[8] * MatrixData[1] * MatrixData[14] + MatrixData[8] * MatrixData[2] * MatrixData[13] + MatrixData[12] * MatrixData[1] * MatrixData[10] - MatrixData[12] * MatrixData[2] * MatrixData[9];
			result[2] = MatrixData[1] * MatrixData[6] * MatrixData[15] - MatrixData[1] * MatrixData[7] * MatrixData[14] - MatrixData[5] * MatrixData[2] * MatrixData[15] + MatrixData[5] * MatrixData[3] * MatrixData[14] + MatrixData[13] * MatrixData[2] * MatrixData[7] - MatrixData[13] * MatrixData[3] * MatrixData[6];
			result[6] = -MatrixData[0] * MatrixData[6] * MatrixData[15] + MatrixData[0] * MatrixData[7] * MatrixData[14] + MatrixData[4] * MatrixData[2] * MatrixData[15] - MatrixData[4] * MatrixData[3] * MatrixData[14] - MatrixData[12] * MatrixData[2] * MatrixData[7] + MatrixData[12] * MatrixData[3] * MatrixData[6];
			result[10] = MatrixData[0] * MatrixData[5] * MatrixData[15] - MatrixData[0] * MatrixData[7] * MatrixData[13] - MatrixData[4] * MatrixData[1] * MatrixData[15] + MatrixData[4] * MatrixData[3] * MatrixData[13] + MatrixData[12] * MatrixData[1] * MatrixData[7] - MatrixData[12] * MatrixData[3] * MatrixData[5];
			result[14] = -MatrixData[0] * MatrixData[5] * MatrixData[14] + MatrixData[0] * MatrixData[6] * MatrixData[13] + MatrixData[4] * MatrixData[1] * MatrixData[14] - MatrixData[4] * MatrixData[2] * MatrixData[13] - MatrixData[12] * MatrixData[1] * MatrixData[6] + MatrixData[12] * MatrixData[2] * MatrixData[5];
			result[3] = -MatrixData[1] * MatrixData[6] * MatrixData[11] + MatrixData[1] * MatrixData[7] * MatrixData[10] + MatrixData[5] * MatrixData[2] * MatrixData[11] - MatrixData[5] * MatrixData[3] * MatrixData[10] - MatrixData[9] * MatrixData[2] * MatrixData[7] + MatrixData[9] * MatrixData[3] * MatrixData[6];
			result[7] = MatrixData[0] * MatrixData[6] * MatrixData[11] - MatrixData[0] * MatrixData[7] * MatrixData[10] - MatrixData[4] * MatrixData[2] * MatrixData[11] + MatrixData[4] * MatrixData[3] * MatrixData[10] + MatrixData[8] * MatrixData[2] * MatrixData[7] - MatrixData[8] * MatrixData[3] * MatrixData[6];
			result[11] = -MatrixData[0] * MatrixData[5] * MatrixData[11] + MatrixData[0] * MatrixData[7] * MatrixData[9] + MatrixData[4] * MatrixData[1] * MatrixData[11] - MatrixData[4] * MatrixData[3] * MatrixData[9] - MatrixData[8] * MatrixData[1] * MatrixData[7] + MatrixData[8] * MatrixData[3] * MatrixData[5];
			result[15] = MatrixData[0] * MatrixData[5] * MatrixData[10] - MatrixData[0] * MatrixData[6] * MatrixData[9] - MatrixData[4] * MatrixData[1] * MatrixData[10] + MatrixData[4] * MatrixData[2] * MatrixData[9] + MatrixData[8] * MatrixData[1] * MatrixData[6] - MatrixData[8] * MatrixData[2] * MatrixData[5];

			det = MatrixData[0] * result[0] + MatrixData[1] * result[4] + MatrixData[2] * result[8] + MatrixData[3] * result[12];

			if (det == 0)
				return false;

			det = 1.0 / det;

			for (int i = 0; i < 16; i++)
			{
				MatrixData[i] = result[i] * det;
			}				

			return true;
		}

		void Set(NumberType value)
		{
			memset(this->MatrixData, value, 16 * sizeof(NumberType));
		} 		

		void Orthographic(NumberType left, NumberType right, NumberType bottom, NumberType top, NumberType zNear, NumberType zFar)
		{		
			Reset();

			MatrixData[ScaleX] = (2) / (NumberType)(right - left);
			MatrixData[ScaleY] = (2) / (NumberType)(top - bottom);
			MatrixData[ScaleZ] = -(2) / (NumberType)(zFar - zNear);
			MatrixData[TransformX] = -(right + left) / (NumberType)(right - left);
			MatrixData[TransformY] = -(top + bottom) / (NumberType)(top - bottom);
			MatrixData[TransformZ] = -(zFar + zNear) / (NumberType)(zFar - zNear);
		}

		void Perspective(const NumberType fielfOfView, const NumberType aspectRatio, const NumberType near, const NumberType far)
		{
			NumberType fielfOfViewRadians = Math::DegreeToRadians(fielfOfView);
			float tanHalfFovy = Math::Tangens(fielfOfViewRadians / 2.0f);

			memset(MatrixData, 0, 16 * sizeof(float));

			MatrixData[ScaleX] = (1) / (aspectRatio * tanHalfFovy);
			MatrixData[ScaleY] = (1) / (tanHalfFovy);
			MatrixData[ScaleZ] = -(far + near) / (far - near);
			MatrixData[11] = -(1);
			MatrixData[TransformZ] = -((2) * far * near) / (far - near);
			
		}
		Vector3<NumberType> ScaleXYZ()
		{
			return Vector3<NumberType>(MatrixData[ScaleX], MatrixData[ScaleY], MatrixData[ScaleZ]);
		}
		Vector4<NumberType> ScaleXYZW()
		{
			return Vector4<NumberType>(MatrixData[ScaleX], MatrixData[ScaleY], MatrixData[ScaleZ], MatrixData[ScaleW]);
		}
		Vector3<NumberType> PositionXYZ()
		{
			return Vector3<NumberType>(MatrixData[TransformX], MatrixData[TransformY], MatrixData[TransformZ]);
		}
		Vector4<NumberType> PositionXYZW()
		{
			return Vector4<NumberType>(MatrixData[TransformX], MatrixData[TransformY], MatrixData[TransformZ], MatrixData[TransformW]);
		}
		Vector4<NumberType> CurrentRotation()
		{
			Vector4<NumberType> x = CurrentAxisX();
			Vector4<NumberType> y = CurrentAxisY();
			Vector4<NumberType> z = CurrentAxisZ();

			return x + y + z;
		}
		Vector4<NumberType> CurrentScaling()
		{
			return Vector4<NumberType>(MatrixData[0], MatrixData[5], MatrixData[10], MatrixData[15]);
		}

		void Print()
		{
			printf
			(
				"| X-Axis | Y-Axis | Z-Axis | Positio |\n"
				"| %7.2f | %7.2f | %7.2f | %7.2f |\n"
				"| %7.2f | %7.2f | %7.2f | %7.2f |\n"
				"| %7.2f | %7.2f | %7.2f | %7.2f |\n"
				"| %7.2f | %7.2f | %7.2f | %7.2f |\n",
				MatrixData[0],
				MatrixData[1],
				MatrixData[2],
				MatrixData[3],
				MatrixData[4],
				MatrixData[5],
				MatrixData[6],
				MatrixData[7],
				MatrixData[8],
				MatrixData[9],
				MatrixData[10],
				MatrixData[11],
				MatrixData[12],
				MatrixData[13],
				MatrixData[14],
				MatrixData[15]
			);


			
		}


		Vector4<NumberType> CurrentAxisX()
		{
			return Vector4<NumberType>(MatrixData[XAxisX], MatrixData[XAxisY], MatrixData[XAxisZ], MatrixData[XAxisW]);
		}
		Vector4<NumberType> CurrentAxisY()
		{
			return Vector4<NumberType>(MatrixData[YAxisX], MatrixData[YAxisY], MatrixData[YAxisZ], MatrixData[YAxisW]);
		}
		Vector4<NumberType> CurrentAxisZ()
		{
			return Vector4<NumberType>(MatrixData[ZAxisX], MatrixData[ZAxisY], MatrixData[ZAxisZ], MatrixData[ZAxisW]);
		}
	};
}