#pragma once
#include<cmath>

class Body {
public:
	Body(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->velocity_x = this->velocity_y = this->velocity_z = 0;
		this->acceleration_x = this->acceleration_y = this->acceleration_z = 0;
	}
	void LinearMove(double time) {
		this->x += time * this->velocity_x;
		this->y += time * this->velocity_y;
		this->z += time * this->velocity_z;
	}
	void Move(double time) {
		this->x += 0.5f * this->acceleration_x * time * time + this ->velocity_x * time;
		this->velocity_x += time * this->acceleration_x;
		this->y += 0.5f * this->acceleration_y * time * time + this->velocity_y * time;
		this->velocity_y += time * this->acceleration_y;
		this->z += 0.5f * this->acceleration_z * time * time + this->velocity_z * time;
		this->velocity_z += time * this->acceleration_z;
	}
	void CircularMove(double time,double x,double y,double omiga) {
		this->x = (this->x - x)*cos(omiga * time) - (this->y - y) * sin(omiga * time) + x;
		this->y = (this->y - y)*cos(omiga * time) + (this->x - x) * sin(omiga * time) + y;
	}

private:
	double x;
	double y;
	double z;
	double velocity_x;
	double velocity_y;
	double velocity_z;
	double acceleration_x;
	double acceleration_y;
	double acceleration_z;
};
