
#ifndef _WX_HEADER_COLUMN_H
#define _WX_HEADER_COLUMN_H

#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
#include <wx/headercol.h>
namespace zzzJs
{
	namespace gui
	{
		class HeaderColumn : public ApiWrapper<HeaderColumn, wxHeaderColumn>
		{
		public:
				
			WXJS_DECLARE_GET_PROP(wxHeaderColumn)
			WXJS_DECLARE_SET_PROP(wxHeaderColumn)
			WXJS_DECLARE_CONSTRUCTOR(wxHeaderColumn)
			WXJS_DECLARE_DESTRUCTOR(wxHeaderColumn)

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
				,	P_IS_RESIZEABLE
				,	P_IS_REORDERABLE
				,	P_IS_HIDDEN
				,	P_IS_SORTABLE
				,	P_IS_SHOWN
				,	P_IS_SORTKEY
				,	P_IS_SORT_ORDER_ASCENDLING
			};

			WXJS_DECLARE_METHOD_MAP()
		    WXJS_DECLARE_METHOD(hasFlag)
				
			//WXJS_DECLARE_CONSTANT_MAP()
		};

	}; // namespace gui
}; //namespace wxjs
#endif //_WX_HEADER_COLUMN_H
