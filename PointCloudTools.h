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
	 * @brief ���ص����ļ��Ľ��
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
	void mainview();//����ͼ
	void leftview();//����ͼ
	void topview();//����ͼ
	void resetview();//������ͼ
	
	// �����˲�
	void openFilterPanel(int type);
	void FilterPassThrough();
	void FilterStatisticalOutlierRemoval();

	//���Ʒָ�
	void segmentation();
	void euclideanSegmentation(const PointCloudT::Ptr &cloud);//ŷ����÷ָ�
	void conditionalEuclideanSegmentation(const PointCloudT::Ptr &Cloud);//����ŷ����÷ָ�

	/*********�˲���ʵ�ֵ������ݵĿռ仮��*********/
	//void SearchKNear(float x, float y, float z, int &k);		//	�����˲�����ָ������Ұ뾶Ϊk�����
	void ShowLeafNode();										//	��ʾ�ռ仮�ֵ�Ҷ�ӽڵ�


	void Centroid();//��������

	//void Triangulation();									//	�ð˲���ʵ�������ʷ�

	void RegionGrowing();
	void RegionGrowingRGB();
	void openRegionGrowingPanel(bool isBasic);


	void Registration();



	void showPointcloud();
	void showPointcloudAdd();
	void savemulti(const QFileInfo &fileInfo, bool isSaveBinary);//�����ģ̬����
	void setCloudColor(unsigned int r, unsigned int g, unsigned int b); //���õ�����ɫ
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
	void setPropertyTable();//�������Դ���
	void setConsoleTable();//���ÿ���̨����
	void consoleLog(QString operation, QString subname, QString filename, QString note);
	int planFit();
	int sphereFit();
	int areaPicking();//����ѡ����


private:
	Ui::PointCloudToolsClass ui;

	PointCloudXYZ src_cloud;
	PointCloudXYZ tgt_cloud;
	PointCloudXYZ::Ptr rst_cloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz;//�����ؽ�����
	
	
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
	MyCloud mycloudSelected;    //����ѡ�ĵ���
	int cloudselect_id = 0;
	int selected_num = 0;
	int m_iAreaPickingIndex =0;
	int m_iSegmentationCarIndex = 0;
	int m_iSegmentationTreeIndex = 0;

};
