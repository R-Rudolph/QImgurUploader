// License: MIT License
// Author: Robert Rudolph

#include "qimguruploader.h"

#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>
#include <QNetworkReply>
#include <QImgurReply>

QImgurReply *QImgurUploader::upload(const QString &filePath)
{
  QFile* file = new QFile(filePath);
  if(!file->open(QIODevice::ReadOnly))
  {
    delete file;
    return nullptr;
  }
  QString filename = filePath.split('/').last();

  QNetworkRequest request(m_uploadUrl);
  QString idValue = "Client-ID "+clientID();
  request.setRawHeader(QByteArray("Authorization"), idValue.toUtf8());
  QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  file->setParent(multiPart);

  QHttpPart imagePart;
  imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"");
  imagePart.setBodyDevice(file);

  QHttpPart namePart;
  namePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"name\"");
  namePart.setBody(filename.toUtf8());

  QHttpPart titlePart;
  titlePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"title\"");
  titlePart.setBody(filename.toUtf8());

  multiPart->append(imagePart);
  multiPart->append(namePart);
  multiPart->append(titlePart);

  QNetworkReply* reply = m_networkAccessManager->post(request,multiPart);
  multiPart->setParent(reply);
  return new QImgurReply(reply,this);
}

QImgurUploader::QImgurUploader(const QString &clientID, QObject *parent)
  : QObject(parent)
{
  m_networkAccessManager = new QNetworkAccessManager(this);
  m_networkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
  setClientID(clientID);
  setUploadUrl(QUrl("https://api.imgur.com/3/upload.json"));
}

QNetworkAccessManager *QImgurUploader::networkAccessManager() const
{
  return m_networkAccessManager;
}

QString QImgurUploader::clientID() const
{
  return m_clientID;
}

QUrl QImgurUploader::uploadUrl() const
{
  return m_uploadUrl;
}

void QImgurUploader::setClientID(QString clientID)
{
  m_clientID = clientID;
}

void QImgurUploader::setUploadUrl(QUrl uploadUrl)
{
  m_uploadUrl = uploadUrl;
}
