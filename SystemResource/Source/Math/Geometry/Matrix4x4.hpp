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

#define WAxisX 6
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
		NumberType Data[16];


		Matrix4x4()
		{
			Reset();
		}

		void Reset()
		{
			memset(Data, 0, sizeof(NumberType) * 16);

			Data[0] = 1;
			Data[5] = 1;
			Data[10] = 1;
			Data[15] = 1;
		}

		void Multiply(Matrix4x4<NumberType>& matrixB)
		{
			NumberType a = this->Data[0];
			NumberType b = this->Data[1];
			NumberType c = this->Data[2];
			NumberType d = this->Data[3];
			NumberType e = this->Data[4];
			NumberType f = this->Data[5];
			NumberType g = this->Data[6];
			NumberType h = this->Data[7];
			NumberType i = this->Data[8];
			NumberType j = this->Data[9];
			NumberType k = this->Data[10];
			NumberType l = this->Data[11];
			NumberType m = this->Data[12];
			NumberType n = this->Data[13];
			NumberType o = this->Data[14];
			NumberType p = this->Data[15];

			NumberType A = matrixB.Data[0];
			NumberType B = matrixB.Data[1];
			NumberType C = matrixB.Data[2];
			NumberType D = matrixB.Data[3];
			NumberType E = matrixB.Data[4];
			NumberType F = matrixB.Data[5];
			NumberType G = matrixB.Data[6];
			NumberType H = matrixB.Data[7];
			NumberType I = matrixB.Data[8];
			NumberType J = matrixB.Data[9];
			NumberType K = matrixB.Data[10];
			NumberType L = matrixB.Data[11];
			NumberType M = matrixB.Data[12];
			NumberType N = matrixB.Data[13];
			NumberType O = matrixB.Data[14];
			NumberType P = matrixB.Data[15];

			NumberType& resultA = Data[0];
			NumberType& resultB = Data[1];
			NumberType& resultC = Data[2];
			NumberType& resultD = Data[3];
			NumberType& resultE = Data[4];
			NumberType& resultF = Data[5];
			NumberType& resultG = Data[6];
			NumberType& resultH = Data[7];
			NumberType& resultI = Data[8];
			NumberType& resultJ = Data[9];
			NumberType& resultK = Data[10];
			NumberType& resultL = Data[11];
			NumberType& resultM = Data[12];
			NumberType& resultN = Data[13];
			NumberType& resultO = Data[14];
			NumberType& resultP = Data[15];

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
			this->Data[3] = 0;
			this->Data[7] = 0;
			this->Data[11] = 0;
			this->Data[12] = 0;
			this->Data[13] = 0;
			this->Data[14] = 0;
			this->Data[15] = 1;
		}

		void Add(Matrix4x4<NumberType>& matrixB)
		{
			NumberType a = this->Data[0];
			NumberType b = this->Data[1];
			NumberType c = this->Data[2];
			NumberType d = this->Data[3];
			NumberType e = this->Data[4];
			NumberType f = this->Data[5];
			NumberType g = this->Data[6];
			NumberType h = this->Data[7];
			NumberType i = this->Data[8];
			NumberType j = this->Data[9];
			NumberType k = this->Data[10];
			NumberType l = this->Data[11];
			NumberType m = this->Data[12];
			NumberType n = this->Data[13];
			NumberType o = this->Data[14];
			NumberType p = this->Data[15];

			NumberType A = matrixB.Data[0];
			NumberType B = matrixB.Data[1];
			NumberType C = matrixB.Data[2];
			NumberType D = matrixB.Data[3];
			NumberType E = matrixB.Data[4];
			NumberType F = matrixB.Data[5];
			NumberType G = matrixB.Data[6];
			NumberType H = matrixB.Data[7];
			NumberType I = matrixB.Data[8];
			NumberType J = matrixB.Data[9];
			NumberType K = matrixB.Data[10];
			NumberType L = matrixB.Data[11];
			NumberType M = matrixB.Data[12];
			NumberType N = matrixB.Data[13];
			NumberType O = matrixB.Data[14];
			NumberType P = matrixB.Data[15];

			NumberType& resultA = Data[0];
			NumberType& resultB = Data[1];
			NumberType& resultC = Data[2];
			NumberType& resultD = Data[3];
			NumberType& resultE = Data[4];
			NumberType& resultF = Data[5];
			NumberType& resultG = Data[6];
			NumberType& resultH = Data[7];
			NumberType& resultI = Data[8];
			NumberType& resultJ = Data[9];
			NumberType& resultK = Data[10];
			NumberType& resultL = Data[11];
			NumberType& resultM = Data[12];
			NumberType& resultN = Data[13];
			NumberType& resultO = Data[14];
			NumberType& resultP = Data[15];

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

		Matrix4x4<NumberType> operator*(Matrix4x4<NumberType> matrixB)
		{
			Matrix4x4<NumberType> matrix;

			matrix.Multiply(matrixB);

			return matrix;
		}	

		void operator=(Matrix4x4<NumberType> matrix4x4)
		{
			memcmp(this->Data, matrix4x4.Data, 16 * sizeof(NumberType));
		}

		Matrix4x4<NumberType> operator*=(Matrix4x4<NumberType> matrixB)
		{
			return (*this) * matrixB;
		}

		void Move(NumberType x, NumberType y, NumberType z)
		{
			Data[TransformX] += x;
			Data[TransformY] += y;
			Data[TransformZ] += z;
		}
		void Move(Vector3<NumberType> vector3)
		{
			Data[TransformX] += vector3.X;
			Data[TransformY] += vector3.Y;
			Data[TransformZ] += vector3.Z;
		}
		void MoveTo(Vector3<NumberType> vector)
		{
			Data[TransformX] = vector.X;
			Data[TransformY] = vector.Y;
			Data[TransformZ] = vector.Z;
		}
		void MoveTo(NumberType x, NumberType y, NumberType z)
		{
			Data[TransformX] = x;
			Data[TransformY] = y;
			Data[TransformZ] = z;
		}

		void Rotate(Vector3<NumberType> vector)
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

				xRotation.Data[5] = cosResult;
				xRotation.Data[6] = sinResult;
				xRotation.Data[9] = -sinResult;
				xRotation.Data[10] = cosResult;
			
			}

			//-----<X ROT>-----
			{
			
				float cosResult = Math::Cosinus(y);
				float sinResult = Math::Sinus(y);

				yRotation.Data[0] = cosResult;
				yRotation.Data[2] = -sinResult;
				yRotation.Data[8] = sinResult;
				yRotation.Data[10] = cosResult;	
			}

			//-----<X ROT>-----
			{
			
				float cosResult = Math::Cosinus(z);
				float sinResult = Math::Sinus(z);

				zRotation.Data[0] = cosResult;
				zRotation.Data[1] = -sinResult;
				zRotation.Data[4] = sinResult;
				zRotation.Data[5] = cosResult;	
			}

			result = xRotation;// *yRotation* zRotation;

			Multiply(xRotation);
		}
		void RotateTo(NumberType x, NumberType y, NumberType z)
		{

		}
		void Orbit(NumberType x, NumberType y, NumberType z)
		{

		}
		void Scale(NumberType scalar)
		{
			Data[ScaleX] *= scalar;
			Data[ScaleY] *= scalar;
			Data[ScaleZ] *= scalar;
		}
		void Scale(NumberType x, NumberType y, NumberType z)
		{
			Data[ScaleX] *= x;
			Data[ScaleY] *= y;
			Data[ScaleZ] *= z;
		}
		void ScaleSet(NumberType x, NumberType y, NumberType z)
		{
			Data[ScaleX] = x;
			Data[ScaleY] = y;
			Data[ScaleZ] = z;
		}
		void ScaleSet(Vector3<NumberType> vector)
		{
			Data[ScaleX] = vector.X;
			Data[ScaleY] = vector.Y;
			Data[ScaleZ] = vector.Z;
		}
		void Scale(Vector3<NumberType> vector)
		{
			Data[ScaleX] *= vector.X;
			Data[ScaleY] *= vector.Y;
			Data[ScaleZ] *= vector.Z;
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

			Data[XAxisX] = s.X;
			Data[XAxisY] = s.Y;
			Data[XAxisZ] = s.Z;

			Data[YAxisX] = u.X;
			Data[YAxisY] = u.Y;
			Data[YAxisZ] = u.Z;

			Data[ZAxisX] = -f.X;
			Data[ZAxisY] = -f.Y;
			Data[ZAxisZ] = -f.Z;

			Data[TransformX] = -Vector3<NumberType>::DotProduct(s, eye);
			Data[TransformY] = -Vector3<NumberType>::DotProduct(u, eye);
			Data[TransformZ] = Vector3<NumberType>::DotProduct(f, eye);
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

		// returns sucessful
		bool Inverse()
		{
			Matrix4x4<NumberType> result;
			double det = 0;

			result[0] = Data[5] * Data[10] * Data[15] - Data[5] * Data[11] * Data[14] - Data[9] * Data[6] * Data[15] + Data[9] * Data[7] * Data[14] + Data[13] * Data[6] * Data[11] - Data[13] * Data[7] * Data[10];
			result[4] = -Data[4] * Data[10] * Data[15] + Data[4] * Data[11] * Data[14] + Data[8] * Data[6] * Data[15] - Data[8] * Data[7] * Data[14] - Data[12] * Data[6] * Data[11] + Data[12] * Data[7] * Data[10];
			result[8] = Data[4] * Data[9] * Data[15] - Data[4] * Data[11] * Data[13] - Data[8] * Data[5] * Data[15] + Data[8] * Data[7] * Data[13] + Data[12] * Data[5] * Data[11] - Data[12] * Data[7] * Data[9];
			result[12] = -Data[4] * Data[9] * Data[14] + Data[4] * Data[10] * Data[13] + Data[8] * Data[5] * Data[14] - Data[8] * Data[6] * Data[13] - Data[12] * Data[5] * Data[10] + Data[12] * Data[6] * Data[9];
			result[1] = -Data[1] * Data[10] * Data[15] + Data[1] * Data[11] * Data[14] + Data[9] * Data[2] * Data[15] - Data[9] * Data[3] * Data[14] - Data[13] * Data[2] * Data[11] + Data[13] * Data[3] * Data[10];
			result[5] = Data[0] * Data[10] * Data[15] - Data[0] * Data[11] * Data[14] - Data[8] * Data[2] * Data[15] + Data[8] * Data[3] * Data[14] + Data[12] * Data[2] * Data[11] - Data[12] * Data[3] * Data[10];
			result[9] = -Data[0] * Data[9] * Data[15] + Data[0] * Data[11] * Data[13] + Data[8] * Data[1] * Data[15] - Data[8] * Data[3] * Data[13] - Data[12] * Data[1] * Data[11] + Data[12] * Data[3] * Data[9];
			result[13] = Data[0] * Data[9] * Data[14] - Data[0] * Data[10] * Data[13] - Data[8] * Data[1] * Data[14] + Data[8] * Data[2] * Data[13] + Data[12] * Data[1] * Data[10] - Data[12] * Data[2] * Data[9];
			result[2] = Data[1] * Data[6] * Data[15] - Data[1] * Data[7] * Data[14] - Data[5] * Data[2] * Data[15] + Data[5] * Data[3] * Data[14] + Data[13] * Data[2] * Data[7] - Data[13] * Data[3] * Data[6];
			result[6] = -Data[0] * Data[6] * Data[15] + Data[0] * Data[7] * Data[14] + Data[4] * Data[2] * Data[15] - Data[4] * Data[3] * Data[14] - Data[12] * Data[2] * Data[7] + Data[12] * Data[3] * Data[6];
			result[10] = Data[0] * Data[5] * Data[15] - Data[0] * Data[7] * Data[13] - Data[4] * Data[1] * Data[15] + Data[4] * Data[3] * Data[13] + Data[12] * Data[1] * Data[7] - Data[12] * Data[3] * Data[5];
			result[14] = -Data[0] * Data[5] * Data[14] + Data[0] * Data[6] * Data[13] + Data[4] * Data[1] * Data[14] - Data[4] * Data[2] * Data[13] - Data[12] * Data[1] * Data[6] + Data[12] * Data[2] * Data[5];
			result[3] = -Data[1] * Data[6] * Data[11] + Data[1] * Data[7] * Data[10] + Data[5] * Data[2] * Data[11] - Data[5] * Data[3] * Data[10] - Data[9] * Data[2] * Data[7] + Data[9] * Data[3] * Data[6];
			result[7] = Data[0] * Data[6] * Data[11] - Data[0] * Data[7] * Data[10] - Data[4] * Data[2] * Data[11] + Data[4] * Data[3] * Data[10] + Data[8] * Data[2] * Data[7] - Data[8] * Data[3] * Data[6];
			result[11] = -Data[0] * Data[5] * Data[11] + Data[0] * Data[7] * Data[9] + Data[4] * Data[1] * Data[11] - Data[4] * Data[3] * Data[9] - Data[8] * Data[1] * Data[7] + Data[8] * Data[3] * Data[5];
			result[15] = Data[0] * Data[5] * Data[10] - Data[0] * Data[6] * Data[9] - Data[4] * Data[1] * Data[10] + Data[4] * Data[2] * Data[9] + Data[8] * Data[1] * Data[6] - Data[8] * Data[2] * Data[5];

			det = Data[0] * result[0] + Data[1] * result[4] + Data[2] * result[8] + Data[3] * result[12];

			if (det == 0)
				return false;

			det = 1.0 / det;

			for (int i = 0; i < 16; i++)
			{
				Data[i] = result[i] * det;
			}				

			return true;
		}

		void Set(NumberType value)
		{
			memset(this->Data, value, 16 * sizeof(NumberType));
		} 		

		void Orthographic(NumberType left, NumberType right, NumberType bottom, NumberType top, NumberType zNear, NumberType zFar)
		{		
			Reset();

			Data[ScaleX] = (2) / (NumberType)(right - left);
			Data[ScaleY] = (2) / (NumberType)(top - bottom);
			Data[ScaleZ] = -(2) / (NumberType)(zFar - zNear);
			Data[TransformX] = -(right + left) / (NumberType)(right - left);
			Data[TransformY] = -(top + bottom) / (NumberType)(top - bottom);
			Data[TransformZ] = -(zFar + zNear) / (NumberType)(zFar - zNear);
		}

		void Perspective(NumberType fielfOfView, NumberType aspectRatio, NumberType near, NumberType far)
		{
			NumberType fielfOfViewRadians = Math::DegreeToRadians(fielfOfView);
			float tanHalfFovy = Math::Tangens(fielfOfViewRadians / 2.0f);

			memset(Data, 0, 16 * sizeof(float));

			Data[ScaleX] = (1) / (aspectRatio * tanHalfFovy);
			Data[ScaleY] = (1) / (tanHalfFovy);
			Data[ScaleZ] = -(far + near) / (far - near);
			Data[11] = -(1);
			Data[TransformZ] = -((2) * far * near) / (far - near);
			
		}
		Vector3<NumberType> ScaleXYZ()
		{
			return Vector3<NumberType>(Data[ScaleX], Data[ScaleY], Data[ScaleZ]);
		}
		Vector4<NumberType> ScaleXYZW()
		{
			return Vector4<NumberType>(Data[ScaleX], Data[ScaleY], Data[ScaleZ], Data[ScaleW]);
		}
		Vector3<NumberType> PositionXYZ()
		{
			return Vector3<NumberType>(Data[TransformX], Data[TransformY], Data[TransformZ]);
		}
		Vector4<NumberType> PositionXYZW()
		{
			return Vector4<NumberType>(Data[TransformX], Data[TransformY], Data[TransformZ], Data[TransformW]);
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
			return Vector4<NumberType>(Data[0], Data[5], Data[10], Data[15]);
		}

		void Print()
		{
			printf("\n\n%7.2f %7.2f %7.2f %7.2f\n", this->Data[0], this->Data[1], this->Data[2], this->Data[3]);
			printf("%7.2f %7.2f %7.2f %7.2f\n", this->Data[4], this->Data[5], this->Data[6], this->Data[7]);
			printf("%7.2f %7.2f %7.2f %7.2f\n", this->Data[8], this->Data[9], this->Data[10], this->Data[11]);
			printf("%7.2f %7.2f %7.2f %7.2f\n\n", this->Data[12], this->Data[13], this->Data[14], this->Data[15]);
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