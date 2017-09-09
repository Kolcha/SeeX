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

#ifndef FILEPROVIDER_H
#define FILEPROVIDER_H

#include <QObject>

#include <QDir>

class FileProvider : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString currentFile READ currentFile WRITE setCurrentFile NOTIFY currentFileChanged)
  Q_PROPERTY(int filesCount READ filesCount NOTIFY filesCountChanged)
  Q_PROPERTY(QString absolutePath READ absolutePath WRITE scanDir)

public:
  explicit FileProvider(QObject *parent = nullptr);

  QString currentFile() const;
  int currentIndex() const;
  int filesCount() const;
  QString absolutePath() const;

signals:
  void currentFileChanged(const QString& current_file);
  void filesCountChanged(int new_files_count);

public slots:
  void scanDir(const QString& path);

  void setCurrentFile(const QString& current_file);

  void nextFile();
  void previousFile();

  void firstFile();
  void lastFile();

private:
  QString fileAtIndex(const int idx) const;
  void setCurrentIndex(const int idx);

private:
  QDir dir_;
  QStringList files_;
  int cur_index_;
};

#endif // FILEPROVIDER_H
