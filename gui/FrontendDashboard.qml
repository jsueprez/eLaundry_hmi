import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "."

Item {
    id: frontendDashboard
    anchors.fill:  parent

    onVisibleChanged: {
        if (!visible) return

        backendDashboard.set_frontend(this)
        backendDashboard.on_show();
    }

    FrontendNovaLockersCarrousel {
        id: frontendNovaLockersCarrousel
        visible: true

    }
}
