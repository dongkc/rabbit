#include <iostream>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QUrl>
#include <QUrlQuery>
#include <QMediaPlayer>
#include <QtDebug>
#include <QProcess>
#include <Poco/Process.h>

#include "photorecognize.h"

using namespace std;
using namespace Poco;

namespace
{
  bool process(QString body, QString output)
  {
    qDebug() << "path: " << body;
    string url("http://tsn.baidu.com/text2audio");
    string cmd("/usr/bin/curl");

    Process::Args arg;
    arg.push_back("-v");
    arg.push_back("--data");
    arg.push_back(body.toStdString());
    arg.push_back("-o");
    arg.push_back(output.toStdString());
    arg.push_back(url);

    ProcessHandle handle = Process::launch(cmd, arg, "/tmp");
    int rc = Process::wait(handle);
    cout << "rc = " << rc << endl;

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
        is_playing = true;

        player->play();
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
  //QString output_txt("C:/test.txt");
  QString output_txt("/home/dongkc/test.txt");
#if 0
    QProcess ocr(this);
    QString cmd("demo.exe");
    ocr.setProgram(cmd);
    QStringList args;
    args << img_path << output_txt;
    ocr.setArguments(args);
    ocr.setWorkingDirectory("D:/ocr/");

    ocr.start();

    if (!ocr.waitFinished()) {
        qDebug() << "photo recognize error";
        return false;
    }
#endif

  QFile f(output_txt);
  f.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream stream(&f);
  stream.setCodec(QTextCodec::codecForName("GB2312"));

  QStringList list;
  QString utf16 = stream.read(500);
  QByteArray arr = line.toUtf8();
  QString line(arr);

  while(!line.isEmpty()) {
    line = line.remove("\n");
    list << line;

    utf16 = stream.read(500);
    arr = line.toUtf8();
    line = arr;
  }

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
    QString mp3 = QString::asprintf("/tmp/%d.mp3", i);
    process(url.toString(), mp3);
    qDebug() << "-------------------";

    play_list->addMedia(QUrl::fromLocalFile(mp3));
    static bool is_playing = false;
    if (!is_playing) {
      play_list->setCurrentIndex(1);
      player->setPlaylist(play_list);
      player->setVolume(50);

      is_playing = true;
      player->play();
    }
  }

  return true;
}
