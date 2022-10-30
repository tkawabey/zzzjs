#ifndef ___ZZZ_JS_APP_H___
#define ___ZZZ_JS_APP_H___


#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/apiwrap.h"



namespace zzzJs
{

	class App :  public ApiWrapper<App, wxApp>
	{
	public:
		App();
		virtual ~App();

		static bool GetProperty(wxApp *p,
								JSContext *cx,
								JSObject *obj,
								int id,
								JS::MutableHandle<JS::Value> vp);
		static bool SetProperty(wxApp *p,
								JSContext *cx,
								JSObject *obj, 
								int id, 
								JS::MutableHandle<JS::Value> vp);
            WXJS_DECLARE_DESTRUCTOR(wxApp)

		WXJS_DECLARE_PROPERTY_MAP()
		enum
		{
		  P_APPLICATION_NAME
		  , P_TOP_WINDOW
		  , P_INITIALIZED
		  , P_CLASS_NAME
		  , P_VENDOR_NAME
		};

	};
}


#endif /*___ZZZ_JS_CONTROL_WINDOW_H___*/