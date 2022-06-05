#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QObject>

#include <QTimer>
#include <QImageReader>

class FrameProvider : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QImage currentFrame READ currentFrame NOTIFY currentFrameChanged)
  Q_PROPERTY(int framesCount READ framesCount NOTIFY framesCountChanged)
  Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
  Q_PROPERTY(QString fileFormat READ fileFormat CONSTANT)

public:
  explicit FrameProvider(QObject* parent = nullptr);

  QImage currentFrame() const;
  int currentIndex() const;
  int framesCount() const;
  QString fileName() const;
  QString fileFormat() const;

signals:
  void currentFrameChanged(const QImage& img);
  void framesCountChanged(int new_frames_count);
  void fileNameChanged(const QString& new_file);

public slots:
  void setFileName(const QString& filename);

  void nextFrame();
  void previousFrame();

private slots:
  void onTimer();

private:
  void setCurrentIndex(const int idx);

private:
  QTimer timer_;
  QVector<int> delays_;
  QImageReader reader_;
  QVector<QImage> frames_;
  int cur_index_;
  QString file_format_;
};

#endif // FRAMEPROVIDER_H
