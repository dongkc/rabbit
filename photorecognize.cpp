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
  void gb2312ToUtf8(std::string& strGb2312)
  {

  QTextCodec* utf8Codec= QTextCodec::codecForName("UTF-8");
  QTextCodec* gb2312Codec = QTextCodec::codecForName("GB18030");

  QString strUnicode= gb2312Codec->toUnicode(strGb2312.c_str());
  QByteArray ByteUtf8= utf8Codec->fromUnicode(strUnicode);

  strGb2312= ByteUtf8.data();
  }

  bool process(QString body, QString output)
  {
    qDebug() << "path: " << body;
    string url("http://tsn.baidu.com/text2audio");
    string cmd("D:/ocr/curl.exe");
    string text(body.toStdString());
    gb2312ToUtf8(text);

    Process::Args arg;
    arg.push_back("-v");
    arg.push_back("--data");
    arg.push_back(text);
    arg.push_back("-o");
    arg.push_back(output.toStdString());
    arg.push_back(url);

    ProcessHandle handle = Process::launch(cmd, arg, "D:/ocr/");
    int rc = Process::wait(handle);
    cout << "rc = " << rc << endl;

    return true;
  }

  bool process2(string img_path, string txt_path)
  {
    cout << "path: " << img_path;
    string cmd("D:/ocr/bin/1.exe");

    Process::Args arg;
    arg.push_back(img_path);
    arg.push_back(txt_path);

    ProcessHandle handle = Process::launch(cmd, arg, "D:/ocr/bin/");
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
  QString output_txt("D:/ocr/test1.txt");
 // QString output_txt("D:/ocr/o.txt");
  //QString output_txt("/home/dongkc/test.txt");
  string img_path("D:/ocr/1.jpg");
  process2(img_path, output_txt.toStdString());
  return true;
#if 0
    QProcess ocr(this);
    QString cmd("1.exe");
    ocr.setProgram(cmd);
    QStringList args;
    //args << img_path << output_txt;
    args << "D:/ocr/1.jpg" << output_txt;
    ocr.setArguments(args);
    ocr.setWorkingDirectory("D:/ocr/bin/");

    ocr.start();

    if (!ocr.waitForFinished()) {
        qDebug() << "photo recognize error";
        return false;
    }
    qDebug() << "photo recognize success";
    return true;
#endif

  QFile f(output_txt);
  f.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream stream(&f);
  //stream.setCodec(QTextCodec::codecForName("UTF-16LE"));

  QStringList list;
  QString line = stream.read(500);

  while(!line.isEmpty()) {
    line = line.remove("\n");
    list << line;

    line = stream.read(500);
  }

  static int click_num = 0;
  for (int i = 0; i < list.size(); i++) {
    //QUrl url("http://tsn.baidu.com/text2audio");
    QUrlQuery url_query;
    url_query.addQueryItem("cuid", "2e8a03f1fea94e6883c804a010c3f315");
    url_query.addQueryItem("ctp", "1");
    url_query.addQueryItem("tok", "24.2f81cbdefa3e459d04c4f86ed3991d53.2592000.1491530300.282335-8649205");
    url_query.addQueryItem("lan", "zh");
    url_query.addQueryItem("tex", list[i]);

    //url.setQuery(url_query.toString());
    //qDebug() << "url: " << url.toString();
    QString mp3 = QString::asprintf("D:/ocr/%d%d.mp3", click_num++, i);
    process(url_query.toString(), mp3);
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
