/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2017  Nick Korotysh <nick.korotysh@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fileprovider.h"

#include <QFileInfo>
#include <QImageReader>


static bool isFileSupported(const QString& file)
{
  QImageReader img_reader(file);
  img_reader.setDecideFormatFromContent(true);
  return img_reader.canRead();
}


FileProvider::FileProvider(QObject *parent) : QObject(parent), cur_index_(-1)
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
