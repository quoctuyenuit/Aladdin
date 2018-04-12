#include "Stair.h"
#include"StaticObject.h"
#include"Aladdin.h"


Stair::Stair(int x, int y, int width, int height, Global::EDirection direct)
	:Object(x, y, width, height)
{
	this->_team = Global::Static;
	this->_id = Global::STAIR;
	this->_allow = true;
	this->_rectBound.update(x, y, width, height);
	this->_vx = this->_vy = 0;
	switch (direct)
	{
	case Global::Right:
	{
		this->_startStair = D3DXVECTOR2(x, y - height);
		this->_endStair = D3DXVECTOR2(x + width, y);
		break;
	}
	case Global::Left:
	{
		this->_startStair = D3DXVECTOR2(x, y);
		this->_endStair = D3DXVECTOR2(x + width, y - height);
		break;
	}
	}
	//Tính phương trình tổng quát của đường thẳng cầu thang
	this->_equation = this->getEquation(_startStair, _endStair);
}

Stair::~Stair()
{
}

std::vector<int> Stair::getEquation(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{
	std::vector<int> result;

	int a = point1.x - point2.x;
	int b = point1.y - point2.y;

	if (a != 0 && b != 0)
	{
		int uc = abs(a);
		while (b%uc != 0 || a%uc != 0)
		{
			uc--;
		}
		a /= uc;
		b /= uc;
	}
	int x0 = point1.x;
	int y0 = point1.y;
	//Vector pháp tuyến
	D3DXVECTOR2 n = D3DXVECTOR2(b, -a);
	result.push_back(n.x);
	result.push_back(n.y);
	result.push_back(-n.x*x0 - n.y*y0);

	return result;
}

D3DXVECTOR2 Stair::getIntersectionPoint(std::vector<int> equation1, std::vector<int> equation2)
{
	float a1 = equation1[0];
	float a2 = equation2[0];
	float b1 = equation1[1];
	float b2 = equation2[1];
	float c1 = equation1[2];
	float c2 = equation2[2];

	float x0 = std::numeric_limits<float>::infinity(), y0 = std::numeric_limits<float>::infinity();
	try
	{
		if (a1 == 0)
		{
			y0 = -c1 / b1;
			x0 = (-c2 - b2*y0) / a2;
		}
		else
		{
			y0 = ((a2*c1) / a1 - c2) / (b2 - (a2*b1) / a1);
			x0 = (-c1 - b1*y0) / a1;
		}
	}
	catch (const std::exception&)
	{
	}

	//Parse float to int
	x0 = (x0 - (int)x0 >= 0.5) ? (int)x0 +1 : (int)x0;
	y0 = (y0 - (int)y0 >= 0.5) ? (int)y0 + 1 : (int)y0;

	return D3DXVECTOR2(x0, y0);
}

void Stair::update(float detalTime)
{
	StaticObject::Instance()->addStair(this);
}

float Stair::getEquationValue(D3DXVECTOR2 M)
{
	//Lấy giá trị của một điểm trong phương trình dùng để xác định vị trí tương đối của điểm M so với đường thẳng
	return (this->_equation[0] * M.x + this->_equation[1] * M.y + this->_equation[2]);
}

Collision::ResultCollision Stair::processCollision(Object * obj)
{
	Collision::ResultCollision result;
	if (obj->getId() == Global::ALADDIN && !this->_allow)
		return result;

	D3DXVECTOR2 objectCurrentLocation = obj->getCurrentLocation();
	D3DXVECTOR2 objectNextLocation = D3DXVECTOR2(obj->getX() + obj->getVx(), obj->getY() + obj->getVy());
	
	std::vector<int> equationObject = this->getEquation(objectCurrentLocation, objectNextLocation);
	D3DXVECTOR2 intersectionPoint;
	if (equationObject[0] == 0 && equationObject[1] == 0)
		intersectionPoint = objectCurrentLocation;
	else
		intersectionPoint = this->getIntersectionPoint(this->_equation, equationObject);

	if (intersectionPoint.x < this->_x|| intersectionPoint.x > this->_x + this->_width ||
		objectCurrentLocation.y < this->_y - _height||
		((objectCurrentLocation.x < _x || objectCurrentLocation.x > _x+_width) &&
			(objectNextLocation.x < _x || objectNextLocation.x > _x+_width)))
		return result;

	if (this->getEquationValue(objectNextLocation) <= 0)
	{
		result.flag = true;
		result.intersectionPoint = intersectionPoint;

		switch (obj->getId())
		{
		case Global::ALADDIN:
		{
			int x = obj->getX() + obj->getVx();
			result.intersectionPoint.x = x;
			result.intersectionPoint.y = this->getResultY(x);

			if (x < this->_x || x > this->_x + this->_width)
			{
				result.intersectionPoint.y += 1;
			}
			Aladdin* aladdin = (Aladdin*)obj;
			aladdin->setGround();
			if (aladdin->getState() == Global::StopRun)
				aladdin->Stand();
			break;
		}
		default:
		{
			if (obj->getVx() == 0 && obj->getVy() == 0)
			{
				result.flag = false;
				return result;
			}
			ActionObject* acObject = (ActionObject*)obj;
			acObject->setGround();
			break;
		}
		}
	}

	return result;
}

int Stair::getResultY(int x)
{
	int a = this->_equation[0];
	int b = this->_equation[1];
	int c = this->_equation[2];
	//ax + by +c = 0

	return (-c - a*x) / b;
}

bool Stair::getAllow()
{
	return this->_allow;
}

void Stair::setAllow(bool allow)
{
	this->_allow = allow;
}
