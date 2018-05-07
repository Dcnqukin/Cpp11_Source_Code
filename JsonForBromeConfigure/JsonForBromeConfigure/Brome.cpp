#include "Brome.h"
#include <rapidjson/document.h>

using namespace rapidjson;
void ModifyConfigJSON(const char* url, ServerConfig& self)
{
	QFile file(url);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "Can't open the file!";
		return;
	}
	QTextStream stream(&file);
	QString json;
	stream.seek(0);
	while (!stream.atEnd()){
		json = stream.readAll();
		qDebug() << json;
	}
	Document document;
	document.Parse(json.toStdString().c_str());
	//assert(document.IsObject());
	self.ServerAddr = document["ServerAddr"].GetString();
	self.ServerPort = document["ServerPort"].GetInt();
	self.User = document["User"].GetString();
	self.Password = document["Password"].GetString();
}

void ServerConfigInitialize(ServerConfig& self)
{
	self.ServerAddr = "192.168.0.1";
	self.ServerPort = 8080;
	self.User = "root";
	self.Password = "";
}

void HKVisionCameraConfigGenerate(HKVisionCameraConfig& self, std::string DeviceID)
{
	std::string tmpID;
	std::string tmpConf;
	char str[] = { '0', '1', '2', '3', '4' };
	tmpID = DeviceID.substr(6, 8);
	for (int i = 0; i < 5; i++)
	{
		tmpConf.clear();
		tmpConf.append("32010000");
		tmpConf += tmpID.substr(0, 2);
		tmpConf.append("132");
		tmpConf += tmpID.substr(2, 6);
		tmpConf += str[i];
		self.HKVisionCameraID.push_back(tmpConf);
	}
}