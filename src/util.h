//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_UTIL_H_
#define _BULLETPLUGIN_UTIL_H_

/**
 * Holds per triangle information for a physics triangle.
 */
struct Triangle {
	/**
	 * The 3 verts that make up a triangle.
	 */
	btVector3 vertex[3];

	/**
	 * The material ID used for identifying what physics material the triangle has.
	 */
	int materialID;
};

class TriangleF {
public:
	TriangleF(const btVector3 &v0, const btVector3 &v1, const btVector3 &v2) {
		mVertex[0] = v0;
		mVertex[1] = v1;
		mVertex[2] = v2;
	}

	bool isPointInside(const btVector3 &point) const;

	bool isPointOnEdge(const btVector3 &point) const;

	bool isTriangleAdjacent(const TriangleF &other) const;

	inline int getCountOfSamePoints(const TriangleF &other) const {
		int same = 0;
		if (other.mVertex[0] == mVertex[0]) same++;
		if (other.mVertex[0] == mVertex[1]) same++;
		if (other.mVertex[0] == mVertex[2]) same++;
		if (other.mVertex[1] == mVertex[0]) same++;
		if (other.mVertex[1] == mVertex[1]) same++;
		if (other.mVertex[1] == mVertex[2]) same++;
		if (other.mVertex[2] == mVertex[0]) same++;
		if (other.mVertex[2] == mVertex[1]) same++;
		if (other.mVertex[2] == mVertex[2]) same++;
		return same;
	}

private:
	btVector3 mVertex[3];
};

inline float point_distance_to_line(const btVector3 &p, const btVector3 &q, const btVector3 &point) {
	return btCross(q - p, p - point).length() / (p - q).length();
}

inline bool isCollinear(const btVector3 &up, const btVector3 &uq, const btVector3 &vp, const btVector3 &vq) {
	//If vp and vq are on line u
	return (point_distance_to_line(up, uq, vp) < 0.1f &&
		point_distance_to_line(up, uq, vq) < 0.1f);
}

#endif // _BULLETPLUGIN_UTIL_H_