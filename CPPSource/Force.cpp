#include"Constants.h"
#include"Force.h"
#include"Object.h"

using namespace std;

//力的正交分解(x轴)
Force Force::ForceOrthogonalDecomposition_x()
{
	return Force((*this).m_name, (*this).m_source, (*this).m_target,
		(*this).m_magnitude_x, double(0));
}

//力的正交分解(y轴)
Force Force::ForceOrthogonalDecomposition_y()
{
	return Force((*this).Name(), (*this).m_source, (*this).m_target, double(0),
		(*this).m_magnitude_y);
}

//构造函数
Force::Force(string name, Object* source, Object* target, float magnitude, double angle) :
	m_name(name), m_source(source), m_target(target)
{
	angle = 360 - angle;
	m_magnitude_x = magnitude * cos(angle*PI/180.0);
	m_magnitude_y = magnitude * sin(angle*PI / 180.0);
	FORCES.push_back(this);
}

//构造函数(内部用)
Force::Force(string name, Object* source, Object* target, float magnitude_x, float magnitude_y) :
	m_name(name), m_source(source), m_target(target), m_magnitude_x(magnitude_x), m_magnitude_y(magnitude_y)
{
	FORCES.push_back(this);
}

//析构函数
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

//反作用力
Force Force::ReactionForce()
{
	if ((*m_source).Name() == "EMPTY")
	{
		return EMPTYFORCE;
	}
	return Force("-" + m_name, m_target, m_source, -1 * m_magnitude_x, -1 * m_magnitude_y);
}

//应用
void Force::Apply()
{
	(*m_source).Stress(this);
	(*m_target).Stressed(this);
}

//移除
void Force::Remove()
{
	(*m_source).Unstress(this);
	(*m_target).Unstressed(this);
}


//获取名称
string Force::Name()
{
	return m_name;
}

//获取施力物体
Object* Force::Source()
{
	return m_source;
}

//获取受力物体
Object* Force::Target()
{
	return m_target;
}

//x分量
double Force::MagnitudeX()
{
	return m_magnitude_x;
}

//y分量
double Force::MagnitudeY()
{
	return m_magnitude_y;
}

//重载+,合成力
Force Force::operator+(Force* force)
{
	Force force_x = (*force).ForceOrthogonalDecomposition_x();
	Force force_y = (*force).ForceOrthogonalDecomposition_y();
	Force Force_x = (*this).ForceOrthogonalDecomposition_x();
	Force Force_y = (*this).ForceOrthogonalDecomposition_y();
	Force PlusedForce = Force(string((*force).Name() + "+" + m_name), &EMPTYOBJECT, m_target, force_x.m_magnitude_x + Force_x.m_magnitude_x, force_y.m_magnitude_y + Force_y.m_magnitude_y);
	return PlusedForce;
}

//重载<<,输出力

ostream& operator<<(ostream& os, Force* force)
{
	cout << "Force Name:" << force->m_name << endl
		<< "Object Applying Force:" << force->m_source->Name() << endl
		<< "Object Under Force:" << force->m_target->Name() << endl
		<< "XMagnitude:" << force->m_magnitude_x << endl
		<< "YMagnitude:" << force->m_magnitude_y << endl;
	return os;
}
//重载<<,输出力

ostream& operator<<(ostream& os, Force force)
{
	cout << "Force Name:" << force.m_name << endl
		<< "Object Applying Force:" << force.m_source->Name() << endl
		<< "Object Under Force:" << force.m_target->Name() << endl
		<< "X Magnitude:" << force.m_magnitude_x << endl
		<< "Y Magnitude:" << force.m_magnitude_y << endl;
	return os;
}
