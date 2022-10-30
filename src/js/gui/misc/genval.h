/*
 * wxJavaScript - genval.h
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
 * $Id: genval.h 715 2007-05-18 20:38:04Z fbraem $
 */
#include "js/common/jswrap.h"
#include <wx/valgen.h>

/////////////////////////////////////////////////////////////////////////////
// Name:        genval.h
// Purpose:		GenericValidator ports wxGenericValidator to JavaScript 
// Author:      Franky Braem
// Modified by:
// Created:     29.01.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

namespace zzzJs
{
    namespace gui
    {
        class GenericValidator : public wxGenericValidator
                               , public JsWrapper<GenericValidator, 
                                                   GenericValidator>
        {
	        DECLARE_CLASS(GenericValidator)
        public:

            GenericValidator(bool val);
            GenericValidator(int val);
            GenericValidator(wxString val);
            GenericValidator(wxArrayInt val);

	        GenericValidator(const GenericValidator &copy);
	        virtual wxObject* Clone() const;
	        virtual ~GenericValidator()
	        {
	        }

	        /**
	         * Validate forwards the validation to the validate method of the JavaScript object.
	         */
	        virtual bool Validate(wxWindow *parent);
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(GenericValidator)


			ZZZJS_DECLARE_GET_PROP(GenericValidator)
			ZZZJS_DECLARE_CONSTRUCTOR(GenericValidator)

			
			// Propeties
	        enum
	        {
		        P_VALUE
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()

        private:
			bool       m_boolValue;
			int        m_intValue;
			wxString   m_stringValue;
			wxArrayInt m_arrayIntValue;
        };
    }; // namespace gui
}; // namespace wxjs
