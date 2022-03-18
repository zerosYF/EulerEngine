#pragma once
#include<cmath>

const double  col = 0.0001;
class Vector {
public:
	double x;
	double y;
	double z;
	Vector() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	};
	Vector(double x,double y,double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	// ��׼��
	void Normalize() {
		double m = this->Magnitude();
		if (m <= col) m = 1;
		x /= m;
		y /= m;
		z /= m;
		if (abs(x) <= col) x = 0.0;
		if (abs(y) <= col) y = 0.0;
		if (abs(z) <= col) z = 0.0;
	};
	// ȡ��
	void Reverse() {
		x = -x;
		y = -y;
		z = -z;
	};
	// ȡģ
	double Magnitude() {
		return (double)sqrt(x*x + y*y + z*z);
	};
	// �����ӷ�
	Vector& operator+=(Vector u) {
		this->x += u.x;
		this->y += u.y;
		this->z += u.z;
		return *this;
	};
	// ��������
	Vector& operator-=(Vector u) {
		this->x -= u.x;
		this->y -= u.y;
		this->z -= u.z;
		return *this;
	};
	// �����˷�
	Vector& operator*=(double k) {
		this->x *= k;
		this->y *= k;
		this->z *= k;
		return *this;
	};
	// ��������
	Vector& operator/=(double k) {
		this->x /= k;
		this->y /= k;
		this->z /= k;
		return *this;
	}
private:
};
inline Vector operator+(Vector v, Vector u) {
	return Vector(v.x+u.x,v.y+u.y,v.z+u.z);
}
inline Vector operator-(Vector v, Vector u) {
	return Vector(v.x - u.x, v.y - u.y, v.z - u.z);
}
inline Vector operator*(Vector v, double k) {
	return Vector(v.x * k, v.y * k, v.z * k);
}
inline Vector operator/(Vector v, double k) {
	return Vector(v.x / k, v.y / k, v.z / k);
}
inline Vector cross(Vector v, Vector u) {
	
}