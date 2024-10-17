#include <fstream>
#include <iostream>
#include <pcl/console/parse.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace pcl;

class PtPicking {
public:
	PtPicking(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in);
	void reset();
	~PtPicking();

	void keyboardEventOccurred(const visualization::KeyboardEvent &event,
		void *junk);
	void areaPicking();    //��ѡ����
	void pointPicking();   //����ѡȡ
	void ptActicPicking(); //��Ļѡ��
	pcl::PointXYZRGB randomPoint();
	void spin();
	pcl::PointCloud<pcl::PointXYZ>::Ptr
		clicked_points_3d; //��ѡ�еĵ��ƣ�������reset��ֵ

protected:
	boost::mutex cloud_mutex;
	int num = 0;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr baseCloud; //���ص�ԭʼ����

	void areaPicking_callback(const pcl::visualization::AreaPickingEvent &event,
		void *args);
	void pointPicking_callback(const pcl::visualization::PointPickingEvent &event,
		void *args);
	void PtActivePick_callback(const pcl::visualization::PointPickingEvent &event,
		void *args);
};
