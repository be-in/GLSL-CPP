#include "glsl-cpp.h"
#include "graph.h"
//#include <cmath>

using namespace glsl;

#define hash(n) fract(abs(sin(n))*1399763.5453123f)
//#define hash(n) fract(mod(((n)*(n)*34.f+n),289.f)/289.f)
//#define hash(n) fract(fract((n)*0.31830988618379067153776752674503f)*fract((n)*0.15915494309189533576888376337251f)*265871.1723f)

vec2 NC0=vec2(1.0,136.0);
vec3 NC1=vec3(1.0,136.0,31.0);

inline vec2 getBL(vec3 pos) { return vec2(atan(pos.x,pos.z),atan(length(vec2(pos.x,pos.z)),pos.y))/3.1415f; }

vec2 sphereIntersect(vec3 ray,vec3 pos,float r)
{
    float r2=r*r;
    float cd = dot(pos,ray);
    vec3 p = ray * cd-pos;
    float t2 = dot(p,p);
    if (t2>=r2) return vec2(-1.0, -1.0);
    float d = sqrt(r2-t2);
    return vec2(- d,d) + cd;
}

vec3 sphereNormal(vec3 pos, vec3 surface)
{
    return normalize(surface-pos);
}

// Simple 2d interpolated noise for mercator projection, using local seed.
float sphereNoise2Ds(vec2 bl,float scale,float seed)
{
    bl = vec2(fract(bl.x*0.5f+0.5f), bl.y*scale);
    vec2 yc = floor(vec2(bl.y)+vec2(0.f,1.f));
    vec2 xc = floor(sin(3.1415f * yc/scale)*scale*2.0);
    vec4 p = vec4(xc,xc) * vec4(vec2(bl.x), fract(vec2(bl.x)+1.0f/max(vec2(1.f),xc)));
    vec3 f = fract(vec3(p.x, p.y, bl.y));
    f=f*f*(3.0f-2.0f*f);
    yc = (yc + vec2(scale)) * NC0.y;
    vec3 fn = 1.f-f;
    vec4 n= hash(floor(p)*NC0.x + vec4(yc,yc) +seed);
    return dot(n, vec4(fn.x,fn.y,f.x,f.y)*vec4(fn.z,f.z,fn.z,f.z));
}

vec2 sphereNoise2D2s(vec2 bl,float scale,vec2 seed)
{
    bl = vec2(fract(bl.x*0.5f+0.5f), bl.y*scale);
    vec2 yc = floor(vec2(bl.y)+vec2(0.f,1.f));
    vec2 xc = floor(sin(yc/scale * 3.1415f)*scale*2.0f);
    vec4 p = vec4(xc,xc)*vec4(vec2(bl.x,bl.x), fract(vec2(bl.x,bl.x)+1.0f/max(vec2(1.f),xc)));
    vec3 f = fract(vec3(p.x,p.y, bl.y));
    f=f*f*(3.0f-2.0f*f);
    yc = (yc + vec2(scale)) * NC0.y;
    vec3 fn = 1.f-f;
    p = floor(p)*NC0.x + vec4(yc,yc);
    vec4 n1= hash(p +seed.x);
    vec4 n2= hash(p +seed.y);
    p = vec4(fn.x,fn.y,f.x,f.y)*vec4(fn.z,f.z,fn.z,f.z);
    return vec2(dot(n1, p), dot(n2, p));
}

// Simple 2d interpolated distortion noise for mercator projection, using global seed.
float sphereNoise2Do(vec2 bl,float scale,float force,float seed)
{
    bl = bl+sphereNoise2D2s(bl,scale*2.0f,vec2(3.,20.))*force/scale;
    bl.y = clamp(bl.y,0.0f,1.0f);
    return sphereNoise2Ds(bl,scale,seed);
}

// Perlin distortion noise with increasing coefficient
float spherePerlinHalfds(vec2 bl,float scale,float force,float seed)
{
    return sphereNoise2Do(bl,16.0f*scale,force,seed)*0.05f
    +sphereNoise2Do(bl,8.0f*scale,force,seed)*0.15f+sphereNoise2Do(bl,4.0f*scale,force,seed)*0.2f
    +sphereNoise2Do(bl,2.0f*scale,force,seed)*0.25f+sphereNoise2Do(bl,scale,force,seed)*0.35f;
}

float spherePerlin(vec2 bl,float scale,float seed)
{
    return (sphereNoise2Ds(bl,128.0*scale,seed)+sphereNoise2Ds(bl,64.0*scale,seed)
     +sphereNoise2Ds(bl,32.0*scale,seed)+sphereNoise2Ds(bl,16.0*scale,seed)
     +sphereNoise2Ds(bl,8.0*scale,seed)+sphereNoise2Ds(bl,4.0*scale,seed)
     +sphereNoise2Ds(bl,2.0*scale,seed)*1.2+sphereNoise2Ds(bl,scale,seed)*1.2)*0.1;
}

float spherePerlinHalf(vec2 bl,float scale,float seed)
{
    return (sphereNoise2Ds(bl, 16.0*scale, seed)+sphereNoise2Ds(bl, 8.0*scale, seed)+sphereNoise2Ds(bl, 4.0*scale, seed)
     +sphereNoise2Ds(bl, 2.0*scale, seed)+sphereNoise2Ds(bl, scale, seed))*0.2;
}

vec3 wind3D(vec3 pos,float rings)
{
    vec3 f = fract(pos)-0.5;
    vec3 px = floor(pos);
    float r = length(pos);
    vec3 wind =vec3(0.);

    for (int z = -0;z<2;z++)
    for (int y = -0;y<2;y++)
    for (int x = -0;x<2;x++) {
        vec3 off = vec3(float(x),float(y),float(z));
        vec3 xyz = px + off;
        float p = dot(xyz,NC1);
        vec3 add = hash(vec3(p,p+30.0f,p+23.0f));
        vec3 fxyz = f + add*0.8-off;
        float ml = clamp(1.0f-length(fxyz)*1.5f,0.f,1.f);
        vec3 wp = normalize(pos - fxyz) * r - pos;
        float l1 = length(wp);
        float l2 = 1.-l1;
        vec3 w = normalize(cross(wp,pos));
        wind +=w*ml*clamp(0.5f-l1,0.f,1.f)*clamp(1.0f-l2*l2*l2,0.f,1.f);
    }
    return wind;
}

float atmosphere(vec3 pos, vec3 atmosSurface, vec3 ray, vec3 lnorm, float planetRadius, float atmosRadius, float atmosDepth)
{
    float wall = sqrt(atmosRadius*atmosRadius - planetRadius*planetRadius);
    float acc = clamp(atmosDepth/wall,0.0f,1.0f);
    acc = acc*pow(clamp(dot(lnorm,normalize(atmosSurface-pos)),0.0f,1.0f),0.4f);
    acc = acc*acc;
    acc = acc*acc;
    return acc;
}

vec3 sphereTexture(vec3 realSurface, vec3 ray, vec3 snorm,vec3 lnorm,float time)
{
    float bal = dot(snorm,lnorm);
    float light = 1.-clamp(bal,0.0f,1.0f);
    bal = clamp(-bal,0.0f,1.0f);
    bal = bal*bal;
    bal = bal*bal;
    light = 1.0-light*light;
    light = clamp(light+0.1f,0.f,1.f);

    vec2 bl = getBL(realSurface);

    float d = spherePerlinHalfds(bl,8.0f,0.5f,2.0f);
    d = clamp(1.0f-abs(d-0.5f)*10.0f,0.0f,1.0f) * clamp(spherePerlin(bl,2.5f,2.0f)*5.0f-1.6f,0.0f,1.0f);
    float mc = clamp(spherePerlinHalfds(bl,6.0f,0.5f,10.0f)*6.0f-2.4f, 0.0f, 1.0f);

    float f = spherePerlin(bl,4.0f,5.0f);
    f = mix(1.f-pow(1.f-f*1.7f,2.f), f*1.7f, 0.3f);
    f = f-d*d*d*0.2*1.7;

    vec3 col = clamp(mix(vec3(0.94f,0.63f,0.33f),vec3(1.0,0.85,0.57),f)*f,vec3(0.,0.,0.),vec3(1.,1.,1.));
    col = mix(col,mix(vec3(1.0f,0.5f,0.0f),vec3(1.0,0.8,0.33),mc),0.2);
    vec3 bac = vec3(0.1f,0.2f,0.5f) * dot(col,vec3(1.f))*bal;
    return col*light+bac;
}

vec2 cloudTexture(vec3 realSurface,float time)
{
   vec3 w = wind3D(realSurface*1.f,1.5f);
   w += wind3D(realSurface*2.f,1.5f)*0.2f;
   w += wind3D(realSurface*6.f,1.5f)*0.1f;
   vec2 bld = getBL(normalize(realSurface-w*1.4f));

   float d = spherePerlinHalf(bld, 6.0f, 14.0f);
   float c = spherePerlinHalf(bld, 192.0f, 16.0f);

   float f = clamp((d*d)*4.0f-c-0.5f,0.0f,1.0f);
   f = 1.f-f;
   return vec2(1.f-f*f,0.f);
}

int _PlanetPixel(float x,float y)
{
    vec3 ray = normalize(vec3(x,y,2.0f));
    vec3 color = vec3(0.f);
    float time = 0.0f;

    float dist=2.3;
    float rplanet = 1.0;
    float ratmos = 1.15;
    float rcloud = 1.005;
    vec3 spos = vec3(0.0f,0.0f,dist);
    //vec3 lpos = vec3(4.5,4.5,-9.0+dist);
    vec3 lpos = vec3(4.5f,4.5f,dist-2.0f);
    vec3 lnorm = normalize(lpos - spos);

    float dplanet = sphereIntersect(ray,spos,rplanet).x;
    vec2 dcloud = sphereIntersect(ray,spos,rcloud);
    float datmos = sphereIntersect(ray,spos,ratmos).x;
    if (dplanet>0.0) {
        vec3 ssurface = ray*dplanet;
        vec3 snorm = sphereNormal(spos,ssurface);
        vec3 lsnorm = normalize(lpos - ssurface);
        float pa = clamp((rplanet*rplanet - magnitude(ray * dot(ray,spos)-spos))*dist*50.f,0.f,1.f);
        color = mix(color,sphereTexture((ssurface-spos),ray,snorm,lsnorm,0.0f),pa);
    }
    if (datmos>0.0) {
        float adepth = dplanet>0.0 ? (dplanet-datmos)*1.2f : abs(dot(ray,spos)-datmos);
        vec3 ssurface = ray*datmos;
        float ap = atmosphere(spos, ssurface, ray, lnorm, rplanet, ratmos, adepth);
        color = mix(color,mix(vec3(1.0,0.96,0.7),vec3(1.0,0.96,0.7),ap),ap);
    }
    if (dcloud.x>0.0) {
        vec3 ssurface = ray*dcloud.x;
        vec3 snorm = sphereNormal(spos,ssurface);
        vec3 lsnorm = normalize(lpos - ssurface);
        vec2 al = cloudTexture((ssurface-spos+lsnorm*0.01f),time*0.2f);
        vec2 a = cloudTexture((ssurface-spos),time*0.2f);
        float emboss = a.x-al.x+0.05f;
        float light = 1.f-clamp(dot(snorm,lsnorm),0.0f,1.0f);
        light = 1.f-light*light;
        light = clamp(light+0.1f,0.f,1.f);
        color = mix(color,mix(vec3(0.9f,0.8f,0.6f),vec3(1.0f,0.9f,0.6f),a.y)*light,clamp(a.x,0.f,1.f))
            + vec3(clamp(emboss*0.2f,0.f,1.f)+clamp(emboss*0.3f*a.x+a.x*0.3f*light,0.f,1.f))*light;
    }

    color = clamp(color,vec3(0.f),vec3(1.f))*255.0f;
    return ARGB(0,color.z,color.y,color.x);
}

void PaintPlanet(int *buff, int w, int h)
{
    int *c=buff;
    float iw = 1.0/h;
    float ih = 1.0/h;
    for (int y=0;y<h;y++)
        for (int x=0;x<w;x++) {
            *c = _PlanetPixel((x-w*0.5)*iw*2.0f,y*ih*2.0f-1.0f);
            c++;
        }
}

int main()
{
    SetWindowSize(400,400);
    CreateWindow();

    //while (!WindowIsClose()) {
        PaintPlanet(ScreenBuffer, WindowWidth, WindowHeight);
        DrawScreenBuffer();
        CheckMessage();
    //}

    return 0;
}
