#ifndef _ZZZJS_JS_GUI_EVENT_BOOKCTRL_EVT_H
#define _ZZZJS_JS_GUI_EVENT_BOOKCTRL_EVT_H

#include <wx/bookctrl.h>
#include "js/common/apiwrap.h"
#include "js/gui/event/jsevent.h"


namespace zzzJs
{
	namespace gui
	{
		typedef JSEvent<wxBookCtrlEvent> PrivBookCtrlEvent;
		class BookCtrlEvent : public ApiWrapper<BookCtrlEvent, PrivBookCtrlEvent>
		{
		public:
			WXJS_DECLARE_GET_PROP(PrivBookCtrlEvent)
			WXJS_DECLARE_SET_PROP(PrivBookCtrlEvent)
			WXJS_DECLARE_SET_STR_PROP(PrivBookCtrlEvent)

			enum
			{
					P_SELECTION
				,	P_OLD_SELECTION
			};

			WXJS_DECLARE_PROPERTY_MAP()
		};
	}; // namespace gui
}; // namespace wxjs

#endif //_ZZZJS_JS_GUI_EVENT_BOOKCTRL_EVT_H
