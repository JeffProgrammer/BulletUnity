//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PLUGINAPI_H_
#define _BULLETPLUGIN_PLUGINAPI_H_

#if _MSC_VER
	#define PLUGIN_API __declspec(dllexport)
#else
	#define PLUGIN_API
#endif

// Reference: https://github.com/natbro/UnityPlugin/blob/master/UnityPluginTest/Assets/Scripts/UnityPlugin.cs
typedef void(*UNITY_TICK_CALLBACK)(float dt);

typedef void(*UNITY_ON_COLLISION_CALLBACK)(void *obj0, void *obj1);

typedef void(*UNITY_MATERIAL_CALLBACK)(void *staticShapePtr, int material, float &friction, float &restitution);

typedef void(*UNITY_ON_ENTER_TRIGGER_CALLBACK)(void *trigger, void *obj);

typedef void(*UNITY_ON_LEAVE_TRIGGER_CALLBACK)(void *trigger, void *obj);

typedef void(*UNITY_DEBUGLOG_CALLBACK)(const char *str);

static UNITY_DEBUGLOG_CALLBACK unityDebugLog;

extern "C" {
	PLUGIN_API void set_debug_callback(UNITY_DEBUGLOG_CALLBACK cb);
}

void unitylogf(const char *format, ...);

#endif // _BULLETPLUGIN_PLUGINAPI_H_