import QtQuick
import QtQuick.Controls

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	Rectangle {
		anchors.fill: parent
		color: "white"

		gradient: Gradient {
			GradientStop { position: 0.0; color: "dark orange" }
			GradientStop { position: 0.8; color: "#191970" }
		}

		Text {
			anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top
			text: "Zdarowa"
			font.family: "OCR-A BT"
			font.pointSize: 64
			color: "black"
		}

		Button {
			anchors.centerIn: parent
			text: "Play"
			onClicked: player.playSong()
		}
	}
}
