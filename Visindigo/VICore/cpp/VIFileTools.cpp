#include "../VIFileTools.h"

QStringList VIFileTools::filesFilter(const QString& root, const QStringList& filters, const bool considerSubDirectories)
{
	QDirIterator it(root, filters, QDir::Files, considerSubDirectories ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);
	QStringList files;
	while (it.hasNext())
	{
		files << it.next();
	}
	return files;
}