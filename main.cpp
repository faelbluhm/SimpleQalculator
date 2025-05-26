#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "calculatorlogic.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  CalculatorLogic logic;
  engine.rootContext()->setContextProperty("logic", &logic);

  QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreationFailed,
      &app,
      []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.loadFromModule("SimpleQalculator", "Main");

  return app.exec();
}
