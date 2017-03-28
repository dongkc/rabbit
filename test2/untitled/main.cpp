#include <QCoreApplication>
#include <QStringList>
#include <QTextStream>
#include <QTextCodec>
#include <QUrlQuery>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtDebug>
#include <QProcess>
#include <QFile>
#include <QUrl>
#include <Poco/Process.h>

#include <iostream>
#include <string>

using namespace std;
using namespace Poco;

namespace
{
  bool process(QString body, QString output)
  {
    qDebug() << "path: " << body;
    string text("tex=北京楼市实施“认房又认贷”，二套房首付比例提至60%；&cuid=2e8a03f1fea94e6883c804a010c3f315&ctp=1&tok=24.2f81cbdefa3e459d04c4f86ed3991d53.2592000.1491530300.282335-8649205&lan=zh&per=0");
    string url("http://tsn.baidu.com/text2audio");
    string cmd("/usr/bin/curl");
#if 1
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
#endif

    return true;
  }
}

bool postMessage(const QString& msg)
{
  QMediaPlayer* player = new QMediaPlayer;
  QMediaPlaylist* play_list = new QMediaPlaylist;
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
  QString line = stream.read(1000);

  while(!line.isEmpty()) {
    line = line.remove("\n");
    list << line;

    line = stream.read(1000);
  }

  //for (int i = 0; i < list.size(); i++) {
  for (int i = 0; i < 1; i++) {
    QUrl url("http://tsn.baidu.com/text2audio");
    QUrlQuery url_query;
    url_query.addQueryItem("cuid", "2e8a03f1fea94e6883c804a010c3f315");
    url_query.addQueryItem("ctp", "1");
    url_query.addQueryItem("tok", "24.2f81cbdefa3e459d04c4f86ed3991d53.2592000.1491530300.282335-8649205");
    url_query.addQueryItem("lan", "zh");
    url_query.addQueryItem("tex", list[i]);

    url.setQuery(url_query.toString());
    qDebug() << "url: " << url.toString();
    QString mp3("/tmp/1.mp3");
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
int main(int argc, char *argv[])
{
    QString output_txt("C:/test.txt");
    QString msg;
    postMessage(msg);

    QCoreApplication a(argc, argv);
    cout << "---------------------" << endl;

    return a.exec();
}
