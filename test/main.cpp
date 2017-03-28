#include <iostream>
#include <string>
#include <Poco/Process.h>
#include <Poco/File.h>
#include <Poco/Path.h>

using namespace std;
using namespace Poco;

int main(int argc, char *argv[])
{
  string text("tex=北京楼市实施“认房又认贷”，二套房首付比例提至60%；&cuid=2e8a03f1fea94e6883c804a010c3f315&ctp=1&tok=24.2f81cbdefa3e459d04c4f86ed3991d53.2592000.1491530300.282335-8649205&lan=zh&per=0");
  string url("http://tsn.baidu.com/text2audio");
  string cmd("/usr/bin/curl");
  Process::Args arg;
  arg.push_back("-v");
  arg.push_back("--data");
  arg.push_back(text);
  arg.push_back("-v");
  arg.push_back("-o");
  arg.push_back("/tmp/1.mp3");
  arg.push_back(url);

  ProcessHandle handle = Process::launch(cmd, arg, "/tmp");
  int rc = Process::wait(handle);
  cout << "rc = " << rc << endl;

  return 0;
}
