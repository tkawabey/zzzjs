#ifndef _wxJS_Type_H
#define _wxJS_Type_H

#include <jsapi.h>
#include <jsdate.h>
#include <jsfriendapi.h>

#include <wx/datetime.h>
#include <wx/variant.h>
#include "js/common/strsptr.h"

class wxStringList;
class wxArrayString;

#ifndef int32
	#define int32	__int32
#endif
#ifndef uintN
	#define	uintN	unsigned int
#endif

namespace zzzJs
{
    template<class T>
    bool FromJS(JSContext *cx, JS::Value v, T& to);

    template<>
    bool FromJS<int>(JSContext *cx, JS::Value v, int &to);

    template<>
    bool FromJS<unsigned int>(JSContext *cx, JS::Value v, unsigned int &to);

    template<>
    bool FromJS<long>(JSContext *cx, JS::Value v, long &to);

    template<>
    bool FromJS<double>(JSContext *cx, JS::Value v, double &to);

    template<>
    bool FromJS<long long>(JSContext *cx, JS::Value v, long long &to);
	
    template<>
    bool FromJS<unsigned long long>(JSContext *cx, JS::Value v, unsigned long long &to);

	
    bool FromJS<int64_t>(JSContext *cx, JS::Value v, int64_t &to);
	
    template<>
    bool FromJS<uint64_t>(JSContext *cx, JS::Value v, uint64_t &to);




    template<>
    bool FromJS<bool>(JSContext *cx, JS::Value v, bool &to);

    template<>
    bool FromJS<wxString>(JSContext *cx, JS::Value v, wxString &to);

    template<>
    bool FromJS<wxDateTime>(JSContext *cx, JS::Value v, wxDateTime& to);

    template<>
    bool FromJS<StringsPtr>(JSContext *cx, JS::Value v, StringsPtr &to);

    template<>
    bool FromJS<wxArrayString>(JSContext *cx, JS::Value v, wxArrayString &to);

    template<>
    bool FromJS<wxArrayInt>(JSContext *cx, JS::Value v, wxArrayInt &to);

    template<>
    bool FromJS<wxStringList>(JSContext *cx, JS::Value v, wxStringList &to);

    template<>
    bool FromJS<wxVariant>(JSContext *cx, JS::Value v, wxVariant &to);
	
    //template<>
    //bool FromJS<wxPoint>(JSContext *cx, JS::Value v, wxPoint &to);
	
    //template<>
    //bool FromJS<wxSize>(JSContext *cx, JS::Value v, wxSize &to);
	
    //template<>
    //bool FromJS<wxRect>(JSContext *cx, JS::Value v, wxRect &to);
	
    //template<>
    //bool FromJS<wxColour>(JSContext *cx, JS::Value v, wxColour &to);



    template<class T>
    JS::Value ToJS(JSContext *cx, const T &wx);

    template<>
    JS::Value ToJS<int>(JSContext *cx, const int &from);

	
    template<class T>
    bool ToJSVal(JSContext *cx, JS::MutableHandle<JS::Value>& v, const T &wx);

    template<>
    bool ToJSVal<int>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const int &from);



    template<>
    JS::Value ToJS<unsigned int>(JSContext *cx, const unsigned int &from);

	
    template<>
    bool ToJSVal<unsigned int>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const unsigned int &from);

    template<>
    JS::Value ToJS<long>(JSContext *cx, const long &from);
		
    template<>
    bool ToJSVal<long>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const long &from);



    template<>
    JS::Value ToJS<unsigned long>(JSContext *cx, const unsigned long&from);
	
    template<>
    bool ToJSVal<unsigned long>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const unsigned long &from);


    template<>
    JS::Value ToJS<float>(JSContext *cx, const float& from);
	
    template<>
    bool ToJSVal<float>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const float &from);


    template<>
    JS::Value ToJS<double>(JSContext *cx, const double &from);
	
    template<>
    bool ToJSVal<double>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const double &from);

    template<>
    JS::Value ToJS<bool>(JSContext *cx, const bool &from);
	
    template<>
    bool ToJSVal<bool>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const bool &from);

    template<>
    JS::Value ToJS<wxString>(JSContext *cx, const wxString &from);
	
    template<>
    bool ToJSVal<wxString>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxString &from);

    template<>
    JS::Value ToJS<wxDateTime>(JSContext *cx, const wxDateTime &from);
	
    template<>
    bool ToJSVal<wxDateTime>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxDateTime &from);

    template<>
    JS::Value ToJS<wxArrayString>(JSContext *cx, const wxArrayString &from);
	

    template<>
    JS::Value ToJS<wxArrayInt>(JSContext *cx, const wxArrayInt &from);

    template<>
    bool ToJSVal<wxArrayInt>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxArrayInt &from);
	
    template<>
    bool ToJSVal<wxArrayString>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxArrayString &from);

    template<>
    JS::Value ToJS<wxStringList>(JSContext *cx, const wxStringList &from);
	
    template<>
    bool ToJSVal<wxStringList>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxStringList &from);

	
    template<>
    JS::Value ToJS<wxVariant>(JSContext *cx, const wxVariant &from);
	
    template<>
    bool ToJSVal<wxVariant>(JSContext *cx, JS::MutableHandle<JS::Value>& v, const wxVariant &from);


	bool ConvertJs2WxVariant(JSContext *cx, JS::Value& v, wxVariant& to);
	bool ConvertWxVariant2Js(JSContext *cx, const wxVariant& v, JS::Value& to);
}; // Namespace zzzJs

#endif // _wxJS_Type_H
