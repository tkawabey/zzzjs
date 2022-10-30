
#ifndef _WX_PG_ARGID_H
#define _WX_PG_ARGID_H

#include <wx/propgrid/property.h>
#include <wx/propgrid/propgridiface.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace pg 
		{


			class GridInterface_ArgID
			{
			public:
				GridInterface_ArgID()
					:	v(NULL)
					,	m_flg( 0 )
				{	
				}
				~GridInterface_ArgID() {
					if( v != NULL ) {
						delete v;
					}
				}
				wxPGPropArgCls& get()
				{
					if( m_flg == 1 ) {
						v = new wxPGPropArgCls(pProp);
					} else {
						v = new wxPGPropArgCls(str);
					}
					return *v;
				}

				int	m_flg;	// 0: string , 1:pProp
				wxString		str;
				wxPGProperty*	pProp;
				wxPGPropArgCls		*v;
			};

			bool getGridInterface_ArgID(JSContext *cx, jsval v, int argIndex, GridInterface_ArgID& ret);
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_PG_ARGID_H
