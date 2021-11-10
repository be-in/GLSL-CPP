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

#define GLSL_PI_2F 6.283185307179586476925286766559f
#define GLSL_PI_2D 6.283185307179586476925286766559
#define GLSL_IPI_2F 0.15915494309189533576888376337251f
#define GLSL_IPI_2D 0.15915494309189533576888376337251

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

  /*template<typename Field, typename Vals, int ind0, int ind1>
  class glsl_field2 {
  public:
    GLSL_INLINE Field () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; return r; }
    GLSL_INLINE Field operator () () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; return r; }
    GLSL_INLINE void operator = (Field value) { ((Vals*)this)[ind0] = ((Vals*)&value)[0]; ((Vals*)this)[ind1] = ((Vals*)&value)[1]; }
  };

  template<typename Field, typename Vals, int ind0, int ind1, int ind2>
  class glsl_field3 {
  public:
    GLSL_INLINE operator Field () { Field r; ((Vals*)&r)[0] = (Vals*)this[ind0]; ((Vals*)&r)[1] = (Vals*)this[ind1]; ((Vals*)&r)[2] = (Vals*)this[ind2]; return r; }
    GLSL_INLINE Field operator () () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; ((Vals*)&r)[2] = ((Vals*)this)[ind2]; return r; }
    GLSL_INLINE void operator = (Field value) { (Vals*)this[ind0] = ((Vals*)&value)[0]; (Vals*)this[ind1] = ((Vals*)&value)[1]; (Vals*)this[ind2] = ((Vals*)&value)[2]; }
  };

  template<typename Field, typename Vals, int ind0, int ind1, int ind2, int ind3>
  class glsl_field4 {
  public:
    GLSL_INLINE operator Field () { Field r; ((Vals*)&r)[0] = (Vals*)this[ind0]; ((Vals*)&r)[1] = (Vals*)this[ind1]; ((Vals*)&r)[2] = (Vals*)this[ind2]; ((Vals*)&r)[3] = (Vals*)this[ind3]; return r; }
    GLSL_INLINE Field operator () () { Field r; ((Vals*)&r)[0] = ((Vals*)this)[ind0]; ((Vals*)&r)[1] = ((Vals*)this)[ind1]; ((Vals*)&r)[2] = ((Vals*)this)[ind2]; ((Vals*)&r)[3] = (Vals*)this[ind3]; return r; }
    GLSL_INLINE void operator = (Field value) { (Vals*)this[ind0] = ((Vals*)&value)[0]; (Vals*)this[ind1] = ((Vals*)&value)[1]; (Vals*)this[ind2] = ((Vals*)&value)[2]; (Vals*)this[ind3] = ((Vals*)&value)[3]; }
  };*/

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
      //glsl_field2<vec2, float, 0, 0> xx;
      //glsl_field2<vec2, float, 0, 1> xy;
      //glsl_field4<_vec4, float, 0, 1, 0, 1> xyxy;
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
      //glsl_field4<dvec4, double, 0, 1, 0, 1> xyxy;
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
      //glsl_field2<vec2, float, 0, 1> xy;
      //glsl_field2<vec2, float, 0, 2> xz;
      //glsl_field2<vec2, float, 1, 2> yz;
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
      //glsl_field2<dvec2, double, 0, 1> xy;
      //glsl_field2<dvec2, double, 0, 2> xz;
      //glsl_field2<dvec2, double, 1, 2> yz;
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
      //glsl_field2<vec2, float, 0, 1> xy;
      //glsl_field2<vec2, float, 0, 2> xz;
      //glsl_field2<vec2, float, 1, 2> yz;
      //glsl_field4<vec4, float, 0, 2, 0, 2> xzxz;
      //glsl_field4<vec4, float, 1, 1, 3, 3> yyww;
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
      //glsl_field2<dvec2, double, 0, 1> xy;
      //glsl_field2<dvec2, double, 0, 2> xz;
      //glsl_field2<dvec2, double, 1, 2> yz;
      //glsl_field4<dvec4, double, 0, 2, 0, 2> xzxz;
      //glsl_field4<dvec4, double, 1, 1, 3, 3> yyww;
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
    GLSL_INLINE dvec4(T a, T b, T c, T d) { x = (double)a; y = (float)b; z = (double)c; w = (double)d; }
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

	GLSL_INLINE float sin(float a);
	GLSL_INLINE vec2 sin(vec2 a) { return vec2(sin(a.x),sin(a.y)); }
	GLSL_INLINE vec3 sin(vec3 a) { return vec3(sin(a.x),sin(a.y),sin(a.z)); }
	GLSL_INLINE vec4 sin(vec4 a) { return vec4(sin(a.x),sin(a.y),sin(a.z),sin(a.w)); }

	GLSL_INLINE float cos(float a);
	GLSL_INLINE vec2 cos(vec2 a) { return vec2(cos(a.x),cos(a.y)); }
	GLSL_INLINE vec3 cos(vec3 a) { return vec3(cos(a.x),cos(a.y),cos(a.z)); }
	GLSL_INLINE vec4 cos(vec4 a) { return vec4(cos(a.x),cos(a.y),cos(a.z),cos(a.w)); }

	GLSL_INLINE int min(int a, int b) { return a < b ? a : b; }
	GLSL_INLINE float min(float a, float b) { return a < b ? a : b; }
	GLSL_INLINE vec2 min(vec2 a, vec2 b) { return vec2(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y); }
	GLSL_INLINE vec3 min(vec3 a, vec3 b) { return vec3(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z); }

  GLSL_INLINE double min(double a, double b) { return a < b ? a : b; }
  GLSL_INLINE dvec3 min(dvec3 a, dvec3 b) { return dvec3(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z); }

	GLSL_INLINE int max(int a, int b) { return a > b ? a : b; }
  GLSL_INLINE float max(float a, float b) { return a > b ? a : b; }
  GLSL_INLINE vec2 max(vec2 a, vec2 b) { return vec2(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y); }
  GLSL_INLINE vec3 max(vec3 a, vec3 b) { return vec3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z); }

  GLSL_INLINE double max(double a, double b) { return a > b ? a : b; }
  GLSL_INLINE dvec3 max(dvec3 a, dvec3 b) { return dvec3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z); }

  GLSL_INLINE int clamp(int a, int b, int c) { return a < b ? b : (a > c ? c : a); }
  GLSL_INLINE float clamp(float a, float b, float c) { return a < b ? b : (a > c ? c : a); }
  GLSL_INLINE vec2 clamp(vec2 a, vec2 b, vec2 c) { return vec2(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y)); }
  GLSL_INLINE vec3 clamp(vec3 a, vec3 b, vec3 c) { return vec3(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z)); }
  GLSL_INLINE vec4 clamp(vec4 a, vec4 b, vec4 c) { return vec4(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z), clamp(a.w, b.w, c.w)); }

  GLSL_INLINE double clamp(double a, double b, double c) { return a < b ? b : (a > c ? c : a); }
  GLSL_INLINE dvec3 clamp(dvec3 a, dvec3 b, dvec3 c) { return dvec3(clamp(a.x, b.x, c.x), clamp(a.y, b.y, c.y), clamp(a.z, b.z, c.z)); }

  GLSL_INLINE int mix(int a, int b, float c) { return (a)*(1.0f-c)+b*c; }
  GLSL_INLINE float mix(float a, float b, float c) { return (a)*(1.0f-c)+b*c; }
  GLSL_INLINE vec2 mix(vec2 a, vec2 b, float c) { float cn = (1.0 - c); return vec2((a.x) * cn + b.x * c, (a.y) * cn + b.y * c); }
  GLSL_INLINE vec3 mix(vec3 a, vec3 b, float c) { float cn = (1.0 - c); return vec3((a.x) * cn + b.x * c, (a.y) * cn + b.y * c, (a.z) * cn + b.z * c); }

	GLSL_INLINE dvec3 mix(dvec3 a, dvec3 b, double c) { double cn = (1.0 - c); return dvec3((a.x) * cn + b.x * c, (a.y) * cn + b.y * c, (a.z) * cn + b.z * c); }

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
		if (a==0) return 0;
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
		if (_a==0) return 0;
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
}

#endif // GLSL_MATH_H_INCLUDED