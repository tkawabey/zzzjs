/*
 * wxJavaScript - fontlist.cpp
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
 * $Id: fontlist.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// fontlist.cpp
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
#include "js/common/jsutil.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/fontlist.h"

using namespace zzzJs;
using namespace zzzJs::gui;

#define PROP_NM_family				"family"
#define PROP_NM_style				"style"
#define PROP_NM_weight				"weight"
#define PROP_NM_underline			"underline"
#define PROP_NM_facename			"facename"
#define PROP_NM_encoding			"encoding"
/***
 * <file>misc/fontlist</file>
 * <module>gui</module>
 * <class name="wxFontList">
 *  A font list is a list containing all fonts which have been created. 
 *  There is only one instance of this class: wxTheFontList. Use this object 
 *  to search for a previously created font of the desired type and create it 
 *  if not already found. In some windowing systems, the font may be a scarce resource, 
 *  so it is best to reuse old resources if possible. 
 *  When an application finishes, all fonts will be deleted and their resources freed, 
 *  eliminating the possibility of 'memory leaks'.
 *  See @wxFont, @wxFontEncoding and @wxFontEnumerator
 * </class>
 */
ZZZJS_INIT_CLASS(FontList, "FontList", 0)


ZZZJS_BEGIN_DESTRUCTOR(wxFontList, FontList)
{
}
ZZZJS_END_DESTRUCTOR


ZZZJS_BEGIN_METHOD_MAP(FontList)
  ZZZJS_METHOD("findOrCreateFont", findOrCreate, 7)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="findOrCreateFont">
 *  <function returns="@wxFont">
 *   <arg name="PointSize" type=WXJS_TYPE_NUMBER />
 *   <arg name="Family" type=WXJS_TYPE_NUMBER />
 *   <arg name="Style" type=WXJS_TYPE_NUMBER />
 *   <arg name="Weight" type=WXJS_TYPE_NUMBER />
 *   <arg name="Underline" type="Boolean" default="false" />
 *   <arg name="FaceName" type=WXJS_TYPE_STRING default="" />
 *   <arg name="Encoding" type="@wxFontEncoding" default="wxFontEncoding.DEFAULT" /> 
 *  </function>
 *  <desc>
 *   Finds a font of the given specification, or creates one and adds it to the list.
 *   The following code shows an example:
 *   <code class="whjs">
 *    var font = wxTheFontList.findOrCreateFont(10, wxFont.DEFAULT, wxFont.NORMAL, wxFont.NORMAL);
 *   </code>
 *  </desc>
 * </method>
 */
//JSBool FontList::findOrCreate(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(FontList, findOrCreate )
{
	int argIndex = 0;
	int point;
	int family;
	int style;
	int weight;
	bool underline = false;
	JSString *faceName = NULL;
	int encoding = wxFONTENCODING_DEFAULT;
	
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	/*
	wxFont* wxFontList::FindOrCreateFont	(	int 	point_size,
		wxFontFamily 	family,
		wxFontStyle 	style,
		wxFontWeight 	weight,
		bool 	underline = false,
		const wxString & 	facename = wxEmptyString,
		wxFontEncoding 	encoding = wxFONTENCODING_DEFAULT 
	)		
		Finds a font of the given specification, or creates one and adds it to the list.

		See the wxFont constructor for details of the arguments.
	*/

	if ( JS_ConvertArguments(cx, argc, vp, "iiii/bSi", &point, &family, &style,
							 &weight, &underline, &faceName, &encoding) == JS_TRUE )
	{
		wxString face;
		if ( faceName == NULL )
		{
			face = wxEmptyString;
		}
		else
		{
			face =  (wxChar *) JS_GetStringCharsZ( cx, faceName );
//			face = (wxChar *) JS_GetStringChars(faceName);
		}
        *vp = Font::CreateObject(cx, wxTheFontList->FindOrCreateFont(point, family, style,
													  weight, underline, face,
                                                      (wxFontEncoding) encoding));
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Object�̏ꍇ
		/*
		{
			  family:Number
			, style:Number
			, weight:Number
			, underline:Boolean[option. default=false]
			, facename:Palette[option. default=""]
			, encoding:Number[option. default=FONTENCODING.DEFAULT]
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			wxString strfacename = wxEmptyString;
			// family
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(family, pObj, PROP_NM_family, WXJS_TYPE_NUMBER)
			// style
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(style, pObj, PROP_NM_style, WXJS_TYPE_NUMBER)
			// weight
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(weight, pObj, PROP_NM_weight, WXJS_TYPE_NUMBER)
			// underline
			ZZZJS_PROP_FROMJS_IF_EXIST(weight, pObj, PROP_NM_underline, WXJS_TYPE_BOOLEAN)
			// facename
			ZZZJS_PROP_FROMJS_IF_EXIST(strfacename, pObj, PROP_NM_facename, WXJS_TYPE_STRING)
			// encoding
			ZZZJS_PROP_FROMJS_IF_EXIST(encoding, pObj, PROP_NM_encoding, WXJS_TYPE_NUMBER)


			
			*vp = Font::CreateObject(cx, wxTheFontList->FindOrCreateFont(point, family, style,
														  weight, underline, strfacename,
														  (wxFontEncoding) encoding));
			return JS_TRUE;
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD
