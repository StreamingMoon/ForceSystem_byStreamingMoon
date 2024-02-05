#include"Constants.h"
#include"Force.h"
#include"Object.h"

using namespace std;


//加速度的正交分解(x轴)
Acceleration Object::AccelerationOrthogonalDecomposition_x(Acceleration acceleration)
{

	Acceleration acceleration_x = { acceleration.magnitude_x,0 };
	return acceleration_x;
}

//加速度的正交分解(y轴)
Acceleration Object::AccelerationOrthogonalDecomposition_y(Acceleration acceleration)
{
	Acceleration acceleration_y = { acceleration.magnitude_y,90 };
	return acceleration_y;
}

//速度的正交分解(x轴)
Velocity Object::VelocityOrthogonalDecomposition_x(Velocity velocity)
{
	Velocity velocity_x = { velocity.magnitude_x,0 };
	return velocity_x;
}

//速度的正交分解(y轴)
Velocity Object::VelocityOrthogonalDecomposition_y(Velocity velocity)
{

	Velocity velocity_y = { velocity.magnitude_y,90 };
	return velocity_y;
}

//力的合成
Force Object::ForceSynthesis()
{
	//Force sum = EMPTYFORCE;
	Force sum = *m_force_target[0];
	for (int i = 0; i < m_force_target.size(); i++)
	{
		if (i == 0)
		{
			Force sum = *m_force_target[0];
		}
		else
		{
			sum = sum + m_force_target[i];
		}
	}
	return sum;
}

//加速度的合成
Acceleration Object::AccelerationSynthesis()
{
	Force ResultantForce = ForceSynthesis();
	m_acceleration = { ResultantForce.MagnitudeX() / m_mass, ResultantForce.MagnitudeY() / m_mass };
	return m_acceleration;
}

//速度的合成
//Velocity Object::VelocitySynthesis()
//{
//
//}

//构造函数
Object::Object(string name, vector<Force*> force_source, vector<Force*> force_target, double mass, Acceleration acceleration, Velocity velocity, double x, double y, int w, int h) :
	m_name(name), m_mass(mass), m_acceleration(acceleration), m_velocity(velocity), m_x(x), m_y(y), m_w(w), m_h(h)
{
	force_source.push_back(&EMPTYFORCE);
	m_force_source = force_source;
	force_target.push_back(&EMPTYFORCE);
	m_force_target = force_target;
	OBJECTS.push_back(this);
}

//析构函数
Object::~Object()
{
	/*string name;
	for (int i = 0; i < OBJECTS.size(); i++)
	{
		if ((*OBJECTS[i]).Name() == m_name)
		{
			OBJECTS.erase(OBJECTS.begin() + i);
			break;
		}
	}*/
}

//获取名称
string Object::Name()
{
	return m_name;
}

//获取X坐标
double Object::XPosition()
{
	return m_x;
}

//获取Y坐标	
double Object::YPosition()
{
	return m_y;
}

//获取宽
int Object::Width()
{
	return m_w;
}

//获取高
int Object::Height()
{
	return m_h;
}

//施力
void Object::Stress(Force* force)
{
	m_force_source.push_back(force);
}

//受力
void Object::Stressed(Force* force)
{
	m_force_target.push_back(force);
}

//不施力
void Object::Unstress(Force* force)
{
	string name = (*force).Name();
	for (int i = 0; i < m_force_source.size(); i++)
	{
		if ((*m_force_source[i]).Name() == m_name)
		{
			m_force_source.erase(m_force_source.begin() + i);
		}
	}
}

//不受力
void Object::Unstressed(Force* force)
{
	string name = (*force).Name();
	for (int i = 0; i < m_force_target.size(); i++)
	{
		if ((*m_force_target[i]).Name() == m_name)
		{
			m_force_target.erase(m_force_target.begin() + i);
		}
	}
}

//刷新
void Object::Update()
{
	AccelerationSynthesis();
	m_velocity = { m_velocity.magnitude_x + UNITTIME * m_acceleration.magnitude_x,m_velocity.magnitude_y + UNITTIME * m_acceleration.magnitude_y };
	double x_ = m_x+m_w + m_velocity.magnitude_x * UNITTIME;
	double y_ = m_x +m_h+ m_velocity.magnitude_x * UNITTIME;
	if (x_ > X-1)
	{
		m_x = X-m_w-1;
		m_acceleration.magnitude_x = -1 * m_acceleration.magnitude_x;
		m_velocity.magnitude_x = -1 * m_velocity.magnitude_x;
	}
	else if (x_ < 1)
	{
		m_x = 1;
		m_acceleration.magnitude_x = -1 * m_acceleration.magnitude_x;
		m_velocity.magnitude_x = -1 * m_velocity.magnitude_x;

	}
	if (y_ > Y-1)
	{
		m_y = Y-m_h-1;
		m_acceleration.magnitude_y = -1 * m_acceleration.magnitude_y;
		m_velocity.magnitude_y = -1 * m_velocity.magnitude_y;
	}
	else if (y_ < 1)
	{
		m_y = 1;
		m_acceleration.magnitude_y = -1 * m_acceleration.magnitude_y;
		m_velocity.magnitude_y = -1 * m_velocity.magnitude_y;
	}
}

//重载<<,输出物体
ostream& operator<<(ostream& os, Object* object)
{
	cout << "Object Name:" << object->m_name << endl << "Force Applyed:" << endl;
	for (int i = 0; i < object->m_force_source.size(); i++)
	{
		if ((*object->m_force_source[i]).Name() != EMPTYFORCE.Name())
		{
			cout << "\t" << (*object->m_force_source[i]).Name() << endl;
		}
	}
	cout << "Object Under Force:" << endl;
	for (int i = 0; i < object->m_force_target.size(); i++)
	{
		if ((*object->m_force_target[i]).Name() != EMPTYFORCE.Name())
		{
			cout << "\t" << (*object->m_force_target[i]).Name() << endl;
		}
	}
	cout << "X Acceleration:" << object->m_acceleration.magnitude_x << endl;
	cout << "Y Acceleration:" << object->m_acceleration.magnitude_y << endl;
	cout << "X Velocity:" << object->m_velocity.magnitude_x << endl;
	cout << "Y Velocity:" << object->m_velocity.magnitude_y << endl;
	cout << "X:" << object->m_x << endl
		<< "Y:" << object->m_y << endl;
	return os;
}

//重载<<,输出物体
ostream& operator<<(ostream& os, Object object)
{
	cout << "Object Name:" << object.m_name << endl << "Force Applyed:" << endl;
	for (int i = 0; i < object.m_force_source.size(); i++)
	{
		if ((*object.m_force_target[i]).Name() != EMPTYFORCE.Name())
		{
			cout << "\t" << (*object.m_force_source[i]).Name() << endl;
		}
	}
	cout << "Object Under Force:" << endl;
	for (int i = 0; i < object.m_force_target.size(); i++)
	{
		if ((*object.m_force_target[i]).Name() != EMPTYFORCE.Name())
		{
			cout << "\t" << (*object.m_force_target[i]).Name() << endl;
		}
	}
	cout << "X Acceleration:" << object.m_acceleration.magnitude_x << endl;
	cout << "Y Acceleration:" << object.m_acceleration.magnitude_y << endl;
	cout << "X Velocity:" << object.m_velocity.magnitude_x << endl;
	cout << "Y Velocity:" << object.m_velocity.magnitude_y << endl;
	cout << "X:" << object.m_x << endl
		<< "Y:" << object.m_y << endl;
	return os;
}