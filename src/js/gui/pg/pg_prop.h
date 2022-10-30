
#ifndef _WX_PC_PROPERTY_H
#define _WX_PC_PROPERTY_H

#include <wx/propgrid/property.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{
			class Property : public ApiWrapper<Property, wxPGProperty>
							, public	wxPGProperty
			{
			public:
				Property() : wxPGProperty()
				{
				}
				virtual ~Property()
				{
				}
				virtual void OnSetValue();
				virtual wxVariant DoGetValue() const;
				/* TODO...
				virtual bool ValidateValue( wxVariant& value,
                                wxPGValidationInfo& validationInfo ) const;*/
				virtual bool StringToValue( wxVariant& variant,
                                const wxString& text,
                                int argFlags = 0 ) const;
				virtual bool IntToValue( wxVariant& value,
                             int number,
                             int argFlags = 0 ) const;
				virtual wxString ValueToString( wxVariant& value, int argFlags = 0 ) const;
				virtual wxSize OnMeasureImage( int item = -1 ) const;
				/* TODO...
				virtual bool OnEvent( wxPropertyGrid* propgrid,
                          wxWindow* wnd_primary,
                          wxEvent& event );*/
				virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;
				/* TODO...
				virtual const wxPGEditor* DoGetEditorClass() const;*/
				/* TODO...
				virtual wxValidator* DoGetValidator () const;*/
				/* TODO...
				virtual void OnCustomPaint( wxDC& dc,	
                                const wxRect& rect,
                                wxPGPaintData& paintdata );*/
				/* TODO...
				virtual wxPGCellRenderer* GetCellRenderer( int column ) const;*/
				virtual int GetChoiceSelection() const;
				virtual void RefreshChildren();
				virtual bool DoSetAttribute( const wxString& name, wxVariant& value );
				virtual wxVariant DoGetAttribute( const wxString& name ) const;
				/* TODO...
				virtual wxPGEditorDialogAdapter* GetEditorDialog() const;*/
				virtual void OnValidationFailure( wxVariant& pendingValue );
				virtual wxString GetValueAsString( int argFlags = 0 ) const;




				static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
		  
				WXJS_DECLARE_GET_PROP(wxPGProperty)
				WXJS_DECLARE_SET_PROP(wxPGProperty)
				WXJS_DECLARE_CONSTRUCTOR(wxPGProperty)
				WXJS_DECLARE_DESTRUCTOR(wxPGProperty)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
						P_CHOICE_SELECTION
					,	P_ENABLE
					,	P_LABEL
					,	P_BASENAME
					,	P_CHILED_COUNT
					,	P_CLIENT_DATA
					,	P_CLIENT_OBJECT
					,	P_DEFAULT_VALUE
					,	P_COMMON_VALUE
					,	P_DISPLAY_STRING
					,	P_HINT_TEXT
					,	P_HELP_STRING
					,	P_INDEX_PARENT
					,	P_LAST_VISIBLE_SUBITEM
					,	P_MAIN_PARENT
					,	P_MAX_LENGTH
					,	P_NAME
					,	P_PARENT
					,	P_VALUE_TYPE
					,	P_Y
					,	P_IS_CATEGPRY
					,	P_EXPANDED
					,	P_IS_ROOT
					,	P_IS_SUB_PROP
					,	P_IS_TEXT_EDIT_ABLE
					,	P_IS_VALUE_UNSPECIFIED
					,	P_IS_VISIBLE
					,	P_LAST
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(doGetValue)
				WXJS_DECLARE_METHOD(validateValue)
				WXJS_DECLARE_METHOD(stringToValue)
				WXJS_DECLARE_METHOD(intToValue)
				WXJS_DECLARE_METHOD(valueToString)
				WXJS_DECLARE_METHOD(setValueFromString)
				WXJS_DECLARE_METHOD(setValueFromInt)
				WXJS_DECLARE_METHOD(childChanged)
				//WXJS_DECLARE_METHOD(doGetEditorClass)	TODO...
				//WXJS_DECLARE_METHOD(doGetValidator)	TODO...
				//WXJS_DECLARE_METHOD(getCellRenderer)	TODO...
				WXJS_DECLARE_METHOD(refreshChildren)
				WXJS_DECLARE_METHOD(doSetAttribute)
				WXJS_DECLARE_METHOD(doGetAttribute)
				//WXJS_DECLARE_METHOD(getEditorDialog)	TODO...
				WXJS_DECLARE_METHOD(addChoice)
				//WXJS_DECLARE_METHOD(addChild) OLD API
				WXJS_DECLARE_METHOD(addPrivateChild)
				WXJS_DECLARE_METHOD(adaptListToValue)
				WXJS_DECLARE_METHOD(appendChild)
				WXJS_DECLARE_METHOD(areAllChildrenSpecified)
				WXJS_DECLARE_METHOD(areChildrenComponents)
				WXJS_DECLARE_METHOD(changeFlag)
				WXJS_DECLARE_METHOD(deleteChildren)
				WXJS_DECLARE_METHOD(deleteChoice)
				WXJS_DECLARE_METHOD(enableCommonValue)
				WXJS_DECLARE_METHOD(generateComposedValue)
				WXJS_DECLARE_METHOD(getAttribute)
				WXJS_DECLARE_METHOD(getAttributeAsLong)
				WXJS_DECLARE_METHOD(getAttributeAsDouble)
				WXJS_DECLARE_METHOD(getAttributes)
				//WXJS_DECLARE_METHOD(getAttributesAsList) getAttributesで事足りているので、このメソッドは実装しない。
				//WXJS_DECLARE_METHOD(getColumnEditor) // TODO...
				WXJS_DECLARE_METHOD(getCell)
				WXJS_DECLARE_METHOD(getOrCreateCell)
				WXJS_DECLARE_METHOD(getChildrenHeight)
				WXJS_DECLARE_METHOD(getChoices)
				//WXJS_DECLARE_METHOD(getEditorClass)	TODO...
				//WXJS_DECLARE_METHOD(getGrid)	TODO...
				//WXJS_DECLARE_METHOD(getGridIfDisplayed)	TODO...
				WXJS_DECLARE_METHOD(getFlagsAsString)
				WXJS_DECLARE_METHOD(getPropertyByName)
				WXJS_DECLARE_METHOD(getValue)
				WXJS_DECLARE_METHOD(getValueImage)
				WXJS_DECLARE_METHOD(getValueAsString)
				WXJS_DECLARE_METHOD(getImageOffset)
				WXJS_DECLARE_METHOD(getItemAtY)
				WXJS_DECLARE_METHOD(hasFlag)
				WXJS_DECLARE_METHOD(hasFlagsExact)
				WXJS_DECLARE_METHOD(hasVisibleChildren)
				WXJS_DECLARE_METHOD(hide)
				WXJS_DECLARE_METHOD(index)
				WXJS_DECLARE_METHOD(insertChild)
				WXJS_DECLARE_METHOD(insertChoice)
				WXJS_DECLARE_METHOD(isSomeParent)
				WXJS_DECLARE_METHOD(item)
				WXJS_DECLARE_METHOD(recreateEditor)
				WXJS_DECLARE_METHOD(refreshEditor)
				WXJS_DECLARE_METHOD(setAttribute)
				//WXJS_DECLARE_METHOD(setAttributes)	TODO...
				WXJS_DECLARE_METHOD(setAutoUnspecified)
				WXJS_DECLARE_METHOD(setBackgroundColour)
				//WXJS_DECLARE_METHOD(setEditor)	TODO...
				WXJS_DECLARE_METHOD(setCell)
				WXJS_DECLARE_METHOD(setChoices)
				WXJS_DECLARE_METHOD(setFlagsFromString)
				WXJS_DECLARE_METHOD(setFlagRecursively)
				WXJS_DECLARE_METHOD(setModifiedStatus)
				WXJS_DECLARE_METHOD(setParentalType)
				WXJS_DECLARE_METHOD(setTextColour)
				WXJS_DECLARE_METHOD(setDefaultColours)
				//WXJS_DECLARE_METHOD(setValidator )	TODO...
				WXJS_DECLARE_METHOD(setValue)
				WXJS_DECLARE_METHOD(setValueImage)
				WXJS_DECLARE_METHOD(setValueInEvent)
				WXJS_DECLARE_METHOD(SetValueToUnspecified)
				WXJS_DECLARE_METHOD(setWasModified)
				WXJS_DECLARE_METHOD(updateParentValues)
				WXJS_DECLARE_METHOD(usesAutoUnspecified )







				//WXJS_DECLARE_CONSTANT_MAP()
			};

			class MyClientData : public wxClientData
			{
			public:
				MyClientData(JSContext *cx, jsval v) : m_cx(cx), m_val(v)
				{
					if ( JSVAL_IS_GCTHING(m_val) ) {}
	//                    JS_AddRoot(m_cx, &m_val);
				}

				virtual ~MyClientData()
				{
					if ( JSVAL_IS_GCTHING(m_val) ) {}
	//                    JS_RemoveRoot(m_cx, &m_val);
				}

				jsval GetJSVal()
				{
					return m_val;
				}
				JSContext* GetContext() 
				{
					return m_cx;
				}
			private:
				JSContext *m_cx;
				jsval m_val;

			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PC_PROPERTY_H
