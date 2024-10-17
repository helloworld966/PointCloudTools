#ifndef __MY_CLOUD_H__
#define __MY_CLOUD_H__

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/PolygonMesh.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/extract_indices.h>
#include <string>
#include <QFileInfo>
#include "Tools.h"

using namespace std;

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::PointXYZRGBNormal PointXYZRGBN;

typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;

typedef pcl::PointXYZ PointTT;
typedef pcl::PointCloud<PointTT> PointCloudTT;

class MyCloud
{
public:
	MyCloud();
	~MyCloud();

	bool isValid = false;
	std::vector<pcl::PointIndices> m_indicesVec;
	PointCloudT::Ptr cloud;      // point cloud pointer
	pcl::PolygonMesh::Ptr mesh;  // polygon mesh pointer



	string filePath;     // dir + file name   e.g. /home/user/hello.min.ply
	string fileDir;      // only dir          e.g. /home/user
	string fileName;     // only file name    e.g. hello.min.ply
	string fileSuffix;   // file name suffx   e.g. ply

	string cloudId;      // cloud id in `viewer`: "cloud-" + fileName
	string meshId;       // mesh id in `viewer`: "mesh-" + fileName

	bool is_seleted = false;     //是否被框选过点云

	bool hasCloud = false;
	bool hasMesh = false;

	//平面参数Ax+By+Cz+D=0
	float plane_A = 0;
	float plane_B = 0;
	float plane_C = 0;
	float plane_D = 0;


	// string filename;             // point cloud file full name
	// string subname;              // point cloud file short name
	// string dirname = "E:\\Date\\PointCloud\\";

	bool visible = true;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	string curMode = "point";    // default show mode
	vector<string> supportedModes;


	void setPointColor(int r, int g, int b);
	void setPointAlpha(int a);
	void setShowMode(const string& mode);
	void showCloud();
	void hideCloud();
	void showMesh();
	void hideMesh();
	void show();
	void hide();

	void init(const QFileInfo& fileInfo, bool hasCloud, bool hasMesh);

	static MyCloud getInvalidMyCloud() {
		MyCloud myCloud;
		myCloud.isValid = false;
		return myCloud;
	}

};
#endif
