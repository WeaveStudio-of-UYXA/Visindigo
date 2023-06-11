#pragma once
#include "../../../Visindigo/VICore/VICore.h"

class YSPMeanBlurThread;
class YSPMeanConvolutionalKernel
{
	friend class YSPMeanBlurThread;
	_Protected QImage* Raw;
	_Protected QImage* Target;
	_Private int D;
	_Private int R;
	_Private QList<QColor> Buffer;
	_Private int x;
	_Private int y;
	_Protected int yStep;
	_Public def_init YSPMeanConvolutionalKernel(QImage* raw, QImage* target, int d) {
		Raw = raw;
		Target = target;
		D = d;
		R = (d - 1) / 2;
		x = 0;
		y = -1;
		yStep = 1;
	}
	_Protected void setYStart(int y) {
		this->y = y - 1;
	}
	_Public void blurIterator(bool rowStart) {
		if (!rowStart) {
			y += yStep;
			x = 0;
			Buffer.clear();
			for (int i = 0; i < D; i++) {
				int r = 0, g = 0, b = 0, a = 0;
				for (int j = y; j < y + D; j++) {
					r += Raw->pixelColor(i, j).red();
					g += Raw->pixelColor(i, j).green();
					b += Raw->pixelColor(i, j).blue();
					a += Raw->pixelColor(i, j).alpha();
				}
				Buffer.append(QColor(r / D, g / D, b / D, a / D));
			}
		}
		else {
			x++;
			int r = 0, g = 0, b = 0, a = 0;
			for (int i = 0; i < D; i++) {
				r += Raw->pixelColor(x + R, y + i).red();
				g += Raw->pixelColor(x + R, y + i).green();
				b += Raw->pixelColor(x + R, y + i).blue();
				a += Raw->pixelColor(x + R , y + i).alpha();
			}
			Buffer.pop_front();
			Buffer.append(QColor(r / D, g / D, b / D, a / D));
		}
		int r = 0, g = 0, b = 0, a = 0;
		for (int i = 0; i < D; i++) {
			r += Buffer[i].red();
			g += Buffer[i].green();
			b += Buffer[i].blue();
			a += Buffer[i].alpha();
		}
		Target->setPixel(x, y, qRgba(r/D, g/D , b/D, a/D));
	}
};
class YSPMeanBlurThread :public QThread
{
	Q_OBJECT;
	friend class YSPMeanBlurMultiThread;
	_Private YSPMeanConvolutionalKernel* Kernel;
	_Protected def_init YSPMeanBlurThread(QImage* raw, QImage* target, int d, int start, int step):QThread() {
		Kernel = new YSPMeanConvolutionalKernel(raw, target, d);
		Kernel->setYStart(start);
		Kernel->yStep = step;
	}
	_Public void run() {
		while (Kernel->y+Kernel->yStep < Kernel->Target->height()) {
			for (int x = 0; x < Kernel->Target->width();x++) {
				Kernel->blurIterator(x);
			}
		}
	}
	_Public def_del ~YSPMeanBlurThread() {
		delete Kernel;
	}
};
class YSPMeanBlurMultiThread :public VIObject {
	_Public static void handle(QImage* raw, QImage* target, int d) {
		if (d % 2 == 0) { d++; }
		int CPUCount = QThread::idealThreadCount();
		QList<QThread*> handlers;
		for (int i = 0; i < CPUCount; i++) {
			YSPMeanBlurThread* thread = new YSPMeanBlurThread(raw, target, d, i, CPUCount);
			handlers.append(thread);
			thread->start();
		}
		for (int i = 0; i < handlers.size(); i++) {
			handlers[i]->wait();
			handlers[i]->deleteLater();
		}
	}
};
class YSPImageFilter : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public enum class FilterName {
		grayScale, changeSaturation, changeLightness, 
		topFadeCover, gaussianBlur, meanBlur,
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
		case YSPImageFilter::FilterName::meanBlur:
			meanBlur(image, p_a);
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
	_Public static void gaussianBlur(QImage* image, int d) {
		meanBlur(image, d);
		meanBlur(image, d);
		meanBlur(image, d);
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
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < r; j++) {
				temp->setPixel(i, j, temp->pixel(r, r));
			}
		}
		for (int i = 0; i < r; i++) {
			for (int j = image->height() + r; j < temp->height(); j++) {
				temp->setPixel(i, j, temp->pixel(r, r + image->height() - 1));
			}
		}
		for (int i = image->width() + r; i < temp->width(); i++) {
			for (int j = 0; j < r; j++) {
				temp->setPixel(i, j, temp->pixel(r + image->width() - 1, r));
			}
		}
		for (int i = image->width() + r; i < temp->width(); i++) {
			for (int j = image->height() + r; j < temp->height(); j++) {
				temp->setPixel(i, j, temp->pixel(r + image->width() - 1, r + image->height() - 1));
			}
		}
		for (int i = 0; i < r; i++) {
			for (int j = r; j < image->height() + r; j++) {
				temp->setPixel(i, j, temp->pixel(r, j));
			}
		}
		for (int i = image->width() + r; i < temp->width(); i++) {
			for (int j = r; j < image->height() + r; j++) {
				temp->setPixel(i, j, temp->pixel(r + image->width() - 1, j));
			}
		}
		for (int i = r; i < image->width() + r; i++) {
			for (int j = 0; j < r; j++) {
				temp->setPixel(i, j, temp->pixel(i, r));
			}
		}
		for (int i = r; i < image->width() + r; i++) {
			for (int j = image->height() + r; j < temp->height(); j++) {
				temp->setPixel(i, j, temp->pixel(i, r + image->height() - 1));
			}
		}
		return temp;
	}
	_Public static void meanBlur(QImage* image, int d) {
		if (d % 2 == 0) { d++; }
		QImage* temp = _edgeExtension(image, d);
		YSPMeanBlurMultiThread::handle(temp, image, d);
		delete temp;
	}
	_Public static void reverse(QImage* image) {
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				QColor color = image->pixel(i, j);
				image->setPixel(i, j, QColor::fromRgb(255 - color.red(), 255 - color.green(), 255 - color.blue(), color.alpha()).rgba());
			}
		}
	}
};