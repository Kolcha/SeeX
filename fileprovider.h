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
  explicit FileProvider(QObject* parent = nullptr);

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

  void deleteCurrentFile();

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
