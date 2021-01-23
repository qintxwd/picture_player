import QtQuick 2.12
import QtQml 2.0
import QtQuick.Window 2.12

Window {
    width: g_config.getWidth()
    height: g_config.getHeight()
    x:Screen.width //show on the second screen
    visible: true
    title: qsTr("qyh_picture_player")
    flags: Qt.FramelessWindowHint|Qt.Window

    Image {
        id: image
        property int image_index: 0
        property var image_paths: g_config.getPictureNames();
        anchors.fill: parent
        source: image_paths.length>0?("file:///"+g_strExeRoot+"/pictures/"+image_paths[image_index]):"";
    }

    Timer{
        interval: g_config.getInterval()*1000;
        repeat: true
        running: true
        onTriggered: {
            if(image.image_index+1>=image.image_paths.length){
                image.image_index = 0;
            }else{
                image.image_index+=1;
            }
        }
    }
}
