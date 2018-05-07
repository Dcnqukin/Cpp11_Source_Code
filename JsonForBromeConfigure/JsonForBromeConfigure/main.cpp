
#include <QtCore/QCoreApplication>
#include "Brome.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	std::string filePath = "../config/BromeServerConfig.json";
	ServerConfig self;
	ServerConfigInitialize(self);
	ModifyConfigJSON(filePath.c_str(), self);

	/*QAxWidget* widget = new QAxWidget(0, 0);
	widget->resize(300, 200);
	widget->setControl(QString::fromUtf8());
	widget->dynamicCall("ConnectServer", self.ServerAddr, self.ServerPort, self.User, self.Password);
*/
	HKVisionCameraConfig HKConfig;
	std::string DeviceID = "B0105-25368452";
	HKVisionCameraConfigGenerate(HKConfig, DeviceID);

	
	return a.exec();
}
