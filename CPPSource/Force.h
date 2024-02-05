#pragma once

#ifndef FORCE
#define FORCE
#endif

#include"Constants.h"
#include"Object.h"
#include<string>

using namespace std;

class Force
{
private:
	string m_name;		//����
	Object* m_source;	//ʩ������
	Object* m_target;	//��������
	float m_magnitude_x;		//x�����С
	float m_magnitude_y;		//y�����С

public:
	Force ForceOrthogonalDecomposition_x();		//���������ֽ�(x��)
	Force ForceOrthogonalDecomposition_y();		//���������ֽ�(y��)
	Force(string name, Object* source, Object* target, float magnitude, double angle);		//���캯��
	Force(string name,Object* source,Object* target, float magnitude_x, float magnitude_y);	//���캯��(�ڲ���)
	Force()=delete;	//�������캯��
	~Force();		//��������
	Force ReactionForce();		//��������
	void Apply();	//Ӧ��
	void Remove();	//�Ƴ�
	string Name();		//��ȡ����
	Object* Source();	//��ȡʩ������
	Object* Target();	//��ȡ��������
	double MagnitudeX();	//x����
	double MagnitudeY();	//y����
	Force operator+(Force* force);	//����+,�ϳ���
	friend ostream& operator<<(ostream & os,Force* force);	//����<<,�����
	friend ostream& operator<<(ostream& os, Force force);	//����<<,�����

};

