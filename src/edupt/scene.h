﻿#ifndef	_SCENE_H_
#define	_SCENE_H_

#include "constant.h"
#include "sphere.h"
#include "intersection.h"

namespace edupt {

// レンダリングするシーンデータ
const Sphere spheres[] = {
//	Sphere(1e5, Vec( 1e5+1, 40.8, 81.6), Color(),      Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE), // 左
//	Sphere(1e5, Vec(-1e5+99, 40.8, 81.6),Color(),      Color(0.25, 0.25, 0.75), REFLECTION_TYPE_DIFFUSE), // 右
//	Sphere(1e5, Vec(50, 40.8, 1e5),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 奥
//	Sphere(1e5, Vec(50, 1e5, 81.6),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 床
//	Sphere(1e5, Vec(50, -1e5+81.6, 81.6),Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 天井
//	Sphere(20,Vec(65, 20, 20),           Color(),      Color(0.25, 0.75, 0.25), REFLECTION_TYPE_DIFFUSE), // 緑球
//	Sphere(16.5,Vec(27, 16.5, 47),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_SPECULAR), // 鏡
//	Sphere(16.5,Vec(77, 16.5, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_REFRACTION), //ガラス
//	Sphere(15.0,Vec(50.0, 90.0, 81.6),   Color(36,36,36), Color(),              REFLECTION_TYPE_DIFFUSE), //照明
	Sphere(1e5, Vec( 1e5+1, 40.8, 81.6), Color(),      Color(0.75, 0.25, 0.25), REFLECTION_TYPE_DIFFUSE), // 左
	Sphere(1e5, Vec(-1e5+99, 40.8, 81.6),Color(),      Color(0.25, 0.25, 0.75), REFLECTION_TYPE_DIFFUSE), // 右
	Sphere(1e5, Vec(50, 40.8, 1e5),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 奥
	Sphere(1e5, Vec(50, 1e5, 81.6),      Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 床
	Sphere(1e5, Vec(50, -1e5+81.6, 81.6),Color(),      Color(0.75, 0.75, 0.75), REFLECTION_TYPE_DIFFUSE), // 天井
	Sphere(16.5,Vec(50.0, 90.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // base
	Sphere(4.5, Vec(50.0, 80.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 1
	Sphere(4.5, Vec(50.0, 80.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 80.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(40.0, 80.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 78.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 2
	Sphere(4.5, Vec(40.0, 78.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 78.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 78.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 76.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 3
	Sphere(4.5, Vec(40.0, 76.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 76.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 76.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 74.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 4
	Sphere(4.5, Vec(40.0, 74.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 74.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 74.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 72.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 5
	Sphere(4.5, Vec(40.0, 72.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 72.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 72.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 70.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 6
	Sphere(4.5, Vec(40.0, 70.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 70.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 70.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(60.0, 68.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 7
	Sphere(4.5, Vec(40.0, 68.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 68.0, 68),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(4.5, Vec(50.0, 68.0, 88),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), 
	Sphere(16.5,Vec(50.0, 60.0, 78),       Color(),      Color(0.99, 0.99, 0.99), REFLECTION_TYPE_ICE), // 8
	Sphere(15.0,Vec(50.0, -7.5, 81.6),   Color(36,36,36), Color(),              REFLECTION_TYPE_DIFFUSE), //照明

};

// シーンとの交差判定関数
inline bool intersect_scene(const Ray &ray, Intersection *intersection) {
	const double n = sizeof(spheres) / sizeof(Sphere);

	// 初期化
	intersection->hitpoint_.distance_ = kINF;
	intersection->object_id_  = -1;
	
	// 線形探索
	for (int i = 0; i < int(n); i ++) {
		Hitpoint hitpoint;
		if (spheres[i].intersect(ray, &hitpoint)) {
			if (hitpoint.distance_ < intersection->hitpoint_.distance_) {
				intersection->hitpoint_ = hitpoint;
				intersection->object_id_ = i;
			}
		}
	}

	return (intersection->object_id_ != -1);
}

};

#endif
