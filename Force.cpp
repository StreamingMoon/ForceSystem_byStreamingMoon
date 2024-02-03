#include"Constants.h"
#include"Force.h"
#include "Object.h"

using namespace std;

//力的正交分解(x轴)
Force Force::ForceOrthogonalDecomposition_x(Force force)
{
	return Force(force.m_name, force.m_source, force.m_target,
		force.m_magnitude_x,0);
}

//力的正交分解(y轴)
Force Force::ForceOrthogonalDecomposition_y(Force force)
{
	return Force(force.Name(), force.m_source, force.m_target,
		force.m_magnitude_y,90);
}

//构造函数
Force::Force(string name, Object source, Object target, double magnitude,int angle):
	m_name(name), m_source(source), m_target(target)
{
		m_magnitude_x = magnitude * cos(angle);
		m_magnitude_y = magnitude * sin(angle);
		FORCES.push_back(*this);
}

//构造函数(内部用)
Force::Force(string name, Object source, Object target, double magnitude_x, double magnitude_y):
	m_name(name), m_source(source), m_target(target)
{
	m_magnitude_x = magnitude_x;
	m_magnitude_y = magnitude_y;
}

//空力构造函数
Force::Force()
{
	string m_name="EMPTY";
	Object m_source=EMPTYOBJECT;
	Object m_target= EMPTYOBJECT;
	double m_magnitude_x=0;
	double m_magnitude_y=0;
	FORCES.push_back(*this);
}

//析构函数
Force::~Force()
{
	string name;
	for (Force force : FORCES)
	{
		if (name == force.Name())
		{
			FORCES.erase(remove(FORCES.begin(), FORCES.end(), force), FORCES.end());
		}
	}
}

//反作用力
Force Force::ReactionForce()
{
	if (m_source.Name() == "EMPTY")
	{
		return EMPTYFORCE;
	}
	return Force("~" + m_name, m_target, m_source, -1*m_magnitude_x,-1*m_magnitude_y);
}

//应用
void Force::Apply()
{
	m_source.Stress(*this);
	m_target.Stressed(*this);
}

//获取名称
string Force::Name()
{
	return m_name;
}

//获取施力物体
Object Force::Source()
{
	return m_source;
}

//获取受力物体
Object Force::Target()
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
Force Force::operator+(Force force)
{
	Force force_x = ForceOrthogonalDecomposition_x(force);
	Force force_y = ForceOrthogonalDecomposition_y(force);
	Force Force_x = ForceOrthogonalDecomposition_x(*this);
	Force Force_y = ForceOrthogonalDecomposition_y(*this);
	Force PlusedForce = Force(string(force.Name() + "+" + this->Name()), EMPTYOBJECT, this->m_target, force_x.m_magnitude_x + Force_x.m_magnitude_x, force_y.m_magnitude_y + Force_y.m_magnitude_y);
	return PlusedForce;
}