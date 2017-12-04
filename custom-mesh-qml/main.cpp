#include <QGuiApplication>
#include <Qt3DQuickExtras/Qt3DQuickWindow>
#include <QQmlApplicationEngine>

#include <CustomMesh.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register our custom type
    qmlRegisterType<CustomMesh>("Examples", 1, 0, "CustomMesh");

    Qt3DExtras::Quick::Qt3DQuickWindow view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
