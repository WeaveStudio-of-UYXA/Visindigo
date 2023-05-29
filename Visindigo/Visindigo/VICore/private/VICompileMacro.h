#pragma once
//此项目控制是否使用3D
//#define VI_USE_3D

//此项目控制是否使用2D
#define VI_USE_2D

//此项目控制是否引入Visindigo.JS
#define VI_USE_JSENGINE

//此项目控制顶层QWidget是否应该被QOpenGLWidget取代
#define VI_USE_OPENGLWIDGET

//此项目控制VICoordinate的浮点置信度
#define VI_COORDINATE_CONFIDENCE 0.0000000001
//我劝你最好别改这个
//1e9也不代表甚么纳米，只是代表内部精度。