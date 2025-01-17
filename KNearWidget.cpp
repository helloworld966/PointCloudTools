#include "KNearWidget.h"

KNearWidget::KNearWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

KNearWidget::~KNearWidget()
{
}
void KNearWidget::SetCloudAndViewer(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::visualization::PCLVisualizer::Ptr viewer)
{
	if (cloud != NULL && viewer != NULL)
	{
		cloud_xyz = cloud;
		viewer_ = viewer;
	}
}

void KNearWidget::OnPushButton_voxelSearch()
{
	// Neighbors within voxel search
	if (!ui.lineEdit->text().isEmpty() && cloud_xyz != NULL)
	{
		pcl::PointXYZ searchPoint;
		int k = ui.lineEdit->text().toInt();

		searchPoint.x = ui.lineEdit_X->text().toFloat();
		searchPoint.y = ui.lineEdit_Y->text().toFloat();
		searchPoint.z = ui.lineEdit_Z->text().toFloat();

		float resolution = 5.0f;

		pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree(resolution);

		octree.setInputCloud(cloud_xyz);
		octree.addPointsFromInputCloud();

		std::vector<int> pointIdxVec;

		if (octree.voxelSearch(searchPoint, pointIdxVec))
		{
			std::cout << "Neighbors within voxel search at (" << searchPoint.x
				<< " " << searchPoint.y
				<< " " << searchPoint.z << ")"
				<< std::endl;

			for (size_t i = 0; i < pointIdxVec.size(); ++i)
				std::cout << "    " << cloud_xyz->points[pointIdxVec[i]].x
				<< " " << cloud_xyz->points[pointIdxVec[i]].y
				<< " " << cloud_xyz->points[pointIdxVec[i]].z << std::endl;
		}

	}
}
void KNearWidget::OnPushButton_kNearNodes()
{
	if (!ui.lineEdit->text().isEmpty() && cloud_xyz != NULL)
	{
		pcl::PointXYZ searchPoint;
		int K = ui.lineEdit->text().toInt();

		searchPoint.x = ui.lineEdit_X->text().toFloat();
		searchPoint.y = ui.lineEdit_Y->text().toFloat();
		searchPoint.z = ui.lineEdit_Z->text().toFloat();

		float resolution = 5.0f;

		pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree(resolution);

		octree.setInputCloud(cloud_xyz);
		octree.addPointsFromInputCloud();

		std::vector<int> pointIdxNKNSearch;
		std::vector<float> pointNKNSquaredDistance;

		std::cout << "K nearest neighbor search at (" << searchPoint.x
			<< " " << searchPoint.y
			<< " " << searchPoint.z
			<< ") with K=" << K << std::endl;

		if (octree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
		{
			for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
				std::cout << "    " << cloud_xyz->points[pointIdxNKNSearch[i]].x
				<< " " << cloud_xyz->points[pointIdxNKNSearch[i]].y
				<< " " << cloud_xyz->points[pointIdxNKNSearch[i]].z
				<< " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
		}
	}
}
void KNearWidget::OnPushButton_NearRadiusSearch()
{
	if (!ui.lineEdit->text().isEmpty() && cloud_xyz != NULL)
	{
		pcl::PointXYZ searchPoint;
		float radius = ui.lineEdit->text().toFloat();

		searchPoint.x = ui.lineEdit_X->text().toFloat();
		searchPoint.y = ui.lineEdit_Y->text().toFloat();
		searchPoint.z = ui.lineEdit_Z->text().toFloat();

		float resolution = 5.0f;

		pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree(resolution);

		octree.setInputCloud(cloud_xyz);
		octree.addPointsFromInputCloud();


		std::vector<int> pointIdxRadiusSearch;
		std::vector<float> pointRadiusSquaredDistance;


		std::cout << "Neighbors within radius search at (" << searchPoint.x
			<< " " << searchPoint.y
			<< " " << searchPoint.z
			<< ") with radius=" << radius << std::endl;


		if (octree.radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
		{
			for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i)
				std::cout << "    " << cloud_xyz->points[pointIdxRadiusSearch[i]].x
				<< " " << cloud_xyz->points[pointIdxRadiusSearch[i]].y
				<< " " << cloud_xyz->points[pointIdxRadiusSearch[i]].z
				<< " (squared distance: " << pointRadiusSquaredDistance[i] << ")" << std::endl;
		}

		int pointsize = pointIdxRadiusSearch.size();
		ui.lineEdit_result->setText(QString(QString::number(pointsize)));
	}
}