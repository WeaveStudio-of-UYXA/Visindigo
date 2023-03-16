//���ĵ��ṩ������λ��ͳһ����
#pragma once
#include <QtCore>
#include "macro/VIMarco.h"
namespace VIUnit {
	enum class UnitType {
		Volume, Mass, Length, Temperature, Time
	};
	enum class VolumeUnit {
		Liter, CubicMeter
	};
	enum class MassUnit {
		Kilogram, Gram
	};
	enum class LengthUnit {
		Meter, Centimeter, Millimeter
	};
	enum class TemperatureUnit {
		Celsius, Fahrenheit, Kelvin
	};
	enum class TimeUnit {
		Second, Millisecond, Microsecond, Nanosecond
	};
}
