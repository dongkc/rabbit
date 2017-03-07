#ifndef PHOTORECOGNIZE_H
#define PHOTORECOGNIZE_H

#include <QObject>

class PhotoRecognize : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE bool postMessage(const QString& msg);

signals:
  void recognizeDone(const QString& txt_path);

public slots:
  void recognize(const QString& path);
};

#endif // PHOTORECOGNIZE_H
