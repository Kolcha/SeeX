#include "frameprovider.h"

FrameProvider::FrameProvider(QObject* parent) : QObject(parent), cur_index_(-1)
{
  reader_.setAutoDetectImageFormat(true);
  reader_.setAutoTransform(true);
  reader_.setDecideFormatFromContent(true);
  connect(&timer_, &QTimer::timeout, this, &FrameProvider::onTimer);
}

QImage FrameProvider::currentFrame() const
{
  if (currentIndex() < 0) return QImage();
  Q_ASSERT(0 <= cur_index_ && cur_index_ < frames_.size());
  Q_ASSERT(!reader_.fileName().isEmpty());
  return frames_[currentIndex()];
}

int FrameProvider::currentIndex() const
{
  return cur_index_;
}

int FrameProvider::framesCount() const
{
  return frames_.size();
}

QString FrameProvider::fileName() const
{
  return reader_.fileName();
}

QString FrameProvider::fileFormat() const
{
  return file_format_;
}

void FrameProvider::setFileName(const QString& filename)
{
  if (reader_.fileName() == filename) return;

  if (timer_.isActive()) timer_.stop();

  int old_count = frames_.size();
  frames_.clear();
  delays_.clear();
  reader_.setFileName(filename);
  file_format_ = QString(reader_.format()).toUpper();

  if (reader_.supportsAnimation()) {
    while (reader_.canRead()) {
      frames_.push_back(reader_.read());
      delays_.push_back(reader_.nextImageDelay());
    }
    Q_ASSERT(delays_.size() == frames_.size());
    timer_.setSingleShot(true);
    timer_.start(delays_.first());
  } else {
    while (reader_.canRead()) {
      frames_.push_back(reader_.read());
      if (!reader_.jumpToNextImage()) break;
    }
  }

  int new_count = frames_.size();
  if (new_count != old_count)
    emit framesCountChanged(new_count);

  emit fileNameChanged(filename);

  setCurrentIndex(new_count > 0 ? 0 : -1);
}

void FrameProvider::nextFrame()
{
  Q_ASSERT(0 <= currentIndex() && currentIndex() < framesCount() - 1);
  setCurrentIndex(currentIndex() + 1);
}

void FrameProvider::previousFrame()
{
  Q_ASSERT(0 < currentIndex() && currentIndex() < framesCount());
  setCurrentIndex(currentIndex() - 1);
}

void FrameProvider::onTimer()
{
  if (currentIndex() == framesCount() - 1)
    setCurrentIndex(0);
  else
    setCurrentIndex(currentIndex() + 1);
  timer_.start(delays_[currentIndex()]);
}

void FrameProvider::setCurrentIndex(const int idx)
{
  Q_ASSERT(-1 <= idx && idx < framesCount());
  cur_index_ = idx;
  emit currentFrameChanged(currentFrame());
}
