#ifndef	_SPHERE_H_
#define	_SPHERE_H_

#include <cmath>

#include "vec.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"

namespace edupt {

struct Sphere {
	double radius_;
	Vec position_;
	Color emission_;
	Color color_;
	ReflectionType reflection_type_;

	Sphere(const double radius, const Vec &position, const Color &emission, const Color &color, const ReflectionType reflection_type) :
	  radius_(radius), position_(position), emission_(emission), color_(color), reflection_type_(reflection_type) {}

	// 入力のrayに対する交差点までの距離を返す。交差しなかったら0を返す。
	// rayとの交差判定を行う。交差したらtrue,さもなくばfalseを返す。
	bool intersect(const Ray &ray, Hitpoint *hitpoint) const {
		const Vec p_o = position_ - ray.org_;
		const double b = dot(p_o, ray.dir_);
		const double D4 = b * b - dot(p_o, p_o) + radius_ * radius_;

		if (D4 < 0.0)
			return false;
		
		const double sqrt_D4 = sqrt(D4);
		const double t1 = b - sqrt_D4, t2 = b + sqrt_D4;
	
		if (t1 < kEPS && t2 < kEPS)
			return false;

		if (t1 > kEPS) {
			hitpoint->distance_ = t1;
		} else {
			hitpoint->distance_ = t2;
		}

		hitpoint->position_ = ray.org_ + hitpoint->distance_ * ray.dir_;
		hitpoint->normal_   = normalize(hitpoint->position_ - position_);
		return true;
	}
};

struct Polygon {
	Vec vertex[3];
	Vec normal[3];
	Polygon(const Vec *Vec) :
		vertex(){vertex[0] = Vec[0]; vertex[1] = Vec[1]; vertex[2] = Vec[2];};

	bool intersect(const Ray &ray, Hitpoint *hitpoint) const
	{
		Vec edge1, edge2;
		Vec pvec, tvec, qvec;
		double t, u, v;
		edge1 = vertex[1]-vertex[0];
		edge2 = vertex[2]-vertex[0];


		pvec = cross(ray.dir_, edge2);
		double det = dot(edge1, pvec);
		if(det > 0.001)
		{
			tvec = ray.org_ - vertex[0];
			u = dot(tvec, pvec);

			if( u <0.0f || u > det) return false;

			qvec = cross(tvec, edge1);
			v = dot(ray.dir_, qvec);
			if( v <0.0f || u + v > det) return false;
		}
		else if (det < -0.001)
		{
			tvec = ray.org_ - vertex[0];
			u = dot(tvec, pvec);

			if( u > 0.0f || u < det) return false;

			qvec = cross(tvec, edge1);
			v = dot(ray.dir_, qvec);
			if( v > 0.0f || u + v < det) return false;
		}
		else 
		{
			return false;
		}

		double inv_det = 1.0f/det;

		t = dot(edge2, qvec);
		t *= inv_det;
		u *= inv_det;
		v *= inv_det;

		hitpoint->distance_ = t;
		hitpoint->position_ = ray.org_ + ray.dir_* t ;
		//hitpoint->normal_ = 
		return true;
	}
};

struct Mesh {
	long num_polygons;
	Polygon *polygons;
	Color emission_;
	Color color_;
	ReflectionType reflection_type_;
	Mesh(const long num_polygons, Polygon *Polygons, const Color &emission, const Color &color, const ReflectionType reflection_type) :
		num_polygons(num_polygons), polygons(Polygons), emission_(emission), color_(color), reflection_type_(reflection_type){}

	bool intersect(const Ray &ray, Hitpoint *hitpoint) const {
		for(int i = 0; i< num_polygons; i++)
		{
			// NOTE 一番近い交点を求めること
			if(polygons[i].intersect(ray, hitpoint)) return true;
		}
		return false;
	}
};

};

#endif
