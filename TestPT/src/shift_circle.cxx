#include <cmath>
#include <ctype.h>
#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>
#include <loopcontrol.h>

void TestPT(CCTK_ARGUMENTS);
void TestPT(CCTK_ARGUMENTS) {
  DECLARE_CCTK_ARGUMENTS_TestPT;
  DECLARE_CCTK_PARAMETERS;

  CCTK_VINFO("TestPT actually ran.");

  const int di = 1;
  const int dj = di * cctk_ash[0];
  const int dk = dj * cctk_ash[1];
  const int np = dk * cctk_ash[2];
  CCTK_LOOP3_ALL(TestPT, cctkGH, i, j, k) {

    const int ind = CCTK_GFINDEX3D(cctkGH, i, j, k);

    CCTK_REAL xx, yy, zz;
    xx = vcoordx[ind] - center_offset[0];
    yy = vcoordy[ind] - center_offset[1];
    zz = vcoordz[ind] - center_offset[2];

	betax[ind] = yy;
	betay[ind] = -xx;
	
	CCTK_VINFO("Set beta inside loop.");
  }
  CCTK_ENDLOOP3_ALL(TestPT);
}
