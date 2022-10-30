
#include "precompile.h"


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/common/conf.h"





JSBool
ZzzJs_JS_PropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                JS::MutableHandle<JS::Value> vp)
{
	return JS_TRUE;
}
JSBool 
ZzzJs_JS_DeletePropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                      JSBool *succeeded)
{	
	return JS_TRUE;
}
JSBool
ZzzJs_JS_ResolveStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id)
{	
	return JS_TRUE;
}
JSBool
ZzzJs_JS_StrictPropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JSBool strict,
                      JS::MutableHandle<JS::Value> vp)
{	
	return JS_TRUE;
}
const TCHAR* ZzzJs_JS_getNativeString(JSContext *cx, jsval str, wxString& buf)
{
	JSString *pJsString = JS_ValueToString(cx, str);
	if( pJsString == NULL ) {
		wxLogError(_T("fail to JS_ValueToString."));
		return _T("");
	}
	return ZzzJs_JS_getNativeString(cx, pJsString, buf);
}
const TCHAR* ZzzJs_JS_getNativeString(JSContext *cx, JSString* pJsString, wxString& buf)
{
	bool bCase = false;
	// 日本語を扱えるように、UTF8で取得して、ネイティブに変換
	char * pUTFStr = JS_EncodeStringToUTF8(cx, pJsString);
	if( pUTFStr == NULL ) {
		wxLogError(_T("fail to JS_EncodeStringToUTF8."));
		return _T("");
	}
	// ネイティブに変換
	buf = wxString(pUTFStr, wxConvUTF8);
	return (const TCHAR*)buf;
}



