// License: MIT License
// Author: Robert Rudolph

#include "qimgurreply.h"

#include<QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

QImgurReply::QImgurReply(QNetworkReply *reply, QObject *parent) : QObject(parent)
{
  m_reply = reply;
  m_finished = false;
  if(m_reply->isFinished())
  {
    replyFinished();
  }
  else
  {
    connect(reply,&QNetworkReply::finished,this,&QImgurReply::replyFinished);
    connect(reply,&QNetworkReply::downloadProgress,this,&QImgurReply::downloadProgress);
    connect(reply,&QNetworkReply::uploadProgress,this,&QImgurReply::uploadProgress);
  }
}

QNetworkReply *QImgurReply::reply() const
{
  return m_reply;
}

int QImgurReply::status() const
{
  return m_status;
}

bool QImgurReply::success() const
{
  return m_success;
}

QString QImgurReply::id() const
{
  return m_id;
}

QString QImgurReply::title() const
{
  return m_title;
}

QString QImgurReply::description() const
{
  return m_description;
}

int QImgurReply::datetime() const
{
  return m_datetime;
}

QString QImgurReply::type() const
{
  return m_type;
}

bool QImgurReply::animated() const
{
  return m_animated;
}

int QImgurReply::width() const
{
  return m_width;
}

int QImgurReply::height() const
{
  return m_height;
}

int QImgurReply::size() const
{
  return m_size;
}

int QImgurReply::views() const
{
  return m_views;
}

int QImgurReply::bandwidth() const
{
  return m_bandwidth;
}

QJsonValue QImgurReply::vote() const
{
  return m_vote;
}

bool QImgurReply::favorite() const
{
  return m_favorite;
}

QJsonValue QImgurReply::nsfw() const
{
  return m_nsfw;
}

QJsonValue QImgurReply::section() const
{
  return m_section;
}

QString QImgurReply::accountUrl() const
{
  return m_account_url;
}

int QImgurReply::accountId() const
{
  return m_account_id;
}

bool QImgurReply::isAd() const
{
  return m_is_ad;
}

bool QImgurReply::inMostViral() const
{
  return m_in_most_viral;
}

QStringList QImgurReply::tags() const
{
  return m_tags;
}

int QImgurReply::adType() const
{
  return m_ad_type;
}

QString QImgurReply::adUrl() const
{
  return m_ad_url;
}

bool QImgurReply::inGallery() const
{
  return m_in_gallery;
}

QString QImgurReply::deletehash() const
{
  return m_deletehash;
}

QString QImgurReply::name() const
{
  return m_name;
}

QString QImgurReply::link() const
{
  return m_link;
}

bool QImgurReply::isFinished() const
{
  return m_finished;
}

QNetworkReply::NetworkError QImgurReply::networkError() const
{
  return m_networkError;
}

QJsonParseError QImgurReply::jsonError() const
{
  return m_jsonError;
}

QString QImgurReply::errorString() const
{
  return m_errorString;
}

void QImgurReply::replyFinished()
{
  m_finished = true;
  m_success = false;
  m_networkError = m_reply->error();
  if(m_networkError==QNetworkReply::NoError)
  {
    QByteArray arr = m_reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(arr,&m_jsonError);
    if(m_jsonError.error == QJsonParseError::NoError)
    {
      QJsonObject object = doc.object();
      m_success = object["success"].toBool(false);
      m_status = object["status"].toInt();
      if(m_success)
      {
        QJsonObject data = object["data"].toObject();

        m_id             = data["id"].toString();
        m_title          = data["title"].toString();
        m_description    = data["description"].toString();
        m_datetime       = data["datetime"].toInt();
        m_type           = data["type"].toString();
        m_animated       = data["animated"].toBool();
        m_width          = data["width"].toInt();
        m_height         = data["height"].toInt();
        m_size           = data["size"].toInt();
        m_views          = data["views"].toInt();
        m_bandwidth      = data["bandwidth"].toInt();
        m_vote           = data["vote"];
        m_favorite       = data["favorite"].toBool();
        m_nsfw           = data["nsfw"];
        m_section        = data["section"];
        m_account_url    = data["account_url"].toString();
        m_account_id     = data["account_id"].toInt();
        m_is_ad          = data["is_ad"].toBool();
        m_in_most_viral  = data["in_most_viral"].toBool();
        m_ad_type        = data["ad_type"].toInt();
        m_ad_url         = data["ad_url"].toString();
        m_in_gallery     = data["in_gallery"].toBool();
        m_deletehash     = data["deletehash"].toString();
        m_name           = data["name"].toString();
        m_link           = data["link"].toString();

        foreach(QJsonValue value, data["tags"].toArray())
          m_tags.append(value.toString());
      }
      else
      {
        m_errorString = "Imgur error: " + QString::number(m_status);
      }
    }
    else
    {
      m_errorString = "Parsing error: " + m_jsonError.errorString();
    }
  }
  else
  {
    m_errorString = "Network error: " + m_reply->errorString();
  }
  emit finished();
  emit linkFound(m_link);
}
