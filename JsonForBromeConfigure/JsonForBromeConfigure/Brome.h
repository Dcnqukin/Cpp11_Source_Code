#include <QFile>
#include <QDataStream>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <string>
#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QAxWidget>
#include <QAxBase>

typedef struct ServerConfig
{
	std::string ServerAddr;
	int ServerPort;
	std::string User;
	std::string Password;
}ServerConfig;

typedef struct HKVisionCameraConfig
{
	std::vector<std::string> HKVisionCameraID;
}HKVisionCameraConfig;

typedef struct BromeDeviceList
{
	std::string DeviceList;
	std::vector<std::string> DeviceID;
	void GetList(std::string DeviceList, QAxWidget* selfWidget);
	void SplitList(decltype(DeviceID)& DeviceID, std::string DeviceList);
}BromeDeviceList;
//QFile file("../config/BromeServerConfig.json");

void BromeDeviceList::SplitList(decltype(DeviceID)& DeviceID, std::string DeviceList)
{
	
}

void GetList(std::string DeviceList, QAxWidget* selfWidget)
{

}

void ModifyConfigJSON(const char* url, ServerConfig &self);

void ServerConfigInitialize(ServerConfig& self);

void HKVisionCameraConfigGenerate(HKVisionCameraConfig& self, std::string DeviceID);

class BromeSystem
{
public:
	void ReceiveStaticInfo();
	void RequestGpsInfo();
};

