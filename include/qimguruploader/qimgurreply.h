#ifndef QIMGURREPLY_H
#define QIMGURREPLY_H

// License: MIT License
// Author: Robert Rudolph

#include <QObject>
#include <QNetworkReply>
#include <QJsonValue>
#include <QJsonParseError>

// Imgur Reply Class
// This class manages responses from imgur.com
// In order to upload a file use QImgurUploader::upload, which returns a QImgurReply

class QImgurReply : public QObject
{
  Q_OBJECT
  //internal state properties
  Q_PROPERTY(bool finished READ isFinished)
  Q_PROPERTY(QNetworkReply* reply READ reply)
  Q_PROPERTY(QNetworkReply::NetworkError networkError READ networkError)
  Q_PROPERTY(QJsonParseError jsonError READ jsonError)
  Q_PROPERTY(QString errorString READ errorString)

  // response properties (refer to apidocs.imgur.com)
  Q_PROPERTY(int status READ status)
  Q_PROPERTY(bool success READ success)

  // data properties (refer to apidocs.imgur.com)
  Q_PROPERTY(QString id READ id)
  Q_PROPERTY(QString title READ title)
  Q_PROPERTY(QString description READ description)
  Q_PROPERTY(int datetime READ datetime)
  Q_PROPERTY(QString type READ type)
  Q_PROPERTY(bool animated READ animated)
  Q_PROPERTY(int width READ width)
  Q_PROPERTY(int height READ height)
  Q_PROPERTY(int size READ size)
  Q_PROPERTY(int views READ views)
  Q_PROPERTY(int bandwidth READ bandwidth)
  Q_PROPERTY(QJsonValue vote READ vote)
  Q_PROPERTY(bool favorite READ favorite)
  Q_PROPERTY(QJsonValue nsfw READ nsfw)
  Q_PROPERTY(QJsonValue section READ section)
  Q_PROPERTY(QString account_url READ accountUrl)
  Q_PROPERTY(int account_id READ accountId)
  Q_PROPERTY(bool is_ad READ isAd)
  Q_PROPERTY(bool in_most_viral READ inMostViral)
  Q_PROPERTY(QStringList tags READ tags)
  Q_PROPERTY(int ad_type READ adType)
  Q_PROPERTY(QString ad_url READ adUrl)
  Q_PROPERTY(bool in_gallery READ inGallery)
  Q_PROPERTY(QString deletehash READ deletehash)
  Q_PROPERTY(QString name READ name)
  Q_PROPERTY(QString link READ link)

  QNetworkReply* m_reply;
  bool m_finished;

  int m_status;
  bool m_success;
  QString m_id;
  QString m_title;
  QString m_description;
  int m_datetime;
  QString m_type;
  bool m_animated;
  int m_width;
  int m_height;
  int m_size;
  int m_views;
  int m_bandwidth;
  QJsonValue m_vote;
  bool m_favorite;
  QJsonValue m_nsfw;
  QJsonValue m_section;
  QString m_account_url;
  int m_account_id;
  bool m_is_ad;
  bool m_in_most_viral;
  QStringList m_tags;
  int m_ad_type;
  QString m_ad_url;
  bool m_in_gallery;
  QString m_deletehash;
  QString m_name;
  QString m_link;
  QNetworkReply::NetworkError m_networkError;
  QJsonParseError m_jsonError;

  QString m_errorString;

public:
  explicit QImgurReply(QNetworkReply* reply, QObject *parent = nullptr);

  QNetworkReply* reply() const;

  //info about finished/error state
  bool isFinished() const;
  QNetworkReply::NetworkError networkError() const;
  QJsonParseError jsonError() const;
  QString errorString() const;

  //properties
  bool success() const;
  int status() const;
  QString id() const;
  QString title() const;
  QString description() const;
  int datetime() const;
  QString type() const;
  bool animated() const;
  int width() const;
  int height() const;
  int size() const;
  int views() const;
  int bandwidth() const;
  QJsonValue vote() const;
  bool favorite() const;
  QJsonValue nsfw() const;
  QJsonValue section() const;
  QString accountUrl() const;
  int accountId() const;
  bool isAd() const;
  bool inMostViral() const;
  QStringList tags() const;
  int adType() const;
  QString adUrl() const;
  bool inGallery() const;
  QString deletehash() const;
  QString name() const;
  QString link() const;

signals:
  void finished();                                       /* Emitted when Reply is complete */
  void downloadProgress(quint64 received,quint64 total); /* forwards downloadProgress from QNetworkReply */
  void uploadProgress(quint64 sent,quint64 total);       /* forwards uploadProgress from QNetworkReply */
  void linkFound(QString value);                         /* convenience signal, emits the link property value when finished*/
private slots:
  void replyFinished();
};

#endif // QIMGURREPLY_H
