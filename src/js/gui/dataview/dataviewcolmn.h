
#ifndef _WX_DATAVIEW_COLMN_H
#define _WX_DATAVIEW_COLMN_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class DataViewColumn : public ApiWrapper<DataViewColumn, wxDataViewColumn>
			{
			public:				
				WXJS_DECLARE_GET_PROP(wxDataViewColumn)
				WXJS_DECLARE_SET_PROP(wxDataViewColumn)
				WXJS_DECLARE_SET_STR_PROP(wxDataViewColumn)
				WXJS_DECLARE_CONSTRUCTOR(wxDataViewColumn)
				WXJS_DECLARE_DESTRUCTOR(wxDataViewColumn)



				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_ModelColumn
					,	P_OWNER
					,	P_RENDER
				};
				
				//WXJS_DECLARE_METHOD_MAP()
				
				WXJS_DECLARE_CONSTANT_MAP()
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_COLMN_H
