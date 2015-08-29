#ifndef GglVector4_h__
#define GglVector4_h__

#include "Vector4d.h"
#include "Vector4f.h"
#include "Vector4i.h"

#define GglVector4_Set(_tgt, _x, _y, _z, _q)		((_tgt).x=(_x));((_tgt).y=(_y));((_tgt).z=(_z));((_tgt).q=(_q))
#define GglVector4_SetInitialize(_out)				GglVector4_Set(_out, 0.0, 0.0, 0.0, 0.0)
#define GglVector4_SetEqual(_x, _y, _z, _q)			{(_x), (_y), (_z), (_q)}
#define GglVector4_SetInitializeEqual()				GglVector4_SetEqual(0.0, 0.0, 0.0, 0.0)
#define GglVector4_Add(_out, _a, _b)				GglVector4_Set(_out, (_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z, (_a).q+(_b).q)
#define GglVector4_AddEqual(_a, _b)					GglVector4_SetEqual((_a).x+(_b).x, (_a).y+(_b).y, (_a).z+(_b).z, (_a).q+(_b).q)
#define GglVector4_Sub(_out, _a, _b)				GglVector4_Set(_out, (_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z, (_a).q-(_b).q)
#define GglVector4_SubEqual(_a, _b)					GglVector4_SetEqual((_a).x-(_b).x, (_a).y-(_b).y, (_a).z-(_b).z, (_a).q-(_b).q)
#define GglVector4_Dot(_a, _b)						(((_a).x*(_b).x)+((_a).y*(_b).y)+((_a).z*(_b).z)+((_a).q*(_b).q))
#define GglVector4_MulScalar(_vec, _out, _scl)		((_out).x)=((_vec).x)*(_scl); ((_out).y)=((_vec).y)*(_scl); ((_out).z)=((_vec).z)*(_scl); ((_out).q)=((_vec).q)*(_scl)

#endif