/*
 * wxJavaScript - bmpbtn.cpp
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
 * $Id: bmpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
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
#include "js/gui/errors.h"
#include "js/gui/pg/pg_validation_info.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	ValidationInfo
//--------------------------------------------------------
WXJS_INIT_CLASS(ValidationInfo, "ValidationInfo", 1)
	
// コンスタント
WXJS_BEGIN_CONSTANT_MAP(ValidationInfo)
    WXJS_CONSTANT(wxPG_VFB_, STAY_IN_PROPERTY)
    WXJS_CONSTANT(wxPG_VFB_, BEEP)
    WXJS_CONSTANT(wxPG_VFB_, MARK_CELL)
    WXJS_CONSTANT(wxPG_VFB_, SHOW_MESSAGE)
    WXJS_CONSTANT(wxPG_VFB_, SHOW_MESSAGEBOX)
    WXJS_CONSTANT(wxPG_VFB_, SHOW_MESSAGE_ON_STATUSBAR)
    WXJS_CONSTANT(wxPG_VFB_, DEFAULT)
    WXJS_CONSTANT(wxPG_VFB_, UNDEFINED)
WXJS_END_CONSTANT_MAP()


// プロパティー
WXJS_BEGIN_PROPERTY_MAP(ValidationInfo)
  WXJS_PROPERTY(P_FailureBehavior, "failureBehavior")
  WXJS_PROPERTY(P_FailureMessage,  "failureMessage")
  WXJS_READONLY_PROPERTY(P_Value,  "value")
WXJS_END_PROPERTY_MAP()

// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPGValidationInfo, ValidationInfo)
	switch (id) 
	{
	case P_FailureBehavior:
		ToJSVal(cx, vp, (int)p->GetFailureBehavior ());
		break;
	case P_FailureMessage:
		ToJSVal(cx, vp, p->GetFailureMessage());
		break;
	case P_Value:
		{			
			JS::Value ret = ToJS(cx, p->GetValue());
			vp.setObjectOrNull( ret.toObjectOrNull() );
		}
		break;
	}
	return true;
WXJS_END_GET_PROP

// プロパティー set の実装
WXJS_BEGIN_SET_PROP(wxPGValidationInfo, ValidationInfo)
	switch (id) 
	{
	case P_FailureBehavior:
		{
			int val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetFailureBehavior( (wxPGVFBFlags)val );
		}
		break;
	case P_FailureMessage:
		{
			wxString  val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetFailureMessage ( val );
		}
		break;
	}
	return true;
WXJS_END_SET_PROP



// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPGValidationInfo, ValidationInfo)
	return  new wxPGValidationInfo();
WXJS_END_CONSTRUCTOR
	
	
