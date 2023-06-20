#include "Settings.h"


void appStartUpSettings()
{
    // application controller initialization
    qmlRegisterSingletonType<ApplicationController>("App.Controller", 1, 0, "AppController", appControllerProvider);

    // Enable logging in QtCreator when available. Otherweise, log files will be created in the build tree.
    if(!qEnvironmentVariableIsEmpty("QTDIR"))
    {
        qDebug()<< QStringLiteral("QtCreator detected!");
        LoggingController::init();
    }
    else
    {
        LoggingController::init(true);
    }

#ifdef QT_DEBUG
     // For no logging, set the type to false. e.g "project.testClass.debug=false\n"
    // To show all debug logging, please set "*.debug=true\n"
  QLoggingCategory::setFilterRules(
              "*.debug=false\n"
      "project.applicationController.debug=true\n"
              "project.applicationController.warning=true\n"
              "project.applicationController.info=true\n"
              "project.applicationController.critical=true\n"
              "project.applicationController.fatal=true\n"
       "project.renamingEngine.debug=true\n"
              "project.renamingEngine.warning=true\n"
              "project.renamingEngine.info=true\n"
              "project.renamingEngine.critical=true\n"
              "project.renamingEngine.fatal=true\n"
        "project.applicationListModel.debug=true\n"
              "project.applicationListModel.info=true\n"
              "project.applicationListModel.critical=true\n"
              "project.applicationListModel.fatal=true\n"
      "");

#else
  QLoggingCategory::setFilterRules("*.debug=false\n"
                                   "");
#endif

}
