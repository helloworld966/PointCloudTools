#include "Tools.h"


QTime time;

Tools::Tools()
{
}


Tools::~Tools()
{
}

//��ȡȫ·���е��ļ���������׺��
std::string getFileName(std::string file_name)
{
	std::string subname;
	for (auto i = file_name.end() - 1; *i != '/'; i--)
	{
		subname.insert(subname.begin(), *i);
	}
	return subname;
}

//��ʱ��ʼ
void timeStart()
{
	time.start();
}

//��ʱ����
QString timeOff()
{
	int timediff = time.elapsed();   //���ش��ϴ�start()��restart()��ʼ������ʱ����λms
	float f = timediff / 1000.0;
	QString tr_timediff = QString("%1").arg(f);  //float->QString
	return tr_timediff;
}

QString toQString(const string& s)
{
	QString qs(s.c_str());
	return qs;
}


string fromQString(const QString& qs) {
	string s = qs.toUtf8().data();
	return s;
}

string joinStrVec(const vector<string> v, string splitor) {
	string s = "";
	if (v.size() == 0) return s;
	for (int i = 0; i != v.size() - 1; ++i) {
		s += (v[i] + splitor);
	}
	s += v[v.size() - 1];
	return s;
}