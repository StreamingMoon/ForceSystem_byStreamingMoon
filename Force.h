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
	Object m_source;	//ʩ������
	Object m_target;	//��������
	double m_magnitude_x;		//x�����С
	double m_magnitude_y;		//y�����С

public:
	Force ForceOrthogonalDecomposition_x(Force force);		//���������ֽ�(x��)
	Force ForceOrthogonalDecomposition_y(Force force);		//���������ֽ�(y��)
	Force(string name, Object source, Object target, double magnitude, int angle);		//���캯��
	Force(string name,Object source,Object target,double magnitude_x,double magnitude_y);	//���캯��(�ڲ���)
	Force();	//�������캯��
	~Force();		//��������
	Force ReactionForce();		//��������
	void Apply();	//Ӧ��
	string Name();		//��ȡ����
	Object Source();	//��ȡʩ������
	Object Target();	//��ȡ��������
	double MagnitudeX();	//x����
	double MagnitudeY();	//y����
	Force operator+(Force force);	//����+,�ϳ���
};

