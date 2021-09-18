#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <nestedwindow.h>
#include <QDebug>
#include <windows.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

//  NestedWindow nested_win;

  QQmlApplicationEngine engine;

 qmlRegisterType<NestedWindow>("NestedWindow.com",1,0,"NestedWindow");

//  QQmlContext* context = engine.rootContext();
//  context->setContextProperty("nestedWindow",&nested_win);

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);

  engine.load(url);

//  WId wid = 0;
//  QWindow *window =nullptr;
//  QObject* root_object =  engine.rootObjects().first();
//  if(root_object){
//      if(root_object->objectName() == "btn"){
//         window = qobject_cast<QWindow *>(root_object);
//         if(window){
//             wid = window->winId();
//           }
//        }else{

//              window =  root_object->findChild< QWindow*>("btn",Qt::FindChildrenRecursively);
//             if(window){
//                 wid = window->winId();
//               }

//        }
//    }

//  qDebug()<<"winId:"<<wid;
//  HWND hWnd = reinterpret_cast<HWND>(wid);
//  qDebug()<<"hWnd:"<<hWnd;

  return app.exec();
}
