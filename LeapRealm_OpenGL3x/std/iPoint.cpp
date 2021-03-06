#include "iPoint.h"

#include "iStd.h"

iPoint::iPoint()
{
	x = 0;
	y = 0;
}

iPoint::iPoint(const iPoint& p)
{
	x = p.x;
	y = p.y;
}

iPoint::iPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}
 
bool iPoint::operator==(const iPoint& p)
{
	return x == p.x && y == p.y;
}

bool iPoint::operator!=(const iPoint& p)
{
	return x != p.x || y != p.y;
}

iPoint& iPoint::operator=(const iPoint& p)
{
	x = p.x;
	y = p.y;

	return *this;
}

iPoint iPoint::operator+(const iPoint& p)
{
	iPoint r;
	r.x = x + p.x;
	r.y = y + p.y;

	return r;
}

iPoint& iPoint::operator+=(const iPoint& p)
{
	x += p.x;
	y += p.y;

	return *this;
}

iPoint iPoint::operator-(const iPoint& p)
{
	iPoint r;
	r.x = x - p.x;
	r.y = y - p.y;

	return r;
}

iPoint& iPoint::operator-=(const iPoint& p)
{
	x -= p.x;
	y -= p.y;

	return *this;
}

iPoint iPoint::operator*(float s)
{
	iPoint r;
	r.x = x * s;
	r.y = y * s;

	return r;
}

iPoint& iPoint::operator*=(float s)
{
	x *= s;
	y *= s;

	return *this;
}

iPoint iPoint::operator/(float s)
{
	iPoint r;
	r.x = x / s;
	r.y = y / s;

	return r;
}

iPoint& iPoint::operator/=(float s)
{
	x /= s;
	y /= s;

	return *this;
}

float iPoint::length()
{
	return sqrtf(x * x + y * y);
}

iPoint iPointMake(float x, float y)
{
	iPoint r;
	r.x = x;
	r.y = y;

	return r;
}

float iPointLength(iPoint p)
{
	return sqrtf(p.x * p.x + p.y * p.y);
}

float iPointDistance(iPoint p0, iPoint p1)
{
	return sqrtf((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
}

iPoint iPointRotate(iPoint p, iPoint pivot, float degree)
{
	while (degree < 0.0f)
		degree += 360.0f;

	while (degree > 360.0f)
		degree -= 360.0f;

	float sinr = sinDeg(degree);
	float cosr = cosDeg(degree);

	iPoint r;
	r.x = pivot.x + (p.x - pivot.x) * cosr - (p.y - pivot.y) * sinr;
	r.y = pivot.y + (p.x - pivot.x) * sinr + (p.y - pivot.y) * cosr;

	return r;
}

float iPointAngle(const iPoint& v1, const iPoint& v2, const iPoint& v3)
{
	float a2 = (v1.x - v3.x) * (v1.x - v3.x) + (v1.y - v3.y) * (v1.y - v3.y);
	float b2 = (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
	float c2 = (v2.x - v3.x) * (v2.x - v3.x) + (v2.y - v3.y) * (v2.y - v3.y);
	float degree = acos((b2 + c2 - a2) / sqrtf(4 * b2 * c2)) * 180 / M_PI;
	if (v3.y > v1.y)
		degree = 360 - degree;
	return degree;
}

float setDegree(float& degree, iPoint att, iPoint def, float spin, float dt)
{
	float d = 360 - iPointAngle(iPointMake(1, 0), iPointZero, def - att);
	float diff = d - degree;
	if (diff < 0) diff += 360;
	if (diff > 180) diff -= 360;

	float tDegree = degree + diff;
	if (degree < tDegree)
	{
		degree += 360 * dt;
		if (degree > tDegree)
			degree = tDegree;
	}
	else if (degree > tDegree)
	{
		degree -= 360 * dt;
		if (degree < tDegree)
			degree = tDegree;
	}

	return diff;
}

float linear(float s, float e, float r)
{
	return s + (e - s) * r;
}

iPoint linear(iPoint s, iPoint e, float r)
{
	return s + (e - s) * r;
}

float easeIn(float s, float e, float r)
{
	return s + (e - s) * sinDeg(90.0f * r);
}

iPoint easeIn(iPoint s, iPoint e, float r)
{
	return s + (e - s) * sinDeg(90.0f * r);
}

float easeOut(float s, float e, float r)
{
	return s + (e - s) * (1.0f - cosDeg(90.0f * r));
}

iPoint easeOut(iPoint s, iPoint e, float r)
{
	return s + (e - s) * (1.0f - cosDeg(90.0f * r));
}

float easeInOut(float s, float e, float r)
{
	if (r < 0.5f)
		return easeIn(s, s + (e - s) / 2.0f, r * 2.0f);
	return easeOut(s + (e - s) / 2.0f, e, r * 2.0f - 1.0f);
}

iPoint easeInOut(iPoint s, iPoint e, float r)
{
	if (r < 0.5f)
		return easeIn(s, s + (e - s) / 2.0f, r * 2.0f);
	return easeOut(s + (e - s) / 2.0f, e, r * 2.0f - 1.0f);
}

bool movePoint(iPoint& p, iPoint sp, iPoint ep, float speedDt)
{
	iPoint v = (ep - sp);
	v /= iPointLength(v);

	v *= speedDt;

	if (p.x < ep.x)
	{
		p.x += v.x;
		if (p.x > ep.x)
			p.x = ep.x;
	}
	else if (p.x > ep.x)
	{
		p.x += v.x;
		if (p.x < ep.x)
			p.x = ep.x;
	}

	if (p.y < ep.y)
	{
		p.y += v.y;
		if (p.y > ep.y)
			p.y = ep.y;
	}
	else if (p.y > ep.y)
	{
		p.y += v.y;
		if (p.y < ep.y)
			p.y = ep.y;
	}

	return p == ep;
}

iPoint normalize(iPoint p)
{
	return p / iPointLength(p);
}
