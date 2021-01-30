import QtQuick 2.2
import QtQuick.Dialogs 1.1

MessageDialog {
	id: messageBox;
	objectName: "msgBox";
	title: "";
	text: "";

	onAccepted: {
		Qt.quit()
	}
	
	onRejected: {
		Qt.quit()
	}

	function displayMessageBox(title: string, text: string) : int {
		messageBox.title = title;
		messageBox.text = text;
		messageBox.open();
		return 0;
	}
}