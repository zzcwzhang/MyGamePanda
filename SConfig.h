#ifndef ZCONFIG___
#define ZCONFIG___

#include "cocos2d.h"
#include<iostream>
#include <ctime>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "vld.h"  
#endif

#include<algorithm>
#include <string>
#include  <map>
#include <vector>
#define array1(type) vector<type>
#define array2(type) vector<array1(type)>
#define array3(type) vector<array2(type)>
#define array4(type) vector<array3(type)>
#define ArrayList(type) vector<type>
#define ArrayList2(type) vector<ArrayList(type)>
#define ArrayList3(type) vector<ArrayList2(type)>
#define ArrayList4(type) vector<ArrayList3(type)>
#define	FPS_RATE			60				//设定游戏帧率
#define	S_WIDTH				720				//游戏设计尺寸宽
#define	S_HEIGHT			1280				//游戏设计尺寸高
#define S_WIDTH_HALF		400
#define S_HEIGHT_HALF		240
#define NAMESPACE_ZJG_BEGIN namespace buttlesfly{
#define NAMESPACE_ZJG_END }
#define USING_SG_GAME using namespace buttlesfly<<<<<<< HEAD
#define GITtest "hello git"
#define ssss "ssss"

USING_NS_CC;
typedef signed char cbyte; 
typedef unsigned char unbyte;
using std::vector;
using std::string;
using std::map;
using std::stringstream;
#endif