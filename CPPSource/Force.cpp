#include"Constants.h"
#include"Force.h"
#include"Object.h"

using namespace std;

//���������ֽ�(x��)
Force Force::ForceOrthogonalDecomposition_x()
{
	return Force((*this).m_name, (*this).m_source, (*this).m_target,
		(*this).m_magnitude_x, double(0));
}

//���������ֽ�(y��)
Force Force::ForceOrthogonalDecomposition_y()
{
	return Force((*this).Name(), (*this).m_source, (*this).m_target, double(0),
		(*this).m_magnitude_y);
}

//���캯��
Force::Force(string name, Object* source, Object* target, float magnitude, double angle) :
	m_name(name), m_source(source), m_target(target)
{
	angle = 360 - angle;
	m_magnitude_x = magnitude * cos(angle*PI/180.0);
	m_magnitude_y = magnitude * sin(angle*PI / 180.0);
	FORCES.push_back(this);
}

//���캯��(�ڲ���)
Force::Force(string name, Object* source, Object* target, float magnitude_x, float magnitude_y) :
	m_name(name), m_source(source), m_target(target), m_magnitude_x(magnitude_x), m_magnitude_y(magnitude_y)
{
	FORCES.push_back(this);
}

//��������
Force::~Force()
{
	/*string name;
	this->Remove();
	for (int i = 0; i < FORCES.size(); i++)
	{
		if ((*FORCES[i]).Name() == m_name)
		{
			FORCES.erase(FORCES.begin() + i);
			break;
		}
	}*/
}

//��������
Force Force::ReactionForce()
{
	if ((*m_source).Name() == "EMPTY")
	{
		return EMPTYFORCE;
	}
	return Force("-" + m_name, m_target, m_source, -1 * m_magnitude_x, -1 * m_magnitude_y);
}

//Ӧ��
void Force::Apply()
{
	(*m_source).Stress(this);
	(*m_target).Stressed(this);
}

//�Ƴ�
void Force::Remove()
{
	(*m_source).Unstress(this);
	(*m_target).Unstressed(this);
}


//��ȡ����
string Force::Name()
{
	return m_name;
}

//��ȡʩ������
Object* Force::Source()
{
	return m_source;
}

//��ȡ��������
Object* Force::Target()
{
	return m_target;
}

//x����
double Force::MagnitudeX()
{
	return m_magnitude_x;
}

//y����
double Force::MagnitudeY()
{
	return m_magnitude_y;
}

//����+,�ϳ���
Force Force::operator+(Force* force)
{
	Force force_x = (*force).ForceOrthogonalDecomposition_x();
	Force force_y = (*force).ForceOrthogonalDecomposition_y();
	Force Force_x = (*this).ForceOrthogonalDecomposition_x();
	Force Force_y = (*this).ForceOrthogonalDecomposition_y();
	Force PlusedForce = Force(string((*force).Name() + "+" + m_name), &EMPTYOBJECT, m_target, force_x.m_magnitude_x + Force_x.m_magnitude_x, force_y.m_magnitude_y + Force_y.m_magnitude_y);
	return PlusedForce;
}

//����<<,�����

ostream& operator<<(ostream& os, Force* force)
{
	cout << "Force Name:" << force->m_name << endl
		<< "Object Applying Force:" << force->m_source->Name() << endl
		<< "Object Under Force:" << force->m_target->Name() << endl
		<< "XMagnitude:" << force->m_magnitude_x << endl
		<< "YMagnitude:" << force->m_magnitude_y << endl;
	return os;
}
//����<<,�����

ostream& operator<<(ostream& os, Force force)
{
	cout << "Force Name:" << force.m_name << endl
		<< "Object Applying Force:" << force.m_source->Name() << endl
		<< "Object Under Force:" << force.m_target->Name() << endl
		<< "X Magnitude:" << force.m_magnitude_x << endl
		<< "Y Magnitude:" << force.m_magnitude_y << endl;
	return os;
}
