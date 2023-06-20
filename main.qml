import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: topLevelWindow
    width: 540
    height: 420
    visible: true
    title: qsTr("PhotoClassifiersApp")

    MainWindow {
        id: mainWindow
    }
}
