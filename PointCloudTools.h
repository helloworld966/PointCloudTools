#pragma once

#include <QtWidgets/QMainWindow>
#include<ui_PointCloudTools.h>
#include <vtkRenderWindow.h> 
#include<FileIO.h>

#include <pcl/ModelCoefficients.h>
#include <pcl/PolygonMesh.h>
#include <pcl/common/transforms.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/passthrough.h>
#include "MyCloud.h"
#include "Tools.h"
#include <QTime>
#include <QTranslator>
#include <pcl/surface/gp3.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/conditional_euclidean_clustering.h>
#include"planfit.h"
#include<QInputDialog>
#include <boost/math/special_functions.hpp>
#include"sphereFit.h"
#include"PtPicking.h"
#include"Filters.h"
#include"Segmentation.h"
#include <Eigen/Core>
#include <pcl/common/transforms.h>
#include <pcl/console/time.h>   // TicToc
#include <pcl/registration/icp.h>

const int CLOUDVIEWER_LANG_ENGLISH = 0;
const int CLOUDVIEWER_LANG_CHINESE = 1;


const int CLOUDVIEWER_MODE_POINT = 0;
const int CLOUDVIEWER_MODE_MESH = 1;
const int CLOUDVIEWER_MODE_POINT_MESH = 2;
const int DEFAUT_PT_SIZE = 1;




//bool next_iteration = false;

class PointCloudTools : public QMainWindow
{
	Q_OBJECT

public:
	PointCloudTools(QWidget *parent = Q_NULLPTR);
	int theme_id = 1;


private slots:
	/*
	 * @brief 加载点云文件的结果
	 */


	void doopen(const QStringList &filePathList);
	void open();
	void AddPointCloud();
	void clear();
	void save();
	void initial();
	void exit();
	void colorCloudVecDistances();
	void colorCloudDist(int cloud_id);
	void mainview();//主视图
	void leftview();//左视图
	void topview();//顶视图
	void resetview();//重置视图
	
	// 点云滤波
	void openFilterPanel(int type);
	void FilterPassThrough();
	void FilterStatisticalOutlierRemoval();

	//点云分割
	void segmentation();
	void euclideanSegmentation(const PointCloudT::Ptr &cloud);//欧几里得分割
	void conditionalEuclideanSegmentation(const PointCloudT::Ptr &Cloud);//条件欧几里得分割

	/*********八叉树实现点云数据的空间划分*********/
	//void SearchKNear(float x, float y, float z, int &k);		//	搜索八叉树中指定点的且半径为k领域点
	void ShowLeafNode();										//	显示空间划分的叶子节点


	void Centroid();//计算质心

	//void Triangulation();									//	用八叉树实现三角剖分

	void RegionGrowing();
	void RegionGrowingRGB();
	void openRegionGrowingPanel(bool isBasic);


	void Registration();



	void showPointcloud();
	void showPointcloudAdd();
	void savemulti(const QFileInfo &fileInfo, bool isSaveBinary);//保存多模态点云
	void setCloudColor(unsigned int r, unsigned int g, unsigned int b); //设置点云颜色
	void setA(unsigned int a);



	void changeTheme(int index);
	void changeLanguage(int index);

	int convertSurface();
	int convertWireframe();

	void itemSelected(QTreeWidgetItem*, int);
	void popMenu(const QPoint &);
	void hideItem();
	void showItem();
	void deleteItem();
	void setPropertyTable();//设置属性窗口
	void setConsoleTable();//设置控制台窗口
	void consoleLog(QString operation, QString subname, QString filename, QString note);
	int planFit();
	int sphereFit();
	int areaPicking();//鼠标框选点云


private:
	Ui::PointCloudToolsClass ui;

	PointCloudXYZ src_cloud;
	PointCloudXYZ tgt_cloud;
	PointCloudXYZ::Ptr rst_cloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz;//网格重建定义
	
	
	MyCloud mycloud;
	std::vector<MyCloud> mycloud_vec;
	std::vector<int> m_indicesVec;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_;

	std::map<QString, MyCloud> m_pointCloudMap;
	QTreeWidgetItem *m_pCarItem;
	QTreeWidgetItem *m_pTreeItem;
	long total_points = 0;
	QString time_cost = "0";
	QTranslator* translator;
	bool enable_console = true;
	FileIO fileio;
	int filtering_axis_;
	int color_mode_;
	MyCloud mycloudSelected;    //被框选的点云
	int cloudselect_id = 0;
	int selected_num = 0;
	int m_iAreaPickingIndex =0;
	int m_iSegmentationCarIndex = 0;
	int m_iSegmentationTreeIndex = 0;

};
