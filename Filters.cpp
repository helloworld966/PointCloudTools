#include <pcl/filters/passthrough.h>
#include "Filters.h"

/**
 * @brief ֻ���� lower_limit �� upper_limit ��Χ�ڵĵ�ͨ�������˵������Χ֮��ĵ�
 * @param cloud
 * @param axis: only accept "x,y,z"
 * @param lower_limit
 * @param upper_limit
 * @return
 */
PointCloudT::Ptr PassThroughFilter(PointCloudT::Ptr cloud, std::string axis, float lower_limit, float upper_limit) {
	PointCloudT::Ptr cloud_filtered(new PointCloudT);
	pcl::PassThrough<PointT> passThrough;
	passThrough.setInputCloud(cloud);
	passThrough.setFilterFieldName(axis);
	passThrough.setFilterLimits(lower_limit, upper_limit);
	passThrough.filter(*cloud_filtered);
	return cloud_filtered;
}

/**
 * @brief ͳ���˲���ɾ����Ⱥ�㣬��Ҫ������ȥ����ɢ��������
 * @param cloud
 * @param isNegative
 * @return
 */
pcl::PointCloud<pcl::PointXYZRGBA>::Ptr StatisticalOutlierRemovalFilter(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud, bool isNegative, int meanK, double stddev_mult) {
	PointCloudT::Ptr cloud_filtered(new PointCloudT);

	// ����һ���˲���
	pcl::StatisticalOutlierRemoval<pcl::PointXYZRGBA> statisticalOutlierRemoval;
	statisticalOutlierRemoval.setInputCloud(cloud);
	statisticalOutlierRemoval.setMeanK(meanK);
	statisticalOutlierRemoval.setStddevMulThresh(stddev_mult);
	statisticalOutlierRemoval.filter(*cloud_filtered);
	if (!isNegative) {
		// ���ط���Ⱥ�㼯
		return cloud_filtered;
	}
	else {
		// ͬ�������ٴε��ã�ͨ��setNegative����������ѡȡ��ȡ��Ⱥ�ĵ㼯
		statisticalOutlierRemoval.setNegative(true);
		statisticalOutlierRemoval.filter(*cloud_filtered);
		return cloud_filtered;
	}
}
