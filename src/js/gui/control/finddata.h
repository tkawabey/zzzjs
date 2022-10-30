/*
 * wxJavaScript - finddata.h
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
 * $Id: finddata.h 672 2007-04-12 20:29:39Z fbraem $
 */
#ifndef _WXJSFindReplaceData_H
#define _WXJSFindReplaceData_H

#include <wx/fdrepdlg.h>

#include "js/common/apiwrap.h"
namespace zzzJs
{
  namespace gui
  {
    class FindReplaceData : public ApiWrapper<FindReplaceData, 
                                              wxFindReplaceData>
    {
    public:
			WXJS_DECLARE_GET_PROP(wxFindReplaceData)
			WXJS_DECLARE_SET_PROP(wxFindReplaceData)
			WXJS_DECLARE_CONSTRUCTOR(wxFindReplaceData)
    	
      WXJS_DECLARE_CONSTANT_MAP()

      WXJS_DECLARE_PROPERTY_MAP()
      enum
      {
        P_FINDSTRING
        , P_REPLACESTRING
        , P_FLAGS
      };
    };
  }; // namespace gui
}; // namespace wxjs

#endif //_WXJSFindReplaceData_H
