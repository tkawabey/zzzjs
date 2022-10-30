
#ifndef _WX_PG_EVT_GRID_H
#define _WX_PG_EVT_GRID_H

#include <wx/propgrid/property.h>
#include <wx/propgrid/propgridiface.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
#include "js/gui/event/jsevent.h"
#include <wx/treectrl.h>


namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			
			typedef JSEvent<wxPropertyGridEvent> PrivGridEvent;
			class GridEvent : public ApiWrapper<GridEvent, PrivGridEvent>
			{
			public:
				WXJS_DECLARE_GET_PROP(PrivGridEvent)
				WXJS_DECLARE_SET_PROP(PrivGridEvent)
				WXJS_DECLARE_SET_STR_PROP(PrivGridEvent)

				virtual ~GridEvent()
				{
				}
                
				enum
				{
					  P_CAN_VETO
					, P_COLUMN
					, P_MAIN_PARENT
					, P_PROPERTY
					, P_VALIDATION_FAILURE_BEHAVIOR
					, P_VALIDATION_FAILURE_MESSAGE
					, P_PROPERTY_NAME
					, P_PROPERTY_VALUE
					, P_VETO
				};

				WXJS_DECLARE_PROPERTY_MAP()
			};
		}; // namespace pg
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_ARGID_H
