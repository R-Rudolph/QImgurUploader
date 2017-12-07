#ifndef QIMGURUPLOADER_H
#define QIMGURUPLOADER_H

// License: MIT License
// Author: Robert Rudolph

#include <QObject>
#include <QtGlobal>
#include <QUrl>
#include <QMap>
#include <QNetworkReply>

class QNetworkAccessManager;
class QImgurReply;

// Imgur Uploader class
// Handles uploads to imgur.com
// Call QImgurUploader::upload to get a QImgurReply, which will parse the response
// This class requires a Imgur Client ID to work. In order to get a Cient ID, you have to register your application (see https://api.imgur.com/)

class QImgurUploader : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QNetworkAccessManager* networkAccessManager READ networkAccessManager)
  Q_PROPERTY(QString clientID READ clientID WRITE setClientID)
  Q_PROPERTY(QUrl uploadUrl READ uploadUrl WRITE setUploadUrl)

  QNetworkAccessManager* m_networkAccessManager;
  QString m_clientID;
  QUrl m_uploadUrl;
public:
  QImgurUploader(const QString& clientID, QObject* parent = nullptr);

  //property get functions
  QNetworkAccessManager* networkAccessManager() const;
  QString clientID() const;
  QUrl uploadUrl() const;

  QImgurReply* upload(const QString& filePath); /* use this to upload an image file to Imgur */
public slots:
  //property set slots
  void setClientID(QString clientID);
  void setUploadUrl(QUrl uploadUrl);
};

#endif // QIMGURUPLOADER_H
