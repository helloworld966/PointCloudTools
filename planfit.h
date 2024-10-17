#ifndef PLANFIT_H
#define PLANFIT_H
#include <algorithm>
#include <iostream>
#include <math.h>
#include <numeric>
#include <string>

#include <pcl/ModelCoefficients.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/surface/concave_hull.h>
#include <pcl/surface/convex_hull.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;
#define PI 3.141592653

class PlanFit {
public:
	typedef pcl::PointXYZ PointT;
	typedef pcl::PointCloud<PointT> PointCloudT;
	PlanFit();
	~PlanFit();
	//�����������
	void setInputCloud(PointCloudT::Ptr &cloud_in);
	//���ò���
	void setPara(double planeDisThres, double normalDisThres, float leaf_size);
	void setAxis(float vx, float vy, float vz, float epsAngle);
	//��ʼ���
	int compute();
	//Ax+By+Cz+D=0
	float A = 0;
	float B = 0;
	float C = 0;
	float D = 0;

private:
	//�������
	PointCloudT::Ptr cloud_src;
	double planDistanceThreshold_ = 0.1; //ƽ����Ͼ�����ֵ
	double normalDistanceWeight_ = 0.3; //ƽ����Ϸ���Ȩ��
	float leaf_size_ = 0.1; //����������
	//�Ƿ����÷�����
	bool ifuseAxis = false;
	Eigen::Vector3f vec_axis;
	float epsAngle_ = 3.0;  //����ƫ��Ƕ�
};
#endif // PLANFIT_H
