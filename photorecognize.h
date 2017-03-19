#ifndef PHOTORECOGNIZE_H
#define PHOTORECOGNIZE_H

#include <string>
#include <QObject>
#include <QNetworkAccessManager>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QNetworkRequest>
#include <QNetworkReply>

class PhotoRecognize : public QObject
{
  Q_OBJECT
PUBLIC:
  PhotoRecognize(QObject* parent = NULL);

  Q_INVOKABLE bool postMessage(const QString& msg);

signals:
  void recognizeDone(const QString& txt_path);

public slots:
  void recognize(const QString& path);

  void replyFinished(QNetworkReply* reply);

 public:
  QNetworkAccessManager *net_mgr;
  QMediaPlayer * player;
  QMediaPlaylist *play_list;
};

#endif // PHOTORECOGNIZE_H
