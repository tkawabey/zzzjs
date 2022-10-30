
#ifndef _WX_DATAVIEW_VIRTUAL_LIST_MODEL_H
#define _WX_DATAVIEW_VIRTUAL_LIST_MODEL_H

#include <wx/dataview.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace dataview 
		{
			class MyDataViewVirtualListModel: public wxDataViewVirtualListModel
			{
			public:
				MyDataViewVirtualListModel(JSContext *cx, JSObject* pObj, unsigned int initial_size = 0 );

				virtual unsigned int GetColumnCount() const wxOVERRIDE;

				virtual wxString GetColumnType( unsigned int col ) const wxOVERRIDE;

				virtual void GetValueByRow( wxVariant &variant,
											unsigned int row, unsigned int col ) const wxOVERRIDE;

				virtual bool GetAttrByRow( unsigned int row, unsigned int col,
										   wxDataViewItemAttr &attr ) const wxOVERRIDE;

				virtual bool SetValueByRow( const wxVariant &variant,
											unsigned int row, unsigned int col ) wxOVERRIDE;
			private:
				JSContext*	m_pCx;
				JSObject*	m_pObj;
			};

			class DataViewVirtualListModel : public ApiWrapper<DataViewVirtualListModel, MyDataViewVirtualListModel>
			{
			public:
				
				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_ADD_PROP(MyDataViewVirtualListModel)
				WXJS_DECLARE_DEL_PROP(MyDataViewVirtualListModel)
				WXJS_DECLARE_GET_PROP(MyDataViewVirtualListModel)
				WXJS_DECLARE_SET_PROP(MyDataViewVirtualListModel)
				WXJS_DECLARE_CONSTRUCTOR(MyDataViewVirtualListModel)
				WXJS_DECLARE_DESTRUCTOR(MyDataViewVirtualListModel)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_ColumnCount 
					,	P_FLAG
					,	P_ManagedWindow
					,	P_DockSizeConstraint
				};

				WXJS_DECLARE_METHOD_MAP()
				//WXJS_DECLARE_METHOD(addNotifier)
				WXJS_DECLARE_METHOD(getItem)
				WXJS_DECLARE_METHOD(reset)
				WXJS_DECLARE_METHOD(rowAppended)
				WXJS_DECLARE_METHOD(rowChanged)
				WXJS_DECLARE_METHOD(rowDeleted)
				WXJS_DECLARE_METHOD(rowInserted)
				WXJS_DECLARE_METHOD(rowPrepended)
				WXJS_DECLARE_METHOD(rowValueChanged)
				WXJS_DECLARE_METHOD(rowsDeleted)


//				WXJS_DECLARE_CONSTANT_MAP()
			};


		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_DATAVIEW_VIRTUAL_LIST_MODEL_H
