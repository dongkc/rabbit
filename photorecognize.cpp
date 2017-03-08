#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QUrl>
#include <QUrlQuery>
#include <QMediaPlayer>
#include <qDebug>
#include "photorecognize.h"
#include "Poco/Path.h"

using namespace std;
using namespace Poco;

void PhotoRecognize::recognize(const QString& path)
{
}

bool PhotoRecognize::postMessage(const QString& msg)
{
  QFile f("D:\\test.txt");
  f.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream stream(&f);
  stream.setCodec(QTextCodec::codecForName("GB2312"));
  QString t = stream.readAll();
  qDebug() << "file context: " << t;

  Path path(Path::current());
  qDebug() << "message from c++ code " << msg << " " << path.toString().c_str();

  QUrl url("http://tsn.baidu.com/text2audio");
  QUrlQuery url_query;
  url_query.addQueryItem("cuid", "2e8a03f1fea94e6883c804a010c3f315");
  url_query.addQueryItem("ctp", "1");
  url_query.addQueryItem("tok", "24.2f81cbdefa3e459d04c4f86ed3991d53.2592000.1491530300.282335-8649205");
  url_query.addQueryItem("lan", "zh");
  url_query.addQueryItem("tex", t);

  url.setQuery(url_query.toString());

  qDebug() << "url: " << url.toString();

  QMediaPlayer *player = new QMediaPlayer;
  player->setMedia(url);
  player->setVolume(50);
  player->play();

  return true;
}
