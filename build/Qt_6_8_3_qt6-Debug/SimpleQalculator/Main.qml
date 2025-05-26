import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ApplicationWindow {
    visible: true
    minimumWidth: 400
    minimumHeight: 400
    title: "Simple Qalculator"
    Material.theme: Material.Dark

    property color numberColor: "#696969"

    ListModel {
        id: keypadModel
        ListElement { label: "%"; action: "percent" }
        ListElement { label: "7"; action: "digit" }
        ListElement { label: "8"; action: "digit" }
        ListElement { label: "9"; action: "digit" }
        ListElement { label: "÷"; action: "divide" }

        ListElement { label: "√"; action: "sqrt" }
        ListElement { label: "4"; action: "digit" }
        ListElement { label: "5"; action: "digit" }
        ListElement { label: "6"; action: "digit" }
        ListElement { label: "×"; action: "multiply" }

        ListElement { label: "²"; action: "square" }
        ListElement { label: "1"; action: "digit" }
        ListElement { label: "2"; action: "digit" }
        ListElement { label: "3"; action: "digit" }
        ListElement { label: "-"; action: "subtract" }

        ListElement { label: "C"; action: "clear" }
        ListElement { label: "0"; action: "digit" }
        ListElement { label: "."; action: "dot" }
        ListElement { label: "="; action: "calculate" }
        ListElement { label: "+"; action: "add" }
    }

    ColumnLayout {
        width: 360
        height: 400
        anchors.centerIn: parent
        spacing: 20

        // Display
        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: "#333333"
            radius: 8
            border.color: "#555555"

            FontLoader {
                id: digitalFont
                source: "qrc:/fonts/DS-DIGIB.TTF"
            }

            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 16
                text: logic ? logic.displayText : ""
                font.pixelSize: 44
                font.family: digitalFont.name
                color: "white"
                elide: Text.ElideLeft
            }
        }

        // Keypad
        GridLayout {
            id: grid
            Layout.alignment: Qt.AlignHCenter
            columns: 5
            rowSpacing: 10
            columnSpacing: 10
            focus: true

            // Keyboard
            Keys.onPressed: (event) => {
                event.accepted = true;

                if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                    logic.handleOperator("calculate");
                } else if (event.key === Qt.Key_Backspace) {
                    logic.deleteDigit();
                } else if (event.text) {
                    switch (event.text) {
                    case "0": case "1": case "2": case "3": case "4":
                    case "5": case "6": case "7": case "8": case "9":
                        logic.handleDigit(event.text);
                        break;
                    case "+":
                        logic.handleOperator("add");
                        break;
                    case "-":
                        logic.handleOperator("subtract");
                        break;
                    case "*": case "x": case "X":
                        logic.handleOperator("multiply");
                        break;
                    case "/":
                        logic.handleOperator("divide");
                        break;
                    case ".":
                        logic.handleDot();
                        break;
                    case "%":
                        logic.handleOperator("percent");
                        break;
                    case "=":
                        logic.handleOperator("calculate");
                        break;
                    case "c": case "C":
                        logic.clear();
                        break;
                    }
                }
            }

            Repeater {
                model: keypadModel

                Button {
                    objectName: "btn_" + model.label
                    text: model.label
                    Layout.preferredWidth: 65
                    Layout.preferredHeight: 60
                    focusPolicy: Qt.NoFocus

                    property string opAction: {
                        switch (text) {
                            case "+": return "add";
                            case "-": return "subtract";
                            case "×": return "multiply";
                            case "÷": return "divide";
                            case "%": return "percent";
                            case "²": return "square";
                            case "√": return "sqrt";
                            default: return "";
                        }
                    }

                    background: Rectangle {
                        color: {
                            if (model.action === "clear") return "red";
                            if (model.action === "digit") return numberColor;
                            if (logic && opAction !== "" && logic.currentOperator === opAction)
                                return "orange";
                            if (["+", "-", "×", "÷", "√", "%", "²", "="].includes(text)) return "#2b2b2b";
                            return numberColor;
                        }
                        radius: 8
                    }

                    onClicked: {
                        switch (model.action) {
                        case "clear": logic.clear(); break;
                        case "digit": logic.handleDigit(model.label); break;
                        case "dot": logic.handleDot(); break;
                        case "add":
                        case "subtract":
                        case "multiply":
                        case "divide":
                        case "square":
                        case "sqrt":
                        case "percent":
                        case "calculate":
                            logic.handleOperator(model.action);
                            break;
                        }
                    }
                }
            }
        }
    }
}
