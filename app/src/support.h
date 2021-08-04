#ifndef SUPPORT_H
#define SUPPORT_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

/*!
 * \brief MessageBox:
 * Dialog with warning message.
 * \param msg: Message to display.
 */
inline void MessageBox(QString msg)
{
    QMessageBox::warning(nullptr,
                         "Error!",
                         msg,
                         QMessageBox::Ok);

    qCritical() << msg;
}

/*!
 * \brief startExplorer:
 * Starts the explorer with an argument.
 * \param argument: path to file or folder.
 */
inline void startExplorer(QString argument)
{
    if(argument.isEmpty()) return;

    QStringList list;
#ifdef _WIN32
    argument = argument.replace("/","\\");
#endif
    list << argument;
    if(list.isEmpty()) return;

    QString program;
#ifdef _WIN32
    program = "explorer";
#endif
#ifdef unix
    program = "xdg-open";
#endif

    QProcess::execute(program, list);
}

#endif // SUPPORT_H
