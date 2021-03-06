/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#ifndef INCLUDED_SW_SOURCE_UIBASE_SIDEBAR_STYLEPRESETSPANEL_HXX
#define INCLUDED_SW_SOURCE_UIBASE_SIDEBAR_STYLEPRESETSPANEL_HXX

#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/document/XUndoManager.hpp>

#include <svx/sidebar/Popup.hxx>
#include <svx/sidebar/PanelLayout.hxx>

#include <sfx2/sidebar/ControllerItem.hxx>

#include <svx/pageitem.hxx>
#include <svx/rulritem.hxx>
#include <editeng/sizeitem.hxx>

#include <vcl/ctrl.hxx>
#include <vcl/fixed.hxx>
#include <vcl/button.hxx>
#include <vcl/toolbox.hxx>
#include <vcl/lstbox.hxx>
#include <vcl/field.hxx>
#include <svl/intitem.hxx>
#include <svl/lstner.hxx>

#include <svx/fntctrl.hxx>

#include "docstyle.hxx"

namespace sw { namespace sidebar {

class StylePresetsPanel : public PanelLayout,
                       public sfx2::sidebar::ControllerItem::ItemUpdateReceiverInterface
{
    friend class VclPtr<StylePresetsPanel>;
public:
    static VclPtr<vcl::Window> Create(vcl::Window* pParent,
                                  const css::uno::Reference<css::frame::XFrame>& rxFrame,
                                  SfxBindings* pBindings);

    virtual void NotifyItemUpdate(const sal_uInt16 nSId,
                                  const SfxItemState eState,
                                  const SfxPoolItem* pState,
                                  const bool bIsEnabled) SAL_OVERRIDE;

    SfxBindings* GetBindings() const
    {
        return mpBindings;
    }

private:
    struct TemplateEntry
    {
        TemplateEntry(OUString& rName, OUString& rURL)
            : maName(rName)
            , maURL(rURL)
        {}

        OUString maName;
        OUString maURL;
    };

    StylePresetsPanel(vcl::Window* pParent,
                   const css::uno::Reference<css::frame::XFrame>& rxFrame,
                   SfxBindings* pBindings);

    virtual ~StylePresetsPanel();
    virtual void dispose() SAL_OVERRIDE;

    SfxBindings* mpBindings;

    VclPtr<ListBox> mpListBox;

    std::vector<std::unique_ptr<TemplateEntry>> maTemplateEntries;

    DECL_LINK(DoubleClickHdl, void*);
};

}} // end of namespace sw::sidebar

#endif // INCLUDED_SW_SOURCE_UIBASE_SIDEBAR_STYLEPRESETSPANEL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
