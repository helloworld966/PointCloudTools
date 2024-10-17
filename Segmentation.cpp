#include "Segmentation.h"

/**
 * @brief Basic Region Growing
 * @param cloud             ԭʼ�������
 * @param k                 k���ڲ���
 * @param min_cluster_size  һ��region���ٵ�����
 * @param max_cluster_size  һ��region����������ͨ������ϣ�������ѡһ���㹻���ֵ�͹���
 * @param neighbour_number  ���ٸ���������һ��ƽ��
 * @param smoothness_theta  �н���ֵ
 * @param curvature         ������ֵ
 * @return
 */
pcl::RegionGrowing<PointT, pcl::Normal>
getRegionGrowing(PointCloudT::Ptr cloud, int k, int min_cluster_size, int max_cluster_size,
	unsigned int neighbour_number, float smoothness_theta, float curvature) {

	// ��triangulation�е�ͬ����Ҫ�õ�������������Normalesimationȥ����
	pcl::search::Search<pcl::PointXYZRGBA>::Ptr tree = boost::shared_ptr<pcl::search::Search<pcl::PointXYZRGBA>>(
		new pcl::search::KdTree<pcl::PointXYZRGBA>);
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::NormalEstimation<pcl::PointXYZRGBA, pcl::Normal> normalEstimation;
	normalEstimation.setSearchMethod(tree);
	normalEstimation.setInputCloud(cloud);
	normalEstimation.setKSearch(k); // get the number of k nearest neighbors used for the feature estimation
	normalEstimation.compute(*normals);

	// ��������
	pcl::RegionGrowing<pcl::PointXYZRGBA, pcl::Normal> regionGrowing;
	// ���ٵ�
	regionGrowing.setMinClusterSize(min_cluster_size); // example default: 50
	// ���㣬һ��ϣ�������
	regionGrowing.setMaxClusterSize(max_cluster_size);
	// �����úõ�kd��
	regionGrowing.setSearchMethod(tree);
	// �ο�����������������ٸ������һ��ƽ�棬�������ݴ���
	// ������ú�С����⵽��ƽ��Ҳ��С���ܴ�Ļ��������еĵ����
	regionGrowing.setNumberOfNeighbours(neighbour_number); // example default: 30
	// ������ĵ���
	regionGrowing.setInputCloud(cloud);
	// regionGrowing.setIndices(indicesPtr);
	// ����㷨��
	regionGrowing.setInputNormals(normals);
	// ����������ֵ���������Ƿ�Ҫ����̽��
	// ����ÿ���㶼��ƽ�������ģ��н�Ҳ��С������̽���������󣬱仯һ���ᳬ����������ֵ
	regionGrowing.setSmoothnessThreshold(smoothness_theta);
	regionGrowing.setCurvatureThreshold(curvature);

	return regionGrowing;
}

/**
 * @brief Color based Region Growing
 * @param cloud                 ����RGB����
 * @param min_cluster_size      region�����ٵ���
 * @param neighbors_distance    ���ڼ����ֵ
 * @param point_color_diff      ����RGB�����ֵ���
 * @param region_color_diff     ����RGB�����ֵ���
 * @return
 */
pcl::RegionGrowingRGB<pcl::PointXYZRGB>
getRegionGrowingRGB(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, int min_cluster_size, float neighbors_distance,
	float point_color_diff, float region_color_diff) {
	// color-based region growing segmentation
	// kd-tree object for searches.
	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZRGB>);
	kdtree->setInputCloud(cloud);

	// Color-based region growing clustering object.
	pcl::RegionGrowingRGB<pcl::PointXYZRGB> clustering;
	clustering.setInputCloud(cloud);
	clustering.setSearchMethod(kdtree);
	// Here, the minimum cluster size affects also the postprocessing step:
	// clusters smaller than this will be merged with their neighbors.
	clustering.setMinClusterSize(min_cluster_size);
	// Set the distance threshold, to know which points will be considered neighbors.
	clustering.setDistanceThreshold(neighbors_distance);
	// Color threshold for comparing the RGB color of two points.
	clustering.setPointColorThreshold(point_color_diff);
	// Region color threshold for the postprocessing step: clusters with colors
	// within the threshold will be merged in one.
	clustering.setRegionColorThreshold(region_color_diff);
	return clustering;
}
