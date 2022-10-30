#ifndef _wxjs_gui_mdi_child_h
#define _wxjs_gui_mdi_child_h

#include "js/common/apiwrap.h"
namespace zzzJs
{
  namespace gui
  {
    class MDIChildFrame : public ApiWrapper<MDIChildFrame, wxMDIChildFrame>
                        , public wxMDIChildFrame
    {
    public:

		MDIChildFrame() : wxMDIChildFrame()
		{
		}

		virtual ~MDIChildFrame() {}

		virtual wxToolBar* OnCreateToolBar(long style, 
							wxWindowID id,
							const wxString& name);


			WXJS_DECLARE_ADD_PROP(wxMDIChildFrame)
			WXJS_DECLARE_DEL_PROP(wxMDIChildFrame)
			WXJS_DECLARE_SET_STR_PROP(wxMDIChildFrame)
			WXJS_DECLARE_CONSTRUCTOR(wxMDIChildFrame)
			WXJS_DECLARE_DESTRUCTOR(wxMDIChildFrame)
      
			WXJS_DECLARE_METHOD_MAP()
			WXJS_DECLARE_METHOD(create)
			WXJS_DECLARE_METHOD(activate)
			WXJS_DECLARE_METHOD(maximize)
			WXJS_DECLARE_METHOD(restore)
                
		static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
      
    private:                     
    };
  }
};

#endif // _wxjs_gui_mdi_child_h
