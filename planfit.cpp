#include "planfit.h"

PlanFit::PlanFit() {

	cloud_src = PointCloudT::Ptr(new PointCloudT);

}

PlanFit::~PlanFit() {}

void PlanFit::setInputCloud(PointCloudT::Ptr &cloud_in) {
	pcl::copyPointCloud(*cloud_in, *cloud_src);
	cout << "src cloud has: " << cloud_src->points.size() << " data points."
		<< endl;
}

void PlanFit::setPara(double planeDisThres, double normalDisThres, float leaf_size) {
	planDistanceThreshold_ = planeDisThres;
	cout << "planefit distance threshold: " << planDistanceThreshold_ << endl;
	normalDistanceWeight_ = normalDisThres;
	cout << "planefit normal distance threshold: " << normalDistanceWeight_ << endl;
	leaf_size_ = leaf_size;
	cout << "voxel filter leaf size: " << leaf_size_ << endl;
}

void PlanFit::setAxis(float vx, float vy, float vz, float epsAngle) {
	vec_axis << vx, vy, vz;
	cout << "normal vector: " << vec_axis << endl;
	epsAngle_ = epsAngle;
	cout << "eps angle: " << epsAngle_ << "°" << endl;
	ifuseAxis = true;
}

int PlanFit::compute() {
	// objects needed
	pcl::VoxelGrid<PointT> voxelFilter;
	pcl::NormalEstimation<PointT, pcl::Normal> ne;
	pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());
	pcl::SACSegmentationFromNormals<PointT, pcl::Normal> seg;
	pcl::PassThrough<PointT> pass;
	// Datasets
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(
		new pcl::PointCloud<pcl::Normal>);

	pcl::ModelCoefficients::Ptr coefficients_plane(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers_plane(new pcl::PointIndices);

	//    //降采样
	//    voxelFilter.setInputCloud (cloud_src);
	//    voxelFilter.setLeafSize (leaf_size_, leaf_size_, leaf_size_);
	//    voxelFilter.filter (*cloud_src);
	//法线估计
	// Estimate point normals
	ne.setSearchMethod(tree);
	ne.setInputCloud(cloud_src);
	ne.setKSearch(50);
	ne.compute(*cloud_normals);

	// Create the segmentation object for the planar model and set all the
	// parameters
	//是否使用法线约束
	if (ifuseAxis) {
		seg.setModelType(pcl::SACMODEL_NORMAL_PARALLEL_PLANE);//设置分割模型为带约束的平面
		seg.setAxis(vec_axis);
		seg.setEpsAngle(epsAngle_ * (PI / 180.0f)); // plane normal can be within 5 degrees of vec_axis;
	}
	else {
		seg.setModelType(pcl::SACMODEL_NORMAL_PLANE);
	}
	seg.setOptimizeCoefficients(true);
	seg.setNormalDistanceWeight(normalDistanceWeight_);
	seg.setMethodType(pcl::SAC_RANSAC);
	// seg.setMaxIterations(100);
	seg.setDistanceThreshold(planDistanceThreshold_);
	seg.setInputCloud(cloud_src);
	seg.setInputNormals(cloud_normals);
	// Obtain the plane inliers and coefficients
	seg.segment(*inliers_plane, *coefficients_plane);

	if (inliers_plane->indices.size() == 0) {
		PCL_ERROR("Could not estimate a planar model for the given dataset.");
		return (-1);
	}

	cout << "plane inliers has: " << inliers_plane->indices.size()
		<< " data points." << endl;
	cout << "Plane coefficients: " << *coefficients_plane << std::endl;

	A = coefficients_plane->values[0];
	B = coefficients_plane->values[1];
	C = coefficients_plane->values[2];
	D = coefficients_plane->values[3];
	if (A < 0) {
		A = -A;
		B = -B;
		C = -C;
		D = -D;
	}
	return 0;
}
