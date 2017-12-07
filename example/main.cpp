#include <QApplication>
#include "samplewidget.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  SampleWidget sample;
  sample.show();

  return app.exec();
}
