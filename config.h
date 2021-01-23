#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
class Config : public QObject
{
    Q_OBJECT
public:

    explicit Config(QObject *parent = nullptr);

    //初始化
    bool init();

    Q_INVOKABLE int getWidth();
    Q_INVOKABLE int getHeight();
    Q_INVOKABLE int getInterval();
    Q_INVOKABLE QStringList getPictureNames();

private:
    bool loadConfig();
    void loadPictureFileLists();
private:

    int width;
    int height;
    int interval;
    QStringList pictureNames;
};

#endif // CONFIG_H
