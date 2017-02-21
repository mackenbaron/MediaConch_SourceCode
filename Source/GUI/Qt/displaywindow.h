/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a GPLv3+/MPLv2+ license that can
 *  be found in the License.html file in the root of the source tree.
 */

#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QFileInfo>
#include <QString>
#include <QStringList>
#include "commonwebwindow.h"

namespace MediaConch {

class DisplayWindow : public CommonWebWindow
{
public:
    explicit DisplayWindow(MainWindow* m);
    ~DisplayWindow();

    void display_display();

    int  add_new_file(const QString& name, const QString& filename);
    int  add_new_files(const QStringList& files);
    void export_file(const QString& name);
    void delete_file(const QString& name);

private:
    // Visual elements
    MainWindow   *main_window;
    WebView      *web_view;
    ProgressBar  *progress_bar;
    bool          is_finished;

    void create_html(QString& html);

    void create_html_display(QString& display);

    void create_html_base(QString& base, const QString& display);
    void set_webmachine_script_in_template(QString& base);
    void change_qt_scripts_in_template(QString& base);
    void change_checker_in_template(QString& base, const QString& display);
    void remove_result_in_template(QString& base);

    void fill_table();

    void create_web_view_finished(bool ok);
};

}

#endif // DISPLAYWINDOW_H
