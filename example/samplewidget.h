#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

// License: MIT License
// Author: Robert Rudolph

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QLineEdit;
class QImgurUploader;
class QImgurReply;
class QProgressBar;

class SampleWidget : public QWidget
{
  Q_OBJECT
  QImgurUploader* m_uploader;
  QVBoxLayout* m_layout;
  QPushButton* m_uploadButton;
  QProgressBar* m_progress;
  QLineEdit* m_lineEdit;
  QImgurReply* m_reply;
public:
  explicit SampleWidget(QWidget *parent = nullptr);

signals:

private slots:
  void buttonClicked();
  void uploadFinished();
  void uploadProgress(quint64 sent, quint64 total);
};

#endif // SAMPLEWIDGET_H
