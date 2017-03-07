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
  Path path(Path::current());
  qDebug() << "message from c++ code " << msg << " " << path.toString().c_str();
  return true;
}
