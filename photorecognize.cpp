#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QUrl>
#include <QUrlQuery>
#include <QMediaPlayer>
#include <QtDebug>
#include "photorecognize.h"
#include "Poco/Path.h"

using namespace std;
using namespace Poco;

namespace
{
  bool process(QString& path, QString& output)
  {
    return true;
  }
}

PhotoRecognize::PhotoRecognize(QObject* parent)
{
  player = new QMediaPlayer;
  net_mgr = new QNetworkAccessManager(this);
  play_list = new QMediaPlaylist;

  connect(net_mgr, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(replyFinished(QNetworkReply*)));
}

void PhotoRecognize::replyFinished(QNetworkReply* reply)
{
  static bool is_playing = false;

  switch(reply->error()) {
  case QNetworkReply::NoError:
    {
      QString mp3("C:/data/test.mp3");
      QFile f(mp3);
      QByteArray arr = reply->readAll();
      f.open(QIODevice::WriteOnly);
      f.write(arr.data(), arr.size());

      play_list->addMedia(QUrl::fromLocalFile(mp3));

      if (!is_playing) {
        play_list->setCurrentIndex(1);
        player->play();
        is_playing = true;
      }
    }
  default:
    qDebug() << "http error: " << reply->errorString();
  }
}

void PhotoRecognize::recognize(const QString& path)
{
}

bool PhotoRecognize::postMessage(const QString& msg)
{
  QFile f("D:\\test.txt");
  f.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream stream(&f);
  stream.setCodec(QTextCodec::codecForName("GB2312"));

  QStringList list;
  QString line = stream.read(1000);

  while(!line.isEmpty()) {
    list << line;

    line = stream.read(1000);
  }

  QString t = stream.readAll();
  qDebug() << "file context: " << t;

  for (int i = 0; i < list.size(); i++) {
    QUrl url("http://tsn.baidu.com/text2audio");
    QUrlQuery url_query;
    url_query.addQueryItem("cuid", "2e8a03f1fea94e6883c804a010c3f315");
    url_query.addQueryItem("ctp", "1");
    url_query.addQueryItem("tok", "24.2f81cbdefa3e459d04c4f86ed3991d53.2592000.1491530300.282335-8649205");
    url_query.addQueryItem("lan", "zh");
    url_query.addQueryItem("tex", list[i]);

    url.setQuery(url_query.toString());
    qDebug() << "url: " << url.toString();

    net_mgr->get(QNetworkRequest(url));
  }

  player->setPlaylist(play_list);
  player->setVolume(50);

  return true;
}
