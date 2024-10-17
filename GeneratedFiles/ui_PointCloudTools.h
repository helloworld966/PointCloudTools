/********************************************************************************
** Form generated from reading UI file 'PointCloudTools.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTCLOUDTOOLS_H
#define UI_POINTCLOUDTOOLS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_PointCloudToolsClass
{
public:
    QAction *open;
    QAction *clear;
    QAction *save;
    QAction *action1_2;
    QAction *actionOrigin;
    QAction *actionLight;
    QAction *actionDark;
    QAction *actionEnglish;
    QAction *actionChinese;
    QAction *meshsurfaceAction;
    QAction *wireframeAction;
    QAction *AddAction;
    QAction *actionPlanFit;
    QAction *mainwindowaction;
    QAction *leftviewaction;
    QAction *topviewaction;
    QAction *resetviewaction;
    QAction *exit;
    QAction *sphereAction;
    QAction *pickingaction;
    QAction *segmentationAction;
    QAction *actionPassThrough;
    QAction *actionStatisticalOutlierRemoval;
    QAction *actionRegionGrowing;
    QAction *actionColorBasedRegionGrowing;
    QAction *RegistrationAction;
    QAction *showleafnodeaction;
    QAction *boxaction;
    QWidget *centralWidget;
    QDockWidget *consoleDock;
    QWidget *dockWidgetContents_7;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *consoleTable;
    QWidget *widget;
    QVTKWidget *qvtkWidget;
    QDockWidget *propertyDock;
    QWidget *dockWidgetContents_6;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *propertyTable;
    QDockWidget *dataDock;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *dataTree;
    QDockWidget *filterDock;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout;
    QTabWidget *filterTab;
    QWidget *filterTab1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_12;
    QLabel *axis;
    QComboBox *axis_input;
    QHBoxLayout *horizontalLayout_14;
    QLabel *lower_limit;
    QLineEdit *lower_limit_input;
    QHBoxLayout *horizontalLayout_15;
    QLabel *upper_limit;
    QLineEdit *upper_limit_input;
    QPushButton *passthrough_confirm;
    QSpacerItem *verticalSpacer;
    QWidget *filterTab2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_16;
    QLabel *negative;
    QComboBox *negative_input;
    QHBoxLayout *horizontalLayout_17;
    QLabel *meank;
    QLineEdit *meank_input;
    QHBoxLayout *horizontalLayout_18;
    QLabel *stddev;
    QLineEdit *stddev_input;
    QPushButton *statistical_confirm;
    QSpacerItem *verticalSpacer_2;
    QDockWidget *regionGrowingDock;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QTabWidget *rgTab;
    QWidget *rgTab1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *ksearch;
    QLineEdit *ksearch_input;
    QHBoxLayout *horizontalLayout_2;
    QLabel *min_cluster_size;
    QLineEdit *min_cluster_size_input;
    QHBoxLayout *horizontalLayout_3;
    QLabel *max_cluster_size;
    QLineEdit *max_cluster_size_input;
    QHBoxLayout *horizontalLayout_4;
    QLabel *neighbour_num;
    QLineEdit *neighbour_num_input;
    QHBoxLayout *horizontalLayout_6;
    QLabel *smoothness_theta;
    QLineEdit *smoothness_theta_input;
    QHBoxLayout *horizontalLayout_7;
    QLabel *curvature;
    QLineEdit *curvature_input;
    QPushButton *basic_confirm;
    QSpacerItem *basic_verticalSpacer;
    QWidget *rgTab2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *min_cluster_size2;
    QLineEdit *min_cluster_size2_input;
    QHBoxLayout *horizontalLayout_9;
    QLabel *neighbours_dist;
    QLineEdit *neighbours_dist_input;
    QHBoxLayout *horizontalLayout_10;
    QLabel *point_color_diff;
    QLineEdit *point_color_diff_input;
    QHBoxLayout *horizontalLayout_11;
    QLabel *region_color_diff;
    QLineEdit *region_color_diff_input;
    QPushButton *color_confirm;
    QSpacerItem *color_verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PointCloudToolsClass)
    {
        if (PointCloudToolsClass->objectName().isEmpty())
            PointCloudToolsClass->setObjectName(QString::fromUtf8("PointCloudToolsClass"));
        PointCloudToolsClass->resize(1364, 859);
        QFont font;
        font.setPointSize(10);
        PointCloudToolsClass->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/PointCloudTools/icon/Selection_Out.svg"), QSize(), QIcon::Normal, QIcon::Off);
        PointCloudToolsClass->setWindowIcon(icon);
        open = new QAction(PointCloudToolsClass);
        open->setObjectName(QString::fromUtf8("open"));
        clear = new QAction(PointCloudToolsClass);
        clear->setObjectName(QString::fromUtf8("clear"));
        save = new QAction(PointCloudToolsClass);
        save->setObjectName(QString::fromUtf8("save"));
        action1_2 = new QAction(PointCloudToolsClass);
        action1_2->setObjectName(QString::fromUtf8("action1_2"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/PointCloudTools/icon/disconnect.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action1_2->setIcon(icon1);
        actionOrigin = new QAction(PointCloudToolsClass);
        actionOrigin->setObjectName(QString::fromUtf8("actionOrigin"));
        actionLight = new QAction(PointCloudToolsClass);
        actionLight->setObjectName(QString::fromUtf8("actionLight"));
        actionDark = new QAction(PointCloudToolsClass);
        actionDark->setObjectName(QString::fromUtf8("actionDark"));
        actionEnglish = new QAction(PointCloudToolsClass);
        actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
        actionChinese = new QAction(PointCloudToolsClass);
        actionChinese->setObjectName(QString::fromUtf8("actionChinese"));
        meshsurfaceAction = new QAction(PointCloudToolsClass);
        meshsurfaceAction->setObjectName(QString::fromUtf8("meshsurfaceAction"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/PointCloudTools/icon/tool_curve.svg"), QSize(), QIcon::Normal, QIcon::Off);
        meshsurfaceAction->setIcon(icon2);
        wireframeAction = new QAction(PointCloudToolsClass);
        wireframeAction->setObjectName(QString::fromUtf8("wireframeAction"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/PointCloudTools/icon/map-gnomonic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        wireframeAction->setIcon(icon3);
        AddAction = new QAction(PointCloudToolsClass);
        AddAction->setObjectName(QString::fromUtf8("AddAction"));
        actionPlanFit = new QAction(PointCloudToolsClass);
        actionPlanFit->setObjectName(QString::fromUtf8("actionPlanFit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/PointCloudTools/icon/show-gpu-effects.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlanFit->setIcon(icon4);
        mainwindowaction = new QAction(PointCloudToolsClass);
        mainwindowaction->setObjectName(QString::fromUtf8("mainwindowaction"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/PointCloudTools/icon/view_front.svg"), QSize(), QIcon::Normal, QIcon::Off);
        mainwindowaction->setIcon(icon5);
        leftviewaction = new QAction(PointCloudToolsClass);
        leftviewaction->setObjectName(QString::fromUtf8("leftviewaction"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/PointCloudTools/icon/view_leftside.svg"), QSize(), QIcon::Normal, QIcon::Off);
        leftviewaction->setIcon(icon6);
        topviewaction = new QAction(PointCloudToolsClass);
        topviewaction->setObjectName(QString::fromUtf8("topviewaction"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/PointCloudTools/icon/view_top.svg"), QSize(), QIcon::Normal, QIcon::Off);
        topviewaction->setIcon(icon7);
        resetviewaction = new QAction(PointCloudToolsClass);
        resetviewaction->setObjectName(QString::fromUtf8("resetviewaction"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/PointCloudTools/icon/view-refresh.svg"), QSize(), QIcon::Normal, QIcon::Off);
        resetviewaction->setIcon(icon8);
        exit = new QAction(PointCloudToolsClass);
        exit->setObjectName(QString::fromUtf8("exit"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/PointCloudTools/icon/application-exit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        exit->setIcon(icon9);
        sphereAction = new QAction(PointCloudToolsClass);
        sphereAction->setObjectName(QString::fromUtf8("sphereAction"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/PointCloudTools/icon/snap-nodes-smooth.svg"), QSize(), QIcon::Normal, QIcon::Off);
        sphereAction->setIcon(icon10);
        pickingaction = new QAction(PointCloudToolsClass);
        pickingaction->setObjectName(QString::fromUtf8("pickingaction"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/PointCloudTools/icon/window-restore.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pickingaction->setIcon(icon11);
        segmentationAction = new QAction(PointCloudToolsClass);
        segmentationAction->setObjectName(QString::fromUtf8("segmentationAction"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/PointCloudTools/icon/dependency.svg"), QSize(), QIcon::Normal, QIcon::Off);
        segmentationAction->setIcon(icon12);
        actionPassThrough = new QAction(PointCloudToolsClass);
        actionPassThrough->setObjectName(QString::fromUtf8("actionPassThrough"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/PointCloudTools/icon/atmosphere.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPassThrough->setIcon(icon13);
        actionStatisticalOutlierRemoval = new QAction(PointCloudToolsClass);
        actionStatisticalOutlierRemoval->setObjectName(QString::fromUtf8("actionStatisticalOutlierRemoval"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/PointCloudTools/icon/clear.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionStatisticalOutlierRemoval->setIcon(icon14);
        actionRegionGrowing = new QAction(PointCloudToolsClass);
        actionRegionGrowing->setObjectName(QString::fromUtf8("actionRegionGrowing"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/PointCloudTools/icon/channelmixer.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRegionGrowing->setIcon(icon15);
        actionColorBasedRegionGrowing = new QAction(PointCloudToolsClass);
        actionColorBasedRegionGrowing->setObjectName(QString::fromUtf8("actionColorBasedRegionGrowing"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/PointCloudTools/icon/filename-moodbar.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionColorBasedRegionGrowing->setIcon(icon16);
        RegistrationAction = new QAction(PointCloudToolsClass);
        RegistrationAction->setObjectName(QString::fromUtf8("RegistrationAction"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/PointCloudTools/icon/office-chart-polar.svg"), QSize(), QIcon::Normal, QIcon::Off);
        RegistrationAction->setIcon(icon17);
        showleafnodeaction = new QAction(PointCloudToolsClass);
        showleafnodeaction->setObjectName(QString::fromUtf8("showleafnodeaction"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/PointCloudTools/icon/object-ungroup-symbolic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        showleafnodeaction->setIcon(icon18);
        boxaction = new QAction(PointCloudToolsClass);
        boxaction->setObjectName(QString::fromUtf8("boxaction"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/PointCloudTools/icon/draw-cuboid.svg"), QSize(), QIcon::Normal, QIcon::Off);
        boxaction->setIcon(icon19);
        centralWidget = new QWidget(PointCloudToolsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        consoleDock = new QDockWidget(centralWidget);
        consoleDock->setObjectName(QString::fromUtf8("consoleDock"));
        consoleDock->setGeometry(QRect(0, 600, 1361, 211));
        consoleDock->setMinimumSize(QSize(200, 140));
        consoleDock->setMaximumSize(QSize(524287, 220));
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QString::fromUtf8("dockWidgetContents_7"));
        verticalLayout_5 = new QVBoxLayout(dockWidgetContents_7);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        consoleTable = new QTableWidget(dockWidgetContents_7);
        if (consoleTable->columnCount() < 5)
            consoleTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        consoleTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        consoleTable->setObjectName(QString::fromUtf8("consoleTable"));
        consoleTable->setShowGrid(false);
        consoleTable->setGridStyle(Qt::SolidLine);
        consoleTable->setRowCount(0);
        consoleTable->setColumnCount(5);
        consoleTable->horizontalHeader()->setVisible(true);
        consoleTable->horizontalHeader()->setDefaultSectionSize(200);
        consoleTable->horizontalHeader()->setStretchLastSection(true);
        consoleTable->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(consoleTable);

        consoleDock->setWidget(dockWidgetContents_7);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(280, 0, 791, 591));
        qvtkWidget = new QVTKWidget(widget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, -10, 791, 601));
        propertyDock = new QDockWidget(centralWidget);
        propertyDock->setObjectName(QString::fromUtf8("propertyDock"));
        propertyDock->setGeometry(QRect(0, 280, 281, 321));
        propertyDock->setMinimumSize(QSize(250, 233));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        propertyDock->setFont(font1);
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_6);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        propertyTable = new QTableWidget(dockWidgetContents_6);
        if (propertyTable->columnCount() < 2)
            propertyTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        propertyTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        propertyTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        if (propertyTable->rowCount() < 4)
            propertyTable->setRowCount(4);
        propertyTable->setObjectName(QString::fromUtf8("propertyTable"));
        propertyTable->setMinimumSize(QSize(0, 180));
        QFont font2;
        font2.setPointSize(9);
        propertyTable->setFont(font2);
        propertyTable->setFrameShadow(QFrame::Sunken);
        propertyTable->setMidLineWidth(0);
        propertyTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        propertyTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        propertyTable->setAutoScroll(true);
        propertyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        propertyTable->setTabKeyNavigation(true);
        propertyTable->setProperty("showDropIndicator", QVariant(true));
        propertyTable->setDragDropOverwriteMode(true);
        propertyTable->setAlternatingRowColors(false);
        propertyTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        propertyTable->setTextElideMode(Qt::ElideLeft);
        propertyTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        propertyTable->setShowGrid(false);
        propertyTable->setWordWrap(true);
        propertyTable->setCornerButtonEnabled(true);
        propertyTable->setRowCount(4);
        propertyTable->setColumnCount(2);
        propertyTable->horizontalHeader()->setCascadingSectionResizes(false);
        propertyTable->horizontalHeader()->setMinimumSectionSize(25);
        propertyTable->horizontalHeader()->setDefaultSectionSize(100);
        propertyTable->horizontalHeader()->setHighlightSections(true);
        propertyTable->horizontalHeader()->setStretchLastSection(true);
        propertyTable->verticalHeader()->setVisible(false);
        propertyTable->verticalHeader()->setCascadingSectionResizes(false);

        verticalLayout_4->addWidget(propertyTable);

        propertyDock->setWidget(dockWidgetContents_6);
        dataDock = new QDockWidget(centralWidget);
        dataDock->setObjectName(QString::fromUtf8("dataDock"));
        dataDock->setGeometry(QRect(0, 0, 281, 281));
        dataDock->setMinimumSize(QSize(250, 233));
        dataDock->setMaximumSize(QSize(300, 524287));
        dataDock->setFont(font1);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        dataTree = new QTreeWidget(dockWidgetContents_5);
        dataTree->setObjectName(QString::fromUtf8("dataTree"));
        dataTree->setMinimumSize(QSize(0, 180));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(9);
        dataTree->setFont(font3);
        dataTree->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_3->addWidget(dataTree);

        dataDock->setWidget(dockWidgetContents_5);
        filterDock = new QDockWidget(centralWidget);
        filterDock->setObjectName(QString::fromUtf8("filterDock"));
        filterDock->setGeometry(QRect(1070, 0, 291, 252));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        gridLayout = new QGridLayout(dockWidgetContents_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        filterTab = new QTabWidget(dockWidgetContents_2);
        filterTab->setObjectName(QString::fromUtf8("filterTab"));
        filterTab1 = new QWidget();
        filterTab1->setObjectName(QString::fromUtf8("filterTab1"));
        verticalLayout = new QVBoxLayout(filterTab1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        axis = new QLabel(filterTab1);
        axis->setObjectName(QString::fromUtf8("axis"));

        horizontalLayout_12->addWidget(axis);

        axis_input = new QComboBox(filterTab1);
        axis_input->addItem(QString());
        axis_input->addItem(QString());
        axis_input->addItem(QString());
        axis_input->setObjectName(QString::fromUtf8("axis_input"));

        horizontalLayout_12->addWidget(axis_input);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        lower_limit = new QLabel(filterTab1);
        lower_limit->setObjectName(QString::fromUtf8("lower_limit"));

        horizontalLayout_14->addWidget(lower_limit);

        lower_limit_input = new QLineEdit(filterTab1);
        lower_limit_input->setObjectName(QString::fromUtf8("lower_limit_input"));

        horizontalLayout_14->addWidget(lower_limit_input);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        upper_limit = new QLabel(filterTab1);
        upper_limit->setObjectName(QString::fromUtf8("upper_limit"));

        horizontalLayout_15->addWidget(upper_limit);

        upper_limit_input = new QLineEdit(filterTab1);
        upper_limit_input->setObjectName(QString::fromUtf8("upper_limit_input"));

        horizontalLayout_15->addWidget(upper_limit_input);


        verticalLayout->addLayout(horizontalLayout_15);

        passthrough_confirm = new QPushButton(filterTab1);
        passthrough_confirm->setObjectName(QString::fromUtf8("passthrough_confirm"));

        verticalLayout->addWidget(passthrough_confirm);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        filterTab->addTab(filterTab1, QString());
        filterTab2 = new QWidget();
        filterTab2->setObjectName(QString::fromUtf8("filterTab2"));
        verticalLayout_6 = new QVBoxLayout(filterTab2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        negative = new QLabel(filterTab2);
        negative->setObjectName(QString::fromUtf8("negative"));

        horizontalLayout_16->addWidget(negative);

        negative_input = new QComboBox(filterTab2);
        negative_input->addItem(QString());
        negative_input->addItem(QString());
        negative_input->setObjectName(QString::fromUtf8("negative_input"));

        horizontalLayout_16->addWidget(negative_input);


        verticalLayout_6->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        meank = new QLabel(filterTab2);
        meank->setObjectName(QString::fromUtf8("meank"));

        horizontalLayout_17->addWidget(meank);

        meank_input = new QLineEdit(filterTab2);
        meank_input->setObjectName(QString::fromUtf8("meank_input"));

        horizontalLayout_17->addWidget(meank_input);


        verticalLayout_6->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        stddev = new QLabel(filterTab2);
        stddev->setObjectName(QString::fromUtf8("stddev"));

        horizontalLayout_18->addWidget(stddev);

        stddev_input = new QLineEdit(filterTab2);
        stddev_input->setObjectName(QString::fromUtf8("stddev_input"));

        horizontalLayout_18->addWidget(stddev_input);


        verticalLayout_6->addLayout(horizontalLayout_18);

        statistical_confirm = new QPushButton(filterTab2);
        statistical_confirm->setObjectName(QString::fromUtf8("statistical_confirm"));

        verticalLayout_6->addWidget(statistical_confirm);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);

        filterTab->addTab(filterTab2, QString());

        gridLayout->addWidget(filterTab, 0, 0, 1, 1);

        filterDock->setWidget(dockWidgetContents_2);
        regionGrowingDock = new QDockWidget(centralWidget);
        regionGrowingDock->setObjectName(QString::fromUtf8("regionGrowingDock"));
        regionGrowingDock->setEnabled(true);
        regionGrowingDock->setGeometry(QRect(1070, 250, 291, 341));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rgTab = new QTabWidget(dockWidgetContents);
        rgTab->setObjectName(QString::fromUtf8("rgTab"));
        rgTab1 = new QWidget();
        rgTab1->setObjectName(QString::fromUtf8("rgTab1"));
        verticalLayout_2 = new QVBoxLayout(rgTab1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ksearch = new QLabel(rgTab1);
        ksearch->setObjectName(QString::fromUtf8("ksearch"));

        horizontalLayout->addWidget(ksearch);

        ksearch_input = new QLineEdit(rgTab1);
        ksearch_input->setObjectName(QString::fromUtf8("ksearch_input"));
        ksearch_input->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(ksearch_input);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        min_cluster_size = new QLabel(rgTab1);
        min_cluster_size->setObjectName(QString::fromUtf8("min_cluster_size"));

        horizontalLayout_2->addWidget(min_cluster_size);

        min_cluster_size_input = new QLineEdit(rgTab1);
        min_cluster_size_input->setObjectName(QString::fromUtf8("min_cluster_size_input"));

        horizontalLayout_2->addWidget(min_cluster_size_input);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        max_cluster_size = new QLabel(rgTab1);
        max_cluster_size->setObjectName(QString::fromUtf8("max_cluster_size"));

        horizontalLayout_3->addWidget(max_cluster_size);

        max_cluster_size_input = new QLineEdit(rgTab1);
        max_cluster_size_input->setObjectName(QString::fromUtf8("max_cluster_size_input"));

        horizontalLayout_3->addWidget(max_cluster_size_input);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        neighbour_num = new QLabel(rgTab1);
        neighbour_num->setObjectName(QString::fromUtf8("neighbour_num"));

        horizontalLayout_4->addWidget(neighbour_num);

        neighbour_num_input = new QLineEdit(rgTab1);
        neighbour_num_input->setObjectName(QString::fromUtf8("neighbour_num_input"));

        horizontalLayout_4->addWidget(neighbour_num_input);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        smoothness_theta = new QLabel(rgTab1);
        smoothness_theta->setObjectName(QString::fromUtf8("smoothness_theta"));

        horizontalLayout_6->addWidget(smoothness_theta);

        smoothness_theta_input = new QLineEdit(rgTab1);
        smoothness_theta_input->setObjectName(QString::fromUtf8("smoothness_theta_input"));

        horizontalLayout_6->addWidget(smoothness_theta_input);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        curvature = new QLabel(rgTab1);
        curvature->setObjectName(QString::fromUtf8("curvature"));

        horizontalLayout_7->addWidget(curvature);

        curvature_input = new QLineEdit(rgTab1);
        curvature_input->setObjectName(QString::fromUtf8("curvature_input"));

        horizontalLayout_7->addWidget(curvature_input);


        verticalLayout_2->addLayout(horizontalLayout_7);

        basic_confirm = new QPushButton(rgTab1);
        basic_confirm->setObjectName(QString::fromUtf8("basic_confirm"));

        verticalLayout_2->addWidget(basic_confirm);

        basic_verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(basic_verticalSpacer);

        rgTab->addTab(rgTab1, QString());
        rgTab2 = new QWidget();
        rgTab2->setObjectName(QString::fromUtf8("rgTab2"));
        verticalLayout_7 = new QVBoxLayout(rgTab2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        min_cluster_size2 = new QLabel(rgTab2);
        min_cluster_size2->setObjectName(QString::fromUtf8("min_cluster_size2"));

        horizontalLayout_8->addWidget(min_cluster_size2);

        min_cluster_size2_input = new QLineEdit(rgTab2);
        min_cluster_size2_input->setObjectName(QString::fromUtf8("min_cluster_size2_input"));

        horizontalLayout_8->addWidget(min_cluster_size2_input);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        neighbours_dist = new QLabel(rgTab2);
        neighbours_dist->setObjectName(QString::fromUtf8("neighbours_dist"));

        horizontalLayout_9->addWidget(neighbours_dist);

        neighbours_dist_input = new QLineEdit(rgTab2);
        neighbours_dist_input->setObjectName(QString::fromUtf8("neighbours_dist_input"));

        horizontalLayout_9->addWidget(neighbours_dist_input);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        point_color_diff = new QLabel(rgTab2);
        point_color_diff->setObjectName(QString::fromUtf8("point_color_diff"));

        horizontalLayout_10->addWidget(point_color_diff);

        point_color_diff_input = new QLineEdit(rgTab2);
        point_color_diff_input->setObjectName(QString::fromUtf8("point_color_diff_input"));

        horizontalLayout_10->addWidget(point_color_diff_input);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        region_color_diff = new QLabel(rgTab2);
        region_color_diff->setObjectName(QString::fromUtf8("region_color_diff"));

        horizontalLayout_11->addWidget(region_color_diff);

        region_color_diff_input = new QLineEdit(rgTab2);
        region_color_diff_input->setObjectName(QString::fromUtf8("region_color_diff_input"));

        horizontalLayout_11->addWidget(region_color_diff_input);


        verticalLayout_7->addLayout(horizontalLayout_11);

        color_confirm = new QPushButton(rgTab2);
        color_confirm->setObjectName(QString::fromUtf8("color_confirm"));

        verticalLayout_7->addWidget(color_confirm);

        color_verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(color_verticalSpacer);

        rgTab->addTab(rgTab2, QString());

        gridLayout_2->addWidget(rgTab, 1, 0, 1, 1);

        regionGrowingDock->setWidget(dockWidgetContents);
        PointCloudToolsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PointCloudToolsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1364, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menu_2);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        PointCloudToolsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PointCloudToolsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PointCloudToolsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PointCloudToolsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PointCloudToolsClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(open);
        menu->addAction(AddAction);
        menu->addAction(clear);
        menu->addAction(save);
        menu->addAction(exit);
        menu_2->addAction(menu_3->menuAction());
        menu_2->addAction(menu_4->menuAction());
        menu_3->addAction(actionOrigin);
        menu_3->addAction(actionLight);
        menu_3->addAction(actionDark);
        menu_4->addAction(actionEnglish);
        menu_4->addAction(actionChinese);
        menu_5->addAction(actionPassThrough);
        menu_5->addAction(actionStatisticalOutlierRemoval);
        mainToolBar->addAction(action1_2);
        mainToolBar->addSeparator();
        mainToolBar->addAction(meshsurfaceAction);
        mainToolBar->addAction(wireframeAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(pickingaction);
        mainToolBar->addAction(actionPlanFit);
        mainToolBar->addAction(sphereAction);
        mainToolBar->addAction(segmentationAction);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPassThrough);
        mainToolBar->addAction(actionStatisticalOutlierRemoval);
        mainToolBar->addSeparator();
        mainToolBar->addAction(mainwindowaction);
        mainToolBar->addAction(leftviewaction);
        mainToolBar->addAction(topviewaction);
        mainToolBar->addAction(resetviewaction);
        mainToolBar->addAction(actionRegionGrowing);
        mainToolBar->addAction(actionColorBasedRegionGrowing);
        mainToolBar->addSeparator();
        mainToolBar->addAction(RegistrationAction);
        mainToolBar->addAction(showleafnodeaction);
        mainToolBar->addAction(boxaction);

        retranslateUi(PointCloudToolsClass);

        filterTab->setCurrentIndex(1);
        rgTab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PointCloudToolsClass);
    } // setupUi

    void retranslateUi(QMainWindow *PointCloudToolsClass)
    {
        PointCloudToolsClass->setWindowTitle(QApplication::translate("PointCloudToolsClass", "\347\202\271\344\272\221\345\244\204\347\220\206", nullptr));
        open->setText(QApplication::translate("PointCloudToolsClass", "\346\211\223\345\274\200", nullptr));
        clear->setText(QApplication::translate("PointCloudToolsClass", "\346\270\205\351\231\244", nullptr));
        save->setText(QApplication::translate("PointCloudToolsClass", "\344\277\235\345\255\230", nullptr));
        action1_2->setText(QApplication::translate("PointCloudToolsClass", "1", nullptr));
        actionOrigin->setText(QApplication::translate("PointCloudToolsClass", "\345\216\237\345\247\213", nullptr));
        actionLight->setText(QApplication::translate("PointCloudToolsClass", "\344\272\256", nullptr));
        actionDark->setText(QApplication::translate("PointCloudToolsClass", "\346\232\227", nullptr));
        actionEnglish->setText(QApplication::translate("PointCloudToolsClass", "\350\213\261\350\257\255", nullptr));
        actionChinese->setText(QApplication::translate("PointCloudToolsClass", "\344\270\255\346\226\207", nullptr));
        meshsurfaceAction->setText(QApplication::translate("PointCloudToolsClass", "\346\233\262\347\272\277\351\235\242\347\211\207", nullptr));
        wireframeAction->setText(QApplication::translate("PointCloudToolsClass", "\346\233\262\347\272\277\347\275\221\346\240\274", nullptr));
        AddAction->setText(QApplication::translate("PointCloudToolsClass", "\346\267\273\345\212\240\347\202\271\344\272\221\346\250\241\345\236\213", nullptr));
        actionPlanFit->setText(QApplication::translate("PointCloudToolsClass", "\345\271\263\351\235\242\346\213\237\345\220\210", nullptr));
        mainwindowaction->setText(QApplication::translate("PointCloudToolsClass", "\344\270\273\350\247\206\345\233\276", nullptr));
        leftviewaction->setText(QApplication::translate("PointCloudToolsClass", "\345\267\246\350\247\206\345\233\276", nullptr));
        topviewaction->setText(QApplication::translate("PointCloudToolsClass", "\351\241\266\350\247\206\345\233\276", nullptr));
        resetviewaction->setText(QApplication::translate("PointCloudToolsClass", "\351\207\215\347\275\256\350\247\206\345\233\276", nullptr));
        exit->setText(QApplication::translate("PointCloudToolsClass", "\351\200\200\345\207\272", nullptr));
        sphereAction->setText(QApplication::translate("PointCloudToolsClass", "\347\220\203\351\235\242\346\213\237\345\220\210", nullptr));
        pickingaction->setText(QApplication::translate("PointCloudToolsClass", "\346\241\206\351\200\211\347\202\271\344\272\221", nullptr));
        segmentationAction->setText(QApplication::translate("PointCloudToolsClass", "\345\210\206\345\211\262", nullptr));
        actionPassThrough->setText(QApplication::translate("PointCloudToolsClass", "\347\233\264\351\200\232\346\273\244\346\263\242\345\231\250", nullptr));
        actionStatisticalOutlierRemoval->setText(QApplication::translate("PointCloudToolsClass", "\347\273\237\350\256\241\345\274\202\345\270\270\345\200\274\345\216\273\351\231\244\350\277\207\346\273\244\345\231\250", nullptr));
        actionRegionGrowing->setText(QApplication::translate("PointCloudToolsClass", "\345\210\206\345\211\262\345\214\272\345\237\237", nullptr));
        actionColorBasedRegionGrowing->setText(QApplication::translate("PointCloudToolsClass", "\351\242\234\350\211\262\345\237\272\347\241\200\345\210\206\345\211\262\345\214\272\345\237\237", nullptr));
        RegistrationAction->setText(QApplication::translate("PointCloudToolsClass", "\351\205\215\345\207\206", nullptr));
        showleafnodeaction->setText(QApplication::translate("PointCloudToolsClass", "\345\261\225\347\244\272\345\217\266\345\255\220\350\212\202\347\202\271", nullptr));
        boxaction->setText(QApplication::translate("PointCloudToolsClass", "\347\224\273\345\214\205\345\233\264\347\233\222", nullptr));
        consoleDock->setWindowTitle(QApplication::translate("PointCloudToolsClass", "Console", nullptr));
        QTableWidgetItem *___qtablewidgetitem = consoleTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PointCloudToolsClass", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = consoleTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PointCloudToolsClass", "Operation", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = consoleTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PointCloudToolsClass", "Operation obeject", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = consoleTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PointCloudToolsClass", "Details", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = consoleTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("PointCloudToolsClass", "Note", nullptr));
        propertyDock->setWindowTitle(QApplication::translate("PointCloudToolsClass", "Properties", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = propertyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("PointCloudToolsClass", "Property", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = propertyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("PointCloudToolsClass", "Value", nullptr));
        dataDock->setWindowTitle(QApplication::translate("PointCloudToolsClass", "PointCloud", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = dataTree->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("PointCloudToolsClass", "Point Cloud File", nullptr));
        filterDock->setWindowTitle(QApplication::translate("PointCloudToolsClass", "Filter Config", nullptr));
        axis->setText(QApplication::translate("PointCloudToolsClass", "Axis", nullptr));
        axis_input->setItemText(0, QApplication::translate("PointCloudToolsClass", "x", nullptr));
        axis_input->setItemText(1, QApplication::translate("PointCloudToolsClass", "y", nullptr));
        axis_input->setItemText(2, QApplication::translate("PointCloudToolsClass", "z", nullptr));

        lower_limit->setText(QApplication::translate("PointCloudToolsClass", "Lower limit", nullptr));
        lower_limit_input->setText(QApplication::translate("PointCloudToolsClass", "0.0", nullptr));
        upper_limit->setText(QApplication::translate("PointCloudToolsClass", "Upper limit", nullptr));
        upper_limit_input->setText(QApplication::translate("PointCloudToolsClass", "1.0", nullptr));
        passthrough_confirm->setText(QApplication::translate("PointCloudToolsClass", "Confirm", nullptr));
        filterTab->setTabText(filterTab->indexOf(filterTab1), QApplication::translate("PointCloudToolsClass", "Passthrough", nullptr));
        negative->setText(QApplication::translate("PointCloudToolsClass", "Negative Select", nullptr));
        negative_input->setItemText(0, QApplication::translate("PointCloudToolsClass", "True", nullptr));
        negative_input->setItemText(1, QApplication::translate("PointCloudToolsClass", "False", nullptr));

        meank->setText(QApplication::translate("PointCloudToolsClass", "Mean K", nullptr));
        meank_input->setText(QApplication::translate("PointCloudToolsClass", "50", nullptr));
        stddev->setText(QApplication::translate("PointCloudToolsClass", "Standard deviation", nullptr));
        stddev_input->setText(QApplication::translate("PointCloudToolsClass", "1.0", nullptr));
        statistical_confirm->setText(QApplication::translate("PointCloudToolsClass", "Confirm", nullptr));
        filterTab->setTabText(filterTab->indexOf(filterTab2), QApplication::translate("PointCloudToolsClass", "Statistical", nullptr));
        regionGrowingDock->setWindowTitle(QApplication::translate("PointCloudToolsClass", "Region Growing Config", nullptr));
        ksearch->setText(QApplication::translate("PointCloudToolsClass", "K Search", nullptr));
        ksearch_input->setText(QApplication::translate("PointCloudToolsClass", "50", nullptr));
        min_cluster_size->setText(QApplication::translate("PointCloudToolsClass", "Min Cluster Size", nullptr));
        min_cluster_size_input->setText(QApplication::translate("PointCloudToolsClass", "50", nullptr));
        max_cluster_size->setText(QApplication::translate("PointCloudToolsClass", "Max Cluster Size", nullptr));
        max_cluster_size_input->setText(QApplication::translate("PointCloudToolsClass", "1000000", nullptr));
        neighbour_num->setText(QApplication::translate("PointCloudToolsClass", "Neighbour Num", nullptr));
        neighbour_num_input->setText(QApplication::translate("PointCloudToolsClass", "30", nullptr));
        smoothness_theta->setText(QApplication::translate("PointCloudToolsClass", "Smoothness Theta", nullptr));
        smoothness_theta_input->setText(QApplication::translate("PointCloudToolsClass", "0.052359878", nullptr));
        curvature->setText(QApplication::translate("PointCloudToolsClass", "Curvature", nullptr));
        curvature_input->setText(QApplication::translate("PointCloudToolsClass", "1.0", nullptr));
        basic_confirm->setText(QApplication::translate("PointCloudToolsClass", "Confirm", nullptr));
        rgTab->setTabText(rgTab->indexOf(rgTab1), QApplication::translate("PointCloudToolsClass", "Basic", nullptr));
        min_cluster_size2->setText(QApplication::translate("PointCloudToolsClass", "Min Cluster Size", nullptr));
        min_cluster_size2_input->setText(QApplication::translate("PointCloudToolsClass", "100", nullptr));
        neighbours_dist->setText(QApplication::translate("PointCloudToolsClass", "Neighbours Dist", nullptr));
        neighbours_dist_input->setText(QApplication::translate("PointCloudToolsClass", "10", nullptr));
        point_color_diff->setText(QApplication::translate("PointCloudToolsClass", "Point Color Diff", nullptr));
        point_color_diff_input->setText(QApplication::translate("PointCloudToolsClass", "6", nullptr));
        region_color_diff->setText(QApplication::translate("PointCloudToolsClass", "Region Color Diff", nullptr));
        region_color_diff_input->setText(QApplication::translate("PointCloudToolsClass", "5", nullptr));
        color_confirm->setText(QApplication::translate("PointCloudToolsClass", "Confirm", nullptr));
        rgTab->setTabText(rgTab->indexOf(rgTab2), QApplication::translate("PointCloudToolsClass", "Color-Based", nullptr));
        menu->setTitle(QApplication::translate("PointCloudToolsClass", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("PointCloudToolsClass", "\345\261\225\347\244\272", nullptr));
        menu_3->setTitle(QApplication::translate("PointCloudToolsClass", "\344\270\273\351\242\230", nullptr));
        menu_4->setTitle(QApplication::translate("PointCloudToolsClass", "\350\257\255\350\250\200", nullptr));
        menu_5->setTitle(QApplication::translate("PointCloudToolsClass", "\346\273\244\346\263\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PointCloudToolsClass: public Ui_PointCloudToolsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTCLOUDTOOLS_H
