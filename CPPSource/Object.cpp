#include"Constants.h"
#include"Force.h"
#include"Object.h"

using namespace std;


//���ٶȵ������ֽ�(x��)
Acceleration Object::AccelerationOrthogonalDecomposition_x(Acceleration acceleration)
{

	Acceleration acceleration_x = { acceleration.magnitude_x,0 };
	return acceleration_x;
}

//���ٶȵ������ֽ�(y��)
Acceleration Object::AccelerationOrthogonalDecomposition_y(Acceleration acceleration)
{
	Acceleration acceleration_y = { acceleration.magnitude_y,90 };
	return acceleration_y;
}

//�ٶȵ������ֽ�(x��)
Velocity Object::VelocityOrthogonalDecomposition_x(Velocity velocity)
{
	Velocity velocity_x = { velocity.magnitude_x,0 };
	return velocity_x;
}

//�ٶȵ������ֽ�(y��)
Velocity Object::VelocityOrthogonalDecomposition_y(Velocity velocity)
{

	Velocity velocity_y = { velocity.magnitude_y,90 };
	return velocity_y;
}

//���ĺϳ�
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

//���ٶȵĺϳ�
Acceleration Object::AccelerationSynthesis()
{
	Force ResultantForce = ForceSynthesis();
	m_acceleration = { ResultantForce.MagnitudeX() / m_mass, ResultantForce.MagnitudeY() / m_mass };
	return m_acceleration;
}

//�ٶȵĺϳ�
//Velocity Object::VelocitySynthesis()
//{
//
//}

//���캯��
Object::Object(string name, vector<Force*> force_source, vector<Force*> force_target, double mass, Acceleration acceleration, Velocity velocity, double x, double y, int w, int h) :
	m_name(name), m_mass(mass), m_acceleration(acceleration), m_velocity(velocity), m_x(x), m_y(y), m_w(w), m_h(h)
{
	force_source.push_back(&EMPTYFORCE);
	m_force_source = force_source;
	force_target.push_back(&EMPTYFORCE);
	m_force_target = force_target;
	OBJECTS.push_back(this);
}

//��������
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

//��ȡ����
string Object::Name()
{
	return m_name;
}

//��ȡX����
double Object::XPosition()
{
	return m_x;
}

//��ȡY����	
double Object::YPosition()
{
	return m_y;
}

//��ȡ��
int Object::Width()
{
	return m_w;
}

//��ȡ��
int Object::Height()
{
	return m_h;
}

//ʩ��
void Object::Stress(Force* force)
{
	m_force_source.push_back(force);
}

//����
void Object::Stressed(Force* force)
{
	m_force_target.push_back(force);
}

//��ʩ��
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

//������
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

//ˢ��
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

//����<<,�������
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

//����<<,�������
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