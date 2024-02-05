#pragma once

#ifndef OBJECT
#define OBJECT
#endif

#include"Constants.h"
#include"Force.h"
#include<string>
#include<vector>

using namespace std;

struct Acceleration		//���ٶȽṹ��
{
	double magnitude_x;		//x����
	double magnitude_y;		//y����
};

struct Velocity		//�ٶȽṹ��
{
	double magnitude_x;		//x����
	double magnitude_y;		//y����
};

class Object
{
private:
	string m_name;		//����
	vector<class Force*> m_force_source;		//ʩ��
	vector<class Force*> m_force_target;		//����
	double m_mass;		//����
	Acceleration m_acceleration;	//���ٶ�
	Velocity m_velocity;	 //�ٶ�
	double m_x;		//x����
	double m_y;		//y����
	int m_w;		//��
	int m_h;		//��

	Acceleration AccelerationOrthogonalDecomposition_x(Acceleration acceleration);		//���ٶȵ������ֽ�(x��)
	Acceleration AccelerationOrthogonalDecomposition_y(Acceleration acceleration);		//���ٶȵ������ֽ�(y��)
	Velocity VelocityOrthogonalDecomposition_x(Velocity velocity);		//�ٶȵ������ֽ�(x��)
	Velocity VelocityOrthogonalDecomposition_y(Velocity velocity);		//�ٶȵ������ֽ�(y��)
	Force ForceSynthesis();		//���ĺϳ�
	Acceleration AccelerationSynthesis();	  //���ٶȵĺϳ�
	//Velocity VelocitySynthesis();		//�ٶȵĺϳ�
public:
	Object(string name, vector<Force*> force_source, vector<Force*> force_target, double mass, Acceleration acceleration, Velocity velocity, double x, double y,int w,int h);		//���캯��
	Object()=delete;
	~Object();		//��������
	string Name();		//��ȡ����
	double XPosition();	//��ȡX����
	double YPosition();	//��ȡY����
	int Width();	//��ȡ��
	int Height();	//��ȡ��
	void Stress(Force* force);	  //ʩ��
	void Stressed(Force* force);		//����
	void Unstress(Force* force);		//��ʩ��
	void Unstressed(Force* force);	//������
	void Update();		//ˢ��
	friend ostream& operator<<(ostream& os, Object* object);	//����<<,�������
	friend ostream& operator<<(ostream& os, Object object);	//����<<,�������
};

