#include "sphereFit.h"
SphereFit::SphereFit() {

	cloud_src = PointCloudT::Ptr(new PointCloudT);

}

SphereFit::~SphereFit() {}

void SphereFit::setInputCloud(PointCloudT::Ptr &cloud_in) {
	pcl::copyPointCloud(*cloud_in, *cloud_src);
	cout << "src cloud has: " << cloud_src->points.size() << " data points."
		<< endl;
}
void SphereFit::setSphereFitThreshold(float thres) {
	sphereDistanceThreshold = thres;
	cout << "SphereFit threshold: " << sphereDistanceThreshold << endl;
}

int SphereFit::compute() {
	// objects needed
	pcl::NormalEstimation<PointT, pcl::Normal> ne;
	pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());
	pcl::SACSegmentationFromNormals<PointT, pcl::Normal> seg;
	// Datasets
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(
		new pcl::PointCloud<pcl::Normal>);

	pcl::ModelCoefficients::Ptr coefficients_sphere(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers_plane(new pcl::PointIndices);

	//·¨Ïß¹À¼Æ
	// Estimate point normals
	ne.setSearchMethod(tree);
	ne.setInputCloud(cloud_src);
	ne.setKSearch(30);
	ne.compute(*cloud_normals);

	// Create the segmentation object for the planar model and set all the
	// parameters
	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_SPHERE);
	//    seg.setNormalDistanceWeight(0.1);
	seg.setMethodType(pcl::SAC_RANSAC);
	// seg.setMaxIterations(100);
	seg.setDistanceThreshold(sphereDistanceThreshold);
	seg.setInputCloud(cloud_src);
	seg.setInputNormals(cloud_normals);
	// Obtain the plane inliers and coefficients
	seg.segment(*inliers_plane, *coefficients_sphere);

	if (inliers_plane->indices.size() == 0) {
		PCL_ERROR("Could not estimate a planar model for the given dataset.");
		return (-1);
	}

	cout << "sphere inliers has: " << inliers_plane->indices.size()
		<< " data points." << endl;
	cout << "sphere coefficients: " << *coefficients_sphere << std::endl;

	diameter = coefficients_sphere->values[3];
	return 0;
}
