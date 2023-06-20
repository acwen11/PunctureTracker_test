#include <cmath>
#include <ctype.h>
#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

#include <loop_device.hxx>
#include <array>

namespace TestPT {
using namespace std;
using namespace Loop;

extern "C" void TestPT_init_shift_circle(CCTK_ARGUMENTS) {
  DECLARE_CCTK_ARGUMENTS_TestPT_init_shift_circle;
  DECLARE_CCTK_PARAMETERS;

  const array<int, dim> indextype = {0, 0, 0};
  const GF3D2layout layout(cctkGH, indextype);

  const GF3D2<CCTK_REAL> betax_(layout, betax);
  const GF3D2<CCTK_REAL> betay_(layout, betay);
  const GF3D2<CCTK_REAL> betaz_(layout, betaz);

  const GridDescBaseDevice grid(cctkGH);
  grid.loop_all_device<0, 0, 0>(grid.nghostzones,
                                [=] CCTK_DEVICE(const PointDesc &p)
                                    CCTK_ATTRIBUTE_ALWAYS_INLINE {
                                      betax_(p.I) = p.y;
                                      betay_(p.I) = -p.x;
                                      betaz_(p.I) = 0;
                                    });
}

extern "C" void TestPT_init_shift_3D(CCTK_ARGUMENTS) {
  DECLARE_CCTK_ARGUMENTS_TestPT_init_shift_3D;
  DECLARE_CCTK_PARAMETERS;

  const array<int, dim> indextype = {0, 0, 0};
  const GF3D2layout layout(cctkGH, indextype);

  const GF3D2<CCTK_REAL> betax_(layout, betax);
  const GF3D2<CCTK_REAL> betay_(layout, betay);
  const GF3D2<CCTK_REAL> betaz_(layout, betaz);

  const GridDescBaseDevice grid(cctkGH);
  grid.loop_all_device<0, 0, 0>(grid.nghostzones,
                                [=] CCTK_DEVICE(const PointDesc &p)
                                    CCTK_ATTRIBUTE_ALWAYS_INLINE {
                                      betax_(p.I) = p.z;
                                      betay_(p.I) = 0;
                                      betaz_(p.I) = -p.x;
                                    });
}
} //namespace TestPT
