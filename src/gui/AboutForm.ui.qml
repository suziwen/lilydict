import QtQuick 2.6
import QtQuick.Controls 1.5

Item {
    width: 800
    height: 600
    property alias labelAbout: labelAbout
    Label {
        id: labelAbout
        x: 33
        y: 34
        text: qsTr("Label")
        textFormat: Text.RichText
    }
}
