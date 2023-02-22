#ifndef WAVEMAP_INTEGRATOR_RAY_TRACING_RAY_TRACING_INTEGRATOR_H_
#define WAVEMAP_INTEGRATOR_RAY_TRACING_RAY_TRACING_INTEGRATOR_H_

#include <utility>

#include "wavemap/data_structure/volumetric/volumetric_data_structure_base.h"
#include "wavemap/integrator/integrator_base.h"
#include "wavemap/integrator/measurement_model/constant_ray.h"
#include "wavemap/iterator/ray_iterator.h"

namespace wavemap {
struct RayTracingIntegratorConfig : ConfigBase<RayTracingIntegratorConfig> {
  FloatingPoint min_range = 0.5f;
  FloatingPoint max_range = 20.f;

  // Constructors
  RayTracingIntegratorConfig() = default;
  RayTracingIntegratorConfig(FloatingPoint min_range, FloatingPoint max_range)
      : min_range(min_range), max_range(max_range) {}

  bool isValid(bool verbose) const override;
  static RayTracingIntegratorConfig from(const param::Map& params);
};

class RayTracingIntegrator : public IntegratorBase {
 public:
  RayTracingIntegrator(const RayTracingIntegratorConfig& config,
                       VolumetricDataStructureBase::Ptr occupancy_map)
      : config_(config.checkValid()),
        occupancy_map_(std::move(CHECK_NOTNULL(occupancy_map))) {}

  void integratePointcloud(const PosedPointcloud<Point3D>& pointcloud) override;

 private:
  using MeasurementModelType = ConstantRay;

  const RayTracingIntegratorConfig config_;
  const VolumetricDataStructureBase::Ptr occupancy_map_;
};
}  // namespace wavemap

#endif  // WAVEMAP_INTEGRATOR_RAY_TRACING_RAY_TRACING_INTEGRATOR_H_
