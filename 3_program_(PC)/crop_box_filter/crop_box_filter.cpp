#include "crop_box_filter.hpp"

#include <vector>
#include <cstring>
#include <memory>
#include <cmath>

namespace pointcloud_preprocessor
{
CropBoxFilter::CropBoxFilter()
: Filter("CropBoxFilter")
{
}

std::unique_ptr<PointCloud> CropBoxFilter::Apply(const PointCloud& pc)
{
  size_t output_size = 0, output_points_count = 0;
  std::vector<double> output(pc.size() * pc.pointSize());

  const auto& points = pc.points();
  size_t point_size = pc.pointSize();
  size_t total_points = pc.size();


  for (size_t global_offset = 0; global_offset + point_size <= total_points * point_size;
       global_offset += point_size) {

    double x, y, z;

    std::memcpy(&x, &points[global_offset + 0], sizeof(double));
    std::memcpy(&y, &points[global_offset + 1], sizeof(double));
    std::memcpy(&z, &points[global_offset + 2], sizeof(double));

    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
      logger_.log("Ignoring point containing NaN values");
      continue;
    }

    bool point_is_inside = x > param_.min_x && x < param_.max_x &&
                           y > param_.min_y && y < param_.max_y &&
                           z > param_.min_z && z < param_.max_z;

    if ((!param_.negative && point_is_inside) || (param_.negative && !point_is_inside)) {
      std::memcpy(&output[output_size], &points[global_offset], point_size * sizeof(double));
      output_size += point_size;
      output_points_count += 1;
    }
  }

  output.resize(output_size);
  auto output_pc = std::make_unique<PointCloud>(pc.type(), output_points_count);
  output_pc->points() = std::move(output);
  return output_pc;
}

void CropBoxFilter::SetParams(const FilterParametr& param)
{

  CropBoxParam new_param{};

  new_param.min_x = param.GetParam("min_x", new_param.min_x);
  new_param.max_x = param.GetParam("max_x", new_param.max_x);
  new_param.min_y = param.GetParam("min_y", new_param.min_y);
  new_param.max_y = param.GetParam("max_y", new_param.max_y);
  new_param.min_z = param.GetParam("min_z", new_param.min_z);
  new_param.max_z = param.GetParam("max_z", new_param.max_z);
  new_param.negative = static_cast<bool>(param.GetParam("negative", param_.negative ? 1 : 0));
  if (
    new_param.min_x != 0 && new_param.max_x != 0 &&
    new_param.min_y != 0 && new_param.max_y != 0 &&
    new_param.min_z != 0 && new_param.max_z != 0) {
    if (
      param_.min_x != new_param.min_x || param_.max_x != new_param.max_x ||
      param_.min_y != new_param.min_y || param_.max_y != new_param.max_y ||
      param_.min_z != new_param.min_z || param_.max_z != new_param.max_z ||
      param_.negative != new_param.negative) {

      logger_.log("[paramCallback] Setting the minimum point to: " +
        std::to_string(new_param.min_x) + " " + 
        std::to_string(new_param.min_y) + " " + 
        std::to_string(new_param.min_z));

      logger_.log("[paramCallback] Setting the maximum point to: " +
        std::to_string(new_param.max_x) + " " + 
        std::to_string(new_param.max_y) + " " + 
        std::to_string(new_param.max_z));

      std::string negative_msg = "[paramCallback] Setting the filter negative flag to: ";
      negative_msg += (new_param.negative ? "true" : "false");
      logger_.log("[paramCallback] Setting the filter negative flag to: " + new_param.negative ? "true" : "false");
      param_ = new_param;
    }
  }
  Filter::SetParams(param);
}

}  // namespace pointcloud_preprocessor
