// designed by Panteleymonov Aleksandr Konstantinovich 2020

#ifndef GLSL_MATH_H_INCLUDED
#define GLSL_MATH_H_INCLUDED

#if defined(_MSC_VER)

#define GLSL_INLINE __forceinline
....
#elif defined(__GNUC__) || defined(__GNUG__)

#define GLSL_INLINE __inline__ __attribute__((always_inline))

#elif defined(__clang__)

#define GLSL_INLINE __attribute__((always_inline))

#endif

#define MAX_SINE_ITER 8

#define GLSL_PIF 3.1415926535897932384626433832795f
#define GLSL_PID 3.1415926535897932384626433832795
#define GLSL_PI_2F 6.283185307179586476925286766559f
#define GLSL_PI_2D 6.283185307179586476925286766559
#define GLSL_IPI_2F 0.15915494309189533576888376337251f
#define GLSL_IPI_2D 0.15915494309189533576888376337251

#define DEG_TO_RADF 0.01745329251994329576923690768489f
#define DEG_TO_RADD 0.01745329251994329576923690768489
#define RAD_TO_DEGF 57.295779513082320876798154814105f
#define RAD_TO_DEGD 57.295779513082320876798154814105

namespace glsl {

  struct ivec2;
  struct vec2;
  struct vec3;
  struct vec4;
  struct dvec2;
  struct dvec3;
  struct dvec4;

  /*struct _vec4 {
	public:
		float x;
		float y;
		float z;
		float w;
  };*/

  template<typename Field, typename Vals, int ind0, int ind1>
  class glsl_field2 {
  public:
    //GLSL_INLINE Field () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; return r; }
    GLSL_INLINE Field operator () () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; return r; }
    GLSL_INLINE void operator = (Field value) { ((Vals*)this)[ind0] = ((Vals*)&value)[0]; ((Vals*)this)[ind1] = ((Vals*)&value)[1]; }
  };

  template<typename Field, typename Vals, int ind0, int ind1, int ind2>
  class glsl_field3 {
  public:
    //GLSL_INLINE operator Field () { Field r; ((Vals*)&r)[0] = (Vals*)this[ind0]; ((Vals*)&r)[1] = (Vals*)this[ind1]; ((Vals*)&r)[2] = (Vals*)this[ind2]; return r; }
    GLSL_INLINE Field operator () () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; ((Vals*)&r)[2] = ((Vals*)this)[ind2]; return r; }
    GLSL_INLINE void operator = (Field value) { (Vals*)this[ind0] = ((Vals*)&value)[0]; (Vals*)this[ind1] = ((Vals*)&value)[1]; (Vals*)this[ind2] = ((Vals*)&value)[2]; }
  };

  template<typename Field, typename Vals, int ind0, int ind1, int ind2, int ind3>
  class glsl_field4 {
  public:
    //GLSL_INLINE operator Field () { Field r; ((Vals*)&r)[0] = (Vals*)this[ind0]; ((Vals*)&r)[1] = (Vals*)this[ind1]; ((Vals*)&r)[2] = (Vals*)this[ind2]; ((Vals*)&r)[3] = (Vals*)this[ind3]; return r; }
    GLSL_INLINE Field operator () () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; ((Vals*)&r)[2] = ((Vals*)this)[ind2]; ((Vals*)&r)[3] = (Vals*)this[ind3]; return r; }
    GLSL_INLINE void operator = (Field value) { (Vals*)this[ind0] = ((Vals*)&value)[0]; (Vals*)this[ind1] = ((Vals*)&value)[1]; (Vals*)this[ind2] = ((Vals*)&value)[2]; (Vals*)this[ind3] = ((Vals*)&value)[3]; }
  };

#define VEC3_FIELDS2(a,b,c) glsl_field2<vec2, a, 0, b> x##c; glsl_field2<vec2, a, 1, b> y##c; glsl_field2<vec2, a, 2, b> z##c;
#define VEC3_FIELDS3X(a,b,c) glsl_field3<vec3, a, 0, 0, b> xx##c; glsl_field3<vec3, a, 0, 1, b> xy##c; glsl_field3<vec3, a, 0, 2, b> xz##c;
#define VEC3_FIELDS3Y(a,b,c) glsl_field3<vec3, a, 1, 0, b> yx##c; glsl_field3<vec3, a, 1, 1, b> yy##c; glsl_field3<vec3, a, 1, 2, b> yz##c;
#define VEC3_FIELDS3Z(a,b,c) glsl_field3<vec3, a, 2, 0, b> zx##c; glsl_field3<vec3, a, 2, 1, b> zy##c; glsl_field3<vec3, a, 2, 2, b> zz##c;
#define VEC3_FIELDS3(a,b,c) VEC3_FIELDS3X(a,b,c) VEC3_FIELDS3Y(a,b,c) VEC3_FIELDS3Z(a,b,c)
#define VEC4_FIELDS2(a,b,c) glsl_field2<vec2, a, 0, b> x##c; glsl_field2<vec2, a, 1, b> y##c; glsl_field2<vec2, a, 2, b> z##c; glsl_field2<vec2, a, 3, b> w##c;
#define VEC4_FIELDS3X(a,b,c) glsl_field3<vec3, a, 0, 0, b> xx##c; glsl_field3<vec3, a, 0, 1, b> xy##c; glsl_field3<vec3, a, 0, 2, b> xz##c; glsl_field3<vec3, a, 0, 3, b> xw##c;
#define VEC4_FIELDS3Y(a,b,c) glsl_field3<vec3, a, 1, 0, b> yx##c; glsl_field3<vec3, a, 1, 1, b> yy##c; glsl_field3<vec3, a, 1, 2, b> yz##c; glsl_field3<vec3, a, 1, 3, b> yw##c;
#define VEC4_FIELDS3Z(a,b,c) glsl_field3<vec3, a, 2, 0, b> zx##c; glsl_field3<vec3, a, 2, 1, b> zy##c; glsl_field3<vec3, a, 2, 2, b> zz##c; glsl_field3<vec3, a, 2, 3, b> zw##c;
#define VEC4_FIELDS3W(a,b,c) glsl_field3<vec3, a, 3, 0, b> wx##c; glsl_field3<vec3, a, 3, 1, b> wy##c; glsl_field3<vec3, a, 3, 2, b> wz##c; glsl_field3<vec3, a, 3, 3, b> ww##c;
#define VEC4_FIELDS3(a,b,c) VEC4_FIELDS3X(a,b,c) VEC4_FIELDS3Y(a,b,c) VEC4_FIELDS3Z(a,b,c) VEC4_FIELDS3W(a,b,c)

  struct ivec2 {
  public:
    union {
      int x;
      int r;
      int s;
    };
    union {
      int y;
      int g;
      int t;
    };

    GLSL_INLINE ivec2() {}
    template<typename T>
    GLSL_INLINE ivec2(T a, T b) { x = (int)a; y = (int)b; }
    GLSL_INLINE ivec2(int a) { x = a; y = a; }

    GLSL_INLINE const ivec2 operator+(const int& a) const { return ivec2(x + a, y + a); }
    GLSL_INLINE const ivec2 operator+(const ivec2& a) const { return ivec2(x + a.x, y + a.y); }
    GLSL_INLINE ivec2 operator+=(const ivec2& a) { x += a.x; y += a.y; return *this; }
    GLSL_INLINE const ivec2 operator-(const ivec2& a) const { return ivec2(x - a.x, y - a.y); }
    GLSL_INLINE const ivec2 operator*(const int& a) const { return ivec2(x * a, y * a); }
    GLSL_INLINE const ivec2 operator*(const float& a) const { return ivec2(x * a, y * a); }
    GLSL_INLINE const ivec2 operator/(const int& a) const { return ivec2(x / a, y / a); }
    GLSL_INLINE const bool operator!=(const ivec2& a) const { return (x != a.x) || (y != a.y); }
  };

  struct vec2 {
  public:
    union {
      float x;
      float r;
      float s;
      glsl_field2<vec2, float, 0, 0> xx;
      glsl_field2<vec2, float, 0, 1> xy;
      glsl_field2<vec2, float, 1, 1> yy;
      glsl_field2<vec2, float, 1, 0> yx;
    };
    union {
      float y;
      float g;
      float t;
    };

    GLSL_INLINE vec2() {}
    template<typename T>
    GLSL_INLINE vec2(T a, T b) { x = (float)a; y = (float)b; }
    GLSL_INLINE vec2(float a) { x = a; y = a; }
    //GLSL_INLINE vec2(_vec4 a) { x = a.x; y = a.y; }

    GLSL_INLINE const vec2 operator+(const float& a) const { return vec2(x + a, y + a); }
    GLSL_INLINE const vec2 operator-(const float& a) const { return vec2(x - a, y - a); }
    GLSL_INLINE const vec2 operator*(const float& a) const { return vec2(x * a, y * a); }
    GLSL_INLINE const vec2 operator/(const float& a) const { float r = 1. / a; return vec2(x * r, y * r); }
    GLSL_INLINE const vec2 operator+(const vec2& a) const { return vec2(x + a.x, y + a.y); }
    GLSL_INLINE const vec2 operator-(const vec2& a) const { return vec2(x - a.x, y - a.y); }
    GLSL_INLINE const vec2 operator*(const vec2& a) const { return vec2(x * a.x, y * a.y); }
    GLSL_INLINE const vec2 operator/(const vec2& a) const { return vec2(x / a.x, y / a.y); }

    GLSL_INLINE vec2 operator+=(const float& a) { x += a; y += a; return *this; }
    GLSL_INLINE vec2 operator-=(const float& a) { x -= a; y -= a; return *this; }
    GLSL_INLINE vec2 operator*=(const float& a) { x *= a; y *= a; return *this; }
    GLSL_INLINE vec2 operator/=(const float& a) { float r = 1. / a; x *= r; y *= r;return *this; }
    GLSL_INLINE vec2 operator+=(const vec2& a) { x += a.x; y += a.y; return *this; }
    GLSL_INLINE vec2 operator-=(const vec2& a) { x -= a.x; y -= a.y; return *this; }
    GLSL_INLINE vec2 operator*=(const vec2& a) { x *= a.x; y *= a.y; return *this; }
    GLSL_INLINE vec2 operator/=(const vec2& a) { x /= a.x; y /= a.y; return *this; }

    //GLSL_INLINE vec3 operator=(const dvec3& a) { x = a.x; y = a.y; z = a.z; return *this; }
    GLSL_INLINE bool operator==(const vec2& a) { return (x == a.x && y == a.y); }
    GLSL_INLINE bool operator!=(const vec2& a) { return (x != a.x || y != a.y); }
  };

  struct dvec2 {
  public:
    union {
      double x;
      double r;
      double s;
      glsl_field2<vec2, double, 0, 0> xx;
      glsl_field2<vec2, double, 0, 1> xy;
      glsl_field2<vec2, double, 1, 1> yy;
      glsl_field2<vec2, double, 1, 0> yx;
    };
    union {
      double y;
      double g;
      double t;
    };

    GLSL_INLINE dvec2() {}
    template<typename T>
    GLSL_INLINE dvec2(T a, T b) { x = (double)a; y = (double)b; }
    GLSL_INLINE dvec2(double a) { x = a; y = a; }

    GLSL_INLINE const dvec2 operator-(const float& a) const { return dvec2(x - a, y - a); }
    GLSL_INLINE const dvec2 operator+(const double& a) const { return dvec2(x + a, y + a); }
    GLSL_INLINE const dvec2 operator-(const double& a) const { return dvec2(x - a, y - a); }
    GLSL_INLINE const dvec2 operator*(const double& a) const { return dvec2(x * a, y * a); }
    GLSL_INLINE const dvec2 operator/(const double& a) const { double r = 1. / a; return dvec2(x * r, y * r); }
    GLSL_INLINE const dvec2 operator+(const dvec2& a) const { return dvec2(x + a.x, y + a.y); }
    GLSL_INLINE const dvec2 operator-(const dvec2& a) const { return dvec2(x - a.x, y - a.y); }
    GLSL_INLINE const dvec2 operator*(const dvec2& a) const { return dvec2(x * a.x, y * a.y); }
    GLSL_INLINE const dvec2 operator/(const dvec2& a) const { return dvec2(x / a.x, y / a.y); }

    GLSL_INLINE dvec2 operator+=(const double& a) { x += a; y += a; return *this; }
    GLSL_INLINE dvec2 operator-=(const double& a) { x -= a; y -= a; return *this; }
    GLSL_INLINE dvec2 operator*=(const double& a) { x *= a; y *= a; return *this; }
    GLSL_INLINE dvec2 operator/=(const double& a) { double r = 1. / a; x *= r; y *= r; return *this; }
    GLSL_INLINE dvec2 operator+=(const dvec2& a) { x += a.x; y += a.y; return *this; }
    GLSL_INLINE dvec2 operator-=(const dvec2& a) { x -= a.x; y -= a.y; return *this; }
    GLSL_INLINE dvec2 operator*=(const dvec2& a) { x *= a.x; y *= a.y; return *this; }
    GLSL_INLINE dvec2 operator/=(const dvec2& a) { x /= a.x; y /= a.y; return *this; }

    GLSL_INLINE dvec2 operator=(const vec2& a) { x = a.x; y = a.y; return *this; }
    GLSL_INLINE bool operator==(const dvec2& a) { return (x == a.x && y == a.y); }
    GLSL_INLINE bool operator!=(const dvec2& a) { return (x != a.x || y != a.y); }
  };

  struct vec3 {
  public:
    union {
      float x;
      float r;
      float s;
			VEC3_FIELDS2(float,0,x)
			VEC3_FIELDS2(float,1,y)
			VEC3_FIELDS2(float,2,z)
			VEC3_FIELDS3(float,0,x)
			VEC3_FIELDS3(float,1,y)
			VEC3_FIELDS3(float,2,z)
    };
    union {
      float y;
      float g;
      float t;
    };
    union {
      float z;
      float b;
      float p;
    };

    vec3() {}
    template<typename T>
    GLSL_INLINE vec3(T a, T b, T c) { x = (float)a; y = (float)b; z = (float)c; }
    GLSL_INLINE vec3(float a) { x = a; y = a; z = a; }
    GLSL_INLINE vec3(vec2 a, float b) { x = a.x; y = a.y; z = b; }
    GLSL_INLINE vec3(float a, vec2 b) { x = a; y = b.x; z = b.y; }

    GLSL_INLINE const vec3 operator+(const float& a) const { return vec3(x + a, y + a, z + a); }
    GLSL_INLINE const vec3 operator-(const float& a) const { return vec3(x - a, y - a, z - a); }
    GLSL_INLINE const vec3 operator*(const float& a) const { return vec3(x * a, y * a, z * a); }
    GLSL_INLINE const vec3 operator/(const float& a) const { float r = 1. / a; return vec3(x * r, y * r, z * r); }
    GLSL_INLINE const vec3 operator+(const vec3& a) const { return vec3(x + a.x, y + a.y, z + a.z); }
    GLSL_INLINE const vec3 operator-(const vec3& a) const { return vec3(x - a.x, y - a.y, z - a.z); }
    GLSL_INLINE const vec3 operator*(const vec3& a) const { return vec3(x * a.x, y * a.y, z * a.z); }
    GLSL_INLINE const vec3 operator/(const vec3& a) const { return vec3(x / a.x, y / a.y, z / a.z); }

    GLSL_INLINE vec3 operator+=(const float& a) { x += a; y += a; z += a; return *this; }
    GLSL_INLINE vec3 operator-=(const float& a) { x -= a; y -= a; z -= a; return *this; }
    GLSL_INLINE vec3 operator*=(const float& a) { x *= a; y *= a; z *= a; return *this; }
    GLSL_INLINE vec3 operator/=(const float& a) { float r = 1. / a; x *= r; y *= r; z *= r; return *this; }
    GLSL_INLINE vec3 operator+=(const vec3& a) { x += a.x; y += a.y; z += a.z; return *this; }
    GLSL_INLINE vec3 operator-=(const vec3& a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
    GLSL_INLINE vec3 operator*=(const vec3& a) { x *= a.x; y *= a.y; z *= a.z; return *this; }
    GLSL_INLINE vec3 operator/=(const vec3& a) { x /= a.x; y /= a.y; z /= a.z; return *this; }

    //GLSL_INLINE vec3 operator=(const dvec3& a) { x = a.x; y = a.y; z = a.z; return *this; }
    GLSL_INLINE bool operator==(const vec3& a) { return (x == a.x && y == a.y && z == a.z); }
    GLSL_INLINE bool operator!=(const vec3& a) { return (x != a.x || y != a.y || z != a.z); }
  };

  struct dvec3 {
  public:
    union {
      double x;
      double r;
      double s;
			VEC3_FIELDS2(double,0,x)
			VEC3_FIELDS2(double,1,y)
			VEC3_FIELDS2(double,2,z)
			VEC3_FIELDS3(double,0,x)
			VEC3_FIELDS3(double,1,y)
			VEC3_FIELDS3(double,2,z)
    };
    union {
      double y;
      double g;
      double t;
    };
    union {
      double z;
      double b;
      double p;
    };

    dvec3() {}
    template<typename T>
    GLSL_INLINE dvec3(T a, T b, T c) { x = (double)a; y = (double)b; z = (double)c; }
    GLSL_INLINE dvec3(double a) { x = a; y = a; z = a; }
    GLSL_INLINE dvec3(dvec2 a, double b) { x = a.x; y = a.y; z = b; }
    GLSL_INLINE dvec3(double a, dvec2 b) { x = a; y = b.x; z = b.y; }

    GLSL_INLINE const dvec3 operator-(const float& a) const { return dvec3(x - a, y - a, z - a); }
    GLSL_INLINE const dvec3 operator+(const double& a) const { return dvec3(x + a, y + a, z + a); }
    GLSL_INLINE const dvec3 operator-(const double& a) const { return dvec3(x - a, y - a, z - a); }
    GLSL_INLINE const dvec3 operator*(const double& a) const { return dvec3(x * a, y * a, z * a); }
    GLSL_INLINE const dvec3 operator/(const double& a) const { double r = 1. / a; return dvec3(x * r, y * r, z * r); }
    GLSL_INLINE const dvec3 operator+(const dvec3& a) const { return dvec3(x + a.x, y + a.y, z + a.z); }
    GLSL_INLINE const dvec3 operator-(const dvec3& a) const { return dvec3(x - a.x, y - a.y, z - a.z); }
    GLSL_INLINE const dvec3 operator*(const dvec3& a) const { return dvec3(x * a.x, y * a.y, z * a.z); }
    GLSL_INLINE const dvec3 operator/(const dvec3& a) const { return dvec3(x / a.x, y / a.y, z / a.z); }

    GLSL_INLINE dvec3 operator+=(const double& a) { x += a; y += a; z += a; return *this; }
    GLSL_INLINE dvec3 operator-=(const double& a) { x -= a; y -= a; z -= a; return *this; }
    GLSL_INLINE dvec3 operator*=(const double& a) { x *= a; y *= a; z *= a; return *this; }
    GLSL_INLINE dvec3 operator/=(const double& a) { double r = 1. / a; x *= r; y *= r; z *= r; return *this; }
    GLSL_INLINE dvec3 operator+=(const dvec3& a) { x += a.x; y += a.y; z += a.z; return *this; }
    GLSL_INLINE dvec3 operator-=(const dvec3& a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
    GLSL_INLINE dvec3 operator*=(const dvec3& a) { x *= a.x; y *= a.y; z *= a.z; return *this; }
    GLSL_INLINE dvec3 operator/=(const dvec3& a) { x /= a.x; y /= a.y; z /= a.z; return *this; }

    GLSL_INLINE dvec3 operator=(const vec3& a) { x = a.x; y = a.y; z = a.z; return *this; }
    GLSL_INLINE bool operator==(const dvec3& a) { return (x == a.x && y == a.y && z == a.z); }
    GLSL_INLINE bool operator!=(const dvec3& a) { return (x != a.x || y != a.y || z != a.z); }
  };

  struct vec4 {
  public:
    union {
      float x;
      float r;
      float s;
			VEC4_FIELDS2(float,0,x)
			VEC4_FIELDS2(float,1,y)
			VEC4_FIELDS2(float,2,z)
			VEC4_FIELDS2(float,3,w)
			VEC4_FIELDS3(float,0,x)
			VEC4_FIELDS3(float,1,y)
			VEC4_FIELDS3(float,2,z)
			VEC4_FIELDS3(float,3,w)
    };
    union {
      float y;
      float g;
      float t;
    };
    union {
      float z;
      float b;
      float p;
    };
    union {
      float w;
      float a;
      float q;
    };

    vec4() {}
    template<typename T>
    GLSL_INLINE vec4(T a, T b, T c, T d) { x = (float)a; y = (float)b; z = (float)c; w = (float)d; }
    //GLSL_INLINE vec4(_vec4 a) { x = a.x; y = a.y; z = a.z; w = a.w; }
    GLSL_INLINE vec4(float a) { x = a; y = a; z = a; w = a; }
    GLSL_INLINE vec4(vec2 a, vec2 b) { x = a.x; y = a.y; z = b.x; w = b.y; }
    GLSL_INLINE vec4(vec3 a, float b) { x = a.x; y = a.y; z = a.z; w = b; }

    GLSL_INLINE const vec4 operator+(const float& a) const { return vec4(x + a, y + a, z + a, w + a); }
    GLSL_INLINE const vec4 operator-(const float& a) const { return vec4(x - a, y - a, z - a, w - a); }
    GLSL_INLINE const vec4 operator*(const float& a) const { return vec4(x * a, y * a, z * a, w * a); }
    GLSL_INLINE const vec4 operator/(const float& a) const { float _a = 1.0f / a; return vec4(x * _a, y * _a, z * _a, w * _a); }
    GLSL_INLINE const vec4 operator+(const vec4& a) const { return vec4(x + a.x, y + a.y, z + a.z, w + a.w); }
    GLSL_INLINE const vec4 operator-(const vec4& a) const { return vec4(x - a.x, y - a.y, z - a.z, w - a.w); }
    GLSL_INLINE const vec4 operator*(const vec4& a) const { return vec4(x * a.x, y * a.y, z * a.z, w * a.w); }
    GLSL_INLINE const vec4 operator/(const vec4& a) const { return vec4(x / a.x, y / a.y, z / a.z, w / a.w); }

    GLSL_INLINE vec4 operator+=(const float& a) { x += a; y += a; z += a; w += a; return *this; }
    GLSL_INLINE vec4 operator-=(const float& a) { x -= a; y -= a; z -= a; w -= a; return *this; }
    GLSL_INLINE vec4 operator*=(const float& a) { x *= a; y *= a; z *= a; w *= a; return *this; }
    GLSL_INLINE vec4 operator/=(const float& a) { x /= a; y /= a; z /= a; w /= a; return *this; }
    GLSL_INLINE vec4 operator+=(const vec4& a) { x += a.x; y += a.y; z += a.z; w += a.w; return *this; }
    GLSL_INLINE vec4 operator-=(const vec4& a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }
    GLSL_INLINE vec4 operator*=(const vec4& a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; return *this; }
    GLSL_INLINE vec4 operator/=(const vec4& a) { x /= a.x; y /= a.y; z /= a.z; w /= a.w; return *this; }

    GLSL_INLINE bool operator==(const vec4& a) { return (x == a.x && y == a.y && z == a.z && w == a.w); }
    GLSL_INLINE bool operator!=(const vec4& a) { return (x != a.x || y != a.y || z != a.z || w != a.w); }
  };

  struct dvec4 {
  public:
    union {
      double x;
      double r;
      double s;
			VEC4_FIELDS2(double,0,x)
			VEC4_FIELDS2(double,1,y)
			VEC4_FIELDS2(double,2,z)
			VEC4_FIELDS2(double,3,w)
			VEC4_FIELDS3(double,0,x)
			VEC4_FIELDS3(double,1,y)
			VEC4_FIELDS3(double,2,z)
			VEC4_FIELDS3(double,3,w)
    };
    union {
      double y;
      double g;
      double t;
    };
    union {
      double z;
      double b;
      double p;
    };
    union {
      double w;
      double a;
      double q;
    };

    dvec4() {}
    template<typename T>
    GLSL_INLINE dvec4(T a, T b, T c, T d) { x = (double)a; y = (double)b; z = (double)c; w = (double)d; }
    GLSL_INLINE dvec4(double a) { x = a; y = a; z = a; w = a; }

    GLSL_INLINE const dvec4 operator+(const double& a) const { return dvec4(x + a, y + a, z + a, w + a); }
    GLSL_INLINE const dvec4 operator-(const double& a) const { return dvec4(x - a, y - a, z - a, w - a); }
    GLSL_INLINE const dvec4 operator*(const double& a) const { return dvec4(x * a, y * a, z * a, w * a); }
    GLSL_INLINE const dvec4 operator/(const double& a) const { double _a = 1.0f / a; return dvec4(x * _a, y * _a, z * _a, w * _a); }
    GLSL_INLINE const dvec4 operator+(const dvec4& a) const { return dvec4(x + a.x, y + a.y, z + a.z, w + a.w); }
    GLSL_INLINE const dvec4 operator-(const dvec4& a) const { return dvec4(x - a.x, y - a.y, z - a.z, w - a.w); }
    GLSL_INLINE const dvec4 operator*(const dvec4& a) const { return dvec4(x * a.x, y * a.y, z * a.z, w * a.w); }
    GLSL_INLINE const dvec4 operator/(const dvec4& a) const { return dvec4(x / a.x, y / a.y, z / a.z, w / a.w); }

    GLSL_INLINE dvec4 operator+=(const double& a) { x += a; y += a; z += a; w += a; return *this; }
    GLSL_INLINE dvec4 operator-=(const double& a) { x -= a; y -= a; z -= a; w -= a; return *this; }
    GLSL_INLINE dvec4 operator*=(const double& a) { x *= a; y *= a; z *= a; w *= a; return *this; }
    GLSL_INLINE dvec4 operator/=(const double& a) { x /= a; y /= a; z /= a; w /= a; return *this; }
    GLSL_INLINE dvec4 operator+=(const dvec4& a) { x += a.x; y += a.y; z += a.z; w += a.w; return *this; }
    GLSL_INLINE dvec4 operator-=(const dvec4& a) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }
    GLSL_INLINE dvec4 operator*=(const dvec4& a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; return *this; }
    GLSL_INLINE dvec4 operator/=(const dvec4& a) { x /= a.x; y /= a.y; z /= a.z; w /= a.w; return *this; }

    GLSL_INLINE bool operator==(const dvec4& a) { return (x == a.x && y == a.y && z == a.z && w == a.w); }
    GLSL_INLINE bool operator!=(const dvec4& a) { return (x != a.x || y != a.y || z != a.z || w != a.w); }
  };

  GLSL_INLINE vec2 operator+(const float& a, const vec2& b) { return vec2(a + b.x, a + b.y); }
  GLSL_INLINE vec2 operator-(const float& a, const vec2& b) { return vec2(a - b.x, a - b.y); }
  GLSL_INLINE vec2 operator*(const float& a, const vec2& b) { return vec2(a * b.x, a * b.y); }
  GLSL_INLINE vec2 operator/(const float& a, const vec2& b) { return vec2(a / b.x, a / b.y); }

  GLSL_INLINE dvec2 operator+(const double& a, const dvec2& b) { return dvec2(a + b.x, a + b.y); }
  GLSL_INLINE dvec2 operator-(const double& a, const dvec2& b) { return dvec2(a - b.x, a - b.y); }
  GLSL_INLINE dvec2 operator*(const double& a, const dvec2& b) { return dvec2(a * b.x, a * b.y); }
  GLSL_INLINE dvec2 operator/(const double& a, const dvec2& b) { return dvec2(a / b.x, a / b.y); }

  GLSL_INLINE vec3 operator+(const float& a, const vec3& b) { return vec3(a + b.x, a + b.y, a + b.z); }
  GLSL_INLINE vec3 operator-(const float& a, const vec3& b) { return vec3(a - b.x, a - b.y, a - b.z); }
  GLSL_INLINE vec3 operator*(const float& a, const vec3& b) { return vec3(a * b.x, a * b.y, a * b.z); }
  GLSL_INLINE vec3 operator/(const float& a, const vec3& b) { return vec3(a / b.x, a / b.y, a / b.z); }

  GLSL_INLINE dvec3 operator+(const double& a, const dvec3& b) { return dvec3(a + b.x, a + b.y, a + b.z); }
  GLSL_INLINE dvec3 operator-(const double& a, const dvec3& b) { return dvec3(a - b.x, a - b.y, a - b.z); }
  GLSL_INLINE dvec3 operator*(const double& a, const dvec3& b) { return dvec3(a * b.x, a * b.y, a * b.z); }
  GLSL_INLINE dvec3 operator/(const double& a, const dvec3& b) { return dvec3(a / b.x, a / b.y, a / b.z); }

  GLSL_INLINE vec4 operator+(const float& a, const vec4& b) { return vec4(a + b.x, a + b.y, a + b.z, a + b.w); }
  GLSL_INLINE vec4 operator-(const float& a, const vec4& b) { return vec4(a - b.x, a - b.y, a - b.z, a - b.w); }
  GLSL_INLINE vec4 operator*(const float& a, const vec4& b) { return vec4(a * b.x, a * b.y, a * b.z, a * b.w); }
  GLSL_INLINE vec4 operator/(const float& a, const vec4& b) { return vec4(a / b.x, a / b.y, a / b.z, a / b.w); }

  GLSL_INLINE dvec4 operator+(const double& a, const dvec4& b) { return dvec4(a + b.x, a + b.y, a + b.z, a + b.w); }
  GLSL_INLINE dvec4 operator-(const double& a, const dvec4& b) { return dvec4(a - b.x, a - b.y, a - b.z, a - b.w); }
  GLSL_INLINE dvec4 operator*(const double& a, const dvec4& b) { return dvec4(a * b.x, a * b.y, a * b.z, a * b.w); }
  GLSL_INLINE dvec4 operator/(const double& a, const dvec4& b) { return dvec4(a / b.x, a / b.y, a / b.z, a / b.w); }

  GLSL_INLINE float radians(float a) { return a*DEG_TO_RADF; }
  GLSL_INLINE vec2 radians(vec2 a) { return a*DEG_TO_RADF; }
  GLSL_INLINE vec3 radians(vec3 a) { return a*DEG_TO_RADF; }
  GLSL_INLINE vec4 radians(vec4 a) { return a*DEG_TO_RADF; }

  GLSL_INLINE double radians(double a) { return a*DEG_TO_RADF; }
  GLSL_INLINE dvec2 radians(dvec2 a) { return a*DEG_TO_RADF; }
  GLSL_INLINE dvec3 radians(dvec3 a) { return a*DEG_TO_RADF; }
  GLSL_INLINE dvec4 radians(dvec4 a) { return a*DEG_TO_RADF; }

  GLSL_INLINE float degrees(float a) { return a*RAD_TO_DEGF; }
  GLSL_INLINE vec2 degrees(vec2 a) { return a*RAD_TO_DEGF; }
  GLSL_INLINE vec3 degrees(vec3 a) { return a*RAD_TO_DEGF; }
  GLSL_INLINE vec4 degrees(vec4 a) { return a*RAD_TO_DEGF; }

  GLSL_INLINE double degrees(double a) { return a*RAD_TO_DEGF; }
  GLSL_INLINE dvec2 degrees(dvec2 a) { return a*RAD_TO_DEGF; }
  GLSL_INLINE dvec3 degrees(dvec3 a) { return a*RAD_TO_DEGF; }
  GLSL_INLINE dvec4 degrees(dvec4 a) { return a*RAD_TO_DEGF; }

	GLSL_INLINE float sqrt(float a);
	GLSL_INLINE double sqrt(double a);

	GLSL_INLINE float floor(float a);
	GLSL_INLINE vec2 floor(vec2 a) { return vec2(floor(a.x), floor(a.y)); }
	GLSL_INLINE vec3 floor(vec3 a) { return vec3(floor(a.x), floor(a.y), floor(a.z)); }
	GLSL_INLINE vec4 floor(vec4 a) { return vec4(floor(a.x), floor(a.y), floor(a.z), floor(a.w)); }

	GLSL_INLINE double floor(double a);
	GLSL_INLINE dvec2 floor(dvec2 a) { return dvec2(floor(a.x), floor(a.y)); }

	GLSL_INLINE float fract(float a) { return a - floor(a); }
	GLSL_INLINE vec2 fract(vec2 a) { return vec2(fract(a.x), fract(a.y)); }
	GLSL_INLINE vec3 fract(vec3 a) { return vec3(fract(a.x), fract(a.y), fract(a.z)); }
	GLSL_INLINE vec4 fract(vec4 a) { return vec4(fract(a.x), fract(a.y), fract(a.z), fract(a.w)); }

	GLSL_INLINE double fract(double a) { return a - floor(a); }
	GLSL_INLINE dvec2 fract(dvec2 a) { return dvec2(fract(a.x), fract(a.y)); }
	GLSL_INLINE dvec3 fract(dvec3 a) { return dvec3(fract(a.x), fract(a.y), fract(a.z)); }
	GLSL_INLINE dvec4 fract(dvec4 a) { return dvec4(fract(a.x), fract(a.y), fract(a.z), fract(a.w)); }

	GLSL_INLINE int mod(int a, int b)  { return a - b * floor(a*1.f/b); }
	GLSL_INLINE float mod(float a, float b) { return a - b * floor(a/b); }
	GLSL_INLINE vec2 mod(vec2 a, float b) { return vec2(mod(a.x,b),mod(a.y,b)); }
	GLSL_INLINE vec3 mod(vec3 a, float b) { return vec3(mod(a.x,b),mod(a.y,b),mod(a.z,b)); }
	GLSL_INLINE vec4 mod(vec4 a, float b) { return vec4(mod(a.x,b),mod(a.y,b),mod(a.z,b),mod(a.w,b)); }

	GLSL_INLINE float sin(float a);
	GLSL_INLINE vec2 sin(vec2 a) { return vec2(sin(a.x),sin(a.y)); }
	GLSL_INLINE vec3 sin(vec3 a) { return vec3(sin(a.x),sin(a.y),sin(a.z)); }
	GLSL_INLINE vec4 sin(vec4 a) { return vec4(sin(a.x),sin(a.y),sin(a.z),sin(a.w)); }

	GLSL_INLINE float cos(float a);
	GLSL_INLINE vec2 cos(vec2 a) { return vec2(cos(a.x),cos(a.y)); }
	GLSL_INLINE vec3 cos(vec3 a) { return vec3(cos(a.x),cos(a.y),cos(a.z)); }
	GLSL_INLINE vec4 cos(vec4 a) { return vec4(cos(a.x),cos(a.y),cos(a.z),cos(a.w)); }

	GLSL_INLINE float atan(float y, float x);
	GLSL_INLINE vec2 atan(vec2 y, vec2 x) { return vec2(atan(y.x, x.x),atan(y.y, x.y)); }
	GLSL_INLINE vec3 atan(vec3 y, vec3 x) { return vec3(atan(y.x, x.x),atan(y.y, x.y),atan(y.z, x.z)); }
	GLSL_INLINE vec4 atan(vec4 y, vec4 x) { return vec4(atan(y.x, x.x),atan(y.y, x.y),atan(y.z, x.z),atan(y.w, x.w)); }

	GLSL_INLINE int min(int a, int b) { return a < b ? a : b; }
	GLSL_INLINE float min(float a, float b) { return a < b ? a : b; }
	GLSL_INLINE vec2 min(vec2 a, vec2 b) { return vec2(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y); }
	GLSL_INLINE vec3 min(vec3 a, vec3 b) { return vec3(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z); }
	GLSL_INLINE vec4 min(vec4 a,vec4 b) { return vec4(a.x<b.x ? a.x:b.x, a.y<b.y ? a.y:b.y, a.z<b.z ? a.z:b.z, a.w<b.w ? a.w:b.w); }

  GLSL_INLINE double min(double a, double b) { return a < b ? a : b; }
  GLSL_INLINE dvec2 min(dvec2 a, dvec2 b) { return dvec2(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y); }
  GLSL_INLINE dvec3 min(dvec3 a, dvec3 b) { return dvec3(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z); }
  GLSL_INLINE dvec4 min(dvec4 a, dvec4 b) { return dvec4(a.x<b.x ? a.x:b.x, a.y<b.y ? a.y:b.y, a.z<b.z ? a.z:b.z, a.w<b.w ? a.w:b.w); }

	GLSL_INLINE int max(int a, int b) { return a > b ? a : b; }
  GLSL_INLINE float max(float a, float b) { return a > b ? a : b; }
  GLSL_INLINE vec2 max(vec2 a, vec2 b) { return vec2(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y); }
  GLSL_INLINE vec3 max(vec3 a, vec3 b) { return vec3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z); }
  GLSL_INLINE vec4 max(vec4 a, vec4 b) { return vec4(a.x>b.x ? a.x:b.x, a.y>b.y ? a.y:b.y, a.z>b.z ? a.z:b.z, a.w>b.w ? a.w:b.w); }

  GLSL_INLINE double max(double a, double b) { return a > b ? a : b; }
  GLSL_INLINE dvec2 max(dvec2 a, dvec2 b) { return dvec2(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y); }
  GLSL_INLINE dvec3 max(dvec3 a, dvec3 b) { return dvec3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z); }
  GLSL_INLINE dvec4 max(dvec4 a, dvec4 b) { return dvec4(a.x>b.x ? a.x:b.x, a.y>b.y ? a.y:b.y, a.z>b.z ? a.z:b.z, a.w>b.w ? a.w:b.w); }

  GLSL_INLINE int clamp(int a, int b, int c) { return a < b ? b : (a > c ? c : a); }
  GLSL_INLINE float clamp(float a, float b, float c) { return a < b ? b : (a > c ? c : a); }
  GLSL_INLINE vec2 clamp(vec2 a, vec2 b, vec2 c) { return vec2(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y)); }
  GLSL_INLINE vec3 clamp(vec3 a, vec3 b, vec3 c) { return vec3(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z)); }
  GLSL_INLINE vec4 clamp(vec4 a, vec4 b, vec4 c) { return vec4(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z), clamp(a.w, b.w, c.w)); }

  GLSL_INLINE double clamp(double a, double b, double c) { return a < b ? b : (a > c ? c : a); }
  GLSL_INLINE dvec2 clamp(dvec2 a, dvec2 b, dvec2 c) { return dvec2(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y)); }
  GLSL_INLINE dvec3 clamp(dvec3 a, dvec3 b, dvec3 c) { return dvec3(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z)); }
  GLSL_INLINE dvec4 clamp(dvec4 a, dvec4 b, dvec4 c) { return dvec4(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z), clamp(a.w, b.w, c.w)); }

  GLSL_INLINE int mix(const int a, const int b, const int c) { return (a)*(1.0f-c)+b*c; }
  GLSL_INLINE float mix(const float a, const float b, const float c) { return (a)*(1.0f-c)+b*c; }
  GLSL_INLINE vec2 mix(const vec2& a, const vec2& b, const float c) { float cn = (1.f - c); return vec2((a.x) * cn + b.x * c, (a.y) * cn + b.y * c); }
  GLSL_INLINE vec3 mix(const vec3& a, const vec3& b, const float c) { float cn = (1.f - c); return vec3((a.x) * cn + b.x * c, (a.y) * cn + b.y * c, (a.z) * cn + b.z * c); }
  GLSL_INLINE vec4 mix(const vec4& a, const vec4& b, const float c) { float cn = (1.f - c); return vec4((a.x) * cn + b.x * c, (a.y) * cn + b.y * c, (a.z) * cn + b.z * c, (a.w) * cn + b.w * c); }

  GLSL_INLINE double mix(const double a, const double b, const double c) { return (a)*(1.0f-c)+b*c; }
  GLSL_INLINE dvec2 mix(const dvec2& a, const dvec2& b, const double c) { double cn = (1.0 - c); return dvec2((a.x) * cn + b.x * c, (a.y) * cn + b.y * c); }
	GLSL_INLINE dvec3 mix(const dvec3& a, const dvec3& b, const double c) { double cn = (1.0 - c); return dvec3((a.x) * cn + b.x * c, (a.y) * cn + b.y * c, (a.z) * cn + b.z * c); }
  GLSL_INLINE dvec4 mix(const dvec4& a, const dvec4& b, const double c) { double cn = (1.0 - c); return dvec4((a.x) * cn + b.x * c, (a.y) * cn + b.y * c, (a.z) * cn + b.z * c, (a.w) * cn + b.w * c); }

  GLSL_INLINE float dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
  GLSL_INLINE float dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
  GLSL_INLINE float dot(vec4 a, vec4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

  GLSL_INLINE double dot(dvec2 a, dvec2 b) { return a.x * b.x + a.y * b.y; }
  GLSL_INLINE double dot(dvec3 a, dvec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
  GLSL_INLINE double dot(dvec4 a, dvec4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

  GLSL_INLINE float magnitude(vec2 a) { return a.x * a.x + a.y * a.y; }
  GLSL_INLINE float magnitude(vec3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
  GLSL_INLINE float magnitude(vec4 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

  GLSL_INLINE double magnitude(dvec2 a) { return a.x * a.x + a.y * a.y; }
  GLSL_INLINE double magnitude(dvec3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
  GLSL_INLINE double magnitude(dvec4 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

  GLSL_INLINE vec2 reflect(vec2 a, vec2 b) { return a - 2.f * dot(b, a) * b; }
  GLSL_INLINE vec3 reflect(vec3 a, vec3 b) { return a - 2.f * dot(b, a) * b; }
  GLSL_INLINE vec4 reflect(vec4 a, vec4 b) { return a - 2.f * dot(b, a) * b; }

  GLSL_INLINE dvec2 reflect(dvec2 a, dvec2 b) { return a - 2.0 * dot(b, a) * b; }
  GLSL_INLINE dvec3 reflect(dvec3 a, dvec3 b) { return a - 2.0 * dot(b, a) * b; }
  GLSL_INLINE dvec4 reflect(dvec4 a, dvec4 b) { return a - 2.0 * dot(b, a) * b; }

  GLSL_INLINE float length(vec2 a) { return sqrt(magnitude(a)); }
  GLSL_INLINE float length(vec3 a) { return sqrt(magnitude(a)); }
  GLSL_INLINE float length(vec4 a) { return sqrt(magnitude(a)); }

  GLSL_INLINE double length(dvec2 a) { return sqrt(magnitude(a)); }
  GLSL_INLINE double length(dvec3 a) { return sqrt(magnitude(a)); }
  GLSL_INLINE double length(dvec4 a) { return sqrt(magnitude(a)); }

  GLSL_INLINE float distance(vec2 a, vec2 b) { return sqrt(magnitude(a - b)); }
  GLSL_INLINE float distance(vec3 a, vec3 b) { return sqrt(magnitude(a - b)); }
  GLSL_INLINE float distance(vec4 a, vec4 b) { return sqrt(magnitude(a - b)); }

  GLSL_INLINE double distance(dvec2 a, dvec2 b) { return sqrt(magnitude(a - b)); }
  GLSL_INLINE double distance(dvec3 a, dvec3 b) { return sqrt(magnitude(a - b)); }
  GLSL_INLINE double distance(dvec4 a, dvec4 b) { return sqrt(magnitude(a - b)); }

  GLSL_INLINE vec2 normalize(vec2 a) { return a * (1.f / length(a)); }
  GLSL_INLINE vec3 normalize(vec3 a) { return a * (1.f / length(a)); }
  GLSL_INLINE vec4 normalize(vec4 a) { return a * (1.f / length(a)); }

  GLSL_INLINE dvec2 normalize(dvec2 a) { return a * (1.0 / length(a)); }
  GLSL_INLINE dvec3 normalize(dvec3 a) { return a * (1.0 / length(a)); }
  GLSL_INLINE dvec4 normalize(dvec4 a) { return a * (1.0 / length(a)); }

  GLSL_INLINE vec3 cross(vec3 a, vec3 b) { return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
  GLSL_INLINE dvec3 cross(dvec3 a, dvec3 b) { return dvec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

	struct IEE754FLOAT {
		unsigned int mant : 23;
		unsigned int exp : 8;
		unsigned int sign : 1;
	};

	struct IEE754DOUBLE {
		unsigned long long mant : 52;
		unsigned long long exp : 11;
		unsigned long long sign : 1;
	};

	union conv4b {
		float valfloat;
		int valint;
		unsigned int valuint;
		IEE754FLOAT varIEE;
	};

	union conv8b {
		double valdouble;
		long long vallong;
		unsigned long long valulong;
		IEE754DOUBLE varIEE;
	};

	GLSL_INLINE int abs(int a) { return a<0 ? -a : a; }
  GLSL_INLINE float abs(float a) { conv4b r; r.valfloat = a; r.valuint &= 0x7FFFFFFF; return r.valfloat; }
  GLSL_INLINE vec2 abs(vec2 a) { return vec2(abs(a.x), abs(a.y)); }
  GLSL_INLINE vec3 abs(vec3 a) { return vec3(abs(a.x), abs(a.y), abs(a.z)); }
	GLSL_INLINE vec4 abs(vec4 a) { return vec4(abs(a.x), abs(a.y),abs(a.z), abs(a.w)); }

  GLSL_INLINE double abs(double a) { conv8b r; r.valdouble = a; r.valulong &= 0x7FFFFFFFFFFFFFFF; return r.valdouble; }
  GLSL_INLINE dvec3 abs(dvec3 a) { return dvec3(abs(a.x), abs(a.y), abs(a.z)); }

	GLSL_INLINE float sqrt(float a)
	{
		if (a==0.f) return 0.f;
		conv4b c;
		conv4b al;
		c.valfloat=a;
		al.valuint=0x5f3504f3-(c.valuint>>1);
		float g=al.valfloat;
		float mr=g*(3.0f-c.valfloat*g*g);
		return 1.0/mr+a*mr*0.25;
	}

	GLSL_INLINE double sqrt(double _a)
	{
		if (_a==0.) return 0.;
		double a=_a;
		conv4b c;
		conv4b al;
		c.valfloat=a;
		al.valuint=0x5f3504f3-(c.valuint>>1);
		float g=al.valfloat;
		float mr=g*(3.0-a*g*g);
		double r=2.0/mr+a*mr*0.5;
		return r*0.25+a/r;
	}

	GLSL_INLINE float pow(float b, float e) {
    conv8b u;
    u.valdouble = b;
    u.vallong = (long long)(4606853616395542500L + e * (u.vallong - 4606853616395542500L));
    return u.valdouble;
	}

	GLSL_INLINE double pow(double b, double e) {
    conv8b u;
    u.valdouble = b;
    u.vallong = (long long)(4606853616395542500L + e * (u.vallong - 4606853616395542500L));
    return u.valdouble;
	}

	GLSL_INLINE float log2(float _a)
	{
		conv4b c;
		c.valfloat=_a;
		c.valfloat=((c.valint & 0x7F800000)>>23)-127;

		conv4b d;
		d.valfloat=_a;
		d.valint=(d.valint&0x007FFFFF) | 0x3F800000;

		float rez=((((((-3.4436006e-2f*d.valfloat)+3.1821337e-1f)*d.valfloat)-1.2315303f)*d.valfloat+2.5988452f)*d.valfloat-3.3241990f)*d.valfloat+3.1157899f;
		return (d.valfloat-1.0f)*rez+c.valfloat;
	}

	GLSL_INLINE float floor(float _a)
	{
		conv4b rd = *(conv4b*)&_a;
		if (rd.valint == 0) return 0;
		return ((rd.varIEE.mant | 0x00800000) >> clamp(127 + 23 - (int)rd.varIEE.exp,-31,31))*(1 - (((int)rd.varIEE.sign)<<1)) - (int)rd.varIEE.sign;
	}

	GLSL_INLINE double floor(double _a)
	{
		conv8b rd = *(conv8b*)&_a;
		if (rd.vallong == 0) return 0;
		int val0 = (1023 + 52 - (int)rd.varIEE.exp);
		return (long long)((rd.varIEE.mant | 0x0010000000000000) >> clamp(val0,-63,63))*(1 - (((int)rd.varIEE.sign)<<1)) - (long long)rd.varIEE.sign;
	}

	const float fastsindividef[]={0.5f, 1.0f/6.0f,1.0f/24.0f, 1.0f/120.0f,1.0f/720.0f, 1.0f/5040.0f, 1.0f/40320.0f,
			1.0f/362880.0f, 1.0f/3628800.0f, 1.0f/3.99168E7f, 1.0f/4.790016E8f, 1.0f/6.2270208E9f, 1.0f/8.717828912E10f, 1.0f/1.307674368E12f,
			(float)4.7794773323873852974382074911175e-14,(float)2.8114572543455207631989455830103e-15,0,0,0,0};
	const float fasttgdividef[]={1.0f/3,1.0f/5,1.0f/7,1.0f/9,1.0f/11,1.0f/13,1.0f/15,1.0f/17,1.0f/19,1.0f/21,1.0f/23,1.0f/25,1.0f/27,1.0f/29,1.0f/31,1.0f/33,1.0f/35};

	GLSL_INLINE float sin(float _a)
	{
		float a = (fract(_a*GLSL_IPI_2F + 0.5f)-0.5f) *GLSL_PI_2F;
		float b=a;
		a *= a;
		float _s=b;
		for (int i=0;i<MAX_SINE_ITER;i++) {
			b=(float)((-1.f) * b * a);
			_s+=(float)(b*fastsindividef[(i<<1)+1]);
		}
		return _s;
	}

	GLSL_INLINE float cos(float _a)
	{
		float a = (fract(_a * GLSL_IPI_2F + 0.5f)-0.5f) * GLSL_PI_2F;
		a *= a;
		float b = 1.f;
		float _c = b;
		for (int i=0; i<MAX_SINE_ITER; i++) {
			b=(float)((-1.f) * b * a);
			_c+=(float)(b*fastsindividef[(i<<1)]);
		}
		return _c;
	}

	GLSL_INLINE double sin(double _a)
	{
		double a = (fract(_a*GLSL_IPI_2D + 0.5)-0.5) *GLSL_PI_2D;
		double b = a;
		a *= a;
		double _s=b;
		for (int i=0;i<MAX_SINE_ITER;i++) {
			b=(double)((-1.0)*b * a);
			_s+=(double)(b*fastsindividef[(i<<1)+1]);
		}
		return _s;
	}

	GLSL_INLINE double cos(double _a)
	{
		double a = (fract(_a*GLSL_IPI_2D + 0.5)-0.5) *GLSL_PI_2D;
		a *= a;
		double b = a;
		double _c=1.0f;
		for (int i=0;i<MAX_SINE_ITER;i++) {
			b=(double)((-1.0) * b * a);
			_c+=(double)(b * fastsindividef[(i<<1)]);
		}
		return _c;
	}

	GLSL_INLINE float atan(float y, float x)
	{
		float _b;
		vec2 ab=abs(vec2(x,y));
		if (ab.y==ab.x) {
			_b = 0.78539816339744830961566084581988f;
		} else {
			float b = min(ab.x,ab.y)/max(ab.x,ab.y);
			if (b>0.4142135623730950488016887242097f) {
				if (ab.y>ab.x) {
					ab = ab*0.92387953251128675612818318939679f + vec2(-ab.y,ab.x)*0.3826834323650897717284599840304f;
					b = ab.x/ab.y;
				} else {
					ab = ab*0.92387953251128675612818318939679f + vec2(ab.y,-ab.x)*0.3826834323650897717284599840304f;
					b = ab.y/ab.x;
				}
				_b = b+0.39269908169872415480783042290994f;
			} else _b = b;
			float a = b*b;
			float* fds = (float*)fasttgdividef;
			float* fdse = (float*)fasttgdividef+8;
			while (fds<fdse) {
				b *= a; _b -= b*fds[0];
				b *= a; _b += b*fds[1];
				fds+=2;
			}
		}
		if (y*x<0) _b = -_b;
		float fs=0;
		if (ab.y>ab.x) {
			_b = -_b;
			fs = GLSL_PIF * 0.5f;
		} else if (x<0) fs = GLSL_PIF;
		return _b + (y<0 ? -fs : fs);
	}

	GLSL_INLINE double atan(double y, double x)
	{
		double _b;
		vec2 ab=abs(vec2(x,y));
		if (ab.y==ab.x) {
			_b = 0.78539816339744830961566084581988;
		} else {
			double b = min(ab.x,ab.y)/max(ab.x,ab.y);
			if (b>0.4142135623730950488016887242097) {
				if (ab.y>ab.x) {
					ab = ab*0.92387953251128675612818318939679 + vec2(-ab.y,ab.x)*0.3826834323650897717284599840304;
					b = ab.x/ab.y;
				} else {
					ab = ab*0.92387953251128675612818318939679 + vec2(ab.y,-ab.x)*0.3826834323650897717284599840304;
					b = ab.y/ab.x;
				}
				_b = b+0.39269908169872415480783042290994;
			} else _b = b;
			double a = b*b;
			float* fds = (float*)fasttgdividef;
			float* fdse = (float*)fasttgdividef+8;
			while (fds<fdse) {
				b *= a; _b -= b*fds[0];
				b *= a; _b += b*fds[1];
				fds+=2;
			}
		}
		if (y*x<0) _b = -_b;
		double fs=0;
		if (ab.y>ab.x) {
			_b = -_b;
			fs = GLSL_PID * 0.5;
		} else if (x<0) fs = GLSL_PID;
		return _b + (y<0 ? -fs : fs);
	}
}

#endif // GLSL_MATH_H_INCLUDED
