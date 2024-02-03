#pragma once

#ifndef OBJECT
#define OBJECT
#endif

#include"Constants.h"
#include"Force.h"
#include<string>
#include<vector>

using namespace std;

struct Acceleration		//加速度结构体
{
	double magnitude_x;		//x分量
	double magnitude_y;		//y分量
};

struct Velocity		//速度结构体
{
	double magnitude_x;		//x分量
	double magnitude_y;		//y分量
};

class Object
{
private:
	string m_name;		//名称
	vector<class Force> m_force_source;		//施力
	vector<class Force> m_force_target;		//受力
	double m_mass;		//质量
	Acceleration m_acceleration;	//加速度
	Velocity m_velocity;	 //速度
	double m_x;		//x坐标
	double m_y;		//y坐标

	Acceleration AccelerationOrthogonalDecomposition_x(Acceleration acceleration);		//加速度的正交分解(x轴)
	Acceleration AccelerationOrthogonalDecomposition_y(Acceleration acceleration);		//加速度的正交分解(y轴)
	Velocity VelocityOrthogonalDecomposition_x(Velocity velocity);		//速度的正交分解(x轴)
	Velocity VelocityOrthogonalDecomposition_y(Velocity velocity);		//速度的正交分解(y轴)
	Force ForceSynthesis();		//力的合成
	Acceleration AccelerationSynthesis();	  //加速度的合成
	//Velocity VelocitySynthesis();		//速度的合成
public:
	Object(string name, vector<Force> force_source, vector<Force> force_target, double mass, Acceleration acceleration, Velocity velocity, double x, double y);		//构造函数
	Object();	  //空物体构造函数
	~Object();		//析构函数
	string Name();		//获取名称
	void Stress(Force force);	  //施力
	void Stressed(Force force);		//受力
	void Update();		//刷新
};

