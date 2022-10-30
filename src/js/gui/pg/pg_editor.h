
#ifndef _WX_PG_EDITOR_H_
#define _WX_PG_EDITOR_H_
#include <wx/gdicmn.h>
#include <wx/window.h>
#include <wx/propgrid/editors.h>
#include <wx/propgrid/property.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class Editor : public wxPGEditor
					   , public ApiWrapper<Editor, wxPGEditor>
					   , wxClientDataContainer
			{
			public:
				Editor(){

				}
				virtual wxString GetName() const;
				virtual wxPGWindowList CreateControls(wxPropertyGrid* propgrid,
                                          wxPGProperty* property,
                                          const wxPoint& pos,
                                          const wxSize& size) const ;
				virtual void UpdateControl( wxPGProperty* property,
											wxWindow* ctrl ) const;
				virtual void DrawValue( wxDC& dc,
										const wxRect& rect,
										wxPGProperty* property,
										const wxString& text ) const;
				virtual bool OnEvent( wxPropertyGrid* propgrid, wxPGProperty* property,
					wxWindow* wnd_primary, wxEvent& event ) const;
				virtual bool GetValueFromControl( wxVariant& variant,
												wxPGProperty* property,
												wxWindow* ctrl ) const;
				virtual void SetControlAppearance( wxPropertyGrid* pg,
													wxPGProperty* property,
													wxWindow* ctrl,
													const wxPGCell& appearance,
													const wxPGCell& oldAppearance,
													bool unspecified ) const;
				virtual void SetValueToUnspecified( wxPGProperty* property,
													wxWindow* ctrl ) const;
				virtual void SetControlStringValue( wxPGProperty* property,
													wxWindow* ctrl,
													const wxString& txt ) const;
				virtual void SetControlIntValue( wxPGProperty* property,
													wxWindow* ctrl,
													int value ) const;
				virtual int InsertItem( wxWindow* ctrl,
										const wxString& label,
										int index ) const;
				virtual void DeleteItem( wxWindow* ctrl, int index ) const;
				virtual void OnFocus( wxPGProperty* property, wxWindow* wnd ) const;
				virtual bool CanContainCustomImage() const;

				WXJS_DECLARE_CONSTRUCTOR(wxPGEditor)
				WXJS_DECLARE_DESTRUCTOR(wxPGEditor)
				WXJS_DECLARE_GET_PROP(wxPGEditor)

				WXJS_DECLARE_STATIC_PROPERTY_MAP()
				enum
				{
						P_STOCK_SPINCTRL
					,	P_STOCK_DATETIMECTRL
				};
				WXJS_DECLARE_GET_STATIC_PROP() 
				//WXJS_DECLARE_CONSTANT_MAP()

				
				WXJS_DECLARE_PROPERTY_MAP()
				/**
				* Property Ids.
				*/
				enum
				{
						P_NAME
					,	P_CanContainCustomImage 
				};
				
				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(createControls)
				WXJS_DECLARE_METHOD(updateControl)
				WXJS_DECLARE_METHOD(drawValue)
				//WXJS_DECLARE_METHOD(onEvent)	...TODO
				WXJS_DECLARE_METHOD(getValueFromControl)
				WXJS_DECLARE_METHOD(setValueToUnspecified)
				WXJS_DECLARE_METHOD(setControlAppearance)
				WXJS_DECLARE_METHOD(setControlStringValue)
				WXJS_DECLARE_METHOD(setControlIntValue)
				WXJS_DECLARE_METHOD(insertItem)
				WXJS_DECLARE_METHOD(deleteItem)
				//WXJS_DECLARE_METHOD(onFocus)	...TODO
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_EDITOR_H_
