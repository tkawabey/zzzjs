
#ifndef _WX_SETABLE_HEADER_COLUMN_H
#define _WX_SETABLE_HEADER_COLUMN_H

#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
#include <wx/headercol.h>
namespace zzzJs
{
	namespace gui
	{
		class SettableHeaderColumn : public ApiWrapper<SettableHeaderColumn, wxSettableHeaderColumn>
		{
		public:
				
		  
			WXJS_DECLARE_GET_PROP(wxSettableHeaderColumn)
			WXJS_DECLARE_SET_PROP(wxSettableHeaderColumn)
			WXJS_DECLARE_SET_STR_PROP(wxSettableHeaderColumn)
			WXJS_DECLARE_CONSTRUCTOR(wxSettableHeaderColumn)
			WXJS_DECLARE_DESTRUCTOR(wxSettableHeaderColumn)

			WXJS_DECLARE_PROPERTY_MAP()

			/**
			* Property Ids.
			*/
			enum
			{
					P_TITLE
				,	P_BITMAP
				,	P_WIDTH
				,	P_MINWIDTH
				,	P_ALIGNMENT
				,	P_FLAGS
				,	P_FLAG
				,	P_RESIZEABLE
				,	P_SORTABLE
				,	P_REORDERABLE
				,	P_HIDDEN
				,	P_SORT_ORDER
			};

			WXJS_DECLARE_METHOD_MAP()
		    WXJS_DECLARE_METHOD(changeFlag)
			WXJS_DECLARE_METHOD(clearFlag)
			WXJS_DECLARE_METHOD(toggleFlag )
			WXJS_DECLARE_METHOD(unsetAsSortKey)
			WXJS_DECLARE_METHOD(toggleSortOrder)
				
			//WXJS_DECLARE_CONSTANT_MAP()
		};

	}; // namespace gui
}; //namespace wxjs
#endif //_WX_SETABLE_HEADER_COLUMN_H
