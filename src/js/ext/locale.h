#ifndef _ZZZJS_EXT_LOCALE_H
#define _ZZZJS_EXT_LOCALE_H

#include <wx/intl.h>
#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/apiwrap.h"
#include "js/common/conf.h"


namespace zzzJs
{
	namespace ext
	{
		class Locale : public ApiWrapper<Locale, wxLocale>
		{
		public:
            static void InitClass(JSContext *cx,
                                  JSObject *obj,
                                  JSObject *proto);

			WXJS_DECLARE_GET_PROP(wxLocale)
			WXJS_DECLARE_CONSTRUCTOR(wxLocale)
			enum
			{
					P_CanonicalName
				,	P_Locale
				,	P_Name
				,	P_SysName
				,	P_SystemEncoding
				,	P_SystemEncodingName
				,	P_SystemLanguage
				,	P_IsOk
			};

			WXJS_DECLARE_PROPERTY_MAP()
				
			WXJS_DECLARE_METHOD_MAP()
			WXJS_DECLARE_METHOD(addCatalog)
			WXJS_DECLARE_METHOD(addCatalogLookupPathPrefix)
			//WXJS_DECLARE_METHOD(addLanguage)	... TODO
			//WXJS_DECLARE_METHOD(findLanguageInfo)... TODO
			//WXJS_DECLARE_METHOD(getLanguageInfo)... TODO
			WXJS_DECLARE_METHOD(getLanguageName)
			WXJS_DECLARE_METHOD(getString)
			WXJS_DECLARE_METHOD(getHeaderValue)
			WXJS_DECLARE_METHOD(init)
			WXJS_DECLARE_METHOD(isLoaded)


			WXJS_DECLARE_STATIC_METHOD_MAP()
			WXJS_DECLARE_METHOD(getTranslation)
		};
	}; // namespace ext
}; // namespace wxjs

#endif //_ZZZJS_EXT_LOCALE_H
