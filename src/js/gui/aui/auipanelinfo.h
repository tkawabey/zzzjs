
#ifndef _WX_AUI_PANEL_INFO_H
#define _WX_AUI_PANEL_INFO_H


#include <wx/aui/framemanager.h>
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
		namespace aui 
		{
			class AuiPaneInfo : public ApiWrapper<AuiPaneInfo, wxAuiPaneInfo>
			{
			public:

				WXJS_DECLARE_GET_PROP(wxAuiPaneInfo)
				WXJS_DECLARE_SET_PROP(wxAuiPaneInfo)
				WXJS_DECLARE_CONSTRUCTOR(wxAuiPaneInfo)
				WXJS_DECLARE_DESTRUCTOR(wxAuiPaneInfo)


				WXJS_DECLARE_PROPERTY_MAP()

				/**
				* Property Ids.
				*/
				enum
				{
					P_FLAG
				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(bottom)
				WXJS_DECLARE_METHOD(bottomDockable)
				WXJS_DECLARE_METHOD(caption)
				WXJS_DECLARE_METHOD(captionVisible)
				WXJS_DECLARE_METHOD(closeButton)
				WXJS_DECLARE_METHOD(defaultPane)
				WXJS_DECLARE_METHOD(destroyOnClose)
				WXJS_DECLARE_METHOD(direction)
				WXJS_DECLARE_METHOD(dock)
				WXJS_DECLARE_METHOD(dockFixed)
				WXJS_DECLARE_METHOD(dockable)
				WXJS_DECLARE_METHOD(fixed)
				WXJS_DECLARE_METHOD(float_fn)
				WXJS_DECLARE_METHOD(floatable)
				WXJS_DECLARE_METHOD(gripper)
				WXJS_DECLARE_METHOD(gripperTop)
				WXJS_DECLARE_METHOD(hasBorder)
				WXJS_DECLARE_METHOD(hasCaption)
				WXJS_DECLARE_METHOD(hasCloseButton)
				WXJS_DECLARE_METHOD(hasFlag)
				WXJS_DECLARE_METHOD(hasGripper)
				WXJS_DECLARE_METHOD(hasGripperTop)
				WXJS_DECLARE_METHOD(hasMaximizeButton)
				WXJS_DECLARE_METHOD(hasMinimizeButton)
				WXJS_DECLARE_METHOD(hasPinButton)
				WXJS_DECLARE_METHOD(hide)
				WXJS_DECLARE_METHOD(icon)
				WXJS_DECLARE_METHOD(isBottomDockable)
				WXJS_DECLARE_METHOD(isDockable)
				WXJS_DECLARE_METHOD(isDocked)
				WXJS_DECLARE_METHOD(isFixed)
				WXJS_DECLARE_METHOD(isFloatable)
				WXJS_DECLARE_METHOD(isFloating)
				WXJS_DECLARE_METHOD(isLeftDockable)
				WXJS_DECLARE_METHOD(isMovable)
				WXJS_DECLARE_METHOD(isOk)
				WXJS_DECLARE_METHOD(isResizable)
				WXJS_DECLARE_METHOD(isRightDockable)
				WXJS_DECLARE_METHOD(isShown)
				WXJS_DECLARE_METHOD(isToolbar)
				WXJS_DECLARE_METHOD(isTopDockable)
				WXJS_DECLARE_METHOD(layer)
				WXJS_DECLARE_METHOD(left)
				WXJS_DECLARE_METHOD(leftDockable)
				WXJS_DECLARE_METHOD(maximizeButton)
				WXJS_DECLARE_METHOD(minimizeButton)
				WXJS_DECLARE_METHOD(maximize)
				WXJS_DECLARE_METHOD(movable)
				WXJS_DECLARE_METHOD(name)
				WXJS_DECLARE_METHOD(paneBorder)
				WXJS_DECLARE_METHOD(pinButton)
				WXJS_DECLARE_METHOD(position)
				WXJS_DECLARE_METHOD(resizable)
				WXJS_DECLARE_METHOD(right)
				WXJS_DECLARE_METHOD(rightDockable)
				WXJS_DECLARE_METHOD(row)
				WXJS_DECLARE_METHOD(setFlag)
				WXJS_DECLARE_METHOD(show)
				WXJS_DECLARE_METHOD(toolbarPane)
				WXJS_DECLARE_METHOD(top)
				WXJS_DECLARE_METHOD(topDockable)
				WXJS_DECLARE_METHOD(window)
				WXJS_DECLARE_METHOD(bestSize)
				WXJS_DECLARE_METHOD(centre)
				WXJS_DECLARE_METHOD(center)
				WXJS_DECLARE_METHOD(centrePane)
				WXJS_DECLARE_METHOD(centerPane)
				WXJS_DECLARE_METHOD(floatingPosition)
				WXJS_DECLARE_METHOD(floatingSize)
				WXJS_DECLARE_METHOD(maxSize)
				WXJS_DECLARE_METHOD(minSize)
			};
		};
	}; // namespace gui
}; //namespace wxjs
#endif //_WX_AUI_PANEL_INFO_H
