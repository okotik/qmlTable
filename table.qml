import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4
import Qt.labs.qmlmodels
import org.lxqt.qps 1.0
import "."
//import "../content"

ApplicationWindow
{
    title: qsTr("top");
    width: 1300
    height: 700
    visible: true
    header: ToolBar
    {
        RowLayout
        {
            anchors.fill: parent
            Switch
            {
                id: cbUpdate
                checked: true
                text: qsTr("Update every")
            }
            SpinBox
            {
                id: sbUpdate
                from: 1
                to: 60
                value: 2
                enabled: cbUpdate.checked
            }
            Label
            {
                text: "sec"
            }
            Item
            {
                Layout.fillWidth: true
            }
            TextField
            {
                id: tfFilter
                implicitWidth: parent.width / 4
                onTextEdited: table.contentY = 0
            }
        }
    }
    Row
    {
        id: header
        width: table.contentWidth
        height: cbUpdate.height
        x: -table.contentX
        z: 1
        spacing: 4
        function forceLayout()
        {
            peter.model = 0
            peter.model = table.model.columnCount()
        }
        Repeater
        {
            id: peter
            model: table.model.columnCount()
            SortableColumnHeading
            {
                width: Math.min(600, table.model.columnWidth(index))
                height: parent.height
                text: table.model.headerData(index, Qt.Horizontal)
                onSorting:
                {
                    for(var i = 0; i < peter.model; ++i)
                        if(i !== index)
                            peter.itemAt(i).stopSorting()
                    table.model.sort(index, state === "up" ? Qt.AscendingOrder : Qt.DescendingOrder)
                }
                onDropped: (position) =>
                           {
                               table.model.reorderColumn(index, position)
                               header.forceLayout()
                           }

            }
        }
    }
    TableView
    {
        id: table
        anchors.fill: parent
        anchors.topMargin: header.height
        columnSpacing: 4
        rowSpacing: 4
        model: SortFilterProcessModel{filterText: tfFilter.text}
        Timer
        {
            interval: sbUpdate.value * 1000
            repeat: true
            running: cbUpdate.checked
            onTriggered: table.model.processModel.update()
        }
        columnWidthProvider: function (column) {return Math.min(600, model.columnWidth(column))}
        delegate: DelegateChooser
        {
            role: "type"
            DelegateChoice
            {
                roleValue: "%"
                BarGraph
                {
                    value: model.number
                }
            }

            DelegateChoice
            {
                roleValue: "string"
                Rectangle
                {
                    color: "#EEE"
                    implicitHeight: stringText.implicitHeight
                    Text
                    {
                        id: stringText
                        text: model.display
                        width: parent.width
                        elide: Text.ElideRight
                        font.preferShaping: false
                    }
                }
            }

            DelegateChoice
            {
                Rectangle
                {
                    color: "#EEE"
                    implicitHeight: defaultText.implicitHeight
                    Text
                    {
                        id: defaultText
                        text: model.display
                        width: parent.width
                        elide: Text.ElideRight
                        font.preferShaping: false
                    }
                }
            }
        }
        ScrollBar.horizontal: ScrollBar{}
        ScrollBar.vertical: ScrollBar{}
    }
    Shortcut {sequence: StandardKey.Quit; onActivated: Qt.quit()}
}
