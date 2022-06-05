#include "fileprovider.h"

#include <QFileInfo>
#include <QImageReader>


static bool isFileSupported(const QString& file)
{
  QImageReader img_reader(file);
  img_reader.setDecideFormatFromContent(true);
  return img_reader.canRead();
}


FileProvider::FileProvider(QObject* parent) : QObject(parent), cur_index_(-1)
{
  dir_.setFilter(QDir::Files | QDir::Readable);
  dir_.setSorting(QDir::Name | QDir::IgnoreCase | QDir::LocaleAware);
}

QString FileProvider::currentFile() const
{
  if (currentIndex() < 0) return QString();
  Q_ASSERT(0 <= cur_index_ && cur_index_ < files_.size());
  Q_ASSERT(!dir_.path().isEmpty() && dir_.exists());
  return fileAtIndex(currentIndex());
}

int FileProvider::currentIndex() const
{
  return cur_index_;
}

int FileProvider::filesCount() const
{
  return files_.size();
}

QString FileProvider::absolutePath() const
{
  return dir_.absolutePath();
}

void FileProvider::scanDir(const QString& path)
{
  setCurrentIndex(-1);
  dir_.setPath(path);
  files_ = dir_.entryList();
  emit filesCountChanged(files_.size());
}

void FileProvider::setCurrentFile(const QString& current_file)
{
  QFileInfo fi(current_file);
  if (fi.absolutePath() != dir_.absolutePath()) return;

  if (currentFile() == fi.absoluteFilePath()) return;

  int idx = files_.indexOf(fi.fileName());
  if (idx != -1) setCurrentIndex(idx);
}

void FileProvider::deleteCurrentFile()
{
  Q_ASSERT(0 <= cur_index_ && cur_index_ < files_.size());
  int cur_index = currentIndex();
  if (!QFile::remove(currentFile())) return;
  files_.removeAt(cur_index);
  emit filesCountChanged(files_.size());

  int idx = cur_index - 1;
  while (++idx < filesCount() && !isFileSupported(fileAtIndex(idx)));
  if (idx < filesCount()) {
    setCurrentIndex(idx);
  } else {
    int idx = cur_index;
    while (--idx >= 0 && !isFileSupported(fileAtIndex(idx)));
    if (idx >= 0)
      setCurrentIndex(idx);
    else
      emit currentFileChanged(QString());
  }
}

void FileProvider::nextFile()
{
  Q_ASSERT(0 <= cur_index_ && cur_index_ < files_.size() - 1);
  int idx = currentIndex();
  while (++idx < filesCount() && !isFileSupported(fileAtIndex(idx)));
  if (idx < filesCount()) setCurrentIndex(idx);
}

void FileProvider::previousFile()
{
  Q_ASSERT(0 < cur_index_ && cur_index_ < files_.size());
  int idx = currentIndex();
  while (--idx >= 0 && !isFileSupported(fileAtIndex(idx)));
  if (idx >= 0) setCurrentIndex(idx);
}

void FileProvider::firstFile()
{
  int idx = -1;
  while (++idx < filesCount() && !isFileSupported(fileAtIndex(idx)));
  if (idx < filesCount()) setCurrentIndex(idx);
}

void FileProvider::lastFile()
{
  int idx = filesCount();
  while (--idx >= 0 && !isFileSupported(fileAtIndex(idx)));
  if (idx >= 0) setCurrentIndex(idx);
}

QString FileProvider::fileAtIndex(const int idx) const
{
  Q_ASSERT(0 <= idx && idx < filesCount());
  return dir_.absoluteFilePath(files_[idx]);
}

void FileProvider::setCurrentIndex(const int idx)
{
  Q_ASSERT(-1 <= idx && idx < filesCount());
  cur_index_ = idx;
  emit currentFileChanged(currentFile());
}
