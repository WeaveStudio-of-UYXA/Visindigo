#pragma once
#include "../../../Visindigo/VICore/VICore.h"
/*
ImageFilter
*/
typedef uchar QARGB32;
#define QARGB32_NEXT +=4
#define QARGB32_Length 4
#define QARGB32_ALPHA 3
#define QARGB32_RED 2
#define QARGB32_GREEN 1
#define QARGB32_BLUE 0
class YSPMeanBlurThread;
class YSPMeanConvolutionalKernel
{
	friend class YSPMeanBlurThread;
	_Protected QImage* Raw;
	_Protected QImage* Target;
	_Private int D;
	_Private int R;
	_Private QList<QColor*> Buffer;
	_Private int x;
	_Private int y;
	_Private int xFirst;
	_Protected int yStep;
	_Private QARGB32* PixelPointer;
	_Private QARGB32* TargetPixelPointer;
	_Public def_init YSPMeanConvolutionalKernel(QImage* raw, QImage* target, int d) {
		Raw = raw;
		Target = target;
		D = d;
		R = (d - 1) / 2;
		x = 0;
		y = -1;
		yStep = 1;
		PixelPointer = Raw->bits() -1;
		xFirst = 0;
		TargetPixelPointer = Target->bits();
	}
	_Protected void setYStart(int y) {
		this->y = y;
	}
	_Public void blurIterator(bool rowStart) {
		if (!rowStart) {
			xFirst = y * Raw->width()*4;
			TargetPixelPointer = Target->bits() + y * Target->width() * QARGB32_Length;
			x = 0;
			for (auto i = Buffer.begin(); i != Buffer.end(); i++) {
				delete *i;
			}
			Buffer.clear();
			for (int x0 = 0; x0 < D; x0++) {
				int r = 0, g = 0, b = 0, a = 0;
				PixelPointer = Raw->bits() + x0*4 + xFirst;
				for (int y0 = 0; y0 < D; y0++) {
					a += PixelPointer[QARGB32_ALPHA];
					r += PixelPointer[QARGB32_RED];
					g += PixelPointer[QARGB32_GREEN];
					b += PixelPointer[QARGB32_BLUE];
					PixelPointer += Raw->width() * QARGB32_Length;
				}
				Buffer.append(new QColor(r / D, g / D, b / D, a / D));
			}
			y += yStep;
		}
		else {
			x++;
			int r = 0, g = 0, b = 0, a = 0;
			PixelPointer = Raw->bits() + (x + R)* QARGB32_Length + xFirst;
			for (int i = 0; i < D; i++) {
				a += PixelPointer[QARGB32_ALPHA];
				r += PixelPointer[QARGB32_RED];
				g += PixelPointer[QARGB32_GREEN];
				b += PixelPointer[QARGB32_BLUE];
				PixelPointer += Raw->width() * QARGB32_Length;
			}
			delete Buffer.first();
			Buffer.pop_front();
			Buffer.append(new QColor(r / D, g / D, b / D, a / D));
		}
		int r = 0, g = 0, b = 0, a = 0;
		for (auto i = Buffer.begin(); i != Buffer.end();i++) {
			r += (*i)->red();
			g += (*i)->green();
			b += (*i)->blue();
			a += (*i)->alpha();
		}
		TargetPixelPointer[QARGB32_ALPHA] = a / D;
		TargetPixelPointer[QARGB32_RED] = r / D;
		TargetPixelPointer[QARGB32_GREEN] = g / D;
		TargetPixelPointer[QARGB32_BLUE] = b / D;
		TargetPixelPointer QARGB32_NEXT;
	}
	_Public def_del ~YSPMeanConvolutionalKernel(){
		for (auto i = Buffer.begin(); i != Buffer.end(); i++) {
			delete *i;
		}
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
class YSPConvolutionKernal :public QThread
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QImage* Image;
	_Private QImage* Raw;
	_Private int D;
	_Private QRectF Range;
	_Private double* Kernal;
	_Public def_init YSPConvolutionKernal(QImage* image, QImage* raw, int d, double* kernal, QRectF range) {
		Image = image;
		Raw = raw;
		D = d;
		Kernal = kernal;
		Range = range;
	}
	_Public void run() {
		QPointF pos = Range.topLeft();
		convolute(Image, pos,*Raw, Range, Kernal, D, D);
	}
	//The following code is from Qt's source code, version 5.15.2
	_Public static void convolute(QImage* destImage, const QPointF& pos, const QImage& srcImage,
		const QRectF& srcRect, qreal* kernel, int kernelWidth, int kernelHeight) {
		const QImage processImage = (srcImage.format() != QImage::Format_ARGB32_Premultiplied) ? srcImage.convertToFormat(QImage::Format_ARGB32_Premultiplied) : srcImage;
		// TODO: support also other formats directly without copying

		std::unique_ptr<int[]> fixedKernel(new int[kernelWidth * kernelHeight]);
		for (int i = 0; i < kernelWidth * kernelHeight; i++)
		{
			fixedKernel[i] = (int)(65536 * kernel[i]);
		}
		QRectF trect = srcRect.isNull() ? processImage.rect() : srcRect;
		trect.moveTo(pos);
		QRectF bounded = trect.adjusted(-kernelWidth / 2, -kernelHeight / 2, (kernelWidth - 1) / 2, (kernelHeight - 1) / 2);
		QRect rect = bounded.toAlignedRect();
		QRect targetRect = rect.intersected(destImage->rect());

		QRectF srect = srcRect.isNull() ? processImage.rect() : srcRect;
		QRectF sbounded = srect.adjusted(-kernelWidth / 2, -kernelHeight / 2, (kernelWidth - 1) / 2, (kernelHeight - 1) / 2);
		QPoint srcStartPoint = sbounded.toAlignedRect().topLeft() + (targetRect.topLeft() - rect.topLeft());

		const uint* sourceStart = (const uint*)processImage.scanLine(0);
		uint* outputStart = (uint*)destImage->scanLine(0);

		int yk = srcStartPoint.y();
		for (int y = targetRect.top(); y <= targetRect.bottom(); y++) {
			uint* output = outputStart + (destImage->bytesPerLine() / sizeof(uint)) * y + targetRect.left();
			int xk = srcStartPoint.x();
			for (int x = targetRect.left(); x <= targetRect.right(); x++) {
				int r = 0;
				int g = 0;
				int b = 0;
				int a = 0;

				// some out of bounds pre-checking to avoid inner-loop ifs
				int kernely = -kernelHeight / 2;
				int starty = 0;
				int endy = kernelHeight;
				if (yk + kernely + endy >= srcImage.height())
					endy = kernelHeight - ((yk + kernely + endy) - srcImage.height()) - 1;
				if (yk + kernely < 0)
					starty = -(yk + kernely);

				int kernelx = -kernelWidth / 2;
				int startx = 0;
				int endx = kernelWidth;
				if (xk + kernelx + endx >= srcImage.width())
					endx = kernelWidth - ((xk + kernelx + endx) - srcImage.width()) - 1;
				if (xk + kernelx < 0)
					startx = -(xk + kernelx);

				for (int ys = starty; ys < endy; ys++) {
					const uint* pix = sourceStart + (processImage.bytesPerLine() / sizeof(uint)) * (yk + kernely + ys) + ((xk + kernelx + startx));
					const uint* endPix = pix + endx - startx;
					int kernelPos = ys * kernelWidth + startx;
					while (pix < endPix) {
						int factor = fixedKernel[kernelPos++];
						a += (((*pix) & 0xff000000) >> 24) * factor;
						r += (((*pix) & 0x00ff0000) >> 16) * factor;
						g += (((*pix) & 0x0000ff00) >> 8) * factor;
						b += (((*pix) & 0x000000ff)) * factor;
						pix++;
					}
				}
				r = qBound((int)0, r >> 16, (int)255);
				g = qBound((int)0, g >> 16, (int)255);
				b = qBound((int)0, b >> 16, (int)255);
				a = qBound((int)0, a >> 16, (int)255);
				uint color = (a << 24) + (r << 16) + (g << 8) + b;
				*output++ = color;
				xk++;
			}
			yk++;
		}
	}
};
class YSPConvolutionKernalMultiThread :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public static void gaussianBlur(QImage* image, int d) {
		QImage destImage = QImage(image->size(), QImage::Format_ARGB32);
		if (d % 2 == 0) { d++; }
		if (d < 3) { d = 3; }
		int r = (d - 1) / 2;
		int d2 = d * d;
		double* kernal = new double[d2];
		double sum = 0;
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++) {
				int x = i - r;
				int y = j - r;
				kernal[i + j * d] = qExp(-(x * x + y * y) / (2)) / (2 * M_PI);
				sum += kernal[i + j * d];
			}
		}
		for (int i = 0; i < d2; i++) {
			kernal[i] /= sum;
		}
		int CPUCount = QThread::idealThreadCount();
		int normalHeight = image->height() / CPUCount;
		int lastHeight = image->height() - normalHeight * (CPUCount - 1);
		QList<YSPConvolutionKernal*> Threads;
		for (int i = 0; i < CPUCount; i++) {
			QRectF rect = QRectF(0, i * normalHeight, image->width(), i == CPUCount - 1 ? lastHeight : normalHeight);
			YSPConvolutionKernal* thread = new YSPConvolutionKernal(&destImage, image, d, kernal, rect);
			Threads.append(thread);
			thread->start();
		}
		for (int i = 0; i < CPUCount; i++) {
			Threads[i]->wait();
			delete Threads[i];
		}
		*image = destImage;
		delete[] kernal;
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
	_Public static void gaussianBlurQt(QImage* image, int d) {
		YSPConvolutionKernalMultiThread::gaussianBlur(image, d);
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
		QColor color = image->pixel(0, 0);
		QARGB32 red = color.red();
		QARGB32 green = color.green();
		QARGB32 blue = color.blue();
		QARGB32 alpha = color.alpha();
		QARGB32* pixels;
		for (int i = 0; i < r; i++) {
			pixels = temp->scanLine(i);
			for (int j = 0; j < r; j++) {
				pixels[j * QARGB32_Length + QARGB32_ALPHA] = alpha;
				pixels[j * QARGB32_Length + QARGB32_RED] = red;
				pixels[j * QARGB32_Length + QARGB32_GREEN] = green;
				pixels[j * QARGB32_Length + QARGB32_BLUE] = blue;
			}
		}
		color = image->pixel(0, image->height() - 1);
		red = color.red();
		green = color.green();
		blue = color.blue();
		for (int j = image->height() + r; j < temp->height(); j++){
			pixels = temp->scanLine(j);
			for (int i = 0; i < r; i++) {
				pixels[i*QARGB32_Length + QARGB32_ALPHA] = alpha;
				pixels[i*QARGB32_Length + QARGB32_RED] = red;
				pixels[i*QARGB32_Length + QARGB32_GREEN] = green;
				pixels[i*QARGB32_Length + QARGB32_BLUE] = blue;	
			}
		}
		color = image->pixel(image->width() - 1, 0);
		red = color.red();
		green = color.green();
		blue = color.blue();
		for (int j = 0; j < r; j++) {
			pixels = temp->scanLine(j);
			for (int i = image->width() + r; i < temp->width(); i++) {
				pixels[i * QARGB32_Length + QARGB32_ALPHA] = alpha;
				pixels[i * QARGB32_Length + QARGB32_RED] = red;
				pixels[i* QARGB32_Length + QARGB32_GREEN] = green;
				pixels[i * QARGB32_Length + QARGB32_BLUE] = blue;
			}
		}
		color = image->pixel(image->width() - 1, image->height() - 1);
		red = color.red();
		green = color.green();
		blue = color.blue();
		for (int i = image->height() + r; i < temp->height(); i++) {
			pixels = temp->scanLine(i);
			for (int j = image->width() + r; j < temp->width(); j++) {
				pixels[j * QARGB32_Length + QARGB32_ALPHA] = alpha;
				pixels[j * QARGB32_Length + QARGB32_RED] = red;
				pixels[j * QARGB32_Length + QARGB32_GREEN] = green;
				pixels[j * QARGB32_Length + QARGB32_BLUE] = blue;
			}
		}
		QARGB32* pixelRaw = image->scanLine(0);
		for (int i = 0; i < r; i++) {
			pixels = temp->scanLine(i);
			for (int j = r; j < image->height() + r; j++) {
				pixels[j * QARGB32_Length + QARGB32_ALPHA] = pixelRaw[j * QARGB32_Length + QARGB32_ALPHA];
				pixels[j * QARGB32_Length + QARGB32_RED] = pixelRaw[j * QARGB32_Length + QARGB32_RED];
				pixels[j * QARGB32_Length + QARGB32_GREEN] = pixelRaw[j * QARGB32_Length + QARGB32_GREEN];
				pixels[j * QARGB32_Length + QARGB32_BLUE] = pixelRaw[j * QARGB32_Length + QARGB32_BLUE];
			}
		}
		pixelRaw = image->scanLine(image->height() - 1);
		for (int i = image->height() + r; i < temp->height(); i++) {
			pixels = temp->scanLine(i);
			for (int j = r; j < image->height() + r; j++) {
				pixels[j * QARGB32_Length + QARGB32_ALPHA] = pixelRaw[j * QARGB32_Length + QARGB32_ALPHA];
				pixels[j * QARGB32_Length + QARGB32_RED] = pixelRaw[j * QARGB32_Length + QARGB32_RED];
				pixels[j * QARGB32_Length + QARGB32_GREEN] = pixelRaw[j * QARGB32_Length + QARGB32_GREEN];
				pixels[j * QARGB32_Length + QARGB32_BLUE] = pixelRaw[j * QARGB32_Length + QARGB32_BLUE];
			}
		}
		for (int i = r; i < image->height() + r; i++) {
			pixelRaw = image->scanLine(i-r);
			pixels = temp->scanLine(i + r);
			for (int j = 0; j < r; j++) {
				pixels[j * QARGB32_Length + QARGB32_ALPHA] = pixelRaw[QARGB32_ALPHA];
				pixels[j * QARGB32_Length + QARGB32_RED] = pixelRaw[QARGB32_RED];
				pixels[j * QARGB32_Length + QARGB32_GREEN] = pixelRaw[QARGB32_GREEN];
				pixels[j * QARGB32_Length + QARGB32_BLUE] = pixelRaw[QARGB32_BLUE];
			}
		}
		for (int i = r; i < image->height() + r; i++) {
			pixelRaw = image->scanLine(i-r) + (image->width() - 1) * QARGB32_Length;
			pixels = temp->scanLine(i + r);
			for (int j = image->width()+r; j < temp->width(); j++) {
				pixels[j * QARGB32_Length + QARGB32_ALPHA] = pixelRaw[QARGB32_ALPHA];
				pixels[j * QARGB32_Length + QARGB32_RED] = pixelRaw[QARGB32_RED];
				pixels[j * QARGB32_Length + QARGB32_GREEN] = pixelRaw[QARGB32_GREEN];
				pixels[j * QARGB32_Length + QARGB32_BLUE] = pixelRaw[QARGB32_BLUE];
			}
		}
		return temp;
	}
	_Public static void meanBlur(QImage* image, int d) {
		if (d % 2 == 0) { d++; }
		QImage* temp = _edgeExtension(image, d);
		if (image->format() != QImage::Format_ARGB32) { image->convertToFormat(QImage::Format_ARGB32); qDebug() << "convert"; }
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