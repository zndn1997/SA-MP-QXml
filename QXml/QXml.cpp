// QXml.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "QXml.h"
#include "XML.h"
#include "Debug.h"
#include "Native.h"

typedef void(*logprintf_t)(const char* format, ...);

logprintf_t logprintf;
QXMLHandler* gXMLHandler;

extern void *pAMXFunctions;

AMX_NATIVE_INFO projectNatives[] = {
	{"CreateXMLDocument", Native::CreateXMLDocument},
	{"DestroyXMLDocument", Native::DestroyXMLDocument},
	
	{"CreateXMLNodePointer", Native::CreateXMLNodePointer},
	{"CreateXMLCloneNodePointer", Native::CreateXMLCloneNodePointer},
	{"DestroyXMLNodePointer", Native::DestroyXMLNodePointer},
	{"SetNodeFirstChild", Native::SetNodeFirstChild},
	{"SetNodeNextSibling", Native::SetNodeNextSibling},
	{"GetNodeName", Native::GetNodeName},
	//{"GetNodeValue", Native::GetNodeValue},

	{"CreateXMLAttributePointer", Native::CreateXMLAttributePointer},
	{"DestroyXMLAttributePointer", Native::DestroyXMLAttributePointer},
	{"SetAttributeFirst", Native::SetAttributeFirst},
	{"SetAttributeNext", Native::SetAttributeNext},
	{"GetAttributeName", Native::GetAttributeName},
	{"GetAttributeValue", Native::GetAttributeValue},
	{"GetAttributeValueInt", Native::GetAttributeValueInt},
	{"GetAttributeValueFloat", Native::GetAttributeValueFloat},
	{"GetAttributeValueBool", Native::GetAttributeValueBool},

	{0, 0}
};

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = static_cast<logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);

	gXMLHandler = new QXMLHandler();

	Debug::Initialize("QXml_Debug.txt");

	DEBUG << "QXml debugging started." << std::endl;
	logprintf("[QXml] Plugin version %s loaded.", PLUGIN_VERSION);

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("QXml unloaded.");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, projectNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
