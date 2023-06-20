// Qt imports
import QtQuick
import QtCore
import QtQuick.Controls 2.15
import QtQuick.Controls
import QtQuick.Dialogs

// Project imports
import App.Controller 1.0
import App.ListModel 1.0

Item {
    id: rowItem
    anchors.fill: parent

    FolderDialog {
        id: folderDialog
        currentFolder: StandardPaths.standardLocations(
                           StandardPaths.PicturesLocation)[0]
        options: FolderDialog.ShowDirsOnly
        onAccepted: textInput.text = folderDialog.selectedFolder
    }
    /***************************Header section *********************************/
    Row {
        id: headersRow
        spacing: 3
        anchors {
            top: rowItem.top
            topMargin: 3
            left: rowItem.left
            leftMargin: 3
            right: rowItem.right
            rightMargin: 3
        }
        Rectangle {
            id: lineEditRect

            width: rowItem.width * 0.8
            height: 40
            border.color: "#000000"
            Text {
                id: dirPath
                text: qsTr("Folder Path: |")
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 2
                }
            }
            TextInput {
                id: textInput
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: dirPath.left
                    leftMargin: 80
                    right: parent.right
                    rightMargin: 2
                }
                onTextChanged: AppController.photoDirPath = textInput.text
            }
        }

        Button {
            id: selectDirButton
            width: rowItem.width * 0.2
            height: 40
            text: qsTr("Select folder")
            onClicked: folderDialog.open()
        }
    }

    Rectangle {
        id: patternRect
        anchors {
            left: rowItem.left
            leftMargin: 3
            top: headersRow.bottom
            topMargin: 3
        }
        width: rowItem.width * 0.8
        height: 30
        border.color: "#000000"
        Text {
            id: schemePattern
            text: qsTr("Scheme Pattern: ")
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 2
            }
        }
        TextInput {
            id: schemePatterntext
            clip: true
            anchors {
                verticalCenter: parent.verticalCenter
                left: schemePattern.left
                leftMargin: 100
                right: parent.right
                rightMargin: 2
            }
            onTextChanged: AppController.schemePattern = schemePatterntext.text
        }
    }

    /***************************Body section(ListView) *********************************/
    Rectangle {
        id: listViewRect
        width: rowItem.width
        height: rowItem.height * 0.6
        anchors {
            top: patternRect.bottom
            topMargin: 3
            left: rowItem.left
            leftMargin: 3
            right: rowItem.right
            rightMargin: 3
        }
        border.color: "#000000"

        ListView {
            id: listView
            anchors.fill: parent
            clip: true
            spacing: 1
            focus: true
            model: AppListModel
            delegate: Rectangle {
                height: 20
                width: listView.width
                border.color: "#052127"
                color: listView.currentIndex === index ? "#6fa8dc" : "white"
                Text {
                    id: filePathTxt
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 3
                    }
                    text: '<b> ' + "File" + " " + (index + 1) + ':</b> ' + model.FileNameRole
                    color: listView.currentIndex === index ? "#f3f6f4" : "black"
                }
                Text {
                    id: dateTxt
                    clip: true
                    anchors {
                        left: filePathTxt.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    text: qsTr("| Date: ") + Date()
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.currentIndex = index
                }
            }
        }
    }

    /***************************Foot section with start button etc... *********************************/
    Rectangle {
        id: stateRect
        width: 120
        height: 40
        border.color: "#000000"
        anchors {
            top: listViewRect.bottom
            topMargin: 5
            left: rowItem.left
            leftMargin: 3
        }
        Text {
            id: stateTxt
            text: qsTr("State: ")
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 2
            }
        }
        TextInput {
            id: stateTextInput
            clip: true
            readOnly: true
            anchors {
                verticalCenter: parent.verticalCenter
                left: stateTxt.left
                leftMargin: 40
                right: parent.right
                rightMargin: 2
            }
            text: AppController.classifierStateToString + "..."
        }
    }

    Button {
        id: startBtn
        width: 100
        height: 40
        anchors {
            right: parent.right
            rightMargin: 3
            top: listViewRect.bottom
            topMargin: 5
        }
        text: qsTr("Start Classifier")
        onClicked: AppController.startClassifier()
    }
    Button {
        id: clearBtn
        width: 100
        height: 40
        anchors {
            right: parent.right
            rightMargin: 3
            top: startBtn.bottom
            topMargin: 3
        }
        text: qsTr("Clear all")
    }
}
