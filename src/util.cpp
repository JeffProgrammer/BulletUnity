//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include <btBulletDynamicsCommon.h>
#include "pluginAPI.h"
#include "util.h"
#include <stdarg.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef _WIN32
	// Win32 compatability layer
	#include <asprintf.h>
#endif

bool TriangleF::isPointInside(const btVector3 &point) const {
	//http://www.blackpawn.com/texts/pointinpoly/
	btVector3 v0 = mVertex[2] - mVertex[0],
				 v1 =  mVertex[1] - mVertex[0],
				 v2 = point - mVertex[0];

	float dot00 = btDot(v0, v0),
			dot01 = btDot(v0, v1),
			dot02 = btDot(v0, v2),
			dot11 = btDot(v1, v1),
			dot12 = btDot(v1, v2);

	float invDenom = 1.f / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u >= 0.f) && (v >= 0.f) && (u + v < 1.f);
}

bool TriangleF::isPointOnEdge(const btVector3 &point) const {
	float lineDist01 = btCross(mVertex[0] - point, mVertex[1] - mVertex[0]).length();
	float lineDist12 = btCross(mVertex[1] - point, mVertex[2] - mVertex[1]).length();
	float lineDist20 = btCross(mVertex[2] - point, mVertex[0] - mVertex[2]).length();
	return (lineDist01 <= 0.001f || lineDist12 <= 0.001f || lineDist20 <= 0.001f);
}

bool TriangleF::isTriangleAdjacent(const TriangleF &other) const {
	// Check if the two are the same triangle, or the easy check if 2 or more the same, its adjacent.
	if (getCountOfSamePoints(other) >= 2)
		return true;

	// Collinear check
	if (isCollinear(mVertex[1], mVertex[0], other.mVertex[1], other.mVertex[0]))
		return true;
	if (isCollinear(mVertex[2], mVertex[1], other.mVertex[1], other.mVertex[0]))
		return true;
	if (isCollinear(mVertex[0], mVertex[2], other.mVertex[1], other.mVertex[0]))
		return true;
	if (isCollinear(mVertex[1], mVertex[0], other.mVertex[2], other.mVertex[1]))
		return true;
	if (isCollinear(mVertex[2], mVertex[1], other.mVertex[2], other.mVertex[1]))
		return true;
	if (isCollinear(mVertex[0], mVertex[2], other.mVertex[2], other.mVertex[1]))
		return true;
	if (isCollinear(mVertex[1], mVertex[0], other.mVertex[0], other.mVertex[2]))
		return true;
	if (isCollinear(mVertex[2], mVertex[1], other.mVertex[0], other.mVertex[2]))
		return true;
	if (isCollinear(mVertex[0], mVertex[2], other.mVertex[0], other.mVertex[2]))
		return true;
	return false;
}

extern "C" {
	PLUGIN_API void set_debug_callback(UNITY_DEBUGLOG_CALLBACK cb) {
		unityDebugLog = cb;
	}
}

void unitylogf(const char *format, ...) {
	//Get the args formatted
	va_list args;
	va_start(args, format);

	char *string;
	vasprintf(&string, format, args);

	va_end(args);

	//Print it
	unityDebugLog(string);

	//Hacky file
	std::time_t t = std::time(nullptr);

	//Todo: get actual file path?
	std::ofstream tmpFile("out.log", std::ios::app);
	tmpFile << "[" << std::put_time(std::localtime(&t), "%c") << "] " << string << std::endl;
	tmpFile.flush();
	tmpFile.close();

	//Hooray, C
	free(string);

}