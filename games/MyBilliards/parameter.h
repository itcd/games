#pragma once

/************************************************************************
��ʽ���������
http://www.top147.com/bjtx/9qjs.php

Ӣʽ˹ŵ��̨���������ʱ�����̨�� 
���ߴ磺3850��2060��850mm
�ڿ�ߴ磺3560��1780mm
˹ŵ��̨��: ֱ��:52.5mm ����:154.5g

��ʽ�����̨ 
���ߴ磺2810��1530��840mm
�ڿ�ߴ磺2540��1270mm
��ʽ��: ֱ��:57.15mm ����:170g

��ʽ����̨���� 
���ߴ磺2880��1600��800mm
�ڿ�ߴ磺2540��1270mm
��ʽ����ֱ��:57.15mm ����:170g
************************************************************************/

//////////////////////////////////////////////////////////////////////////
// constants in math
const float SQRT2 = 1.4142135623730950488016887242097f;
const float SQRT3 = 1.7320508075688772935274463415059f;
const float PI = 3.1415926535897932384626433832795f;

//////////////////////////////////////////////////////////////////////////
// size in millimeter
const float BALL_DIAMETER_MM = 57.15f;

//////////////////////////////////////////////////////////////////////////
// size related to Ball Diameter
const float BALL_DIAMETER = 1;
const float BALL_RADIUS = 0.5f;
const float TABLE_WIDTH = 1270 / BALL_DIAMETER_MM;
const float TABLE_LENGTH = 2540 / BALL_DIAMETER_MM;
const float BALL_WEIGHT = 170;
const float POCKET_DIAMETER = 105 / BALL_DIAMETER_MM;
const float POCKET_DIAMETER_DIVIDED_BY_SQRT2 = POCKET_DIAMETER / SQRT2;
const float POCKET_RADIUS = POCKET_DIAMETER / 2;
const float POCKET_RADIUS_DIVIDED_BY_SQRT2 = POCKET_RADIUS / SQRT2;
const float MIDDLE_POCKET_ENTRANCE_DIAMETER = 120 / BALL_DIAMETER_MM;
const float MIDDLE_POCKET_ENTRANCE_RADIUS = MIDDLE_POCKET_ENTRANCE_DIAMETER / 2;
const float MIN_X = -TABLE_WIDTH/2;
const float MAX_X =  TABLE_WIDTH/2;
const float MIN_Y = -TABLE_LENGTH/2;
const float MAX_Y =  TABLE_LENGTH/2;


/************************************************************************
Bibliography

The Math and Physics of Billiards
http://archive.ncsa.illinois.edu/Classes/MATH198/townsend/math.html

Physics on the Back of a Cocktail Napkin
http://www.darwin3d.com/gamedev/articles/col0999.pdf

Physics of Pool
http://library.thinkquest.org/C006300/main.htm
http://ffden-2.phys.uaf.edu/212_spring2005.web.dir/Erik_Crawford/PoolHome.htm

Billiards and Pool Physics Resources
http://billiards.colostate.edu/physics/index.html

Computational Modeling of Pool Games: Sensitivity of Outcomes to Initial Conditions
http://www.ajur.uni.edu/v1no4/Leerberg-Roth.pdf

************************************************************************/

//////////////////////////////////////////////////////////////////////////
// constants in physics
const float ROLLING_FRICTION = 0.1f;
const float SLIDING_FRICTION = 0.5f;
const float COLLISION_FRICTION = 0.1f;
const float GRAVITY_ACCELERATION = 9780 / BALL_DIAMETER_MM;

// Coefficients of Restitution
// http://hypertextbook.com/facts/2006/restitution.shtml
const float RESTITUTION = 0.804f;

const float VELOCITY_ZERO = 0.01f;
const float VELOCITY_SLIDING_MIN = 1;

/************************************************************************
Suppose maximum force f=100N, the contact time of the cue and cue ball t=0.01s
So, f*t=mv, f=100 N, t=0.01 s, m=0.17 kg
Hence, maximum velocity v=f*t/m=5.88235 meter/s =102.92831 BALL_DIAMETER_MM/s
In this program, maximum velocity of the cue ball is 100 BALL_DIAMETER_MM/s
************************************************************************/

//////////////////////////////////////////////////////////////////////////
// other constants
const int BALL_NUM = 16; // eight balls

// header files
#include <iostream>
#include <cmath>
#include <SFML/Graphics/Color.hpp>

// OpenGL Mathematics (GLM) http://www.g-truc.net/project-0016.html
#include <glm/ext.hpp>
//// OpenGL Image (GLI) http://www.g-truc.net/project-0024.html
//#include <gli/gtx/gl_texture2d.hpp>

#include "vector_utils.h"
