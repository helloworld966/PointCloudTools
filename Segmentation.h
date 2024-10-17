
//PointXYZRGB，包含点的三维坐标 (x, y, z) 和 RGB 颜色信息。RGB 颜色信息被压缩到一个浮点数中，颜色信息是浮点数
//PointXYZRGBA，包含点的三维坐标 (x, y, z) 和 RGBA 颜色信息。RGBA 颜色信息包含一个额外的 Alpha 通道，用于表示透明度，颜色信息是整形变量
#pragma once
#ifndef POINT_CLOUD_TOOL_CLASSIFIER_H
#define POINT_CLOUD_TOOL_CLASSIFIER_H

#include <iostream>
#include <pcl/point_types.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/region_growing.h>
#include <pcl/segmentation/region_growing_rgb.h>

#include"MyCloud.h"


class Segmentation {

};


pcl::RegionGrowing<PointT, pcl::Normal>
getRegionGrowing(PointCloudT::Ptr cloud, int k, int min_cluster_size, int max_cluster_size,
	unsigned int neighbour_number, float smoothness_theta, float curvature);

//pcl::RegionGrowingRGB<pcl::PointXYZRGB>
//getRegionGrowingRGB(pcl::PointCloud<pcl::PointXYZRGB::Ptr cloud, int min_cluster_size, float neighbors_distance,
//	float point_color_diff, float region_color_diff);


#endif //POINT_CLOUD_TOOL_CLASSIFIER_H
