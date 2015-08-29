#ifndef GglVector3_h__
#define GglVector3_h__

#include "Vector3d.h"
#include "Vector3f.h"
#include "Vector3i.h"

#define GglVector3_Set(_tgt, _x, _y, _z)			((_tgt).x=(_x));((_tgt).y=(_y));((_tgt).z=(_z))
#define GglVector3_SetInitialize(_out)				GglVector3_Set(_out, 0.0, 0.0, 0.0)
#define GglVector3_SetEqual(_x, _y, _z)				{(_x), (_y), (_z)}
#define GglVector3_SetInitializeEqual()				GglVector3_SetEqual(0.0, 0.0, 0.0)
#define GglVector3_Add(_out, _a, _b)				GglVector3_Set(_out, (_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z)
#define GglVector3_AddEqual(_a, _b)					GglVector3_SetEqual((_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z)
#define GglVector3_Sub(_out, _a, _b)				GglVector3_Set(_out, (_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z)
#define GglVector3_SubEqual(_a, _b)					GglVector3_SetEqual((_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z)
#define GglVector3_Dot(_a, _b)						(((_a).x*(_b).x)+((_a).y*(_b).y)+((_a).z*(_b).z))
#define GglVector3_Cross(_out, _a, _b)				GglVector3_Set((_out), ((_a).y*(_b).z-(_a).z*(_b).y), ((_a).z*(_b).x-(_a).x*(_b).z), ((_a).x*(_b).y-(_a).y*(_b).x))
#define GglVector3_CrossEqual(_a, _b)				GglVector3_SetEqual(((_a).y*(_b).z-(_a).z*(_b).y), ((_a).z*(_b).x-(_a).x*(_b).z), ((_a).x*(_b).y-(_a).y*(_b).x))
#define GglVector3_MulScalar(_vec, _out, _scl)		((_out).x)=((_vec).x)*(_scl); ((_out).y)=((_vec).y)*(_scl); ((_out).z)=((_vec).z)*(_scl)

#endif