#ifndef _WXJSSpinEvent_H
#define _WXJSSpinEvent_H

#include <wx/spinctrl.h>

#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		typedef JSEvent<wxSpinEvent> PrivSpinEvent;
		class SpinEvent : public ApiWrapper<SpinEvent, PrivSpinEvent>
		{
		public:
			WXJS_DECLARE_GET_PROP(PrivSpinEvent)
			WXJS_DECLARE_SET_PROP(PrivSpinEvent)
			WXJS_DECLARE_SET_STR_PROP(PrivSpinEvent)

			enum
			{
				P_POSITION
			};

			WXJS_DECLARE_PROPERTY_MAP()
		};
	}; // namespace gui
}; // namespace wxjs

#endif //_WXJSSpinEvent_H
