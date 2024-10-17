
//PointXYZRGB�����������ά���� (x, y, z) �� RGB ��ɫ��Ϣ��RGB ��ɫ��Ϣ��ѹ����һ���������У���ɫ��Ϣ�Ǹ�����
//PointXYZRGBA�����������ά���� (x, y, z) �� RGBA ��ɫ��Ϣ��RGBA ��ɫ��Ϣ����һ������� Alpha ͨ�������ڱ�ʾ͸���ȣ���ɫ��Ϣ�����α���
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
