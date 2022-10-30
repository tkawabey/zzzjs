// radioboxit.cpp
#include "precompile.h"


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"


#include "js/gui/control/radiobox.h"
#include "js/gui/control/radioboxit.h"



using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/radioboxit</file>
 * <module>gui</module>
 * <class name="wxRadioBoxItem">
 *	wxRadioBoxItem is a helper class for working with items of @wxRadioBox.
 *	There's no corresponding class in wxWidgets. 
 *	See wxRadioBox @wxRadioBox#item property.
 * </class>
 */
WXJS_INIT_CLASS(RadioBoxItem, "RadioBoxItem", 0)

/***
 * <properties>
 *	<property name="enable" type="Boolean">
 *   Enables/Disables the button.
 *  </property>
 *	<property name="selected" type="Boolean">
 *   Returns true when the item is selected or sets the selection
 *  </property>
 *	<property name="show" type="Boolean">
 *   Hides or shows the item.
 *  </property>
 *	<property name="string" type=WXJS_TYPE_STRING>
 *	 Get/Set the label of the button.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(RadioBoxItem)
	WXJS_PROPERTY(P_ENABLE, "enable")
	WXJS_PROPERTY(P_STRING, "string")
	WXJS_PROPERTY(P_SELECTED, "selected")
	WXJS_PROPERTY(P_SHOW, "show")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(Index, RadioBoxItem)
	JSObject *parent = JS_GetParent(/*cx,*/ obj);
	wxASSERT_MSG(parent != NULL, wxT("No parent found for RadioBoxItem"));

    wxRadioBox *radiobox = RadioBox::GetPrivate(cx, parent);
	if ( radiobox == NULL )
		return false;

	// When id is greater then 0, then we have an array index.
	if ( id >= 0 )
	{
		if ( id < radiobox->GetCount() )
		{
			// Set the item index and don't forget to return ourselves.
			p->SetIndex(id);
			vp.set( OBJECT_TO_JSVAL(obj) );
		}
	}
	else
	{
		// A negative index means a defined property.
        int idx = p->GetIndex();
		if ( idx < radiobox->GetCount() ) // To be sure
		{
			switch (id) 
			{
			case P_STRING:
                ToJSVal(cx, vp, radiobox->wxControl::GetLabel());
				break;
			case P_SELECTED:
				ToJSVal(cx, vp, radiobox->GetSelection() == idx);
				break;
			}
		}
	}
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(Index, RadioBoxItem)
	JSObject *parent = JS_GetParent(/*cx,*/ obj);
	wxASSERT_MSG(parent != NULL, wxT("No parent found for RadioBoxItem"));

    wxRadioBox *radiobox = RadioBox::GetPrivate(cx, parent);
	if ( radiobox == NULL )
		return false;

    int idx = p->GetIndex();
	if ( idx < radiobox->GetCount() ) // To be sure
	{
		switch (id) 
		{
		case P_STRING:
			{
				wxString str;
				FromJS(cx, vp, str);
				radiobox->SetString(idx, str);
				break;
			}
		case P_SELECTED:
			{
				bool value;
				if (    FromJS(cx, vp, value) 
					 && value )
					radiobox->SetSelection(idx);
				break;
			}
		case P_ENABLE:
			{
				bool value;
				if ( FromJS(cx, vp, value) )
					radiobox->Enable(idx, value);
				break;
			}
		case P_SHOW:
			{
				bool value;
				if ( FromJS(cx, vp, value) )
					radiobox->Show(idx, value);
				break;
			}
		}
	}
	return true;
WXJS_END_SET_PROP
