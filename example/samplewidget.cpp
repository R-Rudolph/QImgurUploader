// License: MIT License
// Author: Robert Rudolph

#include "samplewidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QImgurUploader>
#include <QImgurReply>
#include <QProgressBar>

#include <QFileDialog>

SampleWidget::SampleWidget(QWidget *parent) : QWidget(parent)
{
  m_layout = new QVBoxLayout(this);
  m_uploadButton = new QPushButton("Upload",this);
  m_progress = new QProgressBar(this);
  m_progress->setDisabled(true);
  m_lineEdit = new QLineEdit(this);
  m_lineEdit->setReadOnly(true);
  m_layout->addWidget(m_uploadButton);
  m_layout->addWidget(m_progress);
  m_layout->addWidget(m_lineEdit);
  // Uploader is initialized with a client id. For your own application, please register with Imgur to get your own id
  m_uploader = new QImgurUploader("3a7b4071829410b",this);
  m_reply = nullptr;

  connect(m_uploadButton,&QPushButton::clicked,this,&SampleWidget::buttonClicked);
}

void SampleWidget::buttonClicked()
{
  if(m_reply!=nullptr)
    return;
  QString filepath = QFileDialog::getOpenFileName(nullptr,"Select Image File",QString(),"Image Files (*.png *.jpg *.bmp)");
  if(filepath.isEmpty())
    return;
  m_progress->setDisabled(false);

  // upload() is called. the resulting QImgurReply is saved and connected
  m_reply = m_uploader->upload(filepath);
  connect(m_reply,&QImgurReply::finished,this,&SampleWidget::uploadFinished);
  connect(m_reply,&QImgurReply::uploadProgress,this,&SampleWidget::uploadProgress);
}

void SampleWidget::uploadFinished()
{
  //if successful, link is written, if not successful, write error message
  if(m_reply->success())
  {
    m_lineEdit->setText(m_reply->link());
  }
  else
  {
    m_lineEdit->setText(m_reply->errorString());
  }
  m_reply->deleteLater();
  m_reply = nullptr;
  m_progress->setDisabled(true);
  m_progress->reset();
}

void SampleWidget::uploadProgress(quint64 sent, quint64 total)
{
  //write upload progress to progress bar
  m_progress->setMaximum(total);
  m_progress->setValue(sent);
}
