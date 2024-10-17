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
	void areaPicking();    //框选点云
	void pointPicking();   //单点选取
	void ptActicPicking(); //屏幕选点
	pcl::PointXYZRGB randomPoint();
	void spin();
	pcl::PointCloud<pcl::PointXYZ>::Ptr
		clicked_points_3d; //被选中的点云，可以用reset充值

protected:
	boost::mutex cloud_mutex;
	int num = 0;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr baseCloud; //加载的原始点云

	void areaPicking_callback(const pcl::visualization::AreaPickingEvent &event,
		void *args);
	void pointPicking_callback(const pcl::visualization::PointPickingEvent &event,
		void *args);
	void PtActivePick_callback(const pcl::visualization::PointPickingEvent &event,
		void *args);
};
