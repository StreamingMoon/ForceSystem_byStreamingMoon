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
	string m_name;		//名称
	Object m_source;	//施力物体
	Object m_target;	//受力物体
	double m_magnitude_x;		//x方向大小
	double m_magnitude_y;		//y方向大小

public:
	Force ForceOrthogonalDecomposition_x(Force force);		//力的正交分解(x轴)
	Force ForceOrthogonalDecomposition_y(Force force);		//力的正交分解(y轴)
	Force(string name, Object source, Object target, double magnitude, int angle);		//构造函数
	Force(string name,Object source,Object target,double magnitude_x,double magnitude_y);	//构造函数(内部用)
	Force();	//空力构造函数
	~Force();		//析构函数
	Force ReactionForce();		//反作用力
	void Apply();	//应用
	string Name();		//获取名称
	Object Source();	//获取施力物体
	Object Target();	//获取受力物体
	double MagnitudeX();	//x分量
	double MagnitudeY();	//y分量
	Force operator+(Force force);	//重载+,合成力
};

