//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
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

#endif // _BULLETPLUGIN_PLUGINAPI_H_