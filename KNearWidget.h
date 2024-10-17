#pragma once

#include <QDialog>
#include "ui_KNearWidget.h"
#include"stdafx.h"
enum SearchType
{
	VOVEXSEARCH = 1,
	KNEARESTNODESEARCH,				//	k个最近领域点搜索
	RADIUSSEARCH					//	半径搜索
};
class KNearWidget : public QDialog
{
	Q_OBJECT

public:
	KNearWidget(QWidget *parent = Q_NULLPTR);
	~KNearWidget();
	void SetCloudAndViewer(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::visualization::PCLVisualizer::Ptr viewer);
signals:
	
private slots:
	void OnPushButton_voxelSearch();
	void OnPushButton_kNearNodes();
	void OnPushButton_NearRadiusSearch();
private:
	Ui::KNearWidget ui;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz;
	pcl::visualization::PCLVisualizer::Ptr viewer_;


};
