#ifndef ___ZZZ_JS_COMMON_CONF_H___
#define ___ZZZ_JS_COMMON_CONF_H___


#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>

#ifdef _MSC_VER
	// Turn off identifier was truncated warning
	#pragma warning(disable:4786)
	// Turn off deprecated warning
	#pragma warning(disable:4996)
#endif 

#include <jsapi.h>
/*
#include "defs.h"
#include "clntdata.h"
#include "apiwrap.h"
#include "type.h"
*/
static const int WXJS_CONTEXT_SIZE = 32768;
static const int WXJS_START_PROPERTY_ID = -128;



JSBool ZzzJs_JS_PropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                JS::MutableHandle<JS::Value> vp);
JSBool ZzzJs_JS_DeletePropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                      JSBool *succeeded);
JSBool ZzzJs_JS_ResolveStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id);
JSBool
ZzzJs_JS_StrictPropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JSBool strict,
                      JS::MutableHandle<JS::Value> vp);

const TCHAR* ZzzJs_JS_getNativeString(JSContext *cx, jsval str, wxString& buf);
const TCHAR* ZzzJs_JS_getNativeString(JSContext *cx, JSString* pJsString, wxString& buf);

template<typename TYPE>
bool ZzzJs_JS_getJsValToT(const JS::Value& value, TYPE &r)
{
	if( value.isBoolean() ) {
		r = (TYPE)value.toBoolean();
	} else
	if( value.isDouble() ) {
		r = (TYPE)value.toDouble();
	} else
	if( value.isFalse() ) {
		r = (TYPE)0;
	} else
	if( value.isTrue() ) {
		r = (TYPE)1;
	} else
	if( value.isInt32() ) {
		r = (TYPE)value.toInt32();
	} else
	if( value.isNumber() ) {
		r = (TYPE)value.toNumber();
	} else {
		return false;
	}
	return true;
}


#endif /*___ZZZ_JS_COMMON_CONF_H___*/