#ifndef SPHEREFIT_H
#define SPHEREFIT_H

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

class SphereFit {
public:
	typedef pcl::PointXYZ PointT;
	typedef pcl::PointCloud<PointT> PointCloudT;
	SphereFit();
	~SphereFit();
	//�����������
	void setInputCloud(PointCloudT::Ptr &cloud_in);
	double sphereDistanceThreshold = 0.1; //������Ͼ�����ֵ
	//����ƽ����Ͼ�����ֵ
	void setSphereFitThreshold(float thres);
	//��ʼ���
	int compute();
	//��ֱ��
	float diameter = 0;

private:
	//�������
	PointCloudT::Ptr cloud_src;
};
#endif // SPHEREFIT_H
