#pragma once
#include "../../../Visindigo/VICore/VICore.h"
/*
ImageFilter
此文件是YSP的core_B.h文件的精神续作
在滤镜效率和数量上有所提升
ConvolutionBlur部分代码从Qt的源码中获得了灵感，经过对YSP卷积滤镜初始版本的进一步修改，
现在的实现比原版快100~1000倍
*/
typedef uchar QARGB32_8;
typedef uint QARGB32_32;
#define QARGB32_NEXT +=4
#define QARGB32_Length 4
#define QARGB32_ALPHA 3
#define QARGB32_RED 2
#define QARGB32_GREEN 1
#define QARGB32_BLUE 0
class YSPConvolutionBlur;
class YSPConvolutionBlurThread :public QThread
{
	Q_OBJECT;
	friend class YSPConvolutionBlur;
	_Private bool ConsiderAlpha;
	_Protected QImage* Raw;
	_Protected QImage* Target;
	_Private int D;
	_Private int R;
	_Private QARGB32_32* Buffer;
	_Private int x;
	_Private int y;
	_Private int xFirst;
	_Protected int yStep;
	_Protected int* Kernel1D;
	_Private QARGB32_32* PixelPointer;
	_Private QARGB32_32* TargetPixelPointer;
	_Private int r, g, b, a;
	_Protected def_init YSPConvolutionBlurThread(QImage* raw, QImage* target, int d, int start, int step, int* kernal1DInt, bool considerAlpha):QThread() {
		Raw = raw;
		Target = target;
		D = d;
		R = (d - 1) / 2;
		x = 0;
		y = start;
		PixelPointer = (QARGB32_32*)Raw->bits();
		xFirst = 0;
		TargetPixelPointer = (QARGB32_32*)Target->bits();
		Kernel1D = kernal1DInt;
		Buffer = new QARGB32_32[d];
		yStep = step;
		ConsiderAlpha = considerAlpha;
		r = 0; g = 0; b = 0; a = 0;
	}
	_Public void run() {
		if (ConsiderAlpha) {
			while (this->y + this->yStep < this->Target->height()) {
				this->blurIteratorFirstColumn();
				for (int x = 1; x < this->Target->width(); x++) {
					this->blurIterator();
				}
			}
		}
		else {
			while (this->y + this->yStep < this->Target->height()) {
				this->blurIteratorFirstColumnNoAlpha();
				for (int x = 1; x < this->Target->width(); x++) {
					this->blurIteratorNoAlpha();
				}
			}
		}
	}
	_Public static inline void rgbaBound(int* value) {
		if (((unsigned)(*value)) <= (unsigned)255) { return; }
		if (*value > 255) { *value = 255; return; }
		*value = 0;
	}
	_Public void blurIteratorFirstColumn() {
		xFirst = y * Raw->width();
		TargetPixelPointer = (QARGB32_32*)Target->bits() + y * Target->width();
		x = 0;
		for (int x0 = 0; x0 < D; x0++) {
			r = 0, g = 0, b = 0, a = 0;
			PixelPointer = (QARGB32_32*)Raw->bits() + x0 + xFirst;
			for (int y0 = 0; y0 < D; y0++) {
				a += ((*PixelPointer & 0xff000000) >> 24) * Kernel1D[y0];
				r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[y0];
				g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[y0];
				b += (*PixelPointer & 0x000000ff) * Kernel1D[y0];
				PixelPointer += Raw->width();
			}
			r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
			rgbaBound(&r); 
			rgbaBound(&g);
			rgbaBound(&b);
			rgbaBound(&a);
			QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
			Buffer[x0] = color;
		}
		y += yStep;
		r = 0, g = 0, b = 0, a = 0;
		for (int i = 0; i < D; i++) {
			a += ((Buffer[i] & 0xff000000) >> 24) * Kernel1D[i];
			r += ((Buffer[i] & 0x00ff0000) >> 16) * Kernel1D[i];
			g += ((Buffer[i] & 0x0000ff00) >> 8) * Kernel1D[i];
			b += (Buffer[i] & 0x000000ff) * Kernel1D[i];
		}
		r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		rgbaBound(&a);
		QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
		*TargetPixelPointer = color;
		TargetPixelPointer++;
	}
	_Public void blurIterator() {
		x++;
		r = 0, g = 0, b = 0, a = 0;
		PixelPointer = (QARGB32_32*)Raw->bits() + (x + R) + xFirst;
		for (int i = 0; i < D; i++) {
			a += ((*PixelPointer & 0xff000000) >> 24) * Kernel1D[i];
			r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[i];
			g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[i];
			b += (*PixelPointer & 0x000000ff) * Kernel1D[i];
			PixelPointer += Raw->width();
		}
		int cbindex = (x - 1) % D;
		r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		rgbaBound(&a);
		QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
		Buffer[cbindex] = color;
		r = 0, g = 0, b = 0, a = 0;
		int j = cbindex + 1;
		if (j == D) { j = 0; }
		for (int i = 0; i < D; i++) {
			a += ((Buffer[j] & 0xff000000) >> 24) * Kernel1D[i];
			r += ((Buffer[j] & 0x00ff0000) >> 16) * Kernel1D[i];
			g += ((Buffer[j] & 0x0000ff00) >> 8) * Kernel1D[i];
			b += (Buffer[j] & 0x000000ff) * Kernel1D[i];
			j++;
			if (j == D) { j = 0; }
		}
		r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		rgbaBound(&a);
		color = (a << 24) + (r << 16) + (g << 8) + b;
		*TargetPixelPointer = color;
		TargetPixelPointer++;
	}
	_Public void blurIteratorFirstColumnNoAlpha() {
		xFirst = y * Raw->width();
		TargetPixelPointer = (QARGB32_32*)Target->bits() + y * Target->width();
		x = 0; a = 255;
		for (int x0 = 0; x0 < D; x0++) {
			r = 0, g = 0, b = 0;
			PixelPointer = (QARGB32_32*)Raw->bits() + x0 + xFirst;
			for (int y0 = 0; y0 < D; y0++) {
				r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[y0];
				g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[y0];
				b += (*PixelPointer & 0x000000ff) * Kernel1D[y0];
				PixelPointer += Raw->width();
			}
			r = r >> 16; g = g >> 16; b = b >> 16;
			rgbaBound(&r);
			rgbaBound(&g);
			rgbaBound(&b);

			QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
			Buffer[x0] = color;
		}
		y += yStep;
		r = 0, g = 0, b = 0;
		for (int i = 0; i < D; i++) {
			r += ((Buffer[i] & 0x00ff0000) >> 16) * Kernel1D[i];
			g += ((Buffer[i] & 0x0000ff00) >> 8) * Kernel1D[i];
			b += (Buffer[i] & 0x000000ff) * Kernel1D[i];
		}
		r = r >> 16; g = g >> 16; b = b >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
		*TargetPixelPointer = color;
		TargetPixelPointer++;
	}
	_Public void blurIteratorNoAlpha() {
		x++;
		r = 0, g = 0, b = 0, a = 255;
		PixelPointer = (QARGB32_32*)Raw->bits() + (x + R) + xFirst;
		for (int i = 0; i < D; i++) {
			r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[i];
			g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[i];
			b += (*PixelPointer & 0x000000ff) * Kernel1D[i];
			PixelPointer += Raw->width();
		}
		int cbindex = (x - 1) % D;
		r = r >> 16; g = g >> 16; b = b >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
		Buffer[cbindex] = color;
		r = 0, g = 0, b = 0;
		int j = cbindex + 1;
		if (j == D) { j = 0; }
		for (int i = 0; i < D; i++) {
			r += ((Buffer[j] & 0x00ff0000) >> 16) * Kernel1D[i];
			g += ((Buffer[j] & 0x0000ff00) >> 8) * Kernel1D[i];
			b += (Buffer[j] & 0x000000ff) * Kernel1D[i];
			j++;
			if (j == D) { j = 0; }
		}
		r = r >> 16; g = g >> 16; b = b >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		color = (a << 24) + (r << 16) + (g << 8) + b;
		*TargetPixelPointer = color;
		TargetPixelPointer++;
	}
	_Public def_del ~YSPConvolutionBlurThread() {
		delete[] Buffer;
	}
};
class YSPConvolutionBlur:public VIObject {
	_Public static void blur(QImage* raw, QImage* target, int d, bool considerAlpha = false) {
		if (d % 2 == 0) { d++; }
		int CPUCount = QThread::idealThreadCount();
		QList<QThread*> handlers;
		double* Kernal1D = new double[d];
		double sum = 0;
		double sigma = 0.3*((d - 1)*0.5 - 1) + 0.8; // reference OpenCV
		double sigma2 = sigma * sigma;
		for (int i = 0; i < d; i++) {
			double x = i - (d - 1) / 2;
			Kernal1D[i] = qExp(-(x * x ) / (2*sigma2)) / (qSqrt(2 * M_PI) * sigma);
			sum += Kernal1D[i];
		}
		for (int i = 0; i < d; i++) {
			Kernal1D[i] /= sum;
		}
		int *Kernal1DInt = new int[d];
		for (int i = 0; i < d; i++) {
			Kernal1DInt[i] = (int)(65536*Kernal1D[i]) ; // reference Qt
		}
		for (int i = 0; i < CPUCount; i++) {
			YSPConvolutionBlurThread* thread = new YSPConvolutionBlurThread(raw, target, d, i, CPUCount, Kernal1DInt, considerAlpha);
			handlers.append(thread);
			thread->start();
		}
		for (int i = 0; i < handlers.size(); i++) {
			handlers[i]->wait();
			handlers[i]->deleteLater();
		}
		delete[] Kernal1D;
		delete[] Kernal1DInt;
	}
};

class YSPImageFilter : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public enum class FilterName {
		grayScale, changeSaturation, changeLightness, 
		topFadeCover, gaussianBlur,
		edgeExtension, reverse
	};
	_Public static void filterOperation(FilterName name, QImage& rawImage, float p_a = 0, float p_b = 0, float p_c = 0, float p_d = 0) {
		QImage* image = &rawImage;
		switch (name)
		{
		case YSPImageFilter::FilterName::grayScale:
			grayScale(image);
			break;
		case YSPImageFilter::FilterName::changeSaturation:
			changeSaturation(image, p_a);
			break;
		case YSPImageFilter::FilterName::changeLightness:
			changeLightness(image, p_a);
			break;
		case YSPImageFilter::FilterName::topFadeCover:
			topFadeCover(image, p_a);
			break;
		case YSPImageFilter::FilterName::gaussianBlur:
			gaussianBlur(image, p_a);
			break;
		case YSPImageFilter::FilterName::edgeExtension:
			edgeExtension(image, p_a);
			break;
		case YSPImageFilter::FilterName::reverse:
			reverse(image);
			break;
		}
	}
	_Public static void grayScale(QImage* image) {
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				QColor color = image->pixel(i, j);
				int gray = (color.red()*11 + color.green()*16 + color.blue()*5) / 32;
				image->setPixel(i, j, qRgba(gray, gray, gray, color.alpha()));
			}
		}
	}
	_Public static void changeSaturation(QImage* image, float saturation) {
		if (saturation < -1) { saturation = -1; }
		if (saturation > 1) { saturation = 1; }
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				float delta = 1 + saturation;
				QColor color = image->pixel(i, j);
				int saturation = color.hsvSaturation() * delta;
				if (saturation > 255) { saturation = 255; }
				image->setPixel(i, j, QColor::fromHsv(color.hsvHue(), saturation, color.value(), color.alpha()).rgba() );
			}
		}
	}
	_Public static void changeLightness(QImage* image, float lightness) {
		if (lightness < -1) { lightness = -1; }
		if (lightness > 1) { lightness = 1; }
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				float delta = 1 + lightness;
				QColor color = image->pixel(i, j);
				int value = color.value() * delta;
				if (value > 255) { value = 255; }
				image->setPixel(i, j, QColor::fromHsv(color.hsvHue(), color.hsvSaturation(), value, color.alpha()).rgba());
			}
		}
	}
	_Public static void topFadeCover(QImage* image, float endP) {
		if (endP < 0) { endP = 0; }
		if (endP > 1) { endP = 1; }
		int end = image->height() * endP;
		for (int i = 0; i < end; i++) {
			float delta = ((float)i + 1) / end;
			for (int j = 0; j < image->width(); j++) {
				QColor color = image->pixel(j, i);
				image->setPixel(j, i, QColor::fromHsv(color.hsvHue(), color.hsvSaturation(), color.hslSaturation()*delta, color.alpha()).rgba());
			}
		}
	}
	_Public static void gaussianBlur(QImage* image, int d, bool considerAlpha = false) {
		if (d % 2 == 0) { d++; }
		if (image->format() != QImage::Format_ARGB32) { *image = image->convertToFormat(QImage::Format_ARGB32); qDebug() << "convert"; }
		QImage* temp = _edgeExtension(image, d);
		YSPConvolutionBlur::blur(temp, image, d, considerAlpha);
		delete temp;
	}
	_Public static void edgeExtension(QImage* image, int d) {
		*image = *_edgeExtension(image, d);
	}
	_Private static QImage* _edgeExtension(QImage* image, int d) {
		if (d % 2 == 0) { d++; }
		int r = (d - 1) / 2;
		int d2 = d * d;
		QImage* temp = new QImage(image->width() + r * 2, image->height() + r * 2, QImage::Format_ARGB32);
		//fill temp with image in the center
		QPainter painter(temp);
		painter.drawImage(QPoint(r, r), *image);
		painter.end();
		//top left corner
		QColor color = image->pixel(0, 0);
		QARGB32_8 red = color.red();
		QARGB32_8 green = color.green();
		QARGB32_8 blue = color.blue();
		QARGB32_8 alpha = color.alpha();
		QARGB32_32 color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		QARGB32_32* pixels;
		for (int i = 0; i < r; i++) {
			pixels = (QARGB32_32*)temp->scanLine(i);
			for (int j = 0; j < r; j++) {
				*pixels = color32;
				pixels++;
			}
		}
		//bottom left corner
		color = image->pixel(0, image->height() - 1);
		red = color.red();
		green = color.green();
		blue = color.blue();
		alpha = color.alpha();
		color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		for (int j = image->height() + r; j < temp->height(); j++){
			pixels = (QARGB32_32*)temp->scanLine(j);
			for (int i = 0; i < r; i++) {
				*pixels = color32;
				pixels++;
			}
		}
		//top right corner
		color = image->pixel(image->width() - 1, 0);
		red = color.red();
		green = color.green();
		blue = color.blue();
		alpha = color.alpha();
		color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		for (int j = 0; j < r; j++) {
			pixels = (QARGB32_32*)temp->scanLine(j);
			for (int i = image->width() + r; i < temp->width(); i++) {
				*pixels = color32;
				pixels++;
			}
		}
		//bottom right corner
		color = image->pixel(image->width() - 1, image->height() - 1);
		red = color.red();
		green = color.green();
		blue = color.blue();
		alpha = color.alpha();
		color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		for (int i = image->height() + r; i < temp->height(); i++) {
			pixels = (QARGB32_32*)temp->scanLine(i);
			for (int j = image->width() + r; j < temp->width(); j++) {
				*pixels = color32;
				pixels++;
			}
		}
		QARGB32_32* pixelRaw;
		//Top
		for (int i = 0; i < r; i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(0);
			pixels = (QARGB32_32*)temp->scanLine(i) + r;
			memcpy(pixels, pixelRaw, image->width()*sizeof(QARGB32_32));
			/*for (int j = r; j < image->width() + r; j++) {
				*pixels = *pixelRaw;
				pixels++;
				pixelRaw++;
			}*/
		}
		//Bottom
		for (int i = image->height() + r; i < temp->height(); i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(image->height() - 1);
			pixels = (QARGB32_32*)temp->scanLine(i) + r;
			memcpy(pixels, pixelRaw, image->width() * sizeof(QARGB32_32));
			/*for (int j = r; j < image->width() + r; j++) {
				*pixels = *pixelRaw;
				pixels++;
				pixelRaw++;
			}*/
		}
		//Left
		for (int i = r; i < image->height() + r; i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(i-r);
			pixels = (QARGB32_32*)temp->scanLine(i);
			for (int j = 0; j < r; j++) {
				*pixels = *pixelRaw;
				pixels++;
			}
		}
		//Right
		for (int i = r; i < image->height() + r; i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(i-r) + (image->width() - 1);
			pixels = (QARGB32_32*)temp->scanLine(i)+r+(image->width()-1);
			for (int j = 0; j < r; j++) {
				*pixels = *pixelRaw;
				pixels++;
			}
		}
		return temp;
	}
	//需要优化（按QARGB32_32处理）
	_Public static void reverse(QImage* image) {
		unsigned int length = image->width() * image->height();
		if (image->format() != QImage::Format_ARGB32) { *image = image->convertToFormat(QImage::Format_ARGB32); }
		QARGB32_8* pixels = image->bits();
		unsigned int c = 0;
		for (int i = 0; i < length; i++) {
			pixels[c + QARGB32_ALPHA] = 255 - pixels[c + QARGB32_ALPHA];
			pixels[c + QARGB32_RED] = 255 - pixels[c + QARGB32_RED];
			pixels[c + QARGB32_GREEN] = 255 - pixels[c + QARGB32_GREEN];
			pixels[c + QARGB32_BLUE] = 255 - pixels[c + QARGB32_BLUE];
			c += QARGB32_Length;
		}
	}
};