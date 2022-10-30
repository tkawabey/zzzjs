
#ifndef _WX_AUI_NAMAGER_H
#define _WX_AUI_NAMAGER_H


#include <wx/aui/framemanager.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace aui 
		{
			class AuiManager : public ApiWrapper<AuiManager, wxAuiManager>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(wxAuiManager)
				WXJS_DECLARE_DEL_PROP(wxAuiManager)
				WXJS_DECLARE_GET_PROP(wxAuiManager)
				WXJS_DECLARE_SET_PROP(wxAuiManager)
				WXJS_DECLARE_CONSTRUCTOR(wxAuiManager)
				WXJS_DECLARE_DESTRUCTOR(wxAuiManager)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_FLAG
					,	P_ManagedWindow
					,	P_DockSizeConstraint
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(addPane)
				WXJS_DECLARE_METHOD(update)
				WXJS_DECLARE_METHOD(unInit)
				WXJS_DECLARE_METHOD(detachPane)
				WXJS_DECLARE_METHOD(hideHint)
				WXJS_DECLARE_METHOD(insertPane)
				WXJS_DECLARE_METHOD(savePerspective)
				WXJS_DECLARE_METHOD(loadPerspective)
				WXJS_DECLARE_METHOD(setManagedWindow )
				WXJS_DECLARE_METHOD(getPane)
				
				WXJS_DECLARE_CONSTANT_MAP()
			};


			class AuiManagerEventHandler : public EventConnector<wxAuiManager>
					, public wxEvtHandler
			{
			public:
				// Events
				void OnClicked(wxAuiManagerEvent &event);
				void OnClose(wxAuiManagerEvent &event);
				void OnMaximize(wxAuiManagerEvent &event);
				void OnRestore(wxAuiManagerEvent &event);
				void OnActivated(wxAuiManagerEvent &event);
				void OnRender(wxAuiManagerEvent &event);
				void OnFindManager(wxAuiManagerEvent &event);
				
				
				
				static void InitConnectEventMap();


				private:
				static void ConnectClicked(wxAuiManager *p, bool connect);
				static void ConnectClose(wxAuiManager *p, bool connect);
				static void ConnectMaximize(wxAuiManager *p, bool connect);
				static void ConnectRestore(wxAuiManager *p, bool connect);
				static void ConnectActivate(wxAuiManager *p, bool connect);
				static void ConnectRender(wxAuiManager *p, bool connect);
				static void ConnectFindManager(wxAuiManager *p, bool connect);
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_AUI_NAMAGER_H
