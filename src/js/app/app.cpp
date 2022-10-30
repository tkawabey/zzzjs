#include "precompile.h"
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/ffile.h>
#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/app/app.h"
#include "js/common/type.h"
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"


using namespace zzzJs;



WXJS_INIT_CLASS(App, "wxApp", 0)



/***
 * <properties>
 *	<property name="appName" type=WXJS_TYPE_STRING>アプリケーション名を取得/設定します</property>
 *  <property name="className" type=WXJS_TYPE_STRING>クラス名を取得/設定します</property>
 *  <property name="topWindow" type="@wxWindow">アプリケーションのトップ ウィンドウを取得/設定します。</property>
 *  <property name="vendorName" type=WXJS_TYPE_STRING>ベンダー名を取得/設定します</property>
 *  <property name="argv" type="Array" readonly="Y">
 *   スクリプトに渡された引数を返します
 *  </property>
 * </properties>	
 */
WXJS_BEGIN_PROPERTY_MAP(App)
  WXJS_PROPERTY(P_APPLICATION_NAME, "appName")
  WXJS_PROPERTY(P_CLASS_NAME, "className")
  WXJS_PROPERTY(P_VENDOR_NAME, "vendorName")
  WXJS_PROPERTY(P_TOP_WINDOW, "topWindow")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_DESTRUCTOR(wxApp, App)
	if( p == NULL ) {

	}
WXJS_END_DESTRUCTOR


bool App::GetProperty(wxApp *p,
                      JSContext *cx,
                      JSObject* WXUNUSED(obj),
                      int id,
                      JS::MutableHandle<JS::Value> vp)
{
	switch (id) 
	{
	case P_APPLICATION_NAME:
//		vp.setString( ToJS(cx, p->GetAppName()) );
//		*vp = ToJS(cx, p->GetAppName());
		vp.setString( JS_NewUCStringCopyZ( cx,  p->GetAppName() ) );
		break;
	case P_CLASS_NAME:
//		*vp = ToJS(cx, p->GetClassName());
		vp.setString( JS_NewUCStringCopyZ( cx,  p->GetClassName() ) );
		break;
	case P_VENDOR_NAME:
//		*vp = ToJS(cx, p->GetVendorName());
		vp.setString( JS_NewUCStringCopyZ( cx,  p->GetVendorName() ) );
		break;
	case P_TOP_WINDOW:
		{
		  wxWindow *win = p->GetTopWindow();
          if ( win != NULL )
          {
            JavaScriptClientData *data
              = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
            if ( data != NULL )
				vp.setObjectOrNull( data->GetObject() );
//    	      *vp = OBJECT_TO_JSVAL(data->GetObject());
          }
          break;
		}
/*		case P_USE_BEST_VISUAL:
		*vp = BOOLEAN_TO_JSVAL(p->GetUseBestVisual());
		break;
*/	}

	return true;
}

bool App::SetProperty(wxApp *p,
                      JSContext *cx,
                      JSObject* WXUNUSED(obj),
                      int id,
                      JS::MutableHandle<JS::Value> vp)
{
	switch (id) 
	{
	case P_APPLICATION_NAME:
		{
			wxString name;
			FromJS(cx, vp, name);
			p->SetAppName(name);
			break;
		}
	case P_CLASS_NAME:
	    {
		    wxString name;
		    FromJS(cx, vp, name);
		    p->SetClassName(name);
		    break;
	    }
	case P_VENDOR_NAME:
		{
			wxString name;
			FromJS(cx, vp, name);
			p->SetVendorName(name);
			break;
		}

  case P_TOP_WINDOW:
        {
		if ( vp.isObjectOrNull() )
          {
			  JSObject *objWin = vp.toObjectOrNull();
			if ( zzzJs::HasPrototype(cx, objWin, "Window") )
            {
              wxWindow *win = (wxWindow*)JS_GetPrivate(objWin);
			  if ( win != NULL )
				p->SetTopWindow(win);
    		  break;
            }
          }
		}
    }

	return true;
}