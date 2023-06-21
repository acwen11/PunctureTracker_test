#include <cmath>
#include <ctype.h>
#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

#include <loop_device.hxx>
#include <array>
#include <limits>

namespace TestBetaZ {
using namespace std;
using namespace Loop;

extern "C" void Loop_reflection_bd(CCTK_ARGUMENTS) {
  DECLARE_CCTK_ARGUMENTS_Loop_reflection_bd;
  DECLARE_CCTK_PARAMETERS;

  const array<int, dim> indextype = {0, 0, 0};
  const GF3D2layout layout(cctkGH, indextype);

  const GF3D2<CCTK_REAL> betax_(layout, betax);
  const GF3D2<CCTK_REAL> betay_(layout, betay);
  const GF3D2<CCTK_REAL> betaz_(layout, betaz);

  const GridDescBaseDevice grid(cctkGH);
  grid.loop_device<0, 0, 0, boundaries>(grid.nghostzones,
                                [=] CCTK_DEVICE(const PointDesc &p)
                                    CCTK_ATTRIBUTE_ALWAYS_INLINE {
			CCTK_REAL betaz_upper = betaz_(p.I[0], p.I[1], p.I[2] + 1);
			CCTK_REAL betaz_lower = betaz_(p.I[0], p.I[1], p.I[2] - 1);

			if (abs(betaz_upper - betaz_lower) > 10 * numeric_limits<CCTK_REAL>::epsilon()) {
				CCTK_VERROR("Betaz parity check failed: upper value = %g; lower value = %g", betaz_upper, betaz_lower);
			}

		});
}

} //namespace TestPT
