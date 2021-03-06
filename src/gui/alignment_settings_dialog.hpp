#ifndef BIAS_ALIGNMENT_SETTINGS_DIALOG_HPP
#define BIAS_ALIGNMENT_SETTINSG_DIALOG_HPP

#include <QDialog>
#include <QMap>
#include "ui_alignment_settings_dialog.h"
#include "alignment_settings.hpp"

namespace bias
{

    class AlignmentSettingsDialog : public QDialog, public Ui::AlignmentSettingsDialog
    {
        Q_OBJECT

        public:

            AlignmentSettingsDialog(QWidget *parent=0);
            AlignmentSettingsDialog(AlignmentSettings settings, QWidget *parent=0);

        signals:

            void alignmentSettingsChanged(AlignmentSettings settings);

        private slots:

            void gridVisibleChanged(int state);
            void gridRowsChanged(int index);
            void gridColsChanged(int index);
            void gridColorChangeClicked();

            void ellipseVisibleChanged(int state);
            void ellipseColorChangeClicked();

        private:

            AlignmentSettings settings_;
            QMap<unsigned int, unsigned int> gridRowsValueToIndexMap_;
            QMap<unsigned int, unsigned int> gridColsValueToIndexMap_;
             
            void initialize();
            void initializeGridTab();
            void initializeEllipseTab();
            void connectWidgets();
            void updateSettings(AlignmentSettings settings);
            void setGridColorLabel(QColor color);
            void setEllipseColorLabel(QColor color);
    };

} // namespace bias

#endif // #ifndef BIAS_ALIGNMENT_SETTINGS_DIALOG_HPP
