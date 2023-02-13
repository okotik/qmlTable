import QtQuick

Rectangle
{
    id:root
    color: "wheat"
    property int initialSortOrder: Qt.AscendingOrder
    property alias text: label.text
    property real initialWidth: 100
    signal sorting
    signal dropped(real position)
    width: splitter.x + 6

    function stopSorting()
    {
        state = ""
    }

    Text
    {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        x: 4
        width: parent.width - 4
        text: table.model.headerData(index, Qt.Horizontal)
    }

    Text
    {
        id: upDownIndicator
        anchors.right: parent.right
        anchors.margins: 4
        anchors.verticalCenter: parent.verticalCenter
        text: "^"
        visible: false
    }

    TapHandler {id: tap; onTapped: nextState()}
    // робимо невидиму айтему, щоб можна було змінювати розмір колонок
    Item
    {
        id: splitter
        x: root.initialWidth - 6
        width: 12
        height: parent.height + 10

        HoverHandler
        {
                id: control
                //acceptedModifiers: Qt.ControlModifier
                cursorShape: Qt.SplitHCursor
        }

        DragHandler
        {
            yAxis.enabled: false
            onActiveChanged: if(!active) table.forceLayout()
        }
    }

    //дозволяє змінювати місця в колонках
    DragHandler
    {
        id: dragHandler
        onActiveChanged: if(!active) root.dropped(centroid.scenePosition.x)
    }

    function nextState()
    {
        if(state === "up")
            state = "down"
        else
            state = "up"
        root.sorting()
    }

    states:
        [
        State
        {
            name: "up"
            PropertyChanges {target: upDownIndicator; visible: true; rotation: 0}
            PropertyChanges {target: root; color: "orange"}
        },
        State
        {
            name: "down"
            PropertyChanges {target: upDownIndicator; visible: true; rotation: 180}
            PropertyChanges {target: root; color: "orange"}
        }
    ]
}
