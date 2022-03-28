#pragma once
class Scene {
public:
	Scene() {
		this->GR = 0;
	}
	void setGR(double a) {
		this->GR = a;
	}
private:
	double GR; // 重力加速度；dot/F^2（像素/帧平方）
};