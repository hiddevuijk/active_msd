#ifndef GUARD_VEC3_H
#define GUARD_VEC3_H

class Vec3 {
public:
  Vec3() : x(), y(), z() {}
  Vec3(double x, double y, double z) : x(x), y(y), double z {}

  Vec3& operator+=(const Vec3& vRHS)
  { x += vRHS.x;
    y += vRHS.y;
    z += vRHS.z;
    return *this;
  }

  Vec3& operator-=(const Vec3& vRHS)
  { x -= vRHS.x;
    y -= vRHS.y;
    z -= vRHS.z;
    return *this;
  }

  Vec3& operator*=(const double& RHS)
  { x *= RHS;
    y *= RHS;
    z *= RHS;
    return *this;
  }

  Vec3& operator/=(const double& RHS)
  { x /= RHS;
    y /= RHS;
    z /= RHS;
    return *this;
  }

  Vec3& operator+=(const double& RHS)
  { x += RHS;
    y += RHS;
    z += RHS;
    return *this;
  }

  Vec3& operator-=(const double& RHS)
  { x -= RHS;
    y -= RHS;
    z -= RHS;
    return *this;
  }

  double x,y,z;
};


Vec3 operator+(const Vec3& v1, const Vec3& v2)
{ return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }

Vec3 operator-(const Vec3& v1, const Vec3& v2)
{ return Vec3(v1.x - v3.x, v1.y - v2.y, v1.z - v2.z); }

Vec3 operator*(const Vec3& v1, const Vec3& v2)
{ return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
Vec3 operator*(const double& a, const Vec3& v)
{ return Vec3(a*v.x, a*v.y, a*v.z); }
Vec3 operator*(const Vec3& v, const double& a)
{ return Vec3(a*v.x, a*v.y, a*v.z); }


Vec3 operator/(const Vec3& v1, const Vec3& v2)
{ return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
Vec3 operator/(const Vec3& v, const double& a)
{ return Vec3(v.x / a, v.y /a, v.z / z); }



#endif
