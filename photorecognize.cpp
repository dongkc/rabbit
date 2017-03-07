#include <qDebug>
#include "photorecognize.h"

void PhotoRecognize::recognize(const QString& path)
{
}

bool PhotoRecognize::postMessage(const QString& msg)
{
  qDebug() << "message from c++ code";
  return true;
}
