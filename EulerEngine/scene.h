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
	double GR; // �������ٶȣ�dot/F^2������/֡ƽ����
};