
#ifndef _WX_AUI_NOTEBOOK_H
#define _WX_AUI_NOTEBOOK_H

#include <wx/aui/auibook.h>
#include "js/common/evtconn.h"
#include "js/common/jswrap.h"



namespace zzzJs
{
	namespace gui
	{
		namespace aui 
		{
			class AuiNotebook : public JsWrapper<AuiNotebook, wxAuiNotebook>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);

				ZZZJS_DECLARE_ADD_PROP(wxAuiNotebook)
				ZZZJS_DECLARE_DEL_PROP(wxAuiNotebook)
				ZZZJS_DECLARE_GET_PROP(wxAuiNotebook)
				ZZZJS_DECLARE_SET_PROP(wxAuiNotebook)
				ZZZJS_DECLARE_CONSTRUCTOR(wxAuiNotebook)
				ZZZJS_DECLARE_DESTRUCTOR(wxAuiNotebook)
				
				// Object 2 Instatance
				ZZZJS_DECLARE_O2I(wxAuiNotebook)

				ZZZJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_GetPageCount
					,	P_Selection
					,	P_TabCtrlHeight
				};

				ZZZJS_DECLARE_METHOD_MAP()
				ZZZJS_DECLARE_METHOD(create)
				ZZZJS_DECLARE_METHOD(addPage )
				ZZZJS_DECLARE_METHOD(insertPage)
				ZZZJS_DECLARE_METHOD(getHeightForPageHeight)
				ZZZJS_DECLARE_METHOD(getPageBitmap)
				ZZZJS_DECLARE_METHOD(getPageIndex)
				ZZZJS_DECLARE_METHOD(getPageToolTip)
				ZZZJS_DECLARE_METHOD(setFont)
				ZZZJS_DECLARE_METHOD(setMeasuringFont)
				ZZZJS_DECLARE_METHOD(setNormalFont)
				ZZZJS_DECLARE_METHOD(setPageBitmap)
				ZZZJS_DECLARE_METHOD(setPageToolTip)
				ZZZJS_DECLARE_METHOD(setSelectedFont)
				ZZZJS_DECLARE_METHOD(setTabCtrlHeight)
				ZZZJS_DECLARE_METHOD(setUniformBitmapSize)
				ZZZJS_DECLARE_METHOD(split)
				ZZZJS_DECLARE_METHOD(showWindowMenu)


				ZZZJS_DECLARE_CONSTANT_MAP()
				static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
			};


			class AuiNotebookEventHandler : public EventConnector<wxAuiNotebook>
					, public wxEvtHandler
			{
			public:
				// Events
				void OnPageClose(wxAuiNotebookEvent  &event);
				static void InitConnectEventMap();
				private:
				static void ConnectPageClose(wxAuiNotebook *p, bool connect);
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_AUI_NOTEBOOK_H
