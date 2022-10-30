/*
 * wxJavaScript - bookctrlbase.h
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://wxjs.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id: control.h 672 2007-04-12 20:29:39Z fbraem $
 */
#ifndef _ZZZJS_GUI_CONTROL_BookCtrlBase_H
#define _ZZZJS_GUI_CONTROL_BookCtrlBase_H

#include "js/common/evtconn.h"
#include "js/common/jswrap.h"
#include <wx/bookctrl.h>



namespace zzzJs
{
    namespace gui
    {
        class BookCtrlBase : public JsWrapper<BookCtrlBase, wxBookCtrlBase>
        {
        public:

			ZZZJS_DECLARE_GET_PROP(wxBookCtrlBase)
			ZZZJS_DECLARE_SET_PROP(wxBookCtrlBase)
			ZZZJS_DECLARE_SET_STR_PROP(wxBookCtrlBase)
			ZZZJS_DECLARE_DESTRUCTOR(wxBookCtrlBase)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxBookCtrlBase)



            ZZZJS_DECLARE_PROPERTY_MAP()
            enum
            {
					P_PAGE_COUNT		// RO size_t GetPageCount()
				,	P_CURRENT_PAGE		// RO wxWindow *GetCurrentPage()
				,	P_SELECTION			// RW int Get/SetSelection()
				,	CONTROLLER_SIZE		// RO wxSize   GetControllerSize()
				,	CONTROL_SIZER		// RO wxSizer* GetControlSizer() 
				,   INTERNAL_BORDER		// RW int Get/SetInternalBorder()
				,	CONTOL_MARGIN		// RW int Get/SetControlMargin()
				,	IS_VETICAL			// RO bool IsVertical()
				,	FIT_TO_CURRENT_PAGE // RW bool Get/SetFitToCurrentPage
				
            };

            ZZZJS_DECLARE_METHOD_MAP()
			// wxWithImages  imple
			ZZZJS_DECLARE_METHOD(assignImageList)
			ZZZJS_DECLARE_METHOD(setImageList)
			ZZZJS_DECLARE_METHOD(getImageList)
			// Image list functions
			ZZZJS_DECLARE_METHOD(getPageImage)
			ZZZJS_DECLARE_METHOD(setPageImage)
			//Page text functions
			ZZZJS_DECLARE_METHOD(getPageText)
			ZZZJS_DECLARE_METHOD(setPageText)
			// Selection functions
			ZZZJS_DECLARE_METHOD(advanceSelection)
			ZZZJS_DECLARE_METHOD(changeSelection)
			ZZZJS_DECLARE_METHOD(findPage)
			// Page management functions
            ZZZJS_DECLARE_METHOD(getPage)
			ZZZJS_DECLARE_METHOD(addPage)
			ZZZJS_DECLARE_METHOD(deleteAllPages)
			ZZZJS_DECLARE_METHOD(deletePage)
			ZZZJS_DECLARE_METHOD(insertPage)
			ZZZJS_DECLARE_METHOD(removePage)


        };
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZJS_GUI_CONTROL_BookCtrlBase_H
