/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_SVX_SOURCE_SIDEBAR_AREA_AREATRANSPARENCYGRADIENTCONTROL_HXX
#define INCLUDED_SVX_SOURCE_SIDEBAR_AREA_AREATRANSPARENCYGRADIENTCONTROL_HXX

#include "svx/sidebar/PopupControl.hxx"

#include <vcl/fixed.hxx>
#include <vcl/field.hxx>
#include <vcl/toolbox.hxx>
#include <svx/xenum.hxx>
#include <com/sun/star/awt/GradientStyle.hpp>

class XFillFloatTransparenceItem;
class SfxBindings;

namespace svx { namespace sidebar {

class AreaPropertyPanel;

class AreaTransparencyGradientControl : public PopupControl
{
public:
    AreaTransparencyGradientControl (
        vcl::Window* pParent,
        AreaPropertyPanel& rPanel);
    virtual ~AreaTransparencyGradientControl();
    virtual void dispose() SAL_OVERRIDE;

    void Rearrange(XFillFloatTransparenceItem* pGradientItem);
    void InitStatus(XFillFloatTransparenceItem* pGradientItem);
    void ExecuteValueModify( sal_uInt8 nStartCol, sal_uInt8 nEndCol );
    void SetControlState_Impl(css::awt::GradientStyle eXGS);

private:
    VclPtr<FixedText>           maFtTrgrCenterX;
    VclPtr<MetricField>         maMtrTrgrCenterX;
    VclPtr<FixedText>           maFtTrgrCenterY;
    VclPtr<MetricField>         maMtrTrgrCenterY;
    VclPtr<FixedText>           maFtTrgrAngle;
    VclPtr<MetricField>         maMtrTrgrAngle;
    VclPtr<ToolBox>             maBtnLeft45;
    VclPtr<ToolBox>             maBtnRight45;
    VclPtr<FixedText>           maFtTrgrStartValue;
    VclPtr<MetricField>         maMtrTrgrStartValue;
    VclPtr<FixedText>           maFtTrgrEndValue;
    VclPtr<MetricField>         maMtrTrgrEndValue;
    VclPtr<FixedText>           maFtTrgrBorder;
    VclPtr<MetricField>         maMtrTrgrBorder;
    Image               maRotLeft;
    Image               maRotRight;

    AreaPropertyPanel& mrAreaPropertyPanel;
    SfxBindings*        mpBindings;
    DECL_LINK( ModifiedTrgrHdl_Impl, void* );
    DECL_LINK_TYPED( Left_Click45_Impl, ToolBox*, void );
    DECL_LINK_TYPED( Right_Click45_Impl, ToolBox*, void );
};


} } // end of namespace svx::sidebar

#endif // INCLUDED_SVX_SOURCE_SIDEBAR_AREA_AREATRANSPARENCYGRADIENTCONTROL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
