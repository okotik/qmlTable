#include "qtquickplugin.h"
#include "processmodel.h"
#include "sortfilterprocessmodel.h"

#include <qqml.h>

QtquickPlugin::QtquickPlugin()
{

}

void QtquickPlugin::registerTypes(const char *url)
{
    ///якщо ми використовуємо дану комбінацію, яка є прописана нижже на рядок то ці 2 типи можна імпортувати в
    /// qml за допомогою дерективи  import org.lxqt.qps 1.0
// @uri org.lxqt.qps
    qmlRegisterType<ProcessModel>(url, 1, 0, "ProcessModel");
    qmlRegisterType<SortFilterProcessModel>(url, 1, 0, "SortFilterProcessModel");
}
