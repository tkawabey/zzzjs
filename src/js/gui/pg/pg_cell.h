
#ifndef _WX_PG_CELL_H_
#define _WX_PG_CELL_H_

#include <wx/propgrid/property.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class Cell : public wxPGCell
					   , public ApiWrapper<Cell, wxPGCell>
			{
			public:
				Cell(){

				}
				Cell(const wxPGCell& other)
					  :wxPGCell(other){

				}
				Cell( const wxString& text,
						  const wxBitmap& bitmap = wxNullBitmap,
						  const wxColour& fgCol = wxNullColour,
						  const wxColour& bgCol = wxNullColour )
					  :wxPGCell(text, bitmap, fgCol, bgCol)
				{
				}

				WXJS_DECLARE_GET_PROP(wxPGCell)
				WXJS_DECLARE_SET_PROP(wxPGCell)
				WXJS_DECLARE_CONSTRUCTOR(wxPGCell)
				WXJS_DECLARE_DESTRUCTOR(wxPGCell)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_TEXT
					,	P_HAS_TEXT
					,	P_BITMAP
					,	P_FG_COLOR
					,	P_BG_COLOR
					,	P_FG_FONT
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(setEmptyData)
				WXJS_DECLARE_METHOD(mergeFrom)
				//WXJS_DECLARE_CONSTANT_MAP()
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_CELL_H_
