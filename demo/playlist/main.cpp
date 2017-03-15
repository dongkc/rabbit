#include <iostream>
#include <QCoreApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QFile>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMediaPlaylist * list = new QMediaPlaylist;
    list->addMedia(QUrl::fromLocalFile("/home/dongkc/rabbit/test/1.mp3"));
    list->setCurrentIndex(1);

    QMediaPlayer *player = new QMediaPlayer;
    player->setPlaylist(list);
    player->setVolume(90);
    player->play();
    list->addMedia(QUrl::fromLocalFile("/home/dongkc/rabbit/test/4.mp3"));
    list->addMedia(QUrl::fromLocalFile("/home/dongkc/rabbit/test/2.mp3"));
    list->addMedia(QUrl::fromLocalFile("/home/dongkc/rabbit/test/3.mp3"));

    cout << "playing mp3 ..." << endl;

    return a.exec();
}
