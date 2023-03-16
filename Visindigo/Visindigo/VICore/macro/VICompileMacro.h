#pragma once
//此项目控制是否使用3D
//#define VI_USE_3D

//此项目控制是否使用2D
#define VI_USE_2D

//此项目控制是否引入Visindigo.JS
#define VI_USE_JSENGINE

//此项目控制顶层QWidget是否应该被QOpenGLWidget取代
#define VI_USE_OPENGLWIDGET

//以下内容建立Visindigo缩写
#define VI_Property(Type, name) public:Type name;void set##name(Type value){this->name = value;}Type get##name(){return name;}
#define VI_PrivateProperty(Type, name) private:Type name;private: void set##name(Type value){this->name = value;}public:Type get##name(){return name;}
#define VI_Flag(name) public:bool name;void set##name(bool value){this->name = value;}bool is##name(){return name;}
#define VI_PrivateFlag(name) private:bool name;private: void set##name(bool value){this->name = value;}public:bool is##name(){return name;}
