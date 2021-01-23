#include "config.h"
#include <QDomDocument>
#include <QFile>
#include <QCoreApplication>
#include <QSettings>
#include <QDir>

Config::Config(QObject *parent) : QObject(parent),
    width(1920),
    height(1080),
    interval(20)
{

}

bool Config::init()
{
    if(!loadConfig()){
        return false;
    }
    loadPictureFileLists();
    return true;
}

int Config::getWidth()
{
    return width;
}
int Config::getHeight()
{
    return height;
}
int Config::getInterval()
{
    return interval;
}
QStringList Config::getPictureNames()
{
    return pictureNames;
}

void Config::loadPictureFileLists()
{
    QDir dir( QCoreApplication::applicationDirPath()+"/pictures");

    if(dir.exists()){

        QStringList filters;

        filters << "*.bmp" << "*.jpg" << "*.png"<<"*.jpeg";

        dir.setNameFilters(filters);

        QFileInfoList list = dir.entryInfoList();

        for(auto fileInfo:list)
        {
            pictureNames.append(fileInfo.fileName());
        }
    }
}

bool Config::loadConfig()
{
    QString filePath =  QCoreApplication::applicationDirPath()+"/config/config.xml";
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QString errorMsg;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(&file,&errorMsg,&errorLine,&errorColumn))
    {
        file.close();
        return false;
    }
    file.close();
    bool ok;
    QDomElement root = doc.firstChildElement("config");
    QDomNodeList domConfig = root.childNodes();
    for(int i=0;i<domConfig.length();++i){
        QDomNode dnConfig = domConfig.at(i);
        if(dnConfig.toElement().tagName()=="ui"){
            int width_temp = dnConfig.toElement().attribute("width").toInt(&ok);
            if(ok)width = width_temp;
            int height_temp = dnConfig.toElement().attribute("height").toInt(&ok);
            if(ok)height = height_temp;
        }else if(dnConfig.toElement().tagName()=="picture"){
            int interval_temp = dnConfig.toElement().attribute("width").toInt(&ok);
            if(ok)interval = interval_temp;
        }
    }

    return true;
}

