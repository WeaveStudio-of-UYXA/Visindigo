#pragma once
#include "macro/VIMarco.h"
#include <QtCore>
#include <QtGui>
//This file is NOT prepared
//DO NOT USE
namespace VIMath {
	template <typename T>class VIRange 
	{
		class iterator {
			_Public VIRange<T> *Control;
			_Protected bool beginFlag;
			_Protected bool endFlag;
			_Public VIRange::iterator operator++() {
				if (beginFlag) {
					beginFlag = false;
					return *this;
				}
				if (endFlag) {
					return *this;
				}
				Control->onUpdate(Control->Current);
				if (Control->Current == Control->Target) {
					endFlag = true;
				}
				return *this;
			};
			_Public VIRange::iterator operator--();
			_Public T operator*();
			_Public bool operator==(const VIRange::iterator& it);
		};
		_Public def_init VIRange(T* t) :{
			this->Current = t;
			this->Target = t;
		}
		_Protected T* Target;
		_Protected T* Current;
		_Public void setTarget(T* t);
		_Public T* getTarget(void);
		_Public virtual void onUpdate(T* t) PureVirtual; //�û������Թ涨ÿ����T�Ĳ���
		_Public virtual unsigned long long getStepCount(T* target) PureVirtual;//�û��������ڿ�ʼrange֮ǰȷ���ܲ��������������ã�
		_Public iterator begin();
		_Public iterator end();
	};
}