#ifndef _wxjs_gui_mdi_h
#define _wxjs_gui_mdi_h

#include "js/common/apiwrap.h"
namespace zzzJs
{
  namespace gui
  {
    class MDIParentFrame : public ApiWrapper<MDIParentFrame, wxMDIParentFrame>
                         , public wxMDIParentFrame
    {
    public:

		MDIParentFrame() : wxMDIParentFrame()
		{
		}

		virtual ~MDIParentFrame() {}

		virtual wxToolBar* OnCreateToolBar(long style, 
									wxWindowID id,
									const wxString& name);

		WXJS_DECLARE_ADD_PROP(wxMDIParentFrame)
		WXJS_DECLARE_DEL_PROP(wxMDIParentFrame)
		WXJS_DECLARE_GET_PROP(wxMDIParentFrame)
		WXJS_DECLARE_SET_STR_PROP(wxMDIParentFrame)
		WXJS_DECLARE_CONSTRUCTOR(wxMDIParentFrame)
        WXJS_DECLARE_DESTRUCTOR(wxMDIParentFrame)
      
		WXJS_DECLARE_PROPERTY_MAP()
		enum
		{
			P_ACTIVE_CHILD
		};
      
		WXJS_DECLARE_METHOD_MAP()
		WXJS_DECLARE_METHOD(create)
		WXJS_DECLARE_METHOD(activateNext)
		WXJS_DECLARE_METHOD(activatePrevious)
		WXJS_DECLARE_METHOD(arrangeIcons)
		WXJS_DECLARE_METHOD(cascade)
		WXJS_DECLARE_METHOD(tile)
                     
		static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);

    private:                     
    };
  }
};

#endif // _wxjs_gui_mdi_h
